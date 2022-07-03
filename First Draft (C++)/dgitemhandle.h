#ifndef dgitemhandle_H
#define dgitemhandle_H

/*
    DGItemHandle class decleration
    (c) 2003 root-1 Software
*/

#include "dgcharacter.h"

#define TOT_NUM_ITM 5

class DGItemHandle
{
    public:
        DGItemHandle();
        
        char* Name(int ind) const;	//returns name of item at ind
        bool Use(DGCharacter* victim, int ind) const;	//returns true if item use is successful
    
    private:
};

//#include dgitemhandle.cpp

#endif