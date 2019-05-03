/* Lab2 csci360    *********************************************
 * Sept 24, 2018   *********************************************
 * Sami Al-Qusus    ********************************************
 * Credits: MODERN OPERATING SYSTEMS 3rd ed. *******************
 *          Dr.LoPinto notes ***********************************
 *          ****************************************************/

#include <stdio.h>
#include <pthread.h>
#include <errno.h>

//Create a function to run in our thread
//this is just an integer used to identify the thread in the system
pthread_t tSender;

// this is just a normal C function that is executed as a thread  
// when its name is specified in pthread_create() 
void *sender(void *arg) {
   
   for(int i=0;i<20;i++)
      printf("Thread: Count is %d\n",i);
}

int main() {
   printf("Test Threads\n");
   void *arg; 
   int x = 9;
   arg = &x;
   void *dummy;
   
   pthread_create(&tSender,NULL,&sender,arg);//function to create a thread
                                             //takes 4 arguments
					     //first argument is a pointer to thread_id which is set by this function
					     //second argument specifies attributes
					     //value is NULL, then default attributes are used
					     //third argument is name of function to be executed for the thread to be created
					     //fourth argument is used to pass arguments to thread

   pthread_join(tSender,&dummy); // this function is equivalent to wait() for processes
                                   //A call to pthread_join blocks the calling thread until the thread with identifier equal to the first argument terminates.
   return 0;
}


