/*
    DGDemi class implementation
    (c) 2003 root-1 Software
*/

//#include "dgdemi.h"
#include "dgcharacter.h"
#include "dgplayable.h"
#include "dgweapon.h"
#include "dginit.h"
#include <string.h>
#include <math.h>

extern const DGAttackHandle DGATK;
extern const DGItemHandle DGITM;
extern const DGTypeHandle DGTYP;

DGDemi::DGDemi()
  : DGCharacter(),
    myAppendName("---empty---"),
    hybridStartXP(0)
{
    myFused = NULL;
}

DGDemi::DGDemi(char* name, char* appendName, int level, int hp, int maxhp, int mp, int maxmp, int atk,
               int def, int mag, int spd, int acc, int element, const DGClass& jobclass, const DGAttack& attack)
  : DGCharacter(name, level, hp, maxhp, mp, maxmp, atk, def, mag, spd, acc, element, jobclass, attack),
    myAppendName(appendName),
    hybridStartXP(0)
{
    myFused = NULL;
}

DGDemi::DGDemi(const DGDemi &demi)
  : DGCharacter(demi),
    myAppendName(demi.AppendName()),
    hybridStartXP(demi.StartingXP())
{
    if (demi.IsFused()) myFused = new DGPlayable(*(demi.FusionLink()));
    else myFused = NULL;
}

DGDemi::~DGDemi()
{
    if (myFused != NULL) delete myFused;
}
        
DGPlayable* DGDemi::Fuse(DGPlayable* original) //returns new character, myFused = original
{
    int k;
    if (original == NULL) return NULL;
    
    myFused = original;
    char* newName = /*myAppendName + */original->Name();
    int newLevel = (Level() / 2) + original->Level();
    
    hybridStartXP = XP_LV * (newLevel + 1);
    // find starting number of XP (to be used in Defuse)
    
    DGPlayable* fused = new DGPlayable(newName,
                                       newLevel,
                                       ((HP() / 2) + original->HP()),
                                       ((MaxHP() / 2) + original->MaxHP()),
                                       ((MP() / 2) + original->MP()),
                                       ((MaxMP() / 2) + original->MaxMP()),
                                       ((AttackLv() / 2) + original->AttackLv()),
                                       ((DefenseLv() / 2) + original->DefenseLv()),
                                       ((MagicLv() / 2) + original->MagicLv()),
                                       ((SpeedLv() / 2) + original->SpeedLv()),
                                       ((AccuracyLv() / 2) + original->AccuracyLv()),
                                       Element(),
                                       original->GetClass(),
                                       original->StandardAttack(),
                                       this,
                                       original->GetPlayableIntel());
    fused->SetTeam(original->Team());
    for (k = 0; k < NUM_WEAPONS; k++)
        fused->Equip(original->GetWeapon(k));
    for (k = 0; k < original->NumAttacks(); k++)
        fused->Learn(original->GetAttack(k));
    for (k = 0; k < this->NumAttacks(); k++)
        fused->Learn(this->GetAttack(k));
    for (k = 0; k < original->NumAbilities(); k++)
        fused->Learn(original->GetAbility(k));
    for (k = 0; k < this->NumAbilities(); k++)
        fused->Learn(this->GetAbility(k));
    for (k = 0; k < original->NumSummons(); k++)
        fused->Junction(original->GetRealSummons(k));
    
    return fused;
}

DGPlayable* DGDemi::Defuse(DGPlayable* hybrid) //returns myFused, deletes hybrid
{
    if (myFused == NULL) return NULL;
    
    //restore myFused HP/MP
    myFused->HPUp(myFused->MaxHP());
    myFused->MPUp(myFused->MaxMP());
    
    //restore this HP/MP
    HPUp(MaxHP());
    MPUp(MaxMP());
    
    int downHP = ((hybrid->MaxHP() - hybrid->HP()) / 2);
    int downMP = ((hybrid->MaxMP() - hybrid->MP()) / 2);
    
    myFused->HPDown(downHP);
    myFused->MPDown(downMP);
    HPDown(downHP);
    MPDown(downMP);
    
    int finishingXP = (50 * (hybrid->Level() + 1)) - hybrid->LvUp();
    myFused->XPUp(finishingXP); // don't /2 because I'm feeling generous. :-)
    XPUp(finishingXP);
    
    DGPlayable* temp = myFused;
    myFused = NULL;
    delete hybrid;
    
    return temp;
}
        
bool DGDemi::IsFused() const
{
    return (myFused != NULL);
}