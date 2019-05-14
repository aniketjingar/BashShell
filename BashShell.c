#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define BUF 1024

int main(){

	char listOfCommands[BUF];
	while(1){
		
		printf("~$");  
		if(!fgets(listOfCommands, BUF, stdin))
			break;
		size_t length = strlen(listOfCommands);
		
		if (listOfCommands[length - 1] == '\n')
			listOfCommands[length - 1] = '\0'; 
		
		if(strcmp(listOfCommands, "exit") == 0)      
			break;
  
  		char *commands[10]; 
  		char *token = strtok(listOfCommands, ";" );
  		int i = 0;
  		while (token != NULL){
    			commands[i] = token;
    			i++;
    			token = strtok(NULL, ";" );
  		}
  		int numOfCommands = i; 

  		i = 0;
  
		while (i < numOfCommands){
    			printf("Command: %s\n", commands[i]);
    			char *args[10] = {}; 
    			args[0] = strtok(commands[i], " ");
    			int counter = 0;
    
			while (args[counter] != NULL){
      				counter++;
      				args[counter] = strtok(NULL, " ");
    			}

    			int child = fork();

    			if (child == 0){
      				if ((execvp(args[0], args)) < 0){
        				printf("-%s: Command not recognized.\n", args[0]);
      				}
      			exit(0);
    			}
			else if (child > 0){
    				int status;  
    				waitpid(child, &status, 0);

         			if(WIFEXITED(status)){
             				int exitStatus = WEXITSTATUS(status);
             				printf("Child %d exited with status %d\n", child, exitStatus);
         			}
      
    			}
    			else{
      				printf("Error\n");
      				exit(1);
    			}

    			i++;
  		}
  	}
  	return 0;
}
