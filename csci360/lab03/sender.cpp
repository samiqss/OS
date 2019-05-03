//sender
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

string start= "0"; //flag initial start value
string sender_done= "1"; //flag used for sender
string readString; //message from user

int main() {
	  
	  //Create a key to use for IPC
	  key_t key = ftok("/tmp",1);
	  if(key == -1) {
		  perror("ftok");
	          exit(0);
	  } else
 		  printf("key = %x\n",key); 	  
	  //Create a shared memory segment of 101 byte
	  int id = shmget(key, 101,IPC_CREAT | S_IRUSR | S_IWUSR);
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
	  
	  strcpy(flag,(char*)start.c_str());
	  
	  while(1){ //keep running
            
            if(*flag=='0'){ //checks if its senders turn to use shared memory
		
		//write to the shared memory
          	cout<<"Write Data/message to send to receiver: ";
	  	cin>>readString;
		
		//chnage flag to give receiver
                strcpy(flag,(char*)sender_done.c_str());
		
		//write to the shared memory done here
	  	strcpy(ptr,(char*)readString.c_str());
	  	printf("Shared Ram holds: %s\n",ptr);	
	    
		//detach from shared memory
	  	//shmdt(sharedRam);
	    }
	  }
	  
	  return 0;
}

