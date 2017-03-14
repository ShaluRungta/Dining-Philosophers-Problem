/*
   THE FILE HAVING FUNCTIONS IN THE MONITOR. ALSO A FUNCTION TO PRINT THE CURRENT STATE OF THE PHILOSOPHERS.
GROUP: OSSSS
GROUP NO.:26
MEMBERS:
SAMBHAV KUMAR DASH	140101088
SARTHAK AGARWAL		140123031
SHALU RUNGTA		140123033
SHIVAM SINGLA		140123035
 */
#include "declarations.h"

//code to pick up sticks
void pick_up(int philosopherID)
{

	//lock states
	pthread_mutex_lock(&mutex);

	if(philosopher_States[philosopherID] != HUNGRY)    // TO SAVE THE FIRST TIME HUNGRY
		time_p[philosopherID]=clock();
	// when he tries to get the sticks he's obviously hungry
	philosopher_States[philosopherID] = HUNGRY;

	//if any of the right or left stick is in use wait on the condition variable
	while(stick_States[LEFT(philosopherID)] == IN_USE || stick_States[RIGHT(philosopherID)] == IN_USE) {

		pthread_cond_wait(&condition_variables[philosopherID], &mutex);
	}

	// mark philosopher as eating and stick as in use

	stick_States[LEFT(philosopherID)] = IN_USE;
	stick_States[RIGHT(philosopherID)] = IN_USE;
	philosopher_States[philosopherID] = EAT;
	//unlock the mutex
	pthread_mutex_unlock(&mutex);
}

//code to put sticks down after eating also signals the right and left philosopher
	void
put_down(int philosopherID)
{

	// lock states
	pthread_mutex_lock(&mutex);

	// put down the sticks
	stick_States[LEFT(philosopherID)] = FREE;
	stick_States[RIGHT(philosopherID)] = FREE;

	// change the state back to thinking
	philosopher_States[philosopherID] = THINK;

	// signals the right and left philosopher
	pthread_cond_signal(&condition_variables[LEFTNEIGHB(philosopherID)]);
	pthread_cond_signal(&condition_variables[RIGHTNEIGHB(philosopherID)]);
	//unlock the mutex
	pthread_mutex_unlock(&mutex);
}



//display the current states of the philosophers
	void
disp_philo_states(int philosopherID)
{
	pthread_mutex_lock(&mutex);  
	eat_count[philosopherID]++;    // eat count of philo increaed	
	time_p[philosopherID]=0;	// hungry time reset to zero
	total_eat++;		// increment the total_eat eat count
	int i;


	if(total_eat == 0)
		start=clock();
	if(total_eat == PROPORTION * NO_PHILOSOPHERS)
		end = clock();
	if(end != 0)
		MAX_TIME = (double) (end-start)/CLOCKS_PER_SEC;

	// check for an error in the states order
	for(i = 0; i < NO_PHILOSOPHERS; i++) {
		if(philosopher_States[i] == EAT && (philosopher_States[LEFTNEIGHB(i)] == EAT || philosopher_States[RIGHTNEIGHB(i)] == EAT)) {
			printf("Something Wrong ....\n\n");
			break;
		}
	}




	printf("# EATING COUNT= %d \n",total_eat);
	// display anyway to see what might be wrong or actual states
	for(i = 0; i < NO_PHILOSOPHERS; i++) {
		if(philosopher_States[i] == THINK)
			printf(" Philosopher %d is thinking and has eaten %d times. \n",i+1, eat_count[i]);
		else if(philosopher_States[i] == EAT)
			printf(" Philosopher %d is eating and has eaten %d times. \n",i+1, eat_count[i]);
		else if(philosopher_States[i] == HUNGRY)
			printf(" Philosopher %d has been waiting for %lf and calling pick_up() and has eaten %d times. \n",i+1, get_time(i), eat_count[i]);

	}
	printf(".......\n\n");

	pthread_mutex_unlock(&mutex);
}



double get_time(int i)
{
	if(time_p[i]==0)
		return 0.0;
	else
		return ((double)(clock()-time_p[i])/CLOCKS_PER_SEC);

}




