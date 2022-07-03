/*
    DGAttackHandle class implementation
    (c) 2003 root-1 Software
*/

#include "dgattackhandle.h"
#include "dgattack.h"
#include "dgplayable.h"
#include "dgbattle.h"
#include "dgcharacter.h"
#include "dginit.h"
//#include "dgteam.h"

extern const DGAttackHandle DGATK;
extern const DGItemHandle DGITM;
extern const DGTypeHandle DGTYP;

const double CHANCE_OF_CRIT_HIT = 0.1;
const double CHANCE_OF_STAT_CHANGE = 0.25;

// Constructor: initializes attack database
DGAttackHandle::DGAttackHandle()
{
    //cout << "Initializing Attacks... ";
        myAttacks[0]  = DGAttack("Slash", 	1,  3,  2, false, 'n');
        myAttacks[1]  = DGAttack("QuickAtack", 	10, 1,  2, false, 'n');
        myAttacks[2]  = DGAttack("Wind Blade", 	10, 4,  0, true, 'n');
        myAttacks[3]  = DGAttack("Heal", 	5,  1,  -1, false, 'n');
        myAttacks[4]  = DGAttack("Esuna", 	5,  0,  3, false, 'n');
        myAttacks[5]  = DGAttack("Fireworks", 	5,  2,  3, false, 'n');
        myAttacks[6]  = DGAttack("Permeate",	5,  4,  0, false, 'n');
        myAttacks[7]  = DGAttack("Elven Eye",	4,  1,  1, false, 'n');
        myAttacks[8]  = DGAttack("Lullaby",	0,  0,  3, true, 's');
        myAttacks[9]  = DGAttack("TripleShot",	4,  4,  0, false, 'n');
        myAttacks[10] = DGAttack("Beatdown", 	0,  2,  2, false, 'n');
        myAttacks[11] = DGAttack("DragonRage",	9,  4,  0, true, 'n');
        myAttacks[12] = DGAttack("Smoke Bomb",	9,  1,  10, true, 'p');
        myAttacks[13] = DGAttack("Restore", 	5,  0,  7, true, 'n');
        myAttacks[14] = DGAttack("Combust", 	5,  4,  0, false, 'n');
        myAttacks[15] = DGAttack("Infection", 	6,  2,  3, false, 'p');
        myAttacks[16] = DGAttack("Bind", 	6,  2,  3, false, 'n');
        myAttacks[17] = DGAttack("Illusion",	6,  1,  7, true, 'n');
        myAttacks[18] = DGAttack("Reaper", 	6,  4,  0, true, 'n');
        myAttacks[19] = DGAttack("New Attack", 	0,  0,  0, false, 'n');
    //cout << "done" << endl;
}

int DGAttackHandle::Exe(DGCharacter* attacking, DGCharacter* defending, int ind, DGBattle* battle) const
{
    switch (ind)
    {
    case 3:
        return Heal(attacking, defending);
    case 4:
        return Esuna(attacking, defending);
    case 13:
        return Restore(attacking, defending->Team(), battle);
    case 14:
        return Combust(attacking, defending->Team(), battle);
    default:
        return Normal(attacking, defending, battle, myAttacks[ind]);
    }
}

int DGAttackHandle::ExeStdAtk(DGCharacter* attacking, DGCharacter* defending) const
{
    return Normal(attacking, defending, NULL, attacking->StandardAttack());
}

int DGAttackHandle::Normal(DGCharacter* attacking, DGCharacter* defending, DGBattle* battle, DGAttack attack) const
{
    attacking->MPDown(attack.Draw);
    if (attack.IsTeam) return NormalTeam(attacking, defending->Team(), battle, attack);
    
    double hitProb = double(attacking->Acc()) / double(defending->Spd());
    if (DGRandomDouble() >= hitProb)
    {
        cout << "Attack missed!" << endl;
        return 0;
    }
    
    int atkPow, defPow, totDamage, hpBefore;
    bool isNegDamage;
    
    atkPow = attacking->Level() * attacking->NormalAtkPow(attack.Type, attack.Pow);
    defPow = defending->DefPow(attack.Type);
    hpBefore = defending->HP();
    
    if (atkPow > 0)
    {
        isNegDamage = (defPow < 0);
        if (DGRandomDouble() <= CHANCE_OF_CRIT_HIT)
        {
            defPow = 0;
            cout << "Critical hit!" << endl;
        }
        totDamage = atkPow - defPow;
        if (isNegDamage)
        {
            defending->HPUp(totDamage);
            cout << defending->Name() << " gained " << (defending->HP() - hpBefore) << " HP." << endl;
        }
        else
        {
            defending->HPDown(totDamage);
            cout << defending->Name() << " took " << (hpBefore - defending->HP()) << " damage." << endl;
        }
    }
    
    if (attack.Status != 'n')
    {
        if (DGRandomDouble() <= CHANCE_OF_STAT_CHANGE)
        {
            defending->ChangeStatus(attack.Status);
            switch (attack.Status)
            {
            case 'p':
                cout << defending->Name() << " was poisoned." << endl;
                break;
            case 's':
                cout << defending->Name() << " fell asleep." << endl;
                break;
            default:
                break;
            }
        }
    }
    return (hpBefore - defending->HP());
}

int DGAttackHandle::NormalTeam(DGCharacter* attacking, DGTeam* defendingTeam, DGBattle* battle, DGAttack attack) const
{
    DGCharacter* defending;
    int atkPow, defPow, totDamage, hpBefore, totHPLost = 0;
    double hitProb;
    bool isNegDamage;
    
    atkPow = attacking->Level() * attacking->NormalAtkPow(attack.Type, attack.Pow);
    
    for (int k = 0; k < battle->NumPlayers(); k++)
    {
        defending = battle->GetFromQueue(k);
        
        if ((defending->IsAlive()) && (defending->Team() == defendingTeam))
        {
            hitProb = double(attacking->Acc()) / double(defending->Spd());
            if (DGRandomDouble() >= hitProb)
            {
                cout << "Attack missed " << defending->Name() << "!" << endl;
                return 0;
            }
            
            defPow = defending->DefPow(attack.Type);
            hpBefore = defending->HP();
            
            isNegDamage = (defPow < 0);
            if (DGRandomDouble() <= CHANCE_OF_CRIT_HIT)
            {
                defPow = 1;
                cout << "Critical hit!" << endl;
            }
            totDamage = atkPow - defPow;
            if (isNegDamage)
            {
                defending->HPUp(totDamage);
                cout << defending->Name() << " gained " << (defending->HP() - hpBefore) << " HP." << endl;
            }
            else
            {
                defending->HPDown(totDamage);
                cout << defending->Name() << " took " << (hpBefore - defending->HP()) << " damage." << endl;
            }
            totHPLost += (hpBefore - defending->HP());
            
            if (attack.Status != 'n')
            {
                if (DGRandomDouble() <= CHANCE_OF_STAT_CHANGE)
                {
                    defending->ChangeStatus(attack.Status);
                    switch (attack.Status)
                    {
                    case 'p':
                        cout << defending->Name() << " was poisoned." << endl;
                        break;
                    case 's':
                        cout << defending->Name() << " fell asleep." << endl;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
    return totHPLost;
}

int DGAttackHandle::Heal(DGCharacter* attacking, DGCharacter* defending) const
{
    int atkPow = attacking->MagicAtkPow(1, 5);
    int hpBefore = defending->HP();
    defending->HPUp(atkPow);
    attacking->MPDown(atkPow / 4);
    cout << defending->Name() << " gained " << (defending->HP() - hpBefore) << " HP." << endl;
    cout << attacking->Name() << " lost " << (atkPow / 4) << " MP." << endl;
    return (defending->HP() - hpBefore);
}

int DGAttackHandle::Esuna(DGCharacter* attacking, DGCharacter* defending) const
{
    attacking->MPDown(3);
    defending->ChangeStatus('n');
    cout << defending->Name() << "'s health returned." << endl;
    return 5 * attacking->Level();
}

int DGAttackHandle::Restore(DGCharacter* attacking, DGTeam* defendingTeam, DGBattle* battle) const
{
    attacking->MPDown(7);
    
    DGCharacter* defending;
    int hpBefore, totHPLost = 0;
    
    for (int k = 0; k < battle->NumPlayers(); k++)
    {
        defending = battle->GetFromQueue(k);
        if ((defending->IsAlive()) && (defending->Team() == defendingTeam))
        {
            hpBefore = defending->HP();
            defending->HPUp(30);
            cout << defending->Name() << " gained " << (defending->HP() - hpBefore) << " HP." << endl;
            if (defending->Status() != 'n')
            {
                defending->ChangeStatus('n');
                cout << defending->Name() << "'s health returned." << endl;
            }
            totHPLost += (defending->HP() - hpBefore);
        }
    }
    return totHPLost;
}

int DGAttackHandle::Combust(DGCharacter* attacking, DGTeam* defendingTeam, DGBattle* battle) const
{
    cout << attacking->Name() << " blew up!" << endl;
    attacking->HPDown(attacking->HP());
    return NormalTeam(attacking, defendingTeam, battle, myAttacks[14]);
}