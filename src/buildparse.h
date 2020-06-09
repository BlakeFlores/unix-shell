#ifndef BUILDPARSE
#define BUILDPARSE

#include "base.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>

class BuildParse
{
    private:
        std::vector<Base*> commandTree;
        std::vector< char*> commandList;
    public:
        BuildParse();
        void setInput(std::string input);
        Base* parseBuild(char* parseMe, bool firstFlag);
        bool execute();
        Base* makeAndOr(std::vector<char*> firstPart, char* secondPart, bool isAnd);
        Base* makeAndOr(Base* leftKid, Base* rightKid, bool isAnd);
        void interface();  
};



#endif
