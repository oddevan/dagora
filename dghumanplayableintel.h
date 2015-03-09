#ifndef dghumanplayableintel_H
#define dghumanplayableintel_H

/*
    dghumanplayableintel class decleration
    (c) 2003 root-1 Software
*/

#include "dgintelligence.h"
#include "dgplayableintel.h"
#include "dgbattle.h"

class DGHumanPlayableIntel : public DGPlayableIntel
{
    public:
        DGHumanPlayableIntel();
        DGHumanPlayableIntel(DGPlayable* mine);
        
	virtual DGPlayableIntel* GetNewIntel(DGPlayable* mine) const { return new DGHumanPlayableIntel(mine); }

        virtual DGCommand ChooseCommand(DGBattle* battle) const;
        virtual int ChooseAttack(DGBattle* battle) const;
        virtual int ChooseAttackVictim(DGBattle* battle, bool isTeam) const;
        virtual int ChooseAttackVictim(DGBattle* battle, int atkInd) const;
        virtual int ChooseItem(DGBattle* battle) const;
        virtual int ChooseItemVictim(DGBattle* battle, int itmInd) const;
        virtual int ChooseDemi(DGBattle* battle) const;
        virtual int ChooseSummons(DGBattle* battle) const;
    
    private:
        int DispVictims(DGBattle* battle) const;
};

//#include dghumanplayableintel.cpp

#endif