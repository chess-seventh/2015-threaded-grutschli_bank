/**
 * @file clients.h
 *
 * Delcaration of functions relative to clients structure and actions.
 *
 *
 * @author Francesco Piva
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "tickets.h"
#include "bank.h"



/**
 * client information data.
 *
 */
typedef struct {
	/// Probability users' input.
	double proba;

	/// Structure of tickets.
	ticket_t *ticket;

	/// Structure of information in the bank.
	info_t *info;
} client_t;

/**
 * Client task.
 *
 * @param *argv the clients job what they do in or out of bank
 *
 * @return void
 */
void *customer(void *argv);

/**
 * Function that calculates the probability that the client stays in bank.
 *
 * @return proba double  ] 0 < x < 1 [
 *
 */
double randomize_stay();

/**
 * Function that calculates the time of the activity outside the bank
 *
 * @return double which is the time.
 *
 */
double activity();

/**
 * Client creation thread.
 *
 *
 * @param pop population number 
 * @param ticket tickets structure
 * @param proba probability of clients leaving
 * @param info structure of client in bank information
 *
 */
pthread_t *create_customers(int pop, ticket_t *tickets, double proba, info_t *info);

/**
 * Function that calculates the time of the activity outside the bank
 *
 * @param client client structure.
 * @param ticket client structure.
 * @param info of information related to clients = info_t.
 * @param proba probability of client leaving.
 * @return client structure filled out with values which is the time.
 *
 */
void client_fill(client_t *client, ticket_t *ticket, info_t *info, double proba);

#endif // CLIENT_H