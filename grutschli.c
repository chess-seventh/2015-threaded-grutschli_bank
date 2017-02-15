/**
 * @file grutschli.c
 *
 * Main program.
 *
 * @author Francesco Piva
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "clients.h"
#include "bank.h"
#include "tickets.h"

/**
 * Print program usage.
 *
 */
void usage() {
  printf("usage: grutschli [--population OR --pop NUMBER] [--proba NUMBER] [--time NUMBER]\n");
  printf("\n");
  printf("  options:\n");
  printf("  -------\n");
  printf("\n");
  printf("    --population OR --pop NUMBER: put the number of inhabitants in village:\n");
  printf("\n");
  printf("    --proba N: probability in decimals that the client goes out\n");
  printf("          interval of usage : [0 < NUMBER.NUMBER < 1] \n");
  printf("\n");
  printf("    --time N: banker time of service\n");
  printf("\n");
  printf("  author:\n");
  printf("\n");
  printf("    Francesco Piva\n");
  printf("\n");
}


/**
 * @file grutschli.c
 *
 * Program entry-point.
 *
 * - Parse command-line argument
 * - Display program usage
 * - Perform program's main logic
 *
 */
int main (int argc, char **argv) {

	int pop = 0;
  	double proba =0.0;
  	int time = 0;

  	// parsing
  	if(argc <= 6 || argc >= 8) {
  			usage();
  			exit(EXIT_FAILURE);
  		}

  		int i;
      	for (i=1 ; i < argc ; i++) {
      		if (strcmp(argv[i], "--population") == 0 || strcmp(argv[i], "--pop") == 0 ) {
      			if( i+1 >= argc ) {
      				usage();
      				return 1;
      			}
      			pop = atoi(argv[i+1]);
      		}
      		if (strcmp(argv[i], "--proba") == 0) {
      			if(i+1 >= argc ) {
      				usage();
      				return 1;
      			}
      		proba = atof(argv[i+1]);
      		}
      		if (strcmp(argv[i], "--time") == 0) {
      			if(i+1 >= argc ) {
      				usage();
      				return 1;
      			}
      			time = atoi(argv[i+1]);
      		}
      	}


	pthread_t * customers;
	pthread_t * banker;
	info_t *info;

	info = malloc(sizeof(info_t) * pop);


	ticket_t tickets = create_ticket();
	tickets.service_time = time;
	tickets.pop = pop;

	customers = create_customers(pop, &tickets, proba, info);
	banker = create_banks(&tickets, info);

	for (int i = 0; i < pop; i++) {
		if (pthread_join(customers[i] , NULL) != 0) {
			perror("Thread join error");
			exit(EXIT_FAILURE);
		}
	}
	if (pthread_join(*banker , NULL) != 0) {
		perror("Thread join error");
		exit(EXIT_FAILURE);
	}

	free(customers);
	free(banker);

	return EXIT_SUCCESS;
}