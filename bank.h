/**
 * @file bank.h
 *
 * Delcaration of functions relative to banker structure and actions.
 *
 *
 * @author Francesco Piva
 */


#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "tickets.h"

/**
 * Information of clients in bank.
 *
 */
typedef struct info {

	/// ticket number
	unsigned int ticket;

	/// if the customer is in the bank or not.
	bool in_bank;

	/// tu know if the client is active or not
	sem_t s_client;
} info_t;

/**
 * banker information data.
 *
 */
typedef struct banker {
	/// pointer to structure of tickets.
	ticket_t *tickets;

	/// structure that contains major information about current clients.
	info_t *client_info;

	/// ID of the client
	int client_id;
} banker_t;


/**
 * Banker task.
 *
 *
 * @param *argv = pointer on future structure.
 */
void *banker(void *argv);

/**
 * Banker creation.
 *
 *
 * @param ticket ticket_t strcuture.
 * @param info structure of information related to clients = info_t .
 * @return banker thread.
 */
pthread_t *create_banks(ticket_t *tickets, info_t *info);

 /**
 * Banker filling the info.
 *
 * -
 *
 * @param bank the structure of bankers
 * @param ticket the structure of all tickets
 * @param info the structure related to clients infos
 * @return bank structure all filled up with cool data
 */
void banker_fill(banker_t *bank, ticket_t *ticket, info_t *info);

#endif //BANK_H