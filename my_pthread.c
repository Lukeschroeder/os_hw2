#include "my_pthread.h"

/* Scheduler State */
 // Fill in Here //
struct threadControlBlock* r_tail=NULL;
struct threadControlBlock* s_tail=NULL;
struct threadControlBlock* execute=NULL;

/* Scheduler Function
 * Pick the next runnable thread and swap contexts to start executing
 */
 typdef enum scheduler_status{
   OFF,
   ON
 }sched;
sched s=OFF;
void executeToList(struct threadControlBlock** queue){
  if((*queue)!=NULL){
    execute->next=(*queue)->next;
    (*queue)->next=execute;
    (*queue)=execute;
    execute=NULL;
  }
  else{
    execute->next=execute;
    (*queue)=execute;
    execute=NULL;
  }
}
void schedule(int signum){
  if(signum==SIGALRM){
    if(execute!=NULL)
      if(execute->status==RUNNABLE){
        executeToList(&r_tail);
      }
      else if(execute->status==SLEEP){
        executeToList(&s_tail);
      }
      else{
        free(execute);
      }
    }
  }
  else{
    printf("%d\n",signum);
    printf("Something has gone horribly wrong????\n");
  }
}

/* Create a new TCB for a new thread execution context and add it to the queue
 * of runnable threads. If this is the first time a thread is created, also
 * create a TCB for the main thread as well as initalize any scheduler state.
 */
void my_pthread_create(my_pthread_t *thread, void*(*function)(void*), void *arg){

  // Implement Here
  //
  //init scheduler
  if(s=OFF){
    s=ON;
    //insert settimer code with TIME_QUANTUM_MS for time interval
    //set timer interrupt signal to schedule(int signum)
      //this means in the schedule method just check the signum for whatever number is timer interrupt,
      //if an error besides timer interrupt occurs then I will handle it and exit()
  }
  //insert rest of create thread code
}

/* Give up the CPU and allow the next thread to run.
 */
void my_pthread_yield(){

  // Implement Here
  //set status to pause and context swap
  schedule(SIGALRM);
}

/* The calling thread will not continue until the thread with tid thread
 * has finished executing.
 */
 //needs to be changed, he said it was a one line check after identifying node and calling schedular??
void my_pthread_join(my_pthread_t thread){
  //replace my_pthread_tcb with whatever the head of the linked list is
  // Implement Here //
  struct threadControlBlock* temp=&my_pthread_tcb;
  if(temp==NULL){
    return;
  }
  if(temp->tid==thread){
    while(temp->status!=FINISHED){}
    my_pthread_tcb=my_pthread_tcb->next;
    return;
  }
  while(temp->next!=NULL && temp->tid!=thread){
    temp=temp->next;
  }
  if(temp->next!=NULL){
    while(temp->next->status!=FINISHED){}
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
  //just set status to finished and call schedule(SIGALRM)
  //the scheduler will take care of it.
}
