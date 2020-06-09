#include "buildparse.h"
#include "cmdleaf.h"
#include "cmdand.h"
#include "cmdor.h"
#include "outputredir1.h"
#include "inputleaf.h"
#include "pipe.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <sys/wait.h>

BuildParse::BuildParse()
{
}

void BuildParse::setInput(std::string input)
{
      //convert string to char*
     char* temp = new char[input.length() +1];
     strcpy(temp, input.c_str());

     //fill the vector with each command
     char* token = strtok(temp, ";");
     while(token != NULL)
     {
          this->commandList.push_back(token);
          token = strtok(NULL, ";");
     }
}

Base* BuildParse::parseBuild(char* fullCommand, bool firstFlag)
{    
    bool skipLeaf = false; //set to true if there is a connector, parenthesis or input/output redirection
    char* token1 = strtok(fullCommand, " ");
    std::vector<char*> currentCommand;

    Base* currentHead = NULL; 
    while(token1 != NULL)
    {   
//parenthesis
        /*check for parenthesis, if found build a tree out of their contents */
        if(token1[0] == '(')
        {
           char* temp = new char[sizeof(fullCommand)];
           
           strcpy(temp, token1+1);
           strcat(temp, " ");
           int p_counter = 1;//counts opening parenthesis
           while( token1 != NULL && p_counter > 0)
           {
               char* it = &token1[0];

               //check for open parenthesis
               for(int i = 0; i < sizeof(token1); i++)
               {
                 //if you have one, you need to go one token further
                 if(strcmp(&token1[i], "(") == 0)
                     p_counter++;
               }
              
              //get another token up to the next ')'
              token1 = strtok(NULL, ")"); 
              strcat(temp, token1);
              //decrement the parenthesis counter to keep the parenthesis matching
              p_counter--;
             
           } 
           strcat(temp, "\0");
           currentHead = parseBuild(temp, false);
           skipLeaf = true;
        }
//quotes
        if(token1[0] == '"')
        {
            char* temp = new char[sizeof(fullCommand)];
            strcpy(temp, token1+1);//copy the first word and removes the opening quote mark
            strcat(temp, " ");//add a space after the first word

            token1 = strtok(NULL, "\"");//make a token to the last quote mark
            strcat(temp, token1);//store that in the temp cstring
            strcat(temp, "\0");//null terminate

            currentCommand.push_back(temp);
            token1 = strtok(NULL, " ");
            if(token1 == NULL)
            {
                continue;
            }
             
        }

//output redirection        
        if(strcmp(token1, ">") == 0)
        {
            token1 = strtok(NULL, " ");
            //if there is no current head, make a leaf node and create a new outputredir node
            if(currentHead == NULL)
            {
                currentHead = new OutputRedir(
                    new CmdLeaf(currentCommand),token1, true);
            }
            else//if there is a current head, make a new outputredir and store the head in it
            {
                currentHead = new OutputRedir(currentHead, token1, true);
            }
            skipLeaf = true;
        }
        else if(strcmp(token1, ">>") == 0)
        {
            token1 = strtok(NULL," ");
            if(currentHead == NULL)
            {
                 currentHead = new OutputRedir(
                     new CmdLeaf(currentCommand),token1 , false);
            }
            else
            {
               currentHead = new OutputRedir(currentHead, token1, false);
            }
            skipLeaf = true;
        }
//input redirection   
        if(strcmp(token1, "<") == 0)
        {
            token1 = strtok(NULL, " ");
            if(currentHead == NULL)
            {
               currentHead = new InputLeaf(new CmdLeaf(currentCommand), token1);
            }
            else
                currentHead = new InputLeaf(currentHead, token1);
        
            skipLeaf = true;
        }
//pipe!
        if(strcmp(token1, "|") == 0)
        {
            std::vector<Base*> pipeVector;

            if(currentHead != NULL)//if there is a head, make it the start of the vector
            {
                pipeVector.push_back(currentHead);
            }
            token1 = strtok(NULL, "|");
            while(token1 != NULL)
            {
                pipeVector.push_back(this->parseBuild(token1, false));
                token1 = strtok(NULL, "|");
            }            
            
            currentHead = new Pipe(pipeVector);
            skipLeaf = true;
            break;
        } 

         /*
         *check if the current token is an and
         *if it is, create a new and that points to the
         *tokens up to this point on the left, and
         *the rest of the input on the right
         */
//and/or
        if(strcmp(token1, "&&") == 0)
        {
            if(currentHead != NULL)
            {
                currentHead = makeAndOr(
                    currentHead, this->parseBuild(strtok(NULL, ""), false), true);
            }
            else
                currentHead = makeAndOr(currentCommand, strtok(NULL, ""), true);  
            skipLeaf = true;
        }

        else if (strcmp(token1, "||") == 0)
        {
           if(currentHead != NULL)
                currentHead = makeAndOr(
                    currentHead, this->parseBuild(strtok(NULL, ""), false), false);
           else
                currentHead = makeAndOr(currentCommand, strtok(NULL, "") , false);
           skipLeaf = true;
        } 
        //if it isn't an and, push the token onto the vector of tokens
        //to be turned into a leaf later
        else
        {
           currentCommand.push_back(token1);
        }
        token1 = strtok(NULL, " ");
    }

    if(skipLeaf == false)//if you don't skip forming a new leaf
    {
        currentHead = new CmdLeaf(currentCommand);//if it isn't an and or or,
    }                                             // it is a leaf
    //if it's the head of a tree, add it to the list of vectors.
    if(firstFlag == true)
        this->commandTree.push_back(currentHead);

    return currentHead;
}

bool BuildParse::execute()
{
    for(int i = 0; i < this->commandTree.size(); i++)
    {
        this->commandTree[i]->execute();
    }
    this->commandTree.clear();
    this->commandList.clear();
}

Base* BuildParse::makeAndOr(Base* leftKid, Base* rightKid, bool isAnd)
{
    if(isAnd)
    {
        return (new CmdAnd(leftKid, rightKid));
    }
    return (new CmdOr(leftKid, rightKid));
}

Base* BuildParse::makeAndOr(std::vector<char*> firstPart, char* secondPart, bool isAnd)
{
    Base* returnBase;
    Base* newLeaf;
    Base* everythingElse;
   
    if(firstPart.empty())
    {
        newLeaf = NULL;
    }
    else
        newLeaf  = new CmdLeaf(firstPart);

    if(strcmp(secondPart, "") == 0)
    {
        everythingElse  = NULL;
    }
    else
        everythingElse = this->parseBuild(secondPart, false);
   
    //if it's an and, make an and
    if(isAnd)
    {
       returnBase = new CmdAnd(newLeaf, everythingElse);
    }
    else //make an or
        returnBase = new CmdOr(newLeaf, everythingElse);
    return returnBase;
}


//interface that outputs the prompt, reads input and executes commands
void BuildParse::interface()
{
    std::string input;
    while(true)
    {
        std::cout << "$";//output prompt
        getline(std::cin, input);//read user input
        
        for (int i = 0; i < input.size(); i++)
        {
            if (input.at(i) == '#')
            {
               input.erase(i, sizeof(input));
               std::cout << input << std::endl;
            }
        }
        this->setInput(input);
        //cycle through the commands
        for(int i = 0; i < commandList.size(); i++)
            //build a tree for every command using parseBuild
            this->parseBuild(this->commandList[i], true);
        //execute
        this->execute();
    }
}

