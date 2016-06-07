/*
 * main.cpp
 *
 *  Created on: May 27, 2016
 *      Author: root
 */
#include "server.h"
#include <stdio.h>
#include <pthread.h>


int main(int argc, char **argv)
{
	int err;
	if ((err = server()) != 0) {
		printf("Server fails to start!\n");
		return 1;
	}
	return 0;
}
