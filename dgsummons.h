#ifndef dgsummons_H
#define dgsummons_H

/*
    DGSummons class decleration
    (c) 2003 root-1 Software
*/

/*
    A DGSummons is like a single-purpose character. They generally have only one attack that uses most, if not all,
    of their MP. The process is three-fold. A Playable summons the Summon, the Summon attacks, and then returns. At
    the end of the turn, if the Summons is out of MP, it automatically returns with no peanalty. When it returns, it
    automatically regains all MP.
*/

#include "dgcharacter.h"
#include "dgplayable.h"
#include "dgsummonsintel.h"

class DGPlayable;
class DGSummonsIntel;

class DGSummons : public DGCharacter
{
    public:
        DGSummons();
        DGSummons(char* name,
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
                  DGSummonsIntel* intel,
                  int stdAtkInd);
        DGSummons(const DGSummons &summons);
        virtual ~DGSummons();
    
        virtual bool StartTurn(); //returns true if player can have a turn
        virtual DGCharacter* EndTurn();
        
        virtual DGCharacter* ChooseAndSummon(DGBattle* battle) { return this; }
        virtual DGCharacter* Return();
        
        void SetChar(DGPlayable* summoner);
        
        DGPlayable* LinkedChar() const { return myChar; }
        DGSummonsIntel* GetSummonsIntel() const { return mySumIntel; }
        
    private:
        DGPlayable* myChar;
        DGSummonsIntel* mySumIntel;
};

//#include dgsummons.cpp

#endif