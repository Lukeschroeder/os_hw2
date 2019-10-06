#include "my_pthread.h"
#define STACKSIZE 32768

/* Scheduler State */
 // Fill in Here //
my_pthread_tcb* r_tail=NULL;
my_pthread_tcb* s_tail=NULL;
my_pthread_tcb* execute=NULL;

my_pthread_t TID=0;


/* Scheduler Function
 * Pick the next runnable thread and swap contexts to start executing
 */
 typedef enum scheduler_status{
   OFF,
   ON
 }sched;

sched s=OFF;

void executeToList(my_pthread_tcb** queue){
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
    if(execute!=NULL) {
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
    printf("Error: Akshay Fucked Up Our Code\n");
  }
}

/* Create a new TCB for a new thread execution context and add it to the queue
 * of runnable threads. If this is the first time a thread is created, also
 * create a TCB for the main thread as well as initalize any scheduler state.
 */
void my_pthread_create(my_pthread_t *thread, void*(*function)(void*), void *arg){
  //Initialize scheduler, create main thread
  if(s==OFF){
    //Starts scheduler
    s=ON;

    //Initializes maintcb thread control block, stores main context
    my_pthread_tcb * maintcb = (my_pthread_tcb *) malloc(sizeof(my_pthread_tcb));
    *thread = TID;
    maintcb->tid = TID++;
    maintcb->status = RUNNABLE;
    if(!getcontext(&maintcb->context)) {
      printf("Get Main Context Successful\n");
    } else {
      printf("Get Main Context Failed\n");
    }

    ucontext_t * currentcontext = (ucontext_t *) malloc(sizeof(ucontext_t));
    getcontext(currentcontext);
    swapcontext(currentcontext, &maintcb->context);
 

    //Confirms success
    printf("Main Thread Created: TID = %d\n", maintcb->tid);
  }
  
  //Initializes newtcb thread control block, stores function context
  my_pthread_tcb * newtcb = (my_pthread_tcb *) malloc(sizeof(my_pthread_tcb));
  newtcb->tid = TID++;
  newtcb->status = RUNNABLE;
  if(!getcontext(&newtcb->context)) {
    printf("Get New Context Successful\n");
  } else {
    printf("Get New Context Failed\n");
  }
  newtcb->context.uc_link = 0; //May change, terminates process on context return. Need to switch to next context 
  newtcb->context.uc_stack.ss_sp=malloc(STACKSIZE);
  newtcb->context.uc_stack.ss_size=STACKSIZE;
  newtcb->context.uc_stack.ss_flags=0;
  makecontext(&newtcb->context,(void *)function, 0);
  printf("New Thread Created: TID = %d\n", newtcb->tid);
  
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
 * needs to be changed, he said it was a one line check after identifying node and calling schedular??
 */
void my_pthread_join(my_pthread_t thread){
  //replace my_pthread_tcb with whatever the head of the linked list is
  /*
  struct threadControlBlock* temp = &my_pthread_tcb;
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
  */
}


/* Returns the thread id of the currently running thread
 */
my_pthread_t my_pthread_self(){

  // Implement Here //

  return 10;  // temporary return, replace this

}

/* Thread exits, setting the state to finished and allowing the next thread
 * to run.
 */
void my_pthread_exit(){

  // Implement Here //
  //just set status to finished and call schedule(SIGALRM)
  //the scheduler will take care of it.
}
