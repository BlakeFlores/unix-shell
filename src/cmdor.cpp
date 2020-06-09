#include "cmdor.h"

CmdOr::CmdOr(Base* leftKid, Base* rightKid)
{
    this->leftChild = leftKid;
    this->rightChild = rightKid;
}

void CmdOr::setLeft(Base* leftKid)
{
    this->leftChild =  leftKid;
}

void CmdOr::setRight(Base* rightKid)
{
    this->rightChild = rightKid;
}

bool CmdOr::execute()
{
    if ( this->leftChild->execute() == false)
    {
        this->rightChild->execute();
        return true;
    }
return false;
}

