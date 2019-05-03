//receiver
//csci360-LAB4 Sami Al-Qusus Oct 2018 
//Credits: Dr. LoPinto lab3 and lab4 examples.
#include <stdio.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <iostream>
#include <sys/shm.h>
#include <string.h>
#include <time.h>
#include <math.h>
using namespace std;
int main() {
 
   printf("Receiver\n");
   
   //Create a key to use for IPC
   key_t key = ftok("/tmp",1);
   if(key == -1) {
	   perror("ftok");
	   exit(0);
   } else
	   printf("key = %x\n",key);
   //Create a shared memory segment of 101 byte
   int id = shmget(key, 101, IPC_CREAT |S_IRUSR | S_IWUSR);
   if(id == -1) {
	   perror("shmget");
	   exit(0);
   } else
	   printf("id = %d\n",id);
   //Attach the shared memory segment to your program. Let the system pick the
   //address and make the memory read/write
   char *sharedRam = (char *)shmat(id,0,0);
   if(*sharedRam == -1) {
	   perror("shmat");
	   exit(0);
   } else
	   printf("Shared memory pointer is %p\n",sharedRam);
   char *ptr = sharedRam; //shared memory buffers


   //open semaphores
   sem_t *semB = sem_open("/receiver",O_CREAT);
   if(semB == SEM_FAILED) {
      perror("sem receiver");
      return 0;
   }

   sem_t *semA = sem_open("/sender",O_CREAT);
   if(semA == SEM_FAILED) {
	   perror("sem sender");
	   return 0;
   }

   //int value;
   //sem_getvalue(semA,&value);
   //printf("The value of semaphore A is %d\n",value);

   //Set the value of the semaphore
   //sem_init(semB,1,1);

   //Now get the value
   //sem_getvalue(semA,&value);
   //printf("Now the value is %d\n",value);
   
   double t=0;//used for clock
   while(1){
   //Loop if we can.
        string x="";
   	sem_wait(semB);//first run value goes from 1 to 0, afterwards its 0 and an increment puts it to sleep until sender is done and does a sem_post
	//The number of clock ticks elapsed since an epoch related to the particular program execution (nanoseconds)
	if (t!=0) t = (double) clock() - t;//first run its 0 we still didnt start the clock, second run check the elapsed time
	t= (t/ CLOCKS_PER_SEC)*pow (10, 9);//change to nanoseconds
	cout<<"time since last receiver entry: "<<t<<" nanoseconds."<<endl;
   	cout<< "get the message from shared memory.."<<endl;
	t = (double) clock();//start clock 
	printf("Message: %s\n",ptr);//read message from shared memory
	cout<<endl;
	x=ptr;//take ptr value to check if its "q" 
	sem_post(semA);//wake up semA (sender) 
   	
   	
	//quit if input was "q" the destroying of semaphores and shared memory is done by the receiver to make sure we dont lose the data before its received
	if(x == "q"){
   		if(!sem_unlink("/receiver")) printf("Semaphore b destroyed\n");
   		else {
     			perror("destroyB");
   		}
		if(!sem_unlink("/sender")) printf("Semaphore a destroyed\n");
		else {
			perror("destroyA");
		}
		//destroy the shared memory
		if(!shmctl(id,IPC_RMID,NULL)) printf("shared memory destroyed\n");

		cout<< "quiting program.."<<endl;
		return 0;
	}
   }
   return 0;
}
