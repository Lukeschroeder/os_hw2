#include "my_pthread.h"

/* Scheduler State */
 // Fill in Here //


/* Scheduler Function
 * Pick the next runnable thread and swap contexts to start executing
 */
void schedule(int signum){

  // Implement Here

}

/* Create a new TCB for a new thread execution context and add it to the queue
 * of runnable threads. If this is the first time a thread is created, also
 * create a TCB for the main thread as well as initalize any scheduler state.
 */
void my_pthread_create(my_pthread_t *thread, void*(*function)(void*), void *arg){

  // Implement Here
  struct threadControlBlock* temp=&my_pthread_tcb;
  if(temp==NULL){
    temp=malloc(sizeof(struct threadControlBlock));
    temp->tid=thread;
    temp->status=RUNNABLE;
    temp->next=NULL;
    my_pthread_tcb=*temp;
  }
  else{
    while(temp->next!=NULL){
      temp=temp->next;
    }
    temp->next=malloc(sizeof(struct threadControlBlock));
    temp->next->tid=thread;
    temp->next->status=RUNNABLE;
    temp->next->next=NULL;
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

  // Implement Here //
  struct threadControlBlock* temp=&my_pthread_tcb;
  while(temp!=NULL && temp->tid!=thread){
    temp=temp->next;
  }
  if(temp!=NULL){
    while(temp->status!=RUNNABLE){}
  }
}


/* Returns the thread id of the currently running thread
 */
my_pthread_t my_pthread_self(){

  // Implement Here //

  return 0; // temporary return, replace this

}

/* Thread exits, setting the state to finished and allowing the next thread
 * to run.
 */
void my_pthread_exit(){

  // Implement Here //

}
