#ifndef dgclass_H
#define dgclass_H

/*
    DGClass class decleration
    (c) 2003 root-1 Software
*/

#include "dgcharacter.h"
#include "dgcommand.h"
#include "dgclassleveldata.h"
#include <string>

#define MAX_LEVELS 5
#define SP_PER_ATK 5

class DGClass
{
    public:
        DGClass();
        DGClass(DGClassLevelData data);
        DGClass(int numLevels, DGClassLevelData data[]);
        DGClass(const DGClass& jobclass);
        ~DGClass();
        
        bool LevelUp();
        bool LevelDown();
        bool SPUp(DGCharacter* myChar);
        void Reset();
        
        int AdjustedLevel() const;
        bool CanLevelUp() const;
        
        int Level() const { return myLevel; }
        int NumLevels() const { return myNumLevels; }
        DGClassLevelData GetData(int level) const
        {
            if ((level >= 0) && (level < myNumLevels)) return myData[level];
            else return DGClassLevelData();
        }
        
        
    private:
        int myLevel;	//starts at 0!
        int myNumLevels;
        DGClassLevelData myData[MAX_LEVELS];
};

//#include dgclass.cpp

#endif
