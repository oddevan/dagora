#ifndef dgattackhandle_H
#define dgattackhandle_H

/*
    DGAttackHandle class decleration
    (c) 2003 root-1 Software
*/

#include "dgattack.h"
#include "dgcharacter.h"

#define TOT_NUM_ATK 20

struct DGAttack;

class DGAttackHandle
{
    public:
        DGAttackHandle();
        
        char* Name(int ind) const
        {
            if ((ind < TOT_NUM_ATK) && (ind >= 0)) return myAttacks[ind].Name;
            else return "---empty---";
        }
        int Type(int ind) const
        {
            if ((ind < TOT_NUM_ATK) && (ind >= 0)) return myAttacks[ind].Type;
            else return -1;
        }
        int Pow(int ind) const
        {
            if ((ind < TOT_NUM_ATK) && (ind >= 0)) return myAttacks[ind].Pow;
            else return -1;
        }
        int Draw(int ind) const
        {
            if ((ind < TOT_NUM_ATK) && (ind >= 0)) return myAttacks[ind].Draw;
            else return -1;
        }
        bool IsTeam(int ind) const
        {
            if ((ind < TOT_NUM_ATK) && (ind >= 0)) return myAttacks[ind].IsTeam;
            else return false;
        }
        char Status(int ind) const
        {
            if ((ind < TOT_NUM_ATK) && (ind >= 0)) return myAttacks[ind].Status;
            else return 'n';
        }
        DGAttack GetAttack(int ind) const
        {
            if ((ind < TOT_NUM_ATK) && (ind >= 0)) return myAttacks[ind];
            else return DGAttack();
        }
        
        int Exe(DGCharacter* attacking, DGCharacter* defending, int ind, DGBattle* battle) const;
        //precondition: attacking has enough MP; ind is legal index
        int ExeStdAtk(DGCharacter* attacking, DGCharacter* defending) const;
        //both return damage done
    
    private:
        int Normal(DGCharacter* attacking, DGCharacter* defending, DGBattle* battle, DGAttack attack) const;
        int NormalTeam(DGCharacter* attacking, DGTeam* defendingTeam, DGBattle* battle, DGAttack attack) const;
        int Heal(DGCharacter* attacking, DGCharacter* defending) const;
        int Esuna(DGCharacter* attacking, DGCharacter* defending) const;
        int Restore(DGCharacter* attacking, DGTeam* defendingTeam, DGBattle* battle) const;
        int Combust(DGCharacter* attacking, DGTeam* defendingTeam, DGBattle* battle) const;
        DGAttack myAttacks[TOT_NUM_ATK];
};

//#include dgattackhandle.cpp

#endif