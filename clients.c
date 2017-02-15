/**
 * @file clients.c
 *
 * Functions relative to client structure and actions.
 *
 *
 * @author Francesco Piva
 */

#include "clients.h"
#include "tickets.h"

/**
 * Client task.
 *
 * @param *argv the clients job what they do in or out of bank
 *
 * @return void
 */
void *customer(void *argv) {

	client_t *client  = (client_t*) argv;

	while (true) {
		client->info->in_bank = false;
		sleep(10 * (client->ticket->service_time));
		/// ACTION_IN_BANK : this is the main action if the clients ticket is missed/passed compared to current ticket.
		action_in_bank: 
		client->info->ticket = get_ticket( (client->ticket));

		if ( (client->info->ticket - (get_current((client->ticket)))) > 3 ) {
			if (randomize_stay() < client->proba) {
				sleep((client->info->ticket - (get_current((client->ticket)))) * client->ticket->service_time);  // random activity to code for random if he stay in or not put in client.h
				if (client->info->ticket < get_current( (client->ticket) ) ) {
					goto action_in_bank; /// See above
				}
			}
		}
		client->info->in_bank = true; 
		/// Here we check if his number has been taken already or not.
		if (client->info->ticket < get_current(client->ticket)) {
			client->info->ticket = get_ticket((client->ticket));
		}
		else {
		sem_post(&(client->ticket->s_bank)); /// banker semaphore post
		sem_wait(&(client->info->s_client)); /// client semaphore wait	
		}
	}
}

/**
 * Function that calculates the probability that the client stays in bank
 *
 * @return proba double  ] 0 < x < 1 [
 *
 */
double randomize_stay() {
	return ( (double) rand() / (double) RAND_MAX);
}

/**
 * Function that calculates the time of the activity outside the bank
 *
 * @return double which is the time.
 *
 */
double activity() {
	return ( (double) rand() / RAND_MAX  + 1 ) ;
}

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
pthread_t *create_customers(int pop, ticket_t *ticket, double proba, info_t *info) {

	client_t *customer_data;
	pthread_t *customers;

	customer_data = malloc (sizeof (client_t) * pop);
	customers = malloc (sizeof (pthread_t) * pop);

	for (int i = 0; i < pop; i++) {

	  client_fill(&(customer_data[i]), ticket, &(info[i]), proba);

		if (pthread_create(&customers[i], NULL, customer, (void *) &customer_data[i]) != 0) {
			perror("Thread creation error");
			exit(EXIT_FAILURE);
		}
	}

	return customers;
}

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
void client_fill(client_t *client, ticket_t *ticket, info_t *info, double proba) {
	client->ticket = ticket;
	info->ticket = 0;
	client->proba = proba;
	info->in_bank = false;
	client->info = info;
}