/*
    dgteam class implementation
    (c) 2003 root-1 Software
*/

//#include "dgteam.h"
#include "dgplayable.h"
#include "dgdemi.h"
#include "dgitem.h"
#include "dginit.h"
#include <iostream.h>
#include <iomanip.h>

extern const DGAttackHandle DGATK;
extern const DGItemHandle DGITM;
extern const DGTypeHandle DGTYP;

DGTeam::DGTeam()
 :  myNumActive(0),
    myNumBench(0),
    myNumDemi(0),
    myNumItm(0),
    myXPQueue(0)
{
    int k;
    
    for (k = 0; k < NUM_ACTIVE; k++) myActive[k] = NULL;
    for (k = 0; k < NUM_BENCH; k++) myBench[k] = NULL;
    for (k = 0; k < NUM_DEMI; k++) myDemi[k] = NULL;
}

DGTeam::DGTeam(const DGTeam& team)
 :  myNumActive(team.NumActive()),
    myNumBench(team.NumBench()),
    myNumDemi(team.NumDemi()),
    myNumItm(team.NumItems()),
    myXPQueue(team.XPQueue())
{
    int k;
    
    for (k = 0; k < NUM_ACTIVE; k++) myActive[k] = NULL;
    for (k = 0; k < NUM_BENCH; k++) myBench[k] = NULL;
    for (k = 0; k < NUM_DEMI; k++) myDemi[k] = NULL;
    
    for (k = 0; k < myNumActive; k++)
        myActive[k] = new DGPlayable(*team.GetActive(k));
    for (k = 0; k < myNumBench; k++)
        myBench[k] = new DGPlayable(*team.GetBench(k));
    for (k = 0; k < myNumDemi; k++)
        myDemi[k] = new DGDemi(*team.GetDemi(k));
    for (k = 0; k < myNumItm; k++)
        myInventory[k] = team.GetItem(k);
}

DGTeam::~DGTeam()
// Because when a team is deconstructed it generally means the characters are done with as well,
// this function deletes all characters and demis in the team. Make sure everyone's exited before
// deconstructing a team! Otherwise you could be left with dangling pointers...
{
    int k;
    
    for (k = 0; k < NUM_ACTIVE; k++) if (myActive[k] != NULL) delete myActive[k];
    for (k = 0; k < NUM_BENCH; k++) if (myActive[k] != NULL) delete myBench[k];
    for (k = 0; k < NUM_DEMI; k++) if (myActive[k] != NULL) delete myDemi[k];
}

bool DGTeam::UseItem(int itmInd, DGCharacter* victim)
{

    if ((itmInd >= myNumItm) || (itmInd < 0)) return false;
    
    if (DGITM.Use(victim, myInventory[itmInd].Ind))
    {
        myInventory[itmInd].Uses--;
        if (myInventory[itmInd].Uses <= 0)
        {
            for (int k = itmInd; k < myNumItm-1; k++)
                myInventory[k] = myInventory[k+1];
            myNumItm--;
            myInventory[myNumItm] = DGItem();
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool DGTeam::Join(DGPlayable* joining)
{
    if ((myNumActive + myNumBench) > (NUM_BENCH + 1)) return false;
    // max number of characters is NUM_BENCH + 1
    
    if (myNumActive == NUM_ACTIVE) // active is full
    {
        if (myNumBench == NUM_BENCH) return false; //double-checking for out-of-bounds
        myBench[myNumBench] = joining;
        myNumBench++;
    }
    else //has space in active
    {
        myActive[myNumActive] = joining;
        myNumActive++;
    }
    joining->SetTeam(this);
	if (joining->CanSummon())
	{
		for (int k = 0; k < joining->NumSummons(); k++)
			joining->GetSummons(k)->SetTeam(this);
	}
    return true;
}

bool DGTeam::Join(DGDemi* joining)
{
    //Since Demis are not meant to be active chars, they are sent straight to the Demi array.
    if (myNumDemi == NUM_DEMI) return false;
    
    myDemi[myNumDemi] = joining;
    myNumDemi++;
    joining->SetTeam(this);
    return true;
}

DGPlayable* DGTeam::LeaveBench(int charInd)
{
    if ((charInd >= myNumBench) || (charInd < 0)) return NULL;
    
    DGPlayable* left = myBench[charInd];
    
    myNumBench--;
    for (int k = charInd; k < myNumBench; k++)
        myBench[k] = myBench[k+1];
    myBench[myNumBench] = NULL;
    
    return left;
}

DGDemi* DGTeam::LeaveDemi(int charInd)
{
    if ((charInd >= myNumDemi) || (charInd < 0)) return NULL;
    
    DGDemi* left = myDemi[charInd];
    
    myNumDemi--;
    for (int k = charInd; k < myNumDemi; k++)
        myDemi[k] = myDemi[k+1];
    myDemi[myNumDemi] = NULL;
    
    return left;
}

bool DGTeam::BenchActive(int charInd)
{
    if ((charInd >= myNumActive) || (charInd < 0)) return false; //out-of-bounds
    if (myNumBench == NUM_BENCH) return false; //bench is full
    
    myBench[myNumBench] = myActive[charInd];
    myNumBench++;
    myNumActive--;
    for (int k = charInd; k < myNumActive; k++)
        myActive[k] = myActive[k+1];
    myActive[myNumActive] = NULL;
    
    return true;
}

bool DGTeam::CallFromBench(int charInd)
{
    if ((charInd >= myNumBench) || (charInd < 0)) return false; //out-of-bounds
    if (myNumActive == NUM_ACTIVE) return false; //active is full
    
    myActive[myNumActive] = myBench[charInd];
    myNumActive++;
    myNumBench--;
    for (int k = charInd; k < myNumBench; k++)
        myBench[k] = myBench[k+1];
    myBench[myNumBench] = NULL;
    
    return true;
}

bool DGTeam::AddItem(DGItem item)
{
    int k = GetItmInd(item.Ind);
    if (k != -1)
    {
        myInventory[k].Uses += item.Uses;
        return true;
    }
        
    if (myNumItm == NUM_ITM) return false; //inventory is full
    myInventory[myNumItm] = item;
    myNumItm++;
    return true;
}

bool DGTeam::AddItem(int itemMasterInd)
{
    DGItem bob(itemMasterInd, 1);
    return AddItem(bob);
}

bool DGTeam::AddItem(int itemMasterInd, int num)
{
    DGItem bob(itemMasterInd, num);
    return AddItem(bob);
}

void DGTeam::ItemsTaken()
{
    for (int k = 0; k < myNumItm; k++)
        myInventory[k] = DGItem();
    
    myNumItm = 0;
}

void DGTeam::QueueXP(int amt)
{
    myXPQueue += amt;
}

int DGTeam::GetXP()
{
    int temp = myXPQueue;
    myXPQueue = 0;
    return temp;
}
        
int DGTeam::GetItmInd(int itmMasterInd) const // returns myInventory index of item with given MasterIndex
{
    for (int k = 0; k < myNumItm; k++)
        if (myInventory[k].Ind == itmMasterInd)
            return k;
    return -1;
}

bool DGTeam::IsAlive() const
{
    for (int k = 0; k < myNumActive; k++)
        if (myActive[k]->IsAlive()) return true;
    return false;
}

void DGTeam::PrintItems() const
{
    for (int k = 0; k < myNumItm; k++)
    {
        cout << setw(2) << k << " ";
        cout << setw(10) << DGITM.Name(myInventory[k].Ind) << " ";
        cout << myInventory[k].Uses << endl;
    }
}