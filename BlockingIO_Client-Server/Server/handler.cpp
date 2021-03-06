/*
 * handler.cpp
 *
 *  Created on: May 27, 2016
 *      Author: root
 */
#include "handler.h"
#include "macros.h"
#include "shared_data.h"
#include "server.h"
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdio.h>


void *connection_handler(void *socket_desc)
{
	pthread_mutex_lock(&lock);
	INCREASE_VALUE_BY_ONE(current_number_connections);
	client_socks[current_number_connections - 1] = *(int *)socket_desc;
	pthread_mutex_unlock(&lock);
	/* Get the socket descriptor */
	int 	_sock_desc = *(int *)socket_desc;
	int		bytes_read, bytes_written;
	char	client_message[MAX_BUFFER];
	/* Send hello message to new client */
	const char *message = "Hello! Welcome to my server!\n";
	bytes_written = send(_sock_desc, message, strlen(message), 0);
	/* Receive message from client */
	while ((bytes_read = recv(_sock_desc, client_message, MAX_BUFFER, 0)) > 0) {
		/* End of string marker */
		client_message[bytes_read] = '\0';
		/* Send the message back to client */
		if ((bytes_written = send(_sock_desc, client_message, strlen(client_message), 0)) > 0) {
			printf("Send data back to client_sock_desc %d successfully\n", _sock_desc);
		}
		/* Clear the buffer */
		memset(client_message, 0, MAX_BUFFER);
	}
	if (bytes_read == 0) {
		/* Client disconnected */
		printf("Client disconnected!\n");
	} else if (bytes_read < 0) {
		/* Recv failed */
	}
	close(_sock_desc);
	/* Stop the thread */
	return 0;
}
