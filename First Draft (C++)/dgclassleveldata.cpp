/*
    DGClassLevelData class implementation
    (c) 2003 root-1 Software
*/

#include "dgclassleveldata.h"

DGClassLevelData::DGClassLevelData()
{
    for (int k = 0; k < NUM_ATK_PER_LEVEL; k++)
        Attacks[k] = -1;
    
    Reset();
    
    Rush = -1;
    Ability = ATTACK;
}

DGClassLevelData::DGClassLevelData(int atkData[], int lvlRush)
{
    for (int k = 0; k < NUM_ATK_PER_LEVEL; k++)
        Attacks[k] = atkData[k];
    
    Reset();
    
    Rush = lvlRush;
    Ability = ATTACK;
}

DGClassLevelData::DGClassLevelData(int atkData[], int lvlRush, DGCommand lvlAbility)
{
    for (int k = 0; k < NUM_ATK_PER_LEVEL; k++)
        Attacks[k] = atkData[k];
    
    Reset();
    
    Rush = lvlRush;
    Ability = lvlAbility;
}

void DGClassLevelData::Reset()
{
    for (int k = 0; k < NUM_ATK_PER_LEVEL; k++)
        AtkLearned[k] = false;
        
    SP = 0;
}