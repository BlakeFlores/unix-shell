#ifndef OUTPUTREDIR
#define OUTPUTREDIR

#include "base.h"

#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>

class OutputRedir : public Base
{
    private:
        char* fileName;
        Base* command;
        bool overwrite;
    public:
        OutputRedir(Base* newCmd, char* newFileName, bool overwrite_flag);
        bool execute();
        char* getFilename();

};


#endif
