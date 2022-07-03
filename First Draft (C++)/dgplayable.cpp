/*
    DGPlayable class implementation
    (c) 2003 root-1 Software
*/

#include "dgplayable.h"
#include "dgcharacter.h"
#include "dginit.h"
#include "dgweapon.h"
#include "dgintelligence.h"
#include "dgteam.h"
#include <iostream>
#include <iomanip>

extern const DGAttackHandle DGATK;
extern const DGItemHandle DGITM;
extern const DGTypeHandle DGTYP;

DGPlayable::DGPlayable()
 :  DGCharacter(),
    myNumSummons(0)
{
    myTransform = NULL;
    myOriginal = NULL;
}

DGPlayable::DGPlayable(char* name, int level, int hp, int mp, int atk, int def, int mag, int spd, int acc,
                       int element, const DGClass& jobclass, const DGAttack& attack, DGPlayableIntel* intel)
  : DGCharacter(name, level, hp, hp, mp, mp, atk, def, mag, spd, acc, element, jobclass, attack),
    myNumSummons(0)
{
    myTransform = NULL;
    myOriginal = NULL;
    
    myPlayIntel = intel->GetNewIntel(this);
    SetIntel(myPlayIntel);
}

DGPlayable::DGPlayable(char* name, int level, int hp, int maxhp, int mp, int maxmp, int atk,
                       int def, int mag, int spd, int acc, int element, const DGClass& jobclass,
                       const DGAttack& attack, DGDemi* original, DGPlayableIntel* intel)
  : DGCharacter(name, level, hp, maxhp, mp, maxmp, atk, def, mag, spd, acc, element, jobclass, attack),
    myNumSummons(0)
{
    myTransform = NULL;
    myOriginal = original;
    
    myPlayIntel = intel->GetNewIntel(this);
    SetIntel(myPlayIntel);
}

DGPlayable::DGPlayable(const DGPlayable &playable)
  : DGCharacter(playable),
    myNumSummons(0)
{
    if (playable.TransformLink() != NULL)
    {
        DGPlayable* newTransform = playable.TransformLink();
    	myTransform = new DGPlayable(newTransform->Name(),
                                     newTransform->Level(),
                                     newTransform->HP(),
                                     newTransform->MaxHP(),
                                     newTransform->MP(),
                                     newTransform->MaxMP(),
                                     newTransform->AttackLv(),
                                     newTransform->DefenseLv(),
                                     newTransform->MagicLv(),
                                     newTransform->SpeedLv(),
                                     newTransform->AccuracyLv(),
                                     newTransform->Element(),
                                     newTransform->GetClass(),
                                     newTransform->StandardAttack(),
                                     newTransform->FusionLink(),
                                     newTransform->GetPlayableIntel());
        myTransform->SetTransform(this);
    }
    else myTransform = NULL;
    
    myOriginal = playable.FusionLink();
    myPlayIntel = playable.GetPlayableIntel()->GetNewIntel(this);
    SetIntel(myPlayIntel);
    
    for (int k = 0; k < playable.NumSummons(); k++)
        Junction(new DGSummons(*(playable.GetRealSummons(k))));
}

DGPlayable::~DGPlayable()
{
    if (myTransform != NULL)
    {
        myTransform->DeLinkTransform();
        delete myTransform;
    }
    for (int k = 0; k < myNumSummons; k++)
        if (mySummons[k] != NULL) delete mySummons[k];
    delete myPlayIntel;
}

void DGPlayable::SetTransform(DGPlayable* trans)
{
    myTransform = trans;
}

void DGPlayable::DeLinkTransform()
{
    myTransform = NULL;
}

bool DGPlayable::Junction(DGSummons* summon)
{
    if (myNumSummons >= NUM_SUM) return false;
    
    mySummons[myNumSummons] = summon;
    myNumSummons++;
	summon->SetChar(this);
    return true;
}

DGSummons* DGPlayable::DeJunction(int ind)
{
    DGSummons* summon;
    
    summon = mySummons[ind];
    for (int k = 0; k < (myNumSummons - 1); k++)
        mySummons[k] = mySummons[k+1];
    myNumSummons--;
    return summon;
}

bool DGPlayable::IsFused() const
{
    return (myOriginal != NULL);
}

DGCharacter* DGPlayable::ChooseAndSummon(DGBattle* battle)
{
    return mySummons[myPlayIntel->ChooseSummons(battle)];
}

DGCharacter* DGPlayable::Fuse(int ind)
{
    if (Team()->GetDemi(ind) != NULL) return Team()->GetDemi(ind)->Fuse(this);
    else return this;
}

DGCharacter* DGPlayable::Defuse()
{
    if (myOriginal != NULL) return myOriginal->Defuse(this);
    else return this;
}

DGCharacter* DGPlayable::Transform()
{
    if (myTransform != NULL) return myTransform;
    else return this;
}

DGCharacter* DGPlayable::GetSummons(int ind) const
{
    return GetRealSummons(ind);
}