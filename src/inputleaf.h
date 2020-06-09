#include "base.h"

#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>


class InputLeaf: public Base
{
    private:
        char* fileName;
        Base* command;
    public:
        InputLeaf(Base* newCmd, char* newFileName);
        bool execute();
        char* getFileName();
};
