/**
 * @file bridge_sim.h
 * @author Bobby Carangelo
 * @brief Helper functions to ledyard bridge simulation. 
 *        Coordinates threads that each represent cars, and does not allow unsafe passage over the bridge.  
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define OPEN_BRIDGE 0
#define TO_HANOVER 1
#define TO_NORWICH 2 

#define BRIDGE_SLEEP_TIME 5

typedef struct shared_data_t
{
    /*synchronization variables*/
    pthread_mutex_t lock;
    pthread_cond_t wait_to_hanover;
    pthread_cond_t wait_to_norwich;

    /*bridge data*/
    int total_on_bridge;
    int direction;
    int to_hanover_queued;
    int to_norwich_queued;
} shared_data_t;


typedef struct car_args_t
{
	int direction;
	shared_data_t *sd;
} car_args_t;

void *car_thread(void *argp);

int OneVehicle(car_args_t *car_args);

shared_data_t *shared_data_init(void);

void sim_close(shared_data_t *sd);

void ArriveBridge(car_args_t *car_args);

void OnBridge(car_args_t *car_args);

void ExitBridge(car_args_t *car_args);

void print_bridge(shared_data_t *sd);

void print_queue(void);