//client 
//Sami Al-Qusus
//lab 5 csci350 oct 16, 2018
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
	//Client used to demonstrate ingerprocess communications
	//through TCP/IP message passing

	//Create a socket for the client to use to connect to the server
        int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == -1) {
		perror("sock ");
		return -1;  //Indicate error
	}

        //Create the address of the server we want to reach.
	
	struct sockaddr_in srv_addr;//This struct stores information about the machine we want to connect to.
	srv_addr.sin_family = AF_INET;//sets the address family
	srv_addr.sin_port = htons(PORT);// set destination port number

	//convert the string address of localhost into sin_addr
	if(inet_pton(AF_INET,"127.0.0.1",&srv_addr.sin_addr)==-1){
		perror("inet_pton");
		exit(0);
	}
	
	//connect to the server
	int rtn = connect(sock,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
        if(rtn != 0) {
		perror("connect ");
		return -1;
	}

        //write something to the server
	char msg[256];
	int len[1];
	bzero(msg,256);
	cout<<"input a message"<<endl;
	cin.getline(msg,256);
	printf("Client msg to server: %s\n",msg);
	int length = strlen(msg);//length of message
	len[0]=length;
	//write the length of message 
	rtn = write(sock, len,2); 
	if(rtn==-1){
		perror("write");
		exit(0);
	}
	//Writes N bytes (strlen of msg) from buf to the socket associated with sock
	rtn = write(sock, msg, length);
	if(rtn==-1){
		perror("write");
		exit(0);
	}
	bzero(msg,256); //zero the message buffer
	//wait for the server to respond
	if(read(sock,msg,256)==-1){//reads 256 bytes of input from the memory area indicated by sock put it in msg
		perror("read");
		exit(0);
	}
	printf("%s\n",msg);
	return 0;

}
