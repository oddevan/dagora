#ifndef dgattack_H
#define dgattack_H

/*
    DGAttack class decleration
    (c) 2003 root-1 Software
*/

struct DGAttack
{
    DGAttack();
    DGAttack(char* atName, int atType, int atPow, int atDraw, bool atIsTeam, char atStatus);

    char* Name;		//attack's name
    int Type;		//attack's type
    int Pow;		//multiplies attacker's AttackLv by this
    int Draw;		//draws this many of attacker's MP
    bool IsTeam;	//acts on entire team? T/F
    char Status;	//possibility of inflicting this status (ignores 'n')
};

//#include dgattack.cpp

#endif