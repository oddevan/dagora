#ifndef dgplayableintel_H
#define dgplayableintel_H

/*
    dgplayableintel class decleration
    (c) 2003 root-1 Software
*/

#include "dgintelligence.h"
#include "dgplayable.h"
#include "dgcommand.h"

class DGPlayable;

class DGPlayableIntel : public DGIntelligence
{
    public:
        DGPlayableIntel() { myChar = NULL; }
        DGPlayableIntel(DGPlayable* mine) { myChar = mine; }

        virtual DGPlayableIntel* GetNewIntel(DGPlayable* mine) const = 0; 
        void SetChar(DGPlayable* mine) { myChar = mine; }
        
        virtual DGCommand ChooseCommand(DGBattle* battle) const = 0;
        virtual int ChooseAttack(DGBattle* battle) const = 0;
        virtual int ChooseAttackVictim(DGBattle* battle, bool isTeam) const = 0;
        virtual int ChooseAttackVictim(DGBattle* battle, int atkInd) const = 0;
        virtual int ChooseItem(DGBattle* battle) const = 0;
        virtual int ChooseItemVictim(DGBattle* battle, int itmInd) const = 0;
        virtual int ChooseDemi(DGBattle* battle) const = 0;
        virtual int ChooseSummons(DGBattle* battle) const = 0;
    
    protected:
        DGPlayable* myChar;
};

//#include dgplayableintel.cpp

#endif