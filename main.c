/**
 * @file main.c
 * @author Bobby Carangelo
 * @brief Main program of ledyard bridge simulation. Simulates safe passage of cars over a one lane bridge with a maximum capacity. 
 *        Each thread represents a car. Helpers are defined in bridge_sim.h.
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#include "bridge_sim.h"

#define STRING_LEN 32


// prompt the user with message, and save input at buffer
// (which should have space for at least len bytes)
int input_string(char *message, char *buffer, int len) {

  int rc = 0, fetched, lastchar;

  if (NULL == buffer)
    return -1;

  if (message)
    printf("%s: ", message);

  // get the string.  fgets takes in at most 1 character less than
  // the second parameter, in order to leave room for the terminating null.  
  // See the man page for fgets.
  fgets(buffer, len, stdin);
  
  fetched = strlen(buffer);


  // warn the user if we may have left extra chars
  if ( (fetched + 1) >= len) {
    fprintf(stderr, "warning: might have left extra chars on input\n");
    rc = -1;
  }

  // consume a trailing newline
  if (fetched) {
    lastchar = fetched - 1;
    if ('\n' == buffer[lastchar])
      buffer[lastchar] = '\0';
  }

  return rc;
}

/**
 * @brief allocates buffer
 * 
 * @return char* -- pointer to buffer created
 */
char *init_buffer(int size)
{
	char *buf;

	buf = (char *)malloc(size);

	if (NULL == buf) {
		fprintf(stderr,"malloc error\n");
		exit(-1);
	}

	return buf;
}

pthread_t start_new_car_thread(int direction, shared_data_t *sd)
{
	//free from car thread
	car_args_t *car_args = (car_args_t *) malloc(sizeof(car_args_t));
	pthread_t id;
	int rc;

	car_args->direction = direction;
	car_args->sd = sd;


	rc = pthread_create(&id, NULL, car_thread, car_args);

	if (rc != 0)
	{
		printf("error creating thread\n");
	}

	return id;
}

int main(void)
{
	printf("Starting ledyard bridge simulation!\n");

	bool done = false;
	char *buffer = init_buffer(STRING_LEN);
	int direction;

	shared_data_t *sd = shared_data_init();

	while (!done)
	{
		input_string("Add car to sim [h/n]", buffer, STRING_LEN);

		if (strcmp(buffer, "h") == 0)
		{
			printf("Adding car to hanover\n");
			direction = TO_HANOVER;
		}
		else if (strcmp(buffer, "q") == 0)
		{
			printf("Quiting sim\n");
			done = true;
			continue;
		}
		else
		{
			printf("Adding car to norwich\n");
			direction = TO_NORWICH;
		}

		pthread_t thread_id = start_new_car_thread(direction, sd);

		// pthread_join(thread_id, NULL);
	}

	sim_close(sd);
	free(buffer);
  	return 0;
}