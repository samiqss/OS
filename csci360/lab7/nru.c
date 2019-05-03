#include <ctime>
#include <stdio.h>
#include <vector> 
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include <fstream>
#include <iostream>
using namespace std;

#define PAGES 256

int nru(int position, int ref, int mod);

//Page Table
//from 0 to 256 byte, 256-512 ... 25344-25600
//will use arrays to hold different parts entry: referenced, modified, absent-present bit, frame number
//dont need protections or caching for this example
//the lower 8 bits are the offset, the upper 8 give the page number
//find page number by dividing the requested addr by 256
//this way we divide an int by an int and get any addr under one page by ignoring the remiander
//another way would be to use the upper 8 bits and would give us the same   

int index(int addr){//given address return page 
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

int pagefault = 0;//pagefault counter

//simulate memory management process
int main() {
	//zero the table
	for(int i=0; i<PAGES; i++){
		frame[i]=0;
		absentPresent[i]=0;
		modified[i]=0;
		referenced[i]=0;
	}
	
	
	string line;
	ifstream myfile ("data.txt");//read from file calls sent to mmu
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
				i++;
				
			}else if(absentPresent[position]==1 && referenced[position]==0){//if present but not ref
				referenced[position]=call[0];
				if(modified[position]==0 && call[1]==1) modified[position]=call[1],pagefault++;
			
			}else if(absentPresent[position]==1 && modified[position]==0 && call[1]==1){//if refrenced before but modified now
				pagefault++;
				modified[position]=call[1];
			
			}else if(i>=10){//once all frames are populated
				int replace= nru(position,call[0],call[1]);
				cout<<"replace: "<<replace<<endl;
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

			if(oldPos != position && oldPos != -1) referenced[oldPos]=0;//Periodically the R bit is cleared
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
	cout<< "page fault for nru is: "<<pagefault<<endl;
	
	return 0;
}




//Not Recently Used (NRU)
int nru(int position, int ref, int mod){
	srand(time(0));
	bool  pick=false;
	vector<int> nru;
	for(int i=0; i<PAGES; i++){
		if(absentPresent[i]==1 && referenced[i]==0 && modified[i]==0) nru.push_back(i), pick=true;
	}
	
	if(pick){//Class 0: not referenced, not modified.
		int size=nru.size(); 
		int replace= rand()%size;
		return nru[replace];
	}
	
	for(int i=0; i<PAGES; i++){
		if(absentPresent[i]==1 && referenced[i]==0 && modified[i]==1) nru.push_back(i), pick=true;
	}
	if(pick){//Class 1: not referenced, modified.
		int size=nru.size();
		int replace= rand()%size;
		return nru[replace];
	}
	
	for(int i=0; i<PAGES; i++){
		if(absentPresent[i]==1 && referenced[i]==1 && modified[i]==0) nru.push_back(i), pick=true;
	}
	if(pick){//Class 2: referenced, not modified.
		int size=nru.size();
		int replace= rand()%size;
		return nru[replace];
	}
	
	for(int i=0; i<PAGES; i++){
		if(absentPresent[i]==1 && referenced[i]==1 && modified[i]==1) nru.push_back(i), pick=true;

	}
	if(pick){//Class 3: referenced, modified.
		int size=nru.size();
		int replace= rand()%size;
		return nru[replace];
	}	

}

