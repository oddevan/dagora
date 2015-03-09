#ifndef dginit_H
#define dginit_H

/*
    Dagora Battle System initilization header/useful functions
    (c) 2003 root-1 Software
*/

#include "dgattackhandle.h"
#include "dgitemhandle.h"
#include "dgtypehandle.h"

const DGAttackHandle DGATK;
const DGItemHandle DGITM;
const DGTypeHandle DGTYP;

void InitDagora();
//sets the random number generator;
//MUST BE CALLED AT BEGINNING OF PROGRAM

int DGRoundDouble(double roundMe);
//Rounds a double instead of truncating it. Very nice :-)

double DGRandomDouble();
//returns a random double between 1 and 0.

int DGRandomInt(int max);
//returns random integer 0 =< x < max.

//void KillDagora();
//deletes dynamically allocated memory from InitDagora()

//#include "dginit.cpp"

#endif