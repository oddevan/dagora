#ifndef dgclassleveldata_H
#define dgclassleveldata_H

/*
    DGClassLevelData class decleration
    (c) 2003 root-1 Software
*/

#include "dgcommand.h"

#define NUM_ATK_PER_LEVEL 4

struct DGClassLevelData
{
    DGClassLevelData();
    DGClassLevelData(int atkData[], int lvlRush);
    DGClassLevelData(int atkData[], int lvlRush, DGCommand lvlAbility);

    void Reset();
    
    int Attacks[NUM_ATK_PER_LEVEL];
    bool AtkLearned[NUM_ATK_PER_LEVEL];
    int SP;
    int Rush;
    DGCommand Ability;
};

//#include dgclassleveldata.cpp

#endif