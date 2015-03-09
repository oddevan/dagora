/*
    DGCharacter class implementation
    (c) 2003 root-1 Software
*/

#include "dgcharacter.h"
#include "dginit.h"
#include "dgweapon.h"
#include <string.h>
#include <iostream.h>
#include <iomanip.h>

extern const DGAttackHandle DGATK;
extern const DGItemHandle DGITM;
extern const DGTypeHandle DGTYP;

DGCharacter::DGCharacter()
 :  myName("---empty---"),
    myLevel(-1),
    myStatus('k'),
    myInRush(false),
    myHP(-1),
    myMP(-1),
    myAttackLv(-1),
    myDefenseLv(-1),
    myMagicLv(-1),
    mySpeedLv(-1),
    myAccuracyLv(-1),
    myMaxHP(-1),
    myMaxMP(-1),
    myLvUp(-1),
    myElement(0),
    myNumWeapons(0),
    myNumAttacks(0),
    myNumAbilities(0),
    myClass(),
    myStandardAttack()
{
    myIntel = NULL;
    myTeam = NULL;
}

DGCharacter::DGCharacter(char* name, int level, int hp, int maxhp, int mp, int maxmp, int atk, int def, int mag,
                         int spd, int acc, int element, const DGClass& jobclass, const DGAttack& attack)
 :  myName(name),
    myLevel(level),
    myStatus('n'),
    myInRush(false),
    myHP(hp),
    myMP(mp),
    myAttackLv(atk),
    myDefenseLv(def),
    myMagicLv(mag),
    mySpeedLv(spd),
    myAccuracyLv(acc),
    myMaxHP(maxhp),
    myMaxMP(maxmp),
    myLvUp(XP_LV * level),
    myElement(element),
    myNumWeapons(0),
    myNumAttacks(0),
    myNumAbilities(0),
    myClass(jobclass),
    myStandardAttack(attack)
{
    myTeam = NULL;
    myIntel = NULL;
}

DGCharacter::DGCharacter(const DGCharacter &character)
 :  myName(character.Name()),
    myLevel(character.Level()),
    myStatus(character.Status()),
    myInRush(character.InRush()),
    myHP(character.HP()),
    myMP(character.MP()),
    myAttackLv(character.AttackLv()),
    myDefenseLv(character.DefenseLv()),
    myMagicLv(character.MagicLv()),
    mySpeedLv(character.SpeedLv()),
    myAccuracyLv(character.AccuracyLv()),
    myMaxHP(character.MaxHP()),
    myMaxMP(character.MaxMP()),
    myLvUp(character.LvUp()),
    myElement(character.Element()),
    myNumWeapons(0),
    myNumAttacks(0),
    myNumAbilities(0),
    myClass(character.GetClass()),
    myStandardAttack(character.StandardAttack())
{
    int k;
    
    myTeam = character.Team();
    
    for (k = 0; k < NUM_WEAPONS; k++)
        Equip(character.GetWeapon(k));
    for (k = 0; k < character.NumAttacks(); k++)
        Learn(character.GetAttack(k));
    for (k = 0; k < character.NumAbilities(); k++)
        Learn(character.GetAbility(k));
}

DGCharacter::~DGCharacter()
{
}

void DGCharacter::HPUp(int value)
{
    myHP += value;
    if (myHP > myMaxHP) myHP = myMaxHP;
    
    if (myInRush) if (!CheckRush()) ExitRush();
        
//    cout << myName << "'s HP: " << myHP << "/" << myMaxHP << endl;
}

void DGCharacter::HPDown(int value)
{
    myHP -= value;
    if (myHP <= 0)
    {
        myStatus = 'k';
        myHP = 0;
        cout << myName << " fell." << endl;
        if (myInRush) ExitRush();
    }
    else if (!myInRush)
    {
        if (CheckRush()) EnterRush();
    }
//    else cout << myName << "'s HP: " << myHP << "/" << myMaxHP << endl;
}

void DGCharacter::MPUp(int value)
{
    myMP += value;
    if (myMP > myMaxMP) myMP = myMaxMP;
//    cout << myName << "'s MP: " << myMP << "/" << myMaxMP << endl;
}

void DGCharacter::MPDown(int value)
{
    myMP -= value;
    if (myMP < 0) myMP = 0;
//    cout << myName << "'s MP: " << myMP << "/" << myMaxMP << endl;
}

void DGCharacter::XPUp(int value)
{
    myLvUp -= value;
    while (myLvUp <= 0) LevelUp();
//    cout << myName << "'s XP to level " << myLevel+1 << ": " << myLvUp << endl;
}

void DGCharacter::Revive()
{
    myStatus = 'n';
    myHP = 1;
    EnterRush();
//    cout << myName << "'s HP: " << myHP << "/" << myMaxHP << endl;
}

void DGCharacter::ChangeStatus(char stat)
{
    if ((stat == 'n') || (stat == 'p') || (stat == 's')) myStatus = stat;
//    cout << myName << "'s status: " << myStatus << endl;
}

void DGCharacter::LevelUp()
{
/*  XP works on a negative basis. If myLvUp < 0, then the character has enough XP to
    level up. After the stats are increased, myLvUp is increased by XP_LV*myLevel. Thus,
    myLvUp is not how many XP the character has, but _how many XP the character needs
    to level up_. Keep this in mind! */
    
    const double STAT_INCREASE = 0.25;
    
    if (myLvUp > 0) return;
    
    myAttackLv += DGRoundDouble(double(myAttackLv) * STAT_INCREASE);
    myDefenseLv += DGRoundDouble(double(myDefenseLv) * STAT_INCREASE);
    myMagicLv += DGRoundDouble(double(myMagicLv) * STAT_INCREASE);
    mySpeedLv += DGRoundDouble(double(mySpeedLv) * STAT_INCREASE);
    myAccuracyLv += DGRoundDouble(double(myAccuracyLv) * STAT_INCREASE);
    
    int plusme = DGRoundDouble(double(myMaxHP) * STAT_INCREASE);
    myMaxHP += plusme;
    myHP += plusme;
    plusme = DGRoundDouble(double(myMaxMP) * STAT_INCREASE);
    myMaxMP += plusme;
    myMP += plusme;
    
    myStatus = 'n';
    myLevel++;
    myLvUp += myLevel*XP_LV;
    
    cout << myName << " grew to level " << myLevel << endl;
    
    myClass.SPUp(this);
}

void DGCharacter::SetTeam(DGTeam* newTeam)
{
    myTeam = newTeam;
}

bool DGCharacter::Equip(const DGWeapon &newbie)
{
    int slot = -1;
    
    for (int k = 0; k < NUM_ATK; k++)
    {
        if (!myWeapons[k].Defined)
        {
            slot = k;
            break;
        }
    }
    if (slot == -1) return false;
    
    if (newbie.Type == ATK_WEP_IND)
    {
        if (!(myWeapons[ATK_WEP_IND].Defined))
        {
            myWeapons[ATK_WEP_IND] = newbie;
            myNumWeapons++;
        }
        else return false;
    }
    else if (newbie.Type == DEF_WEP_IND)
    {
        if (!(myWeapons[DEF_WEP_IND].Defined))
        {
            myWeapons[DEF_WEP_IND] = newbie;
            myNumWeapons++;
        }
        else return false;
    }
    else if ((slot != ATK_WEP_IND) && (slot != DEF_WEP_IND))
    {
        myWeapons[slot] = newbie;
        myNumWeapons++;
    }
    else return false;
    
    myHP += newbie.HPUp;
    myMaxHP += newbie.HPUp;
    myMP += newbie.MPUp;
    myMaxMP += newbie.MPUp;
    myAttackLv += newbie.AtkUp;
    myDefenseLv += newbie.DefUp;
    myMagicLv += newbie.MagUp;
    mySpeedLv += newbie.SpdUp;
    myAccuracyLv += newbie.AccUp;
    return true;
}

DGWeapon DGCharacter::Dequip(int slot)
{
    DGWeapon dequipped;
    
    if ((slot < 0) || (slot > NUM_ATK)) return DGWeapon();
    dequipped = myWeapons[slot];
    myWeapons[slot] = DGWeapon();
    myNumWeapons--;
    myHP -= dequipped.HPUp;
    myMaxHP -= dequipped.HPUp;
    myMP -= dequipped.MPUp;
    myMaxMP -= dequipped.MPUp;
    myAttackLv -= dequipped.AtkUp;
    myDefenseLv -= dequipped.DefUp;
    myMagicLv -= dequipped.MagUp;
    mySpeedLv -= dequipped.SpdUp;
    myAccuracyLv -= dequipped.AccUp;
    return dequipped;
}

bool DGCharacter::Learn(int atkInd)
{
    if (myNumAttacks == NUM_ATK) return false;
    
    myAttacks[myNumAttacks] = atkInd;
    myNumAttacks++;
    return true;
}

bool DGCharacter::Learn(DGCommand ability)
{
    if (myNumAbilities == NUM_ABILITIES) return false;
    
    myAbilities[myNumAbilities] = ability;
    myNumAbilities++;
    return true;
}

int DGCharacter::Forget(int ind)
{
    if (myNumAttacks == 0) return -1;
    
    int forgot = myAttacks[ind];
    
    for (int k = ind; k < (myNumAttacks - 1); k++)
        myAttacks[k] = myAttacks[k+1];
    myNumAttacks--;
    return forgot;
}

void DGCharacter::ClassLevelUp()
{
    if (myClass.CanLevelUp()) myClass.LevelUp();
}

void DGCharacter::ClassLevelDown()
{
    myClass.LevelDown();
}

bool DGCharacter::IsAlive() const
{
    return (myStatus != 'k');
}

bool DGCharacter::IsFused() const
{
    return false;
}

int DGCharacter::NormalAtkPow(int type, int pow) const
{
    int tab;
    
    tab = Atk() * pow;
    if (type == myElement) tab += (tab / 2);
    return tab;
}

int DGCharacter::MagicAtkPow(int type, int pow) const
{
    int tab;
    
    tab = Mag() * pow;
    if (type == myElement) tab += (tab / 2);
    return tab;
}

int DGCharacter::DefPow(int type) const	//returns defense to attack of type 'type'
{
    int looked;
    double tab = double(Def()) / 2.0;
    
    looked = DGTYP.Lookup(type, myElement);
    if (looked == 1) tab *= 1.5;
    else if (looked == 2) tab /= 1.5;
    else if (looked == -1) tab *= -1.0; //negates defense, resultes in negative damage (absorb)
    
    return DGRoundDouble(tab);
}

bool DGCharacter::HasAbility(DGCommand ability) const
{
    for (int k = 0; k < myNumAbilities; k++)
        if (myAbilities[k] == ability) return true;
    return false;
}

void DGCharacter::PrintAttacks() const
{
    for (int k = 0; k < myNumAttacks; k++)
    {
        if (myAttacks[k] != -1)
        {
            cout << setw(2) << k << " ";
            cout << setw(10) << DGATK.Name(myAttacks[k]) << " ";
            cout << setw(10) << DGTYP.TypName(DGATK.Type(myAttacks[k])) << " ";
            cout << "Pow: " << setw(2) << DGATK.Pow(myAttacks[k]) << " ";
            if (DGATK.Draw(myAttacks[k]) == -1)
                cout << "Draw n/a" << endl;
            else
                cout << "Draw: " << setw(2) << DGATK.Draw(myAttacks[k]) << endl;
        }
    }
    
}

int DGCharacter::GetRushInd() const
{
    return myClass.GetData(myClass.Level()).Rush;
}

bool DGCharacter::StartTurn()
{
    if (myStatus == 's')
    {
        cout << myName << " is asleep." << endl;
        return false;
    }
    else return IsAlive();
}

DGCharacter* DGCharacter::EndTurn()
{
    if (myStatus == 'p')
    {
        HPDown(myMaxHP / 20);
        cout << myName << " lost " << (myMaxHP / 20) << " HP to poison." << endl;
    }
    else if (myStatus == 's')
    {
        if (DGRandomDouble() <= .5)
        {
            myStatus = 'n';
            cout << myName << " woke up." << endl;
        }
    }
    return this;
}

int DGCharacter::Atk() const
{
    if (!myInRush)
        return myAttackLv;
    else
        return DGRoundDouble(double(myAttackLv) * 1.25);
}

int DGCharacter::Def() const
{
    if (!myInRush)
        return myDefenseLv;
    else
        return DGRoundDouble(double(myDefenseLv) * 0.75);
}

int DGCharacter::Mag() const
{
    if (!myInRush)
        return myMagicLv;
    else
        return DGRoundDouble(double(myMagicLv) * 1.75);
}

int DGCharacter::Spd() const
{
    if (!myInRush)
        return mySpeedLv;
    else
        return DGRoundDouble(double(mySpeedLv) * 1.5);
}

int DGCharacter::Acc() const
{
    if (!myInRush)
        return myAccuracyLv;
    else
        return (myAccuracyLv * 2);
}

void DGCharacter::EnterRush()
{
    myInRush = true;
    //play some kewl animation?
}

void DGCharacter::ExitRush()
{
    myInRush = false;
}

bool DGCharacter::CheckRush()
{
    return ((double(myHP) / double(myMaxHP)) <= RUSH_RATIO);
}