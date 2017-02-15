/**
 * @file bank.c
 *
 * Functions relative to banker structure and actions.
 *
 *
 * @author Francesco Piva
 */

#include "bank.h"
#include "tickets.h"


/**
 * Banker task.
 *
 *
 * @param *argv = pointer on future structure.
 */
void *banker(void *argv) {
	int i ;
  int sizelist = 0;
  int current;
  bool indoor;
  banker_t *banker = (banker_t *) argv;
  while (true) {
    sizelist = 0;
    indoor = false;
    current = set_current(banker->tickets);
    for (i = 0;i<banker->tickets->pop;i++) {
      if(banker->client_info[i].in_bank) {
        sizelist++;
      }
      if((banker->client_info[i].ticket) == (current)) {
        indoor = banker->client_info[i].in_bank;
        banker->client_id = i;
      }
    }
    if(indoor == true) {
      printf("\n \n");
      sleep(banker->tickets->service_time);
      sem_post (&(banker->client_info[banker->client_id].s_client)) ;
      sem_wait (&(banker->tickets->s_bank));
    }
    else if(indoor == false && sizelist == 0) {
      sem_wait(&(banker->tickets->s_bank));
    }
  }
}

/**
 * Banker creation.
 *
 *
 * @param *ticket ticket_t strcuture.
 * @param *info structure of information related to clients = info_t .
 * @return banker thread.
 */
pthread_t *create_banks(ticket_t *ticket, info_t *info) {

	pthread_t *bankers;
	banker_t *bank;

	bank = malloc(sizeof(banker_t));
	bankers = malloc(sizeof (pthread_t));

	banker_fill(bank, ticket, info);

	if (pthread_create(bankers, NULL, banker, (void *) bank) != 0) {
		perror("Thread creation error");
		exit(EXIT_FAILURE);
	}

	return bankers;
}

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
void banker_fill(banker_t *bank, ticket_t *ticket, info_t *info) {
	bank->tickets = ticket;
	bank->client_info = info;
	bank->client_id = 0;
}