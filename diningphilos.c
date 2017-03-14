/*

   DEADLOCK FREE AND STARVATION FREE SOLUTION


   MAIN C FILE WHERE THREADS ARE CREATED AND ALL FUNCTIONS ARE CALLED IN A LOOP
GROUP: OSSSS
GROUP NO.:26
MEMBERS:
SAMBHAV KUMAR DASH	140101088
SARTHAK AGARWAL		140123031
SHALU RUNGTA		140123033
SHIVAM SINGLA		140123035
 */
#include "declarations.h"


int main(void)
{
	pthread_t philosopherID[NO_PHILOSOPHERS];
	int i, error;
	initialize();
	// start threads
	for(i = 0; i < NO_PHILOSOPHERS; i++) {

		error=pthread_create(&philosopherID[i], NULL, philosopher_loop, &tmp[i]);
		tmp[i] = i;     // philosophers  ids saved to pass as variable to function philo

		if(error) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}

	// keyboard input
	while(1) {


		if(keyinput == 'q' || keyinput == 'Q') {

			printf("Exit program started\n");
			// do thread join for all philosopher threads i.e it waits for all threads to complete execution one by one
			for(i = 0; i < NO_PHILOSOPHERS; i++) {

				// signal before that to ensure its not waiting,, signal doesnot effect if there was no wait at all
				pthread_cond_signal(&condition_variables[i]);  
				printf("Waiting for Thread %d to be terminated by using pthread_join\n", i);  
				pthread_join(philosopherID[i], NULL);
			}

			printf("Destroying the threads and mutex created\n");
			for(i = 0; i < NO_PHILOSOPHERS; i++) {
				printf("Thread %d destroyed\n", i);
				pthread_cond_destroy(&condition_variables[i]);
			}
			pthread_mutex_destroy(&mutex);

			printf("Exiting...\n");
			pthread_exit(NULL);
			exit(EXIT_FAILURE);    // programm stops here
		}

	}

	return 0;
}   



//the function called by the threads
	void *
philosopher_loop(void *pID)
{

	int *philosopherID = pID;
	int running = 1;            // init

	printf("philospher %d loop started\n", *philosopherID);

	while(running ) {

		if(total_eat > MAX_EAT)       // if no of eat count is excceding max eat
		{	keyinput = 'q';    // set to quit

			running=0;    // loop stop
		}


		think(*philosopherID);


		// check if starving neighbours then donot pick iff he himself is not starving

		if((get_time(RIGHTNEIGHB(*philosopherID)) > MAX_TIME || get_time(LEFTNEIGHB(*philosopherID)) > MAX_TIME) && get_time(*philosopherID) < MAX_TIME)
			continue;							

		pick_up(*philosopherID);

		eat(*philosopherID);


		put_down(*philosopherID);


	}
	return NULL;
}



// empty loop running for thinking
	void
think(int philosopherID)
{
	int i;

	for(i = 0; i < TIMER_THINK; i++) {

	}

}

// eat func for philosophers  
	void
eat(int philosopherID)
{	

	disp_philo_states(philosopherID);	// display current states of philosophers

	int i;
	// loop for eating
	for(i = 0; i < TIMER_EAT; i++) {

	}


}



//initialization of the declared variables

void initialize()
{
	int i, error;



	for(i = 0; i < NO_PHILOSOPHERS; i++) {
		philosopher_States[i] = THINK;		//all philosophers initially thinking
		stick_States[i] = FREE;		//all sticks initially free
		error = pthread_cond_init(&condition_variables[i], NULL);
		assert(!error);					// assrert for error in initializing condition variable
		time_p[i]=0;
		eat_count[i]=0;

	}
	total_eat=0;		//total eat count
	MAX_TIME=1.0;		//maximum time of starvation
	start=0.0;		//dummy to calculate max time
	end=0.0;		//dummy to calculate max time
	pthread_mutex_init(&mutex, NULL);
}

