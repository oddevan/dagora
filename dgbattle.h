#ifndef dgbattle_H
#define dgbattle_H

/*
    DGBattle class decleration
    (c) 2003 root-1 Software
*/

#include "dgcharacter.h"
//#include "dgteam.h"

#define PSN_DRAIN 5
#define QUEUE_SIZE 10

class DGTeam;

class DGBattle
{
    public:
        DGBattle();
        DGBattle(DGTeam* firstTeam, DGTeam* secondTeam);
        DGBattle(const DGBattle& battle);
        ~DGBattle();
        
        bool ExecuteStandardBattle();
        //true if team1 won, false if team2 won
        
        void StandardTurn(DGCharacter* player);
        
        DGTeam* GetTeam1() const { return Team1; }
        DGTeam* GetTeam2() const { return Team2; }
        int NumPlayers() const { return myNumPlayers; }
        DGCharacter* GetFromQueue(int ind) const
        {
            if ((ind >= 0) && (ind < myNumPlayers)) return myQueue[ind];
            else return NULL;
        }
    
    private:
        void NullQueue();
        void SortQueue();
        int FindPlayer(DGCharacter* player);
        DGCharacter* FindPlayer(int victim, DGCharacter* player);
        bool StopBattle();
        void FinishBattle(DGTeam* winner, DGTeam* loser);
        
        DGTeam* Team1;
        DGTeam* Team2;
        int myNumPlayers;
        DGCharacter* myQueue[QUEUE_SIZE];
};

//#include dgbattle.cpp

#endif