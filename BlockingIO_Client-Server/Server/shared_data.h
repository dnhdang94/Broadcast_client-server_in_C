/*
 * data.h
 *
 *  Created on: May 28, 2016
 *      Author: root
 */

#ifndef SHARED_DATA_H_
#define SHARED_DATA_H_


#include "constants.h"
#include <pthread.h>

/* This stores the number of connections. */
extern int number_connections;

/* This stores all client socket descriptors. */
extern int client_socks[MAX_CONNECTIONS];

/* Mutex */
extern pthread_mutex_t lock;

#endif /* SHARED_DATA_H_ */
