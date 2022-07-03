#ifndef dgplayable_H
#define dgplayable_H

/*
    DGPlayable class decleration
    (c) 2003 root-1 Software
*/

#include "dgintelligence.h"
#include "dgplayableintel.h"
#include "dgcharacter.h"
#include "dgsummons.h"
#include "dgweapon.h"
#include <string.h>
//#include "dgdemi.h"
#include "dgclass.h"
#include "dgteam.h"

#define NUM_SUM 5

class DGCharacter;
class DGDemi;
class DGSummons;
class DGTeam;
class DGPlayableIntel;

class DGPlayable : public DGCharacter
{
    public:
        DGPlayable();
        DGPlayable(char* name,
                   int level,
                   int hp,
                   int mp,
                   int atk,
                   int def,
                   int mag,
                   int spd,
                   int acc,
                   int element,
                   const DGClass& jobclass,
                   const DGAttack& attack,
                   DGPlayableIntel* intel);
        DGPlayable(char* name,
                   int level,
                   int hp,
                   int maxhp,
                   int mp,
                   int maxmp,
                   int atk,
                   int def,
                   int mag,
                   int spd,
                   int acc,
                   int element,
                   const DGClass& jobclass,
                   const DGAttack& attack,
                   DGDemi* original,
                   DGPlayableIntel* intel);
        DGPlayable(const DGPlayable &playable);
        virtual ~DGPlayable();

        void SetTransform(DGPlayable* trans);
        void DeLinkTransform();	//sets myTransform = NULL
        bool Junction(DGSummons* summon);
        DGSummons* DeJunction(int ind);
        
        virtual bool IsFused() const;
        
        virtual DGCharacter* ChooseAndSummon(DGBattle* battle);
        virtual DGCharacter* Fuse(int ind);
        virtual DGCharacter* Defuse();
        virtual DGCharacter* Transform();
        
        virtual bool CanSummon() const { return (HasAbility(SUMMON) && (myNumSummons > 0)); }
        virtual bool CanTransform() const { return ((HasAbility(TRANSFORM)) && (myTransform != NULL)); }
        virtual bool CanFuse() const { return (HasAbility(FUSE) /*&& (Team()->NumDemi() > 0)*/); }
        
        DGPlayable* TransformLink() const { return myTransform; }
        DGDemi* FusionLink() const { return myOriginal; }
        virtual int NumSummons() const { return myNumSummons; }
        virtual DGCharacter* GetSummons(int ind) const;
	DGSummons* GetRealSummons(int ind) const
        {
            if ((ind >= 0) && (ind < myNumSummons)) return mySummons[ind];
            else return NULL;
        }
        DGPlayableIntel* GetPlayableIntel() const { return myPlayIntel; }
    
    private:
        DGPlayable* myTransform;
        DGDemi* myOriginal;
        int myNumSummons;
        DGSummons* mySummons[NUM_SUM];
        DGPlayableIntel* myPlayIntel;
};

//#include dgplayable.cpp

#endif
