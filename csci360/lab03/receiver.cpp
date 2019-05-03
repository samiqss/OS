//receiver
//csci360-LAB3 Sami Al-Qusus Sept 2018 
//Credits: Dr. LoPinto lab3 example.
#include <stdio.h>
#include <iostream>
#include <cctype>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

using namespace std;

string receiver_done= "0";//flag used for sender

int main() {
	  //printf("Hello shared memory world\n");

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
	  
	  char *flag = sharedRam; //flags address
	  char *ptr = flag+1; //shared memory buffers
	  
	 
	  while(1){ //keep running
	  	
	     if(flag[0]=='1'){ //checks if its recievers turn to use shared memory

		//this is for debugging purposes, prints what is in the shared flag
		//printf("Shared flag holds: %s\n",flag);

		//read from the shared memory
		cout<< "get the message from shared memory.."<<endl;
	  	printf("Message: %s\n",ptr);
	    
		//change flag to 0 for sender 
		strcpy(flag,(char*)receiver_done.c_str());

		//this is for debugging purposes, prints what is in the shared flag
		//printf("Shared flag holds now: %s\n",flag);
		
		//destroy the shared memory
	  	//shmctl(id,IPC_RMID,NULL);

	     }
	  }

	  return 0;
}

