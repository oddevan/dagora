#ifndef dghumansummonsintel_H
#define dghumansummonsintel_H

/*
    DGHumanSummonsIntel class decleration
    (c) 2003 root-1 Software
*/

#include "dgintelligence.h"
#include "dgsummonsintel.h"
#include "dgbattle.h"

class DGHumanSummonsIntel : public DGSummonsIntel
{
    public:
        DGHumanSummonsIntel();
        DGHumanSummonsIntel(DGSummons* mine);
        
	virtual DGSummonsIntel* GetNewIntel(DGSummons* mine) const { return new DGHumanSummonsIntel(mine); }

        virtual DGCommand ChooseCommand(DGBattle* battle) const;
        virtual int ChooseAttack(DGBattle* battle) const;
        virtual int ChooseAttackVictim(DGBattle* battle, bool isTeam) const;
        virtual int ChooseAttackVictim(DGBattle* battle, int atkInd) const;
    
    private:
        int DispVictims(DGBattle* battle) const;
        
};
//#include dghumansummonsintel.cpp

#endif