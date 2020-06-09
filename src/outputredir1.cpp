#include "outputredir1.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

//constructor
OutputRedir::OutputRedir(Base* newCmd, char* newFileName, bool overwrite_Flag)
{
    this->command = newCmd;
    this->fileName = newFileName;
    this->overwrite = overwrite_Flag;
}

/*checks the overwrite flag, if it's true it overwrites a file with
 * name fileName. If not it appends to the end of fileName
 */
bool OutputRedir::execute()
{
    int fileD;
    int save_stdout = dup(1);    

    //if the overwrite flag is set (for >) overwrite, else don't (>>)
    if(overwrite)
    {
         fileD = open(fileName, O_CREAT| O_WRONLY | O_TRUNC, 0644);
    }
    else
    {
         fileD = open(fileName, O_WRONLY | O_APPEND);
    }

    dup2(fileD, 1);//replace stdout with output file
    
    close(fileD);
    if(this->command->execute())
    {
        dup2(save_stdout, 1);
        close(save_stdout);
        return true;
    }
    dup2(save_stdout, 1);
    close(save_stdout);
    return false;
}


