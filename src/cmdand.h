#ifndef CMDAND
#define CMDAND

#include "base.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>



class CmdAnd: public Base
{
    private:
    Base* leftChild;
    Base* rightChild;
    public:
    CmdAnd(){};
    CmdAnd(Base* leftKid, Base* rightKid);
    void setLeft(Base* leftKid);
    void setRight(Base* rightKid);
    bool execute();

};


#endif
