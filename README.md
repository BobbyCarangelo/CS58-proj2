## CS58 Project 2 - Ledyard Bridge Simulation
Bobby Carangelo

### Overview

This program simulates safe travel across Ledyard Bridge while it is under construction. The bridge only allows one-way traffic and only allows up to MAX_CARS on the bridge at a time (defined in bridge_sim.h). Cars can be added towards Hanover and Norwich. The main program is contained in "main.c" and helpers are contained in bridge_sim.h and bridge_sim.c. This simulation displays thread safety in a mutli-threaded program (more details below).

### How to run

Compile the program by typing "make" into a terminal window in this directory. Run the program by typing "main [mode]". The two valid modes are:
"k" to input from the keyboard, and "f" to input from a file. If you choose to input from the keyboard, you will first be prompted for the total amount of cars you would like to use in the simulation. Then you will be prompted for input to add cars to the simulation. Type "h" to add a car going to Hanover and type "n" to add a car going to Norwich. Type "o" to view all options. If you choose to input from a file, the file input must be contained in the file "sim_input" and must be structured as follows:  

n (number of cars to be used in simulation)
h  
n  
  
.  
.  
.  
  
s 3    
s 1   
h  
empty line  

See the current sim_input or the test files for examples. Other options beside "h" and "n" are "s 1" and "s 3" to delay adding a car for 1 or 3 seconds.

### Concurrency and Synchronization

Each car is represented by its own thread. The threads synchronize themselves with a single, heap allocated instance of a shared data structure called shared_data_t (defined in bridge_sim.h). When a car wants to get on the bridge it goes through the following steps:  


### To do: 
  -do grad level stuff  
  -write test file scenarios  
  -comments
  -finish readme.md and testing.md