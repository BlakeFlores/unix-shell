#include "cmdand.h"

CmdAnd::CmdAnd(Base* leftKid, Base* rightKid)
{
    this->leftChild = leftKid;
    this->rightChild = rightKid;
}

void CmdAnd::setLeft(Base* leftKid)
{
    this->leftChild =  leftKid;
}

void CmdAnd::setRight(Base* rightKid)
{
    this->rightChild = rightKid;
}

bool CmdAnd::execute()
{
    if(this->leftChild == NULL)
        return false;

    if (this->leftChild->execute() == true)
    {
       if(this->rightChild != NULL)
       {
           this->rightChild->execute();
           return true;
       }
    }
    return false;
}
