#include <stdio.h>
#include <vector> 
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include "linkedlist.c"
using namespace std;

#define PAGES 256

int fifo(int position, int ref, int mod);

//Page Table
//from 0 to 256 byte, 256-512 ... 25344-25600
//will use arrays to hold different parts entry: referenced, modified, absent-present bit, frame number
//dont need protections or caching for this example
//the lower 8 bits are the offset, the upper 8 give the page number
//find page number by dividing the requested addr by 256
//this way we divide an int by an int and get any addr under one page by ignoring the remiander
//another way would be to use the upper 8 bits and would give us the same   
int index(int addr){
	int i=addr/PAGES;
	return i;
}

int frame[PAGES];

int absentPresent[PAGES];

//int protection[PAGES];

//if modified means written to
int modified[PAGES]; 

//if refrenced means written to or read from (if its both refrenced and modified then its written to else read from)
int referenced[PAGES]; 

//int cachingDisabled[PAGES];

int pagefault = 0;

int main() {
	
	//zero the table
	for(int i=0; i<PAGES; i++){
		frame[i]=0;
		absentPresent[i]=0;
		modified[i]=0;
		referenced[i]=0;
	}
	
	//way I will do it
	//Read from 1f59
	/*
	int position= index(0x1f59);
	frame[position]=0;
	absentPresent[position]=1;
	referenced[position]=1;
	cout<<"position is: "<<position<<endl;
	*/

	//simulate memory management process
	
	linked_list fifo;
	fifo.add_node(0);//just starting with this head 
	string line;
	ifstream myfile ("data.txt");
	string delimiter = " ";
	string token;
	size_t pos = 0;
	if (myfile.is_open())
	{
		int i=0;
		int oldPos=-1;
		while ( getline (myfile,line) )
		{
			int j=0;
			int call[3];
			while((pos = line.find(delimiter)) != string::npos){	
				token = line.substr(0, pos);
				if(j==0 && token=="Read") call[j]= 1, call[j+1]=0;
				if(j==0 && token=="Write") call[j]= 1, call[j+1]=1;
				line.erase(0, pos + delimiter.length());
				j++;
			}
			const char *hexstring = line.c_str();
			call[2]=(int)strtol(hexstring, NULL, 16);

			int position= index(call[2]);
			cout<<"........"<<endl;
			cout << "pos is: "<<position<<endl;
                        cout << "frame is: "<<frame[position]<<endl;
                        cout << "ref is: "<<referenced[position]<<endl;
                        cout << "mod is: "<<modified[position]<<endl;
			if(absentPresent[position]==1 && modified[position]==call[1] && referenced[position]==call[0] ){//then page is already in frame
			}else if(i<10 && absentPresent[position]==0){//populate frames
				
				pagefault++;
				frame[position]=i;
				absentPresent[position]=1;
				referenced[position]=call[0];
				modified[position]=call[1];
				fifo.add_node(position);
				i++;
				cout<<"i= "<<i<<endl;

			}else if(absentPresent[position]==1 && referenced[position]==0){//if present but not ref
				pagefault++;
				referenced[position]=call[0];
				if(modified[position]==0 && call[1]==1) modified[position]=call[1];
			}else if(absentPresent[position]==1 && modified[position]==0 && call[1]==1){//if refrenced before but modified now
				pagefault++;
				modified[position]=call[1];
			
			}else if(i>=10){//once all frames are populated
				fifo.add_node(position);
				int replace= fifo.gethead()->next->data;
				cout<<"replace: "<<replace<<endl;
				fifo.del(fifo.gethead());
				frame[position]=frame[replace];
				frame[replace]=0;
				absentPresent[position]=1;
				absentPresent[replace]=0;
				referenced[position]=call[0];
				referenced[replace]=0;
				modified[position]=call[1];
				modified[replace]=0;
				pagefault++;			
			}
			//if(oldPos != position && oldPos != -1) referenced[oldPos]=0;//Periodically the R bit is cleared
			oldPos=position;
			cout << "pos is: "<<position<<endl;
		        cout << "frame is: "<<frame[position]<<endl;
			cout << "ref is: "<<referenced[position]<<endl;
			cout << "mod is: "<<modified[position]<<endl;
			cout<<"........"<<endl;
		}
		myfile.close();
	}
	else cout << "Unable to open file"; 
	cout<< "page fault for fifo is: "<<pagefault<<endl;
	
	return 0;
}

