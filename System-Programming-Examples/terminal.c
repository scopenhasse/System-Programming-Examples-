// C Program to create a terminal using fork and execvsp 
//the command can only take 3 options 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define LG_LIGNE 256 

int main(int argc, char const *argv[])
{
    char ligne[LG_LIGNE];
    char delim[] = " ";
    char *ptr1;
    char *ptr2;
    while (1)
    {
        fprintf(stderr,"scope--$");
        if (fgets(ligne,LG_LIGNE,stdin)==NULL) break;
        ligne[strlen(ligne)-1]='\0';    
        char *ptr = strtok(ligne, delim);
        ptr = strtok(NULL, delim);
        ptr1=ptr;
        ptr = strtok(NULL, delim);
        ptr2 = ptr;
        ptr = strtok(NULL, delim);
        char* argument_list[] = {ligne,ptr1,ptr2,ptr,NULL};
        if (fork()==0)
        {   
            execvp(ligne, argument_list);
            perror(ligne);
            exit(EXIT_FAILURE);
        }else
        {
            waitpid(-1,NULL,0);
        }            
    }  
    return EXIT_SUCCESS;
}

//@by: @ILYAS "Sc0Pe" NHASSE 