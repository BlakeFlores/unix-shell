#include "pipe.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

Pipe::Pipe(std::vector<Base*> newList)
{
    this->pipeList = newList;
    this->pipeList.push_back(NULL);
}

char* Pipe::getFileName()
{
    return this->fileName;
} 

bool Pipe::execute()
{
    int save_stdin = dup(0);
    int save_stdout = dup(1);

    int pipefd[2];  
    int status;
    pid_t pid;
    int fd_in = 0;

    int i = 0;
    while(this->pipeList[i] != NULL)
    {
        pipe(pipefd);
        if((pid = fork()) == -1)//check to see if it forks properly
        {
            perror("Error: ");
            exit(1);
        }
        else if(pid  == 0)//if it does it should get here
        {
            dup2(fd_in, 0); //change input
            if(pipeList[i+1] != NULL)
                dup2(pipefd[1], 1);
            close(pipefd[0]);
            this->pipeList[i]->execute();
            exit(0);
        }
        else
        {
            //waitpid(pid, &status, 0);
            wait(NULL);
            close(pipefd[1]);
            fd_in = pipefd[0];//save the input for the next command
            i++;
        }
    }
    dup2(save_stdin, 0);
    dup2(save_stdout, 1); 
    return true; 

}
