/*
    DGSummons class implementation
    (c) 2003 root-1 Software
*/

#include "dgsummons.h"
#include "dgcharacter.h"
#include "dginit.h"

extern const DGAttackHandle DGATK;

DGSummons::DGSummons()
 :  DGCharacter()
{
    myChar = NULL;
    mySumIntel = NULL;
}

DGSummons::DGSummons(char* name, int level, int hp, int maxhp, int mp, int maxmp, int atk, int def, int mag,
                     int spd, int acc, int element, const DGClass& jobclass, DGSummonsIntel* intel, int stdAtkInd)
 :  DGCharacter(name, level, hp, maxhp, mp, maxmp, atk, def, mag, spd, acc, element, jobclass, DGAttack())
{
    Learn(stdAtkInd);
    myChar = NULL;
    mySumIntel = intel->GetNewIntel(this);
    SetIntel(mySumIntel);
}

DGSummons::DGSummons(const DGSummons &summons)
 :  DGCharacter(summons)
{
    Learn(summons.GetAttack(0));
    myChar = summons.LinkedChar();
    mySumIntel = summons.GetSummonsIntel()->GetNewIntel(this);
    SetIntel(mySumIntel);
}

DGSummons::~DGSummons()
{
    delete mySumIntel;
}
    
bool DGSummons::StartTurn()
{
    if (MP() < DGATK.Draw(GetAttack(0))) return false;
    return DGCharacter::StartTurn();
}

DGCharacter* DGSummons::EndTurn()
{
    if ((MP() < DGATK.Draw(GetAttack(0))) || (!this->IsAlive())) return Return();
    else return DGCharacter::EndTurn();
}

DGCharacter* DGSummons::Return()
{
    MPUp(MaxMP());
    if (IsAlive()) ChangeStatus('n');
    return myChar;
}

void DGSummons::SetChar(DGPlayable* summoner)
{
    myChar = summoner;
	SetTeam(summoner->Team());
}