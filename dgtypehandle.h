#ifndef dgtypehandle_H
#define dgtypehandle_H

/*
    DGTypeHandle class decleration
    (c) 2003 root-1 Software
*/

#define TOT_NUM_TYP 13

class DGTypeHandle
{
    public:
        DGTypeHandle();
        
        int Lookup(int atkTyp, int defTyp) const;
        char* TypName(int typ) const;
    
    private:
        int myTypeMatrix[TOT_NUM_TYP][TOT_NUM_TYP];
};

//#include dgtypehandle.cpp

#endif