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
    car_args_t *car_args = (car_args_t *) argp;

    int rc = OneVehicle(car_args);

    free(car_args);
    
    return NULL;
}

int OneVehicle(car_args_t *car_args)
{
    ArriveBridge(car_args);
    OnBridge(car_args);
    ExitBridge(car_args);
    return 0;
}

void ArriveBridge(car_args_t *car_args)
{
    bool done = false;
    //get lock
    int rc = pthread_mutex_lock(&car_args->sd->lock);
    if (rc)
    {
        printf("acquire lock failure\n");
        exit(-1);
    }

    //add self to correct queue
    if (car_args->direction == TO_HANOVER)
    {
        car_args->sd->to_hanover_queued++;
    }
    else
    {
        car_args->sd->to_norwich_queued++;
    }

    //while it is not safe to cross bridge, wait for a signal to check again
    while (!((car_args->sd->total_on_bridge == 0) || (car_args->sd->total_on_bridge < 3 && car_args->direction == car_args->sd->direction)))
    {
        if (car_args->direction == TO_HANOVER)
        {
            pthread_cond_wait(&car_args->sd->wait_to_hanover, &car_args->sd->lock);
        }
        else
        {
            pthread_cond_wait(&car_args->sd->wait_to_norwich, &car_args->sd->lock);
        }  
    }

    //now on bridge -> remove self from queue
    //add self to correct queue
    if (car_args->direction == TO_HANOVER)
    {
        car_args->sd->to_hanover_queued--;
    }
    else
    {
        car_args->sd->to_norwich_queued--;
    }

    //add self to bridge
    car_args->sd->total_on_bridge++;
    car_args->sd->direction = car_args->direction;

    //release lock
    rc = pthread_mutex_unlock(&car_args->sd->lock);
    if (rc)
    {
        printf("acquire lock failure\n");
        exit(-1);
    }
}

void OnBridge(car_args_t *car_args)
{
    //get lock
    int rc = pthread_mutex_lock(&car_args->sd->lock);
    if (rc)
    {
        printf("acquire lock failure\n");
        exit(-1);
    }

    //print bridge
    print_bridge(car_args->sd);

    //release lock
    rc = pthread_mutex_unlock(&car_args->sd->lock);
    if (rc)
    {
        printf("acquire lock failure\n");
        exit(-1);
    }

    //sleep
    sleep(BRIDGE_SLEEP_TIME);
}

void ExitBridge(car_args_t *car_args)
{
    //get lock
    int rc = pthread_mutex_lock(&car_args->sd->lock);
    if (rc)
    {
        printf("acquire lock failure\n");
        exit(-1);
    }

    //remove self from bridge
    car_args->sd->total_on_bridge--;

    //signal other cars potentially safe
    if (car_args->sd->total_on_bridge == 0)
    {
        //tell both queued sides
        pthread_cond_broadcast(&car_args->sd->wait_to_hanover);
        pthread_cond_broadcast(&car_args->sd->wait_to_norwich);

    }
    else if (car_args->sd->direction == TO_HANOVER)
    {
        //just tell to hanover side
        pthread_cond_broadcast(&car_args->sd->wait_to_hanover);
    }
    else
    {
        //just tell to norwhich side
        pthread_cond_broadcast(&car_args->sd->wait_to_norwich);
    }

    //release lock
    rc = pthread_mutex_unlock(&car_args->sd->lock);
    if (rc)
    {
        printf("acquire lock failure\n");
        exit(-1);
    }
}

shared_data_t *shared_data_init(void)
{
    shared_data_t *sd = (shared_data_t *) malloc(sizeof(shared_data_t));

    /*give metadata initial values*/
    sd->direction = OPEN_BRIDGE;
    sd->total_on_bridge = 0;
    sd->to_norwich_queued = 0;
    sd->to_hanover_queued = 0;

    /*initialize synchronization variables*/
    if (pthread_mutex_init(&sd->lock, NULL) != 0)
    {
        printf("Error initializing lock\n");
        return NULL;
    } 

    if (pthread_cond_init(&sd->wait_to_hanover, NULL) != 0)
    {
        printf("Error initializing conditional variable\n");
        return NULL;
    }

    if (pthread_cond_init(&sd->wait_to_norwich, NULL) != 0)
    {
        printf("Error initializing conditional variable\n");
        return NULL;
    }

    return sd;
}

void sim_close(shared_data_t *sd)
{
    /*TO DO: Close lock + conditional variables*/
    pthread_mutex_destroy(&sd->lock);
    pthread_cond_destroy(&sd->wait_to_hanover);
    pthread_cond_destroy(&sd->wait_to_norwich);

    free(sd);
}

void print_bridge(shared_data_t *sd)
{
    printf("\n********* Ledyard Bridge *********\n\n");
    printf("    # Cars on bridge: %d\n", sd->total_on_bridge);

    if (sd->direction == TO_HANOVER)
    {
        printf("    Heading towards: HANOVER\n\n");
    }
    else
    {
        printf("    Heading towards: NORWICH\n\n");
    }

    printf("    Queue cars going TO_HANOVER: %d\n", sd->to_hanover_queued);
    printf("    Queue cars going TO_NORWICH: %d\n", sd->to_norwich_queued);

    printf("\n**********************************\n\n");
}
