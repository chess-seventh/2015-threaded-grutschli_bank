/**
 * @file tickets.c
 *
 * Functions relative to tickets structure and actions.
 *
 *
 * @author Francesco Piva
 */

#include "tickets.h"

 /**
 * Ticket creation.
 *
 * @return ticket_t : the created ticket.
 */
ticket_t create_ticket() {
	ticket_t ticket ;
	ticket.number = 0;
	ticket.current = 0;
	ticket.service_time;
	sem_init (&ticket.s_countID, 0, 1);
	sem_init (&ticket.s_currentID, 0, 1);
	sem_init (&ticket.s_bank, 0, 0);
	return ticket;
}

 /**
 * Get ticket for specific point.
 *
 * @param ticket structure.
 * @return ticket number.
 */
unsigned int get_ticket(ticket_t *ticket) {
	int cnt;
	sem_wait(&(ticket->s_countID));
	cnt = ticket->number++;
	sem_post(&(ticket->s_countID));
	return cnt;
}

 /**
 * Set current ticket.
 *
 * @param ticket structure.
 * @return ticket number.
 */
unsigned int set_current(ticket_t *ticket) {
	int curr;
	sem_wait(&(ticket->s_currentID));
	curr = ticket->current++;
	sem_post(&(ticket->s_currentID));
	return curr;
}

 /**
 * Get current ticket.
 *
 * @param ticket structure.
 * @return ticket number.
 */
unsigned int get_current(ticket_t *ticket) {
	int curr;
	sem_wait(&(ticket->s_countID));
	curr = ticket->current;
	sem_post(&(ticket->s_countID));
	return curr;
}