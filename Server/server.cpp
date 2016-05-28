/*
 * server.cpp
 *
 *  Created on: May 27, 2016
 *      Author: root
 */
#include "server.h"
#include "handler.h"
#include "shared_data.h"
#include "constants.h"
#include "macros.h"
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


/* Init global server variables */
int current_number_connections = 0;
int failure = 0;

int server()
{
	/* Server' s variables */
	int socket_descriptor, client_sock, c;
	struct sockaddr_in server, client;
	/* Create socket */
	socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_descriptor == -1) {
		/* Can not create socket descriptor */
		return -1;
	}
	/* Prepare mutex */
	if (pthread_mutex_init(&lock, NULL) != 0) {
		/* Fails to init mutex */
		failure = 1;
		goto exit;
	}
	/* Prepare the sockaddr_in structure */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(12345);
	/* Bind */
	if (bind(socket_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0) {
		/* Can not bind */
		failure = 1;
		goto exit;
	}
	/* Listening */
	listen(socket_descriptor, MAX_CONNECTIONS);
	/* Accept incoming connections */
	c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	while ((client_sock = accept(socket_descriptor, (struct sockaddr *)&client, (socklen_t *)&c)) != -1) {
		if (pthread_create(&thread_id, NULL, connection_handler, (void *)&client_sock) < 0) {
			/* Fails to create thread */
			failure = 1;
			goto exit;
		}
	}
	if (client_sock < 0) {
		/* Accept failed */
		failure = 1;
		goto exit;
	}
	/* Destroy mutex */
	exit:
	pthread_mutex_destroy(&lock);
	close(socket_descriptor);
	if (failure) {
		/* Fail */
		return -1;
	}
	/* Success */
	return 0;
}
