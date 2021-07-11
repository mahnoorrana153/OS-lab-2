
// LAB NO 2


#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

 // fix max characters per line=100

#define MAX_LINE 1020

// Refreshings args, setting to null

void refresh_args(char *args[])
{
    while(*args) {
        free(*args);  
        *args++ = NULL;
    }
}

//making a function for parsing input called Parse-Input

//Saves previously done command and returns the total number of arguments
//book function III

size_t Parse-Input(char *args[], char *input)
{
    char input_buffer[MAX_LINE + 1];
    size_t num = 0;
    char command[MAX_LINE + 1];

    if(strncmp(input_buffer, "!!", 2) == 0)  // if ueser enters !!
    {
        if(strlen(input) == 0) 
        {
            fprintf(stderr, "No command in history..\n");  
 // if there is no previous command in history
	
        }
        printf("%s", input);
    }
	
	
	
	   if(fgets(input_buffer, MAX_LINE + 1, stdin) == NULL)
    {
        fprintf(stderr, "Failure reading input.. \n");         // if there is no input to read
    }


    strcpy(input, input_buffer);    //Replace history with new command

    strcpy(command, input);
    char *token = strtok(command, DELIMITERS);

    while(token != NULL) 
    {
        args[num] = malloc(strlen(token) + 1);
        strcpy(args[num], token);
        ++num;
        token = strtok(NULL, DELIMITERS);
    }

    return num;
}

// making function to change directories



int Change-direct(char *args[], int size)
{
    int val;
    if(size == 1)
        val = chdir(getenv("M"));  //if enter M, goes to main directory

    
    else if(strcmp(args[1], "P")==0 ) // if P thn goes to parent directory.

        val = chdir("P");
    
    else
        val = chdir(args[1]);

    if(val!=0)
        fprintf(stderr, "Invalid result...\n");

    return val;
}




// making a function named run_command


int run_command(char **args, size_t args_num) 
{
    
    pid_t pid = fork();
    if(pid < 0) // 
    {   
        fprintf(stderr, "Failed...\n");
        return 0;
    } 
    
    else if (pid == 0) // make a child process
    { 
        // in case of failing redirection
        if(redirect_io(args, &args_num) == 0)
        {
            return 0; // Redirect failed
        }
        execvp(args[0], args);
        fflush(stdin);
    } 

    else /
    { 
        wait(NULL);
    }

    return 1;
}

//Function for redirecting input and output named I/O-redirect
//remove all previous redirection tokens
//using 0 and 1 bits for input and output redirection
//book function IV


int I/O-redirect(char ** args, size_t *size)
{
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    size_t to_remove[4], remove_cnt = 0;

    for(size_t i = 0; i != *size; ++i) 
    {
        if(remove_cnt >= 4) 
        {
            break;
        }

        // input
        if(strcmp("<", args[i]) == 0) 
        {     
            to_remove[remove_cnt++] = i;
            if(i == (*size) - 1) 
            {
                fprintf(stderr, "No input file given...");  
                return 0;
            }
            fd = open(args[i+1], O_READONLY, mode);
            if(fd < 0) 
            {
                fprintf(stderr, "Failure opening input file the input file...", args[i+1]);
                return 0;
            }
            dup2(fd, 0);  //dup function to create duplicate the standard output
            to_remove[remove_cnt++] = ++i;
            close(fd);
        } 

        // output
        else if(strcmp(">", args[i]) == 0)
        {   
            to_remove[remove_cnt++] = i;
            if(i == (*size) - 1)
            {
                fprintf(stderr, "Output file not given...");
                return 0;
            }
            fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, mode);
            if(fd < 0) 
            {
                fprintf(stderr, "Failure openng the output file...", args[i+1]);
                return 0;
            }
            dup2(fd, 1);
            to_remove[remove_cnt++] = ++i;
            close(fd);
        }
    }

  
}


// main function that includes history command and I/O redirection

int main(void) 
{
	 char command[MAX_LINE + 1] = "";
    char *args[MAX_LINE / 2 + 1] = { NULL };
   
    int should_run = 1; 
	// to know when the os exit program */

    while (should_run) 
    {
        printf("osh>");
        fflush(stdout);
        fflush(stdin);

        // refrshing/clearing args
        clear_args(args);

     
        size_t args_num = Parse-Input(args, command);

        //exit

	if(args_num == 0) 
	{
	    if(strcmp(args[0], "cd") == 0)
    	    {
	        if(Change-direct(args, args_num) != 0)
		    continue;
	    }

    	    else if(strcmp(args[0], "exit") == 0)
                should_run = 0;
	    
	    else
		
		run_command(args, args_num);
	}

	else // empty input
	{ 
            printf("enter any command... or exit");
            continue;
        }
        
    }
    
    clear_args(args);
    return 0;
}
