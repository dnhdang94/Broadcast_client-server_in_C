/*
 * shared_data.cpp
 *
 *  Created on: May 28, 2016
 *      Author: root
 */


#include "shared_data.h"


/* Prepare shared data */
int number_connections = 0;
int client_socks[MAX_CONNECTIONS];
pthread_mutex_t lock;
