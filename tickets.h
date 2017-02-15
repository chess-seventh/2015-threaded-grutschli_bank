/**
 * @file tickets.h
 *
 * Delcaration of functions relative to tickets structure and actions.
 *
 *
 * @author Francesco Piva
 */

#ifndef TICKETS_H
#define TICKETS_H

#include <semaphore.h>
#include <stdio.h>

/**
 * ticket information data.
 *
 */
typedef struct {
	/// ticket number
	unsigned int number;

	/// current serving ticket number
	unsigned int current;

	/// time of service from the banker
	double service_time;

	/// semaphore that shows if the ticket has been taken or not...
	sem_t s_countID;

	/// semaphore if the current ID is free (in bank or not)
	sem_t s_currentID;

	/// semaphore that defines if the banker is free or not
	sem_t s_bank;

	/// number of population
	int pop;
} ticket_t;

 /**
 * Ticket creation.
 *
 * @return ticket_t : the created ticket.
 */
ticket_t create_ticket();

 /**
 * Get ticket for specific point.
 *
 * @param ticket structure.
 * @return ticket number.
 */
unsigned int get_ticket(ticket_t *ticket);

 /**
 * Set current ticket.
 *
 * @param ticket structure.
 * @return ticket number.
 */
unsigned int set_current(ticket_t *ticket);

 /**
 * Get current ticket.
 *
 * @param ticket structure.
 * @return ticket number.
 */
unsigned int get_current(ticket_t *ticket);

 /**
 * Get next standby tickets in the queue.
 *
 * @param ticket structure.
 * @return ticket number.
 */
unsigned int get_standby(ticket_t *ticket);

#endif //TICKETS_H