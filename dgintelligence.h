#ifndef dgintelligence_H
#define dgintelligence_H

/*
    DGIntelligence class decleration
    (c) 2003 root-1 Software
*/

#include "dgcommand.h"

class DGCharacter;
class DGBattle;

class DGIntelligence
{
    public:
        DGIntelligence() { /*nothing*/ }
        
        virtual DGCommand ChooseCommand(DGBattle* battle) const = 0;
        virtual int ChooseAttack(DGBattle* battle) const = 0;
        virtual int ChooseAttackVictim(DGBattle* battle, bool isTeam) const = 0;
        virtual int ChooseAttackVictim(DGBattle* battle, int atkInd) const = 0;
        virtual int ChooseItem(DGBattle* battle) const = 0;
        virtual int ChooseItemVictim(DGBattle* battle, int itmInd) const = 0;
        virtual int ChooseDemi(DGBattle* battle) const = 0;
        virtual int ChooseSummons(DGBattle* battle) const = 0;
    
    private:

};

//#include dgintelligence.cpp

#endif