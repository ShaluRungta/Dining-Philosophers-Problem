/*
   THIS FILES CONTAINS ALL THE DECLARATIONS AND SHARED VARIABLES
GROUP: OSSSS
GROUP NO.:26
MEMBERS:
SAMBHAV KUMAR DASH	140101088
SARTHAK AGARWAL		140123031
SHALU RUNGTA		140123033
SHIVAM SINGLA		140123035
 */
//all the includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>
#include <time.h>

//Number of philosophers
#define NO_PHILOSOPHERS 5

//Used for the think-loop in think() as a really large number
#define TIMER_THINK 10000000
//Used for the eat-loop in eat() as a really large number
#define TIMER_EAT 300000000
//maximum number of eat counts
#define MAX_EAT 200 
//a macro to clculate the stick number of right stick
#define RIGHT(philosopherID) ((philosopherID+1)%NO_PHILOSOPHERS)
//a macro to clculate the stick number of left stick
#define LEFT(philosopherID) philosopherID
// the proportion for calculate MAX_TIME for starvation
#define PROPORTION 1.5

//a macro to clculate the philosopher id of right stick
#define RIGHTNEIGHB(philosopherID) (philosopherID+1)%NO_PHILOSOPHERS			
//a macro to clculate the philosopher id of left stick		
#define LEFTNEIGHB(philosopherID) (NO_PHILOSOPHERS+philosopherID-1)%NO_PHILOSOPHERS    // to check negative values

//definition of the states of the philosophers
typedef enum {				
	THINK = 0,
	HUNGRY = 1,
	EAT = 2
} State;

//definition of the states of the sticks
typedef enum {
	FREE = 0,
	IN_USE = 1
} Sticks;

//states of the N philosophers
State philosopher_States[NO_PHILOSOPHERS];
//states of the N sticks
Sticks stick_States[NO_PHILOSOPHERS];
//mutual exclusion with pthreads
pthread_mutex_t mutex;
//condition variables with pthreads - one for every philosopher
pthread_cond_t condition_variables[NO_PHILOSOPHERS];
//Used to save philosopherID to be passed to the philo() function during thread creation
int tmp[NO_PHILOSOPHERS]; 
// total eat count               
int total_eat;
//For keyboard input q
char keyinput;
// eat count of each philosopher
int eat_count[NO_PHILOSOPHERS];
// MAX_TIME of starvation
double MAX_TIME;
// dummy vaariables to calculate MAX_TIME
double start,end;
clock_t time_p[NO_PHILOSOPHERS];
// declaration tof all functions
// loop of philosophers i.e. think.....hungry....eat....
void *philosopher_loop(void *arg);
// think function
void think(int philosopherID);
// eat function
void eat(int philosopherID);
void pick_up(int philosopherID);
void put_down(int philosopherID);
void disp_philo_states(int philosopherID);
// get hungry time
double get_time(int i);
// function to initialize the declared variables
void initialize();
