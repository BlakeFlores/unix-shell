#ifndef PIPE
#define PIPE

#include "base.h"

#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>

class Pipe: public Base
{
    private:
        std::vector<Base*> pipeList;
        char* fileName;

    public:
        Pipe(std::vector<Base*> newList);
        char* getFileName();
        bool execute(); 
};


#endif
