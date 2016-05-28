/*
 * client.cpp
 *
 *  Created on: May 27, 2016
 *      Author: root
 */
#include "client.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


int failure = 0;

int client()
{
	int sock_descriptor;
	struct sockaddr_in server;
	/* Create socket */
	sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_descriptor == -1) {
		return 1;
	}
	/* Prepare struct sockaddr_in */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(12345);
	/* Connect to server */
	if (connect(sock_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0) {
		/* Fails to connect to server */
		failure = 1;
		goto exit;
	}
	char buffer[MAX_BUFFER], server_reply[MAX_BUFFER];
	int bytes_read, bytes_written;
	/* Receive hello message from server */
	if ((bytes_read = recv(sock_descriptor, server_reply, MAX_BUFFER, 0)) < 0) {
		/* Can not receive hello message from server */
		failure = 1;
		goto exit;
	}
	/* Terminate character */
	server_reply[bytes_read] = '\0';
	printf("Receive hello message form server: %s", server_reply);
	memset(server_reply, 0, MAX_BUFFER);
	while (1) {
		printf("Type your message here: ");
		gets(buffer);
		/* Send data */
		if ((bytes_written = send(sock_descriptor, buffer, strlen(buffer), 0)) < 0) {
			/* Fails to send to server */
			failure = 1;
			goto exit;
		}
		/* Receive message back from server */
		if ((bytes_read = recv(sock_descriptor, server_reply, MAX_BUFFER, 0)) < 0) {
			/* Fails to receive message from server */
			failure = 1;
			goto exit;
		}
		server_reply[bytes_read] = '\0';
		printf("Server sends back: %s\n", server_reply);
		memset(buffer, 0, MAX_BUFFER);
		memset(server_reply, 0, MAX_BUFFER);
	}
	exit:
	close(sock_descriptor);
	if (failure) {
		/* Fail */
		return -1;
	}
 	/* Success */
	return 0;
}
