{ 
    "version": "0.1.0", 
    "isShellCommand": true, 
    "taskName": "GenericBuild", 
    "showOutput": "always", 
    "command": "sh", 
    "suppressTaskName": false, 
    "args": ["-c", "clang -std=c11 -Wall -Wextra -pedantic -pthread \"${file}\" && ./a.out"] // command arguments... 
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

int next_id;
static sem_t connected_lock; //Binary semaphore
static sem_t operators;      //Connected semaphore
static int NUM_OPERATORS = 5;
static int NUM_LINES = 8;
static int connected = 0;    //Callers that are connected
void *lineBusy(void*ptr, int id);


// This function is called when the line is not busy, and for the caller to get connected to an operator
void available(int curr_id){
  
  printf("Thread [%i] is connected to an operator. Call is ringing ...\n", curr_id);
  connected++;
  sem_post(&connected_lock); // Critical section for binary semaphore ended
  sem_wait(&operators);      // Critical section for connected semaphore starts
  printf("Thread [%i]'s order is being taken by an operator...\n", curr_id);
  sleep(3);
  printf("Thread [%i]'s order is complete. Have a nice day!\n", curr_id);
  connected--;
 sem_post(&operators);      // Critical section for connected semaphore ended
 
 printf("Thread [%i]'s call has ended. \n", curr_id);
 
}

//The method that is called on execution of the thread creation
//This method checks if the line is busy or not. If the line is busy, the thread keeps trying till the line is not busy by calling lineBusy function
//If the line is not busy, available function is called to further complete the order
void *phonecall(void* ptr){
  sem_wait(&connected_lock);
  next_id = next_id + 1;  // Changing the next_id for a unique id for each caller
  int curr_id = next_id;
  printf("Thread [%i] is attempting to connect...\n", curr_id);
     
  if(connected == NUM_LINES){
        
    sem_post(&connected_lock);
    printf("All lines are currently busy. Please wait a moment...\n");
    lineBusy(ptr, curr_id);        
  }
 
  else {
    available(curr_id);
  }

  return NULL; 
}

//This function is called when the line is busy. The thread keeps trying to do the next operation till the condition is satisfied. Once the condition is satisfied,
//available function is called to do the next steps, that is, connect the caller to an operator
void *lineBusy(void*ptr, int id){
  sem_wait(&connected_lock);
  printf("Thread[%i] is attempting to connect... \n", id);

  if(connected == NUM_LINES){
    sem_post(&connected_lock);
    printf("All lines are currently busy. Please wait a moment...\n");
    sleep(5);    // This has been done to ensure that the thread does not keep printing the above line constantly
    lineBusy(ptr,id);
  }

  else{
    available(id);
  }
  return NULL;  
}

int main(int argc, char* argv[]){
  
  if(argc == 2){
    printf("Pass only 1 argument.");
    exit(EXIT_FAILURE);
  }

  int numCalls = atoi(argv[1]);

  sem_init(&connected_lock, 0, 1);
  sem_init(&operators,0,NUM_OPERATORS);

  pthread_t *calls = malloc(sizeof(pthread_t) * numCalls);
    for(int i=0 ; i < numCalls ; ++i){
        pthread_create(&calls[i], NULL, phonecall, NULL);
    }

    for(int i = 0; i < numCalls ; ++i){
        pthread_join(calls[i], NULL);
    }


 

  if(sem_destroy(&connected_lock) == -1){
    printf("Error destroying connected_lock. Error no. is %d\n", errno);
  }

  if(sem_destroy(&operators) == -1){
    printf("Error destroying operators. Error no. is %d\n", errno);
  }
  
  exit(EXIT_SUCCESS);  

}

