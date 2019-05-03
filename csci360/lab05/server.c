//server
//Sami Al-Qusus
//Lab 5 csci360 oct 16, 2018
//Credits: Dr. LoPinto lab5 examples.
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#define PORT 9349

int main() {
	printf("Welcome to the Server\n");
    
	int listenfd, connfd;
        char buf[256], buf1[512], buf2[256];
	int len[1];//buffer than holds message length

	struct sockaddr_in srv_addr;//This struct stores information about the server we want to connect to.
	//listen system call prepares a connection-oriented server to accept client connections.
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd == -1){ //check for errors
		perror("socket");
		exit(0);
	}
					       
	//set option to avoid socket reuse timeouts
	int enable=1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&enable,sizeof(int))==-1){
		perror("setsockopt");
		exit(0);
	}
	//Sets the first num bytes of the block of memory pointed by ptr to 0
	memset(&srv_addr,'0', sizeof(srv_addr));

	//listen on port number PORT
	srv_addr.sin_family = AF_INET;//sets the address family
	srv_addr.sin_port = htons(PORT); // set destination port number
        srv_addr.sin_addr.s_addr = INADDR_ANY; //set destination IP number

	//bind the address to the socket
        int rtn = bind(listenfd,(struct sockaddr *)&srv_addr, sizeof(srv_addr));//bind() system call associates an address with the socket descriptor
	if(rtn < 0) {
		perror("bind");
		return -1;
	}

        //listen for incoming connections
	//allowing a queue of up to 5 pending connection
	if(listen(listenfd,5)==-1){
		perror("listen");
		exit(0);
	}
	
        int count =0;
	int total = 0;
	while(1) {
		//take connections from the queue
		//If there is no connection waiting on the queue the program waits until a connection is received
		connfd=accept(listenfd,(struct sockaddr*)NULL,NULL);//socket descriptor
		if(connfd==-1){
			perror("accept");
			exit(0);
		}
		//reads  length of message indicated by len
		if(read(connfd,len,2)==-1){
			perror("read");
			exit(0);
		}
		int length = len[0];
		cout<<"message length received: "<<length<<endl;
		//reads length bytes of input into the memory area indicated by buf.
		while(total<length){//while total message is still not all received
			int n=length-total;//read remainder n bytes
			count=read(connfd,buf2,n); //count received bytes
			if(count==-1){//error check
				perror("read");
				exit(0);
			}
			for(int i=0;i<count;i++){//store received message into buf from buf2 which is what we just read
				
				buf[i+total]=buf2[i];
				//for debugging purposes
				//cout<<"doing count="<<count<<"at buf"<<buf2[i]<<endl;
			}
			total=total+count;//update the message count received so far
		}

		printf("%s\n",buf);
		bzero(buf1,512);//zero the buf1 buffer
		sprintf(buf1,"Server ACK msg: %s\n",buf);
		bzero(buf,256);//zero the buf buffer
		bzero(buf2,256);//zero the buf2 buffer
		bzero(len,2);
		if(write(connfd,buf1,strlen(buf1))==-1){//Writes N bytes (strlen of buf1) from buf to the socket associated with connfd.
			perror("write");
			exit(0);
		}
		if(close(connfd)==-1){//closes/frees file descriptor
			perror("close");
			exit(0);
		}
		total=0;//reset total 
	}

	return 0;

}
