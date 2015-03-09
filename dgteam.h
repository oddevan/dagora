#ifndef dgteam_H
#define dgteam_H

/*
    DGTeam class decleration
    (c) 2003 root-1 Software
*/

#include "dgcharacter.h"
#include "dgitem.h"
#include "dgplayable.h"
#include "dgdemi.h"

#define NUM_ACTIVE 4
#define NUM_BENCH 4
#define NUM_DEMI 5
#define NUM_ITM 50

class DGTeam
{
    public:
        DGTeam();
        DGTeam(const DGTeam& team);
        ~DGTeam();
        
        bool UseItem(int itmInd, DGCharacter* victim);
        bool Join(DGPlayable* joining);
        bool Join(DGDemi* joining);
        DGPlayable* LeaveBench(int charInd);
        DGDemi* LeaveDemi(int charInd);
        bool BenchActive(int charInd);
        bool CallFromBench(int charInd);
        bool AddItem(DGItem item);
        bool AddItem(int itemMasterInd);
        bool AddItem(int itemMasterInd, int num);
        void ItemsTaken();
        void QueueXP(int amt);
        int GetXP();
        
        int GetItmInd(int itmMasterInd) const; // returns myInventory index of item with given MasterIndex
        bool IsAlive() const; //is someone on this team functional?
        void PrintItems() const; // prints myInventory
        
        DGPlayable* GetActive(int ind) const
        {
            if ((ind >= 0) && (ind < myNumActive)) return myActive[ind];
            else return NULL;
        }
        int NumActive() const { return myNumActive; }
        DGPlayable* GetBench(int ind) const
        {
            if ((ind >= 0) && (ind < myNumBench)) return myBench[ind];
            else return NULL;
        }
        int NumBench() const { return myNumBench; }
        DGDemi* GetDemi(int ind) const
        {
            if ((ind >= 0) && (ind < myNumDemi)) return myDemi[ind];
            else return NULL;
        }
        int NumDemi() const { return myNumDemi; }
        DGItem GetItem(int ind) const
        {
            if ((ind >= 0) && (ind < myNumItm)) return myInventory[ind];
            else return DGItem();
        }
        int NumItems() const { return myNumItm; }
        int XPQueue() const { return myXPQueue; }
        
    private:
        DGPlayable* myActive[NUM_ACTIVE];
        int myNumActive;
        DGPlayable* myBench[NUM_BENCH];
        int myNumBench;
        DGDemi* myDemi[NUM_DEMI];
        int myNumDemi;
        DGItem myInventory[NUM_ITM];
        int myNumItm;
        int myXPQueue;
};

//#include dgteam.cpp

#endif