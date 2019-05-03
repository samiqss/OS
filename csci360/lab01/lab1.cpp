/* Lab1 csci360    *********************************************
 * Sept 17, 2018   *********************************************
 * Sami Al-Qusus    ********************************************
 * Credits: MODERN OPERATING SYSTEMS 3rd ed. *******************
 *          Dr.LoPinto notes ***********************************
 *          youtube: Sandie Xie using fork() and exec() in C ***
 *
 *          ****************************************************/

#include <cstdio>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 
#include <sys/types.h>
#define TRUE 1
using namespace std;

string prompt();

int main()
{
   //printf("\nStart of main\n");

   while(TRUE){
     char* args[3];
     string command= prompt();
     args[0]= (char*)command.c_str();
     args[1]=NULL;

     pid_t pid= fork();
     if(pid!=0){
       //parent code
       waitpid(-1, NULL, 0);
     }else{
       //child code
       execvp(args[0],args);
       abort();
     }
   }
   
   return 0;
}

// get a command choice from the user
string prompt()
{
   string cmnd;
   printf("\n provide me with a command\n");
   cin >> cmnd;
   return cmnd;
}




   
