#ifndef BASE
#define BASE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>


class Base
{
    private:

    public:
    Base(){};
    virtual bool execute()=0;

};


#endif
