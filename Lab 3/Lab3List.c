// Name: Matthew Ding
// Date: 1/20/2022
// Title: Lab Assignment 3: Pthreads and Inter-process Communication - Pipes
// This step in the lab assignment was to replace a section of the original code
// and put the ls command output into the upstream end of the pipe. Then the
// downstream end of the pipe would print out the output of the ls command.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);
   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
       close(fds[0]);
       dup2(fds[1],1); // Redirect standard out through the pipe
       execlp("ls","ls",0); // Run the ls command
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);
       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);
               write(1," ",1);
           }
           printf("\n");
       }
       exit(0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}
