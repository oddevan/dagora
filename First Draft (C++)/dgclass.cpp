/*
    DGClass class implementation
    (c) 2003 root-1 Software
*/

//#include "dgclass.h"
#include "dgcharacter.h"
#include "dgcommand.h"
#include "dgclassleveldata.h"

DGClass::DGClass()
  : myLevel(-1),
    myNumLevels(0)
{
}

DGClass::DGClass(DGClassLevelData data)
  : myLevel(0),
    myNumLevels(1)
{
    myData[0] = data;
}

DGClass::DGClass(int numLevels, DGClassLevelData data[])
  : myLevel(0),
    myNumLevels(numLevels)
{
    for (int k = 0; k < myNumLevels; k++)
        myData[k] = data[k];
}

DGClass::DGClass(const DGClass& jobclass)
  : myLevel(0),
    myNumLevels(jobclass.NumLevels())
{
    for (int k = 0; k < myNumLevels; k++)
        myData[k] = jobclass.GetData(k);
    Reset();
}

DGClass::~DGClass()
{
}
        
bool DGClass::LevelUp()
{
    if ((myLevel + 1) < myNumLevels)
    {
        myLevel++;
        return true;
    }
    else return false;
}

bool DGClass::LevelDown()
{
    if ((myLevel - 1) >= 0)
    {
        myLevel--;
        return true;
    }
    else return false;
}

bool DGClass::SPUp(DGCharacter* myChar)
{
    myData[myLevel].SP++;
    if ((myData[myLevel].SP % SP_PER_ATK) == 0)
    {
        for (int k = 0; k < NUM_ATK_PER_LEVEL; k++)
        {
            if (!myData[myLevel].AtkLearned[k])
            {
                if ((myLevel == 0) || (myData[myLevel - 1].AtkLearned[k]))
                {
                    myData[myLevel].AtkLearned[k] = myChar->Learn(myData[myLevel].Attacks[k]);
                    if (myData[myLevel].SP == (SP_PER_ATK * 2)) myChar->Learn(myData[myLevel].Ability);
                    return myData[myLevel].AtkLearned[k];
                }
            }
        }
    }
    return false;
}

void DGClass::Reset()
{
    for (int k = 0; k < myNumLevels; k++)
        myData[myLevel].Reset();
    myLevel = 0;
}
        
int DGClass::AdjustedLevel() const
{
    return (myLevel + 1);
}

bool DGClass::CanLevelUp() const
{
    return ((myData[myLevel].SP == (SP_PER_ATK * 2)) && ((myLevel + 1) < myNumLevels));
}