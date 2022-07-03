#ifndef dgcharacter_H
#define dgcharacter_H

/*
    DGCharacter class decleration
    (c) 2003 root-1 Software
*/

#include <string.h>
#include "dgattack.h"
#include "dgcommand.h"
#include "dgintelligence.h"
#include "dgweapon.h"
#include "dgclass.h"
#include "dgclassleveldata.h"
//#include "dgteam.h"

#define NUM_ATK 25
#define NUM_WEAPONS 4
#define NUM_ABILITIES 3
#define ATK_WEP_IND 0
#define DEF_WEP_IND 1
#define XP_LV 50
#define RUSH_RATIO 0.2

class DGTeam;
class DGBattle;

class DGCharacter
{

//Please note that DGCharacter is intended to be a superclass for DGPlayable, DGDemi, and DGSummons.

    public:
        //constructors
        DGCharacter();
        DGCharacter(char* name,
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
                    const DGAttack& attack);
        DGCharacter(const DGCharacter &character);
        virtual ~DGCharacter();

        //modifiers
        void HPUp(int value);
        void HPDown(int value);
        void MPUp(int value);
        void MPDown(int value);
        void XPUp(int value);
        void Revive();
        void ChangeStatus(char stat);
        void LevelUp();
        void SetTeam(DGTeam* newTeam);
        bool Equip(const DGWeapon &newbie);
        DGWeapon Dequip(int slot);
        bool Learn(int atkInd);
        bool Learn(DGCommand ability);
        int Forget(int ind);
        void ClassLevelUp();
        void ClassLevelDown();
        
        //info functions
        bool IsAlive() const;
        virtual bool IsFused() const;
        virtual int NormalAtkPow(int type, int pow) const;
        virtual int MagicAtkPow(int type, int pow) const;
        virtual int DefPow(int type) const;
        virtual bool HasAbility(DGCommand ability) const;
        void PrintAttacks() const;
        int GetRushInd() const;
        
        //battle functions
        DGCommand ChooseCommand(DGBattle* battle) const { return myIntel->ChooseCommand(battle); }
        int ChooseAttack(DGBattle* battle) const { return myIntel->ChooseAttack(battle); }
        int ChooseAttackVictim(DGBattle* battle, bool isTeam) const { return myIntel->ChooseAttackVictim(battle, isTeam); }
        int ChooseAttackVictim(DGBattle* battle, int atkInd) const { return myIntel->ChooseAttackVictim(battle, atkInd); }
        int ChooseItem(DGBattle* battle) const { return myIntel->ChooseItem(battle); }
        int ChooseItemVictim(DGBattle* battle, int itmInd) const { return myIntel->ChooseItemVictim(battle, itmInd); }
        int ChooseDemi(DGBattle* battle) const { return myIntel->ChooseDemi(battle); }
        
        virtual bool StartTurn(); //returns true if player can have a turn
        virtual DGCharacter* EndTurn();
        
        virtual DGCharacter* ChooseAndSummon(DGBattle* battle) { return this; }
        virtual DGCharacter* Return() { return this; }
        virtual DGCharacter* Fuse(int ind) { return this; }
        virtual DGCharacter* Defuse() { return this; }
        virtual DGCharacter* Transform() { return this; }
        
        //Command functions - most characters cannot do these, but there are those who can.
        virtual bool CanSummon() const { return false; }
        virtual bool CanTransform() const { return false; }
        virtual bool CanFuse() const { return false; }
        
        //Adjusted stats: using these is preferable to the below
        virtual int Atk() const;
        virtual int Def() const;
        virtual int Mag() const;
        virtual int Spd() const;
        virtual int Acc() const;
        
		//These functions are incredibly bad programming, but they're still here!
		//I hate their very existance, yet they are incredibly necessary!
		virtual int NumSummons() const { return 0; }
		virtual DGCharacter* GetSummons(int ind) const { return NULL; }

        //accessor functions
        char* Name() const { return myName; }
        int Level() const { return myLevel; }
        char Status() const { return myStatus; }
        bool InRush() const { return myInRush; }
        int HP() const { return myHP; }
        int MP() const { return myMP; }
        int AttackLv() const { return myAttackLv; }
        int DefenseLv() const { return myDefenseLv; }
        int MagicLv() const { return myMagicLv; }
        int SpeedLv() const { return mySpeedLv; }
        int AccuracyLv() const { return myAccuracyLv; }
        int MaxHP() const { return myMaxHP; }
        int MaxMP() const { return myMaxMP; }
        int LvUp() const { return myLvUp; }
        int Element() const { return myElement; }
        DGIntelligence* GetIntel() const { return myIntel; }
        DGTeam* Team() const { return myTeam; }
        int NumWeapons() const { return myNumWeapons; }
        DGWeapon GetWeapon(int ind) const
        {
            if ((ind >= 0) && (ind < NUM_WEAPONS)) return myWeapons[ind];
            else return DGWeapon();
        }
        int NumAttacks() const { return myNumAttacks; }
        int GetAttack(int ind) const
        {
            if ((ind >= 0) && (ind < myNumAttacks)) return myAttacks[ind];
            else return -1;
        }
        int NumAbilities() const { return myNumAbilities; }
        DGCommand GetAbility(int ind) const
        {
            if ((ind >= 0) && (ind < myNumAbilities)) return myAbilities[ind];
            else return ATTACK;
        }
        DGClass GetClass() const { return myClass; }
        DGAttack StandardAttack() const { return myStandardAttack; }
    
    protected:
    	void SetIntel(DGIntelligence* intel) { myIntel = intel; }
        //used by inheritance constructors to set myIntel
    
    private:
        void EnterRush();
        void ExitRush();
        bool CheckRush();
    
        char* myName;
        int myLevel;
        char myStatus;
        bool myInRush;
        int myHP;
        int myMP;
        int myAttackLv;
        int myDefenseLv;
        int myMagicLv;
        int mySpeedLv;
        int myAccuracyLv;
        int myMaxHP;
        int myMaxMP;
        int myLvUp;
        int myElement;
        DGIntelligence* myIntel;
        DGTeam* myTeam;
        int myNumWeapons;
        DGWeapon myWeapons[NUM_WEAPONS];
        int myNumAttacks;
        int myAttacks[NUM_ATK];
        int myNumAbilities;
        DGCommand myAbilities[NUM_ABILITIES];
        DGClass myClass;
        DGAttack myStandardAttack;
};

//#include "dgcharacter.cpp"

#endif