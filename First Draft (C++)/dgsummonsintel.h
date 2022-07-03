#ifndef dgsummonsintel_H
#define dgsummonsintel_H

/*
    dgsummonsintel class decleration
    (c) 2003 root-1 Software
*/

#include "dgintelligence.h"
#include "dgsummons.h"
#include "dgbattle.h"

class DGSummons;

class DGSummonsIntel : public DGIntelligence
{
    public:
        DGSummonsIntel() { myChar = NULL; }
        DGSummonsIntel(DGSummons* mine) { myChar = mine; }
        
	virtual DGSummonsIntel* GetNewIntel(DGSummons* mine) const = 0;
        void SetChar(DGSummons* mine) { myChar = mine; }
        
        virtual DGCommand ChooseCommand(DGBattle* battle) const = 0;
        virtual int ChooseAttack(DGBattle* battle) const = 0;
        virtual int ChooseAttackVictim(DGBattle* battle, bool isTeam) const = 0;
        virtual int ChooseAttackVictim(DGBattle* battle, int atkInd) const = 0;
        
        //Summons can't do these things!
        virtual int ChooseItem(DGBattle* battle) const { return -1; }
        virtual int ChooseItemVictim(DGBattle* battle, int itmInd) const { return -1; }
        virtual int ChooseDemi(DGBattle* battle) const { return -1; }
        virtual int ChooseSummons(DGBattle* battle) const { return -1; }
    
    protected:
        DGSummons* myChar;
};

//#include dgsummonsintel.cpp

#endif