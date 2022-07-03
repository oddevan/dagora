/*
    DGAttackHandle class implementation
    (c) 2003 root-1 Software
*/

#include "dgattack.h"

DGAttack::DGAttack()
{
    Name = "---empty---";
    Type = -1;
    Pow = -1;
    Draw = -1;
    IsTeam = false;
    Status = 'n';
}

DGAttack::DGAttack(char* atName, int atType, int atPow, int atDraw, bool atIsTeam, char atStatus)
{
    Name = atName;
    Type = atType;
    Pow = atPow;
    Draw = atDraw;
    IsTeam = atIsTeam;
    Status = atStatus;
}