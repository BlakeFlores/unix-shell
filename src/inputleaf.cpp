#include "inputleaf.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

InputLeaf::InputLeaf(Base* newCmd, char* newFileName)
{
    this->command = newCmd;
    this->fileName = newFileName;
   
}
bool InputLeaf::execute()
{
    int save_stdin = dup(0);

    int fileD =  open(fileName, O_CREAT| O_RDWR, 0644);
    dup2(fileD, 0);
 
    this->command->execute();

    close(fileD);
    dup2(save_stdin, 0);
    close(save_stdin);
    
    return true;

}
char* InputLeaf::getFileName()
{
    return this->fileName;
}
