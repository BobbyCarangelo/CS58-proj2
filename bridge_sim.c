/**
 * @file bridge_sim.c
 * @author Bobby Carangelo
 * @brief Contains implementations of bridge_sim.h. Helper functions to ledyard bridge simulation. 
 *        Coordinates threads that each represent cars, and does not allow unsafe passage over the bridge.  
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "bridge_sim.h"

void *car_thread(void *argp)
{
    printf("Simulating new vehicle\n");
    car_args_t *car_args = (car_args_t *) argp;

    int rc = OneVehicle(car_args);

    free(car_args);
    
    return NULL;
}

int OneVehicle(car_args_t *car_args)
{
    print_bridge(car_args->sd);
    return 0;
}

shared_data_t *shared_data_init(void)
{
    shared_data_t *sd = (shared_data_t *) malloc(sizeof(shared_data_t));

    sd->direction = TO_HANOVER;
    sd->total = 0;
    /*TO DO: INITIALIZE LOCK AND 1+ CONDITIONAL VARIABLES*/

    return sd;
}

void sim_close(shared_data_t *sd)
{
    /*TO DO: Close lock + conditional variables*/

    free(sd);
}

void print_bridge(shared_data_t *sd)
{
    printf("\n********* Ledyard Bridge *********\n\n");
    printf("    # Cars on bridge: %d\n", sd->total);

    if (sd->direction == TO_HANOVER)
    {
        printf("    Heading towards: HANOVER\n\n");
    }
    else
    {
        printf("    Heading towards: NORWICH\n\n");
    }

    printf("Queue for going TO_HANOVER:\n");
    print_queue();
    printf("Queue for going TO_NORWICH:\n");
    print_queue();

    printf("\n**********************************\n\n");
}

void print_queue(void)
{
    printf("queue ???? \n");
}