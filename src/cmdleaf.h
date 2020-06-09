#ifndef CMDLEAF
#define CMDLEAF

#include "base.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>

class CmdLeaf : public Base
{
    protected:
        std::vector<char* > cmdList;
    public:
        CmdLeaf(){};
        CmdLeaf(std::vector<char* > input);
        std::vector<char*> getInput();
        char* getChar();
        bool execute();
        bool test();


};


#endif


