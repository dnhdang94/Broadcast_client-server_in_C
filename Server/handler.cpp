/*
 * handler.cpp
 *
 *  Created on: May 27, 2016
 *      Author: root
 */
#include "handler.h"
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>


void *connection_handler(void *socket_desc)
{
	printf("New connection\n");
	/* Get the socket descriptor */
	int 	sock_desc = *(int *)socket_desc;
	int		bytes_read, bytes_written;
	char	client_message[MAX_BUFFER];
	/* Send hello message to new client */
	const char *message = "Hello! Welcome to my server!\n";
	bytes_written = write(sock_desc, message, strlen(message));
	/* Receive message from client */
	while ((bytes_read = recv(sock_desc, client_message, MAX_BUFFER, 0)) > 0) {
		/* End of string marker */
		client_message[bytes_read] = '\0';
		/* Send the message back to client */
		if ((bytes_written = write(sock_desc, client_message, strlen(client_message))) > 0) {
			printf("Send data back to client\n");
		}
		/* Clear the buffer */
		memset(client_message, 0, MAX_BUFFER);
	}
	if (bytes_read == 0) {
		/* Client disconnected */
	} else if (bytes_read < 0) {
		/* Recv failed */
	}
	/* Stop the thread */
	return 0;
}
