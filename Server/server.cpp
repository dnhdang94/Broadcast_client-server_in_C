/*
 * server.cpp
 *
 *  Created on: May 27, 2016
 *      Author: root
 */
#include "server.h"
#include "handler.h"
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


int server()
{
	int socket_descriptor, client_sock, c;
	struct sockaddr_in server, client;
	/* Create socket */
	socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_descriptor == -1) {
		/* Can not create socket descriptor */
		return 1;
	}
	/* Prepare the sockaddr_in structure */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(12345);
	/* Bind */
	if (bind(socket_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0) {
		/* Can not bind */
		return 2;
	}
	/* Listening */
	listen(socket_descriptor, 3);
	/* Accept incoming connections */
	c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	while ((client_sock = accept(socket_descriptor, (struct sockaddr *)&client, (socklen_t *)&c)) != -1) {
		if (pthread_create(&thread_id, NULL, connection_handler, (void *)&client_sock) < 0) {
			/* Can not create thread */
			return 3;
		}
	}
	if (client_sock < 0) {
		/* Accept failed */
		return 4;
	}
	/* Success */
	return 0;
}
