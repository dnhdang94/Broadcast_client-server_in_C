/*
 * main.cpp
 *
 *  Created on: May 27, 2016
 *      Author: root
 */
#include "client.h"
#include <stdio.h>



int main(int argc, char **argv)
{
	int err;
	if ((err = client()) != 0) {
		printf("Fails to connect to server\n");
		return 1;
	}
	return 0;
}
