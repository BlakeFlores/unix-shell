#include "cmdleaf.h"
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>
#include <sys/stat.h>

CmdLeaf::CmdLeaf(std::vector<char*> input )
{
    this->cmdList = input;

}

std::vector<char*> CmdLeaf::getInput()
{
    return this->cmdList;
}

char* CmdLeaf::getChar()
{
    char* returnMe = new char[cmdList.size()];
    std::copy(*cmdList.begin(), *cmdList.end(), returnMe);
    return returnMe;
    
}

bool CmdLeaf::execute()
{
        if(strcmp(this->cmdList[0], "test") == 0 ||
           strcmp(this->cmdList[0], "[") == 0)
        {
            return this->test();
        }
        char* command[this->cmdList.size() +1];
        for(int i = 0; i < this->cmdList.size(); i++)
        {
            if(strcmp(this->cmdList[i], "exit") == 0)
            {
                exit(1);
            }
            else
            {
            command[i] = this->cmdList[i];
            }
        }
        command[this->cmdList.size()] = '\0';

        pid_t pid = fork();//fork
        int status;
        if(pid < 0)
        {
            perror("Error: ");
            return false;
        }
        else if(pid ==0) //child process
        {
            if(execvp(*command, command) < 0) //execute command
            {
                perror("Error: ");
                return false;
            }

        }
        else //wait for the child process to die
        {
            waitpid(pid, &status, 0);
        }

return true;
}

bool CmdLeaf::test()
{
    struct stat info;
    char* modifier;
    char* pathName;  
    
    //check if there is a parameter, if not default the pathName to
    // the last position in the cmdList
    if(this->cmdList[2] != NULL && this->cmdList[2] != "]")
    {
        modifier = this->cmdList[1];
        pathName = this->cmdList[2];
    }
    else
    {
        pathName = this->cmdList[1];
    }


    //check if the file/directory is a normal file
    if(strcmp(modifier, "-f") == 0)
    {
        if(stat(pathName, &info) == 0 && S_ISREG(info.st_mode))
        {
            std::cout << "(True)" << std::endl;
            return true;
        }
    }
    //check if the file/directory is a directory
    else if(strcmp(modifier, "-d") == 0)
    {
        if( stat(pathName, &info) == 0 && S_ISDIR(info.st_mode))
        {
            std::cout << "(True)" << std::endl;
            return true;
        }
        
    }
    //check if the file/directory exists
    else
    {
        if( (stat(pathName, &info) == 0 && S_ISREG(info.st_mode)) || 
            (stat(pathName, &info) == 0 && S_ISDIR(info.st_mode) ) )
        {
            std::cout << "(True)" << std::endl;
            return true;
        }
    }
    
    std::cout << "(False)" << std::endl;
    return false;
}
