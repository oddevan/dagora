#ifndef dgdemi_H
#define dgdemi_H

/*
    DGDemi class decleration
    (c) 2003 root-1 Software
*/

#include <string.h>
//#include "dgcharacter.h"
//#include "dgteam.h"
#include "dgplayable.h"

class DGCharacter;

class DGDemi : public DGCharacter
{

//There are no intel modules for Demi yet! Do not place a Demi on its own
//in battle or you will get a nasty runtime error!

    public:
        DGDemi();
        DGDemi(char* name,
               char* appendName,
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
        DGDemi(const DGDemi &demi);
        virtual ~DGDemi();
        
        DGPlayable* Fuse(DGPlayable* original); //returns new character, myFused = original
        DGPlayable* Defuse(DGPlayable* hybrid); //returns myFused, deletes fused
        
        virtual bool IsFused() const;
        
        char* AppendName() const { return myAppendName; }
        DGPlayable* FusionLink() const { return myFused; }
        int StartingXP() const { return hybridStartXP; }
        
    private:
        char* myAppendName;
        DGPlayable* myFused;
        int hybridStartXP;
};

//#include dgdemi.cpp

#endif