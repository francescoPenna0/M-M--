//******************************************************************************
//*  A simple M/M/1 queue simulation 			                                     *
//******************************************************************************
//*  Notes: 1. This program requires parameters for Inter Arrival time,        *
//** Service time as well as maximum number of customers                       *
//*----------------------------------------------------------------------------*
//*  Build: gcc -o mm1 mm1.c                                                   *
//*----------------------------------------------------------------------------*
//*  Execute: ./mm1 MAX_CUSTOMERS ARR_TIME SERV_TIME           x                *
//*----------------------------------------------------------------------------*
//*  Author: Anshuman Biswas                                                   *
//*  Email: anshuman@sce.carleton.ca                                           *
//*----------------------------------------------------------------------------*
//*  Version: 1.0                                                              *
//******************************************************************************
//----- Include files ----------------------------------------------------------
#include <stdio.h>  // Needed for printf()
#include <stdlib.h> // Needed for rand()
#include <math.h>   // Needed for log()

// #define MAX 1000000      			// Modify this to change the number of requests
// #define SIM_TIME   1.0e2        // Simulation time

// #define ARR_TIME   1.25         // Mean time between arrivals
// #define SERV_TIME  1.00         // Mean service time
#define RSEED 1234 // Modify this to change seed of the random number generator function

#define FILENAME "mm1ex" //Change the filename here

//----- Link List -------------------------------------------------------------
// This link list will store the future events
typedef struct node
{
	int callerID;
	char event;
	double time;
	struct node *next;
} node_t;

long int MAX;
double ARR_TIME, SERV_TIME;

//----- Function prototypes ----------------------------------------------------
double expntl(double x);	   // Generate exponential RV with mean x
void print_list(node_t *head); // Print the future event list
int popEvent(node_t **head);   // Remove the event at the front of the list
int popBuffer(FILE *f, node_t **head, node_t **bhead,
			  double *busyTime, double *residenceTime,
			  double *waitingTime, double currentTime);					// Remove the waiting event at the front of the buffer
void insertEvent(node_t **head, int callerID, char event, double time); // Insert an event at the appropriate time of occurence
void print_all(node_t *head, node_t *bhead);							// Print both the future event list as well as the buffer

int main(int argc, char *argv[])
{
	int i, j, line = 0, callerID = 0, localCallerID, departures = 0;

	double prevTime = 0.0, newTime = 0.0, busyTime = 0.0, serviceTime = 0.0, waitingTime = 0.0, residenceTime = 0.0;
	node_t *fel = NULL;
	node_t *head = fel;

	node_t *buffer = NULL;
	node_t *bhead = buffer;

	// Check if the command line argument is correct
	if (argc != 4) /* argc should be 4 for correct execution */
	{
		/* We print argv[0] assuming it is the program name */
		printf("usage: %s MAX_CUSTOMERS INTER_ARR_TIME SERV_TIME\n", argv[0]);
		exit(-1);
	}
	else if (atof(argv[2]) < 0)
	{
		printf("Inter arrival time must be greater than 0.\n");
		exit(-1);
	}
	else if (atof(argv[3]) < 0)
	{
		printf("Service time must be greater than 0.\n");
		exit(-1);
	}
	else
	{
		SERV_TIME = atof(argv[3]);
		ARR_TIME = atof(argv[2]);
		MAX = atoi(argv[1]);
	}
	// Open a file for reading
	FILE *f = fopen(FILENAME, "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	// Assign a seed for the random number
	srand(RSEED);

	insertEvent(&head, ++callerID, 'A', prevTime + expntl(ARR_TIME));
	// print_all(head,bhead);   // UNCOMMENT THIS TO VIEW THE FEL and the buffer
	while (1)
	{
		// Pickup the next event in the list
		switch (head->event)
		{
		case 'A':
			prevTime = head->time;
			localCallerID = head->callerID;
			popEvent(&head);
			if (!line)
			{
				// Create a departure event in the FEL
				serviceTime = expntl(SERV_TIME);
				newTime = prevTime + serviceTime;
				busyTime += serviceTime;
				residenceTime += serviceTime;
				insertEvent(&head, localCallerID, 'D', newTime);
				// Write the data to file
				fprintf(f, "%d,%lf,%lf,%lf\n", localCallerID, prevTime, 0.0, serviceTime);
				line = 1; // Make the line busy
			}
			// Add to buffer
			else
				insertEvent(&bhead, localCallerID, 'A', prevTime);

			// Stop creating new arrivals after the conditions are met
			if (callerID < MAX) // Uncomment this to make use of the number of requests
								// if(prevTime < SIM_TIME)		// Uncomment this to make use of the total simulation time
				insertEvent(&head, ++callerID, 'A', prevTime + expntl(ARR_TIME));
			// printf("Arrival Event\n");  // UNCOMMENT THIS TO VIEW THE FEL and the buffer
			// print_all(head,bhead);		// UNCOMMENT THIS TO VIEW THE FEL and the buffer
			break;
		case 'D':
			departures++;
			prevTime = head->time;
			popEvent(&head);
			if (departures == MAX) // Uncomment this to make use of the number of requests
								   // if(departures == callerID)	// Uncomment this to make use of the total simulation time
				goto Result;
			if (bhead != NULL)
				popBuffer(f, &head, &bhead, &busyTime, &residenceTime, &waitingTime, prevTime);
			else
				line = 0;
			// printf("Departure Event\n"); // UNCOMMENT THIS TO VIEW THE FEL and the buffer
			// print_all(head,bhead);		// UNCOMMENT THIS TO VIEW THE FEL and the buffer
			break;
		}
	}

Result:
	// CLose file for writing
	fclose(f);
	// Output results
	printf("**************************************STATISTICS*******************************\n");
	if (ARR_TIME < SERV_TIME)
		printf("*   UNSTABLE:\tArrival rate is greater than service rate!!\n");
	printf("*                        Results from M/M/1 simulation                        * \n");
	printf("*******************************************************************************\n");
	printf("*  INPUTS:                                     \n");
	printf("*    Total simulated time       = %3.4f sec    \n", prevTime);
	printf("*    Mean time between arrivals = %lf sec      \n", ARR_TIME);
	printf("*    Mean service time          = %lf sec      \n", SERV_TIME);
	printf("*******************************************************************************\n");
	printf("*  OUTPUTS:                                    \n");
	printf("*    Number of completions      = %u cust      \n", departures);
	printf("*    Throughput rate            = %lf cust/sec \n", departures / prevTime);
	printf("*    Busy Time                  = %lf sec      \n", busyTime);
	printf("*    Server utilization         = %lf %%       \n", 100.0 * busyTime / prevTime);
	printf("*    Mean residence time        = %lf sec      \n", residenceTime / departures);
	printf("*    Mean queueing time         = %lf sec      \n", waitingTime / departures);
	printf("*    Mean number in system      = %lf cust     \n", residenceTime / prevTime);
	printf("*    Mean number in queue       = %lf cust     \n", (residenceTime - busyTime) / prevTime);
	printf("*******************************************************************************\n");
	return 0;
}

//******************************************************************************
//*  Function: Print both the future event list as well as the buffer		   *
//*    - Input:  	1) The pointer to the head of the link list                *
//*    -  			2) The pointer to the head of the buffer				   *
//*    - Output: void                                                          *
//******************************************************************************

void print_all(node_t *head, node_t *bhead)
{
	printf("*******************************************************************************\n");
	printf("FEL-");
	print_list(head);
	printf("***************************\n");
	printf("BUFFER-");
	print_list(bhead);
	printf("*******************************************************************************\n");
}

//******************************************************************************
//*  Function to generate exponentially distributed RVs using inverse method   *
//*    - Input:  x (mean value of distribution)                                *
//*    - Output: Returns with exponential RV                                   *
//******************************************************************************
double expntl(double x)
{
	double z; // Uniform random number from 0 to 1

	// Pull a uniform RV (0 < z < 1)
	do
	{
		z = ((double)rand() / RAND_MAX);
	} while ((z == 0) || (z == 1));

	// return -log(1.0 - (double) random() / (RAND_MAX + 1)) / x;

	return (-x * log(z));
}

//******************************************************************************
//*  Function: Print the future event list                                     *
//*    - Input:  1) The pointer to the head of the link list                   *
//*    - Output: void                                                          *
//******************************************************************************
void print_list(node_t *head)
{
	node_t *current = head;
	while (current != NULL)
	{
		printf("(%d,%c,%lf)", current->callerID, current->event, current->time);
		current = current->next;
		if (current != NULL)
			printf("|");
	}
	printf("\n");
}

//******************************************************************************
//*  Function: Remove the event at the front of the list                       *
//*    - Input:  1) The pointer to the pointer of the head of the link list    *
//*    - Output: int: A bool type for whether the pop was successful or not	   *
//******************************************************************************
int popEvent(node_t **head)
{
	int retval = -1;
	node_t *next_node = NULL;

	if (*head == NULL)
	{
		return -1;
	}

	next_node = (*head)->next;
	retval = 1;
	free(*head);
	*head = next_node;
	return retval;
}

//******************************************************************************
//*  Function: Remove the waiting event at the front of the buffer             *
//*    - Input:  1) The pointer to the file to store the statistics            *
//*    - Input:  2) The pointer to the pointer of the head of the fel          *
//*    - Input:  3) The pointer to the pointer of the head of the queue        *
//*    - Input:  2) The pointer to the pointer of the head of the link list    *
//*    - Input:  2) The pointer to the pointer of the head of the link list    *
//*    - Input:  2) The pointer to the pointer of the head of the link list    *
//*    - Output: void                                                          *
//******************************************************************************
int popBuffer(FILE *f, node_t **head, node_t **bhead, double *busyTime, double *residenceTime, double *waitingTime, double currentTime)
{
	double newTime, serviceTime, wt;
	int retval = -1;
	node_t *next_node = NULL;

	if (*bhead == NULL)
	{
		return -1;
	}
	// printf("Current Time - %lf\n", currentTime);
	next_node = (*bhead)->next;
	retval = 1;
	// Insert as a departure event
	serviceTime = expntl(SERV_TIME);
	newTime = currentTime + serviceTime;
	*busyTime += serviceTime;
	wt = (currentTime - (*bhead)->time);
	wt = (wt > 0) ? wt : 0;
	*waitingTime += wt;
	*residenceTime += (serviceTime + wt);
	// Write the data to file
	fprintf(f, "%d,%lf,%lf,%lf\n", (*bhead)->callerID, (*bhead)->time, wt, (serviceTime + wt));
	insertEvent((head), (*bhead)->callerID, 'D', newTime);
	free(*bhead);
	*bhead = next_node;
	return retval;
}

//******************************************************************************
//*  Function: Insert an event at the appropriate time of occurence            *
//*    - Input:  1) The pointer to the pointer of the head of the link list    *
//*    - Input:  2) int: ID of the the caller                                  *
//*    - Input:  3) char: Symbol to signify the event                          *
//*    - Input:  4) double: The time the event will occur                      *
//*    - Output: void                                                          *
//******************************************************************************
void insertEvent(node_t **head, int callerID, char event, double time)
{
	node_t *current = *head;
	node_t *newEvent = NULL;
	if (current == NULL)
	{
		newEvent = malloc(sizeof(node_t));
		newEvent->next = NULL;
		*head = newEvent;
		newEvent->time = time;
		newEvent->callerID = callerID;
		newEvent->event = event;
	}
	else
	{
		while (current != NULL)
		{
			// This is the case when the event needs to be inserted in after the last event
			if (current->time <= time && current->next == NULL)
			{
				// Create a new memory and re-assign the pointers
				newEvent = malloc(sizeof(node_t));
				newEvent->next = current->next;
				current->next = newEvent;
				newEvent->time = time;
				newEvent->callerID = callerID;
				newEvent->event = event;
				break;
			}
			// This is the case when the event needs to be inserted before the first event
			else if (current->time > time && current == *head)
			{
				// Create a new memory and re-assign the pointers
				newEvent = malloc(sizeof(node_t));
				newEvent->next = current;
				*head = newEvent;
				newEvent->time = time;
				newEvent->callerID = callerID;
				newEvent->event = event;
				break;
			}
			// This is the case when the event needs to be inserted in between two other events
			else if (current->time < time && current->next->time >= time)
			{
				// Create a new memory and re-assign the pointers
				newEvent = malloc(sizeof(node_t));
				newEvent->next = current->next;
				current->next = newEvent;
				newEvent->time = time;
				newEvent->callerID = callerID;
				newEvent->event = event;
				break;
			}

			// Proceed to the next event
			current = current->next;
		}
	}
}