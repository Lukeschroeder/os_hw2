#include "my_pthread.h"

/* Scheduler State */
 // Fill in Here //
typedef enum schedularState{
  ON,//running
  OFF//not running
}state;
state sched=OFF;


/* Scheduler Function
 * Pick the next runnable thread and swap contexts to start executing
 */
void schedule(int signum){

  // Implement Here
  /*while(threadlist!=NULL){
    //iterate through list
  }
  */
}

/* Create a new TCB for a new thread execution context and add it to the queue
 * of runnable threads. If this is the first time a thread is created, also
 * create a TCB for the main thread as well as initalize any scheduler state.
 */
void my_pthread_create(my_pthread_t *thread, void*(*function)(void*), void *arg){

  // Implement Here
  //
  //init scheduler
  if(sched=OFF){
    sched=ON;
    //insert settimer code with TIME_QUANTUM_MS for time interval
    //set timer interrupt signal to schedule(int signum)
      //this means in the schedule method just check the signum for whatever number is timer interrupt,
      //if an error besides timer interrupt occurs then I will handle it and exit()
    //initialize head of list
  }
}

/* Give up the CPU and allow the next thread to run.
 */
void my_pthread_yield(){

  // Implement Here

}

/* The calling thread will not continue until the thread with tid thread
 * has finished executing.
 */
void my_pthread_join(my_pthread_t thread){
  //replace my_pthread_tcb with whatever the head of the linked list is
  // Implement Here //
  struct threadControlBlock* temp=&my_pthread_tcb;
  if(temp==NULL){
    return;
  }
  if(temp->tid==thread){
    while(temp->status==RUNNABLE){}
    my_pthread_tcb=my_pthread_tcb->next;
    return;
  }
  while(temp->next!=NULL && temp->tid!=thread){
    temp=temp->next;
  }
  if(temp->next!=NULL){
    while(temp->next->status!=RUNNABLE){}
    temp->next=temp->next->next;
  }
}


/* Returns the thread id of the currently running thread
 */
my_pthread_t my_pthread_self(){

  // Implement Here //

  return my_pthread_tcb.tid; // temporary return, replace this

}

/* Thread exits, setting the state to finished and allowing the next thread
 * to run.
 */
void my_pthread_exit(){

  // Implement Here //

}
