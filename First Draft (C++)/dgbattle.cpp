/*
    DGBattle class implementation
    (c) 2003 root-1 Software
*/

#include "dgbattle.h"
#include "dgteam.h"
#include "dgcharacter.h"
#include "dgintelligence.h"
#include "dginit.h"
#include "dgcommand.h"
#include <iostream.h>
#include <iomanip.h>

extern const DGAttackHandle DGATK;
extern const DGItemHandle DGITM;
extern const DGTypeHandle DGTYP;

DGBattle::DGBattle()
{
    Team1 = NULL;
    Team2 = NULL;
    myNumPlayers = 0;
    
    NullQueue();
}

DGBattle::DGBattle(DGTeam* firstTeam, DGTeam* secondTeam)
{
    Team1 = firstTeam;
    Team2 = secondTeam;
    myNumPlayers = Team1->NumActive() + Team2->NumActive();
    
    NullQueue();
    
    // load queue
    int k;
    
    for (k = 0; k < Team1->NumActive(); k++)
        myQueue[k] = Team1->GetActive(k);
    k = Team1->NumActive();
    for (int j = 0; j < Team2->NumActive(); j++)
    {
        myQueue[k] = Team2->GetActive(j);
        k++;
    }
}

DGBattle::DGBattle(const DGBattle& battle)
{
    Team1 = battle.GetTeam1();
    Team2 = battle.GetTeam2();
    myNumPlayers = Team1->NumActive() + Team2->NumActive();
    
    NullQueue();
    
    // load queue
    int k;
    for (k = 0; k < Team1->NumActive(); k++)
        myQueue[k] = Team1->GetActive(k);
    k = Team1->NumActive();
    for (int j = 0; j < Team2->NumActive(); j++)
    {
        myQueue[k] = Team2->GetActive(j);
        k++;
    }
}

DGBattle::~DGBattle()
{
}

bool DGBattle::ExecuteStandardBattle()
{
    cout << "[insert cool opening sequence here :p]\n" << endl;
    
    while (!StopBattle())
    {
        SortQueue();
        
        for (int k = 0; k < myNumPlayers; k++)
        {
            StandardTurn(myQueue[k]);
            if (StopBattle()) break;
        }
    }
    if (Team1->IsAlive()) FinishBattle(Team1, Team2);
    else FinishBattle(Team2, Team1);
    
    return Team1->IsAlive();
}

void DGBattle::StandardTurn(DGCharacter* player)
{
    if (StopBattle()) return;
    
    int victim, ind, xp = 0, myInd;
    bool endTurn = !(player->StartTurn());
    DGCharacter* aChar;
    
    myInd = FindPlayer(player);
    
    while (!endTurn)
    {
        DGCommand cmd = player->ChooseCommand(this);
        switch (cmd)
        {
            case STATUS:
                victim = player->ChooseAttackVictim(this, false);
                if (victim != -1)
                {
                    aChar = FindPlayer(victim, player);
                    if (aChar->Team() != player->Team())
                    {
                        cout << "Hey, no cheating!" << endl;
                    }
                    else
                    {
                        cout << setw(10) << aChar->Name() << " Level: " << aChar->Level() << endl;
                        cout << "HP: " << setw(3) << aChar->HP() << " / " << setw(3) << aChar->MaxHP();
                        cout << "  MP: " << setw(3) << aChar->MP() << " / " << setw(3) << aChar->MaxMP() << endl;
                        cout << "XP to level " << (aChar->Level() + 1) << ": " << aChar->LvUp() << endl;
                    }
                }
                break;
            default:
            case ATTACK:
                victim = player->ChooseAttackVictim(this, player->StandardAttack().IsTeam);
                if (victim != -1)
                {
                    xp = DGATK.ExeStdAtk(player, FindPlayer(victim, player));
                    endTurn = true;
                }
                break;
            case SPECIAL:
                ind = player->ChooseAttack(this);
                if (ind != -1)
                {
                    victim = player->ChooseAttackVictim(this, ind);
                    if (victim != -1)
                    {
                        xp = DGATK.Exe(player, FindPlayer(victim, player), ind, this);
                        endTurn = true;
                    }
                }
                break;
            case RUSH:
                ind = player->GetRushInd();
                if (ind != -1)
                {
                    victim = player->ChooseAttackVictim(this, ind);
                    if (victim != -1)
                    {
                        xp = DGATK.Exe(player, FindPlayer(victim, player), ind, this);
                        endTurn = true;
                    }
                }
                break;
            case ITEM:
                ind = player->ChooseItem(this);
                if (ind != -1)
                {
                    victim = player->ChooseItemVictim(this, ind);
                    if (victim != -1)
                    {
                        if (player->Team()->UseItem(ind, FindPlayer(victim, player)))
                            endTurn = true;
                        else cout << "No Effect." << endl;
                    }
                }
                break;
            case FUSE:
                ind = player->ChooseDemi(this);
                if (ind != -1)
                {
                    victim = FindPlayer(player);
                    if (victim != -1)
                    {
                        myQueue[victim] = player->Fuse(ind);
                        endTurn = true;
                    }
                }
                break;
            case DEFUSE:
                victim = FindPlayer(player);
                if (victim != -1)
                {
                    myQueue[victim] = player->Defuse();
                    endTurn = true;
                }
                break;
            case SUMMON:
                victim = FindPlayer(player);
                if (victim != -1)
                {
                    myQueue[victim] = player->ChooseAndSummon(this);
                    endTurn = true;
                }
                break;
            case RETURN:
                victim = FindPlayer(player);
                if (victim != -1)
                {
                    myQueue[victim] = player->Return();
                    endTurn = true;
                }
                break;
            case TRANSFORM:
                if (player->CanTransform())
                {
                    victim = FindPlayer(player);
                    if (victim != -1)
                    {
                        myQueue[victim] = player->Transform();
                        endTurn = true;
                    }
                }
                break;
        }
        player->XPUp(xp / 2);
        player->Team()->QueueXP((xp / 2) + (xp % 2));
        cout << player->Name() << " gained " << (xp / 2) << " XP" << endl;
        cout << endl;
    }
    if (FindPlayer(player) == myInd) myQueue[myInd] = player->EndTurn();
}
    

void DGBattle::NullQueue()
{
    for (int k = 0; k < QUEUE_SIZE; k++) myQueue[k] = NULL;
}

void DGBattle::SortQueue()
{
    DGCharacter* temp;
   
    for (int j = 0; j < myNumPlayers - 1; j++)
    { 
        for (int k = myNumPlayers-1; k > 0; k--)
        {
            if (myQueue[k-1]->Spd() < myQueue[k]->Spd())
            {
                temp = myQueue[k];
                myQueue[k] = myQueue[k-1];
                myQueue[k-1] = temp;
            }
        }
    }
}

int DGBattle::FindPlayer(DGCharacter* player)
{
    for (int k = 0; k < myNumPlayers; k++) if (myQueue[k] == player) return k;
    return -1;
}

DGCharacter* DGBattle::FindPlayer(int victim, DGCharacter* player)
{
    if (victim < myNumPlayers) return myQueue[victim];
    else
    {
        victim -= myNumPlayers;
        if (victim < player->NumSummons()) return player->GetSummons(victim);
		else
		{
			victim -= player->NumSummons();
			if (victim < player->Team()->NumDemi()) return player->Team()->GetDemi(victim);
		}
    }
    return NULL;
}

bool DGBattle::StopBattle()
{
    return (!((Team1->IsAlive()) && (Team2->IsAlive())));
}

void DGBattle::FinishBattle(DGTeam* winner, DGTeam* loser)
{
    int xp = winner->GetXP();
    bool demiGotXP = false;
    int k, j;
    DGCharacter* battleChar;
    DGPlayable* character;
    
    for (k = 0; k < myNumPlayers; k++)
    {
        battleChar = myQueue[k];
        
        if (battleChar->IsFused())
        {
            myQueue[k] = battleChar->Defuse();
            battleChar = myQueue[k];
            if (!(battleChar->IsAlive())) battleChar->Revive();
        }
        else
        {
            battleChar->Return();
        }
    }
    
    for (k = 0; k < winner->NumActive(); k++)
    {
        character = winner->GetActive(k);
        
        if (character->IsAlive())
        {
            character->XPUp(xp);
            cout << character->Name() << " gained " << xp << " XP" << endl;
            if ((character->CanFuse()) && (!demiGotXP))
            {
                for (j = 0; j < winner->NumDemi(); j++)
                {
                    if (winner->GetDemi(j)->IsAlive())
                    {
                        winner->GetDemi(j)->XPUp(xp);
                        cout << winner->GetDemi(j)->Name() << " gained " << xp << " XP" << endl;
                    }
                    else
                    {
                        cout << winner->GetDemi(j)->Name() << " did not receive XP" << endl;
                    }
                }
            }
            if (character->CanSummon())
            {
                for (j = 0; j < character->NumSummons(); j++)
                {
                    if (character->GetSummons(j)->IsAlive())
                    {
                        character->GetSummons(j)->XPUp(xp);
                        cout << character->GetSummons(j)->Name() << " gained " << xp << " XP" << endl;
                    }
                    else
                    {
                        cout << character->GetSummons(j)->Name() << " did not receive XP" << endl;
                    }
                }
            }
        }
        else
        {
            cout << character->Name() << " did not receive XP" << endl;
            if (character->CanSummon()) cout << character->Name() << "'s summons did not receive XP" << endl;
        }
    }
    if (!demiGotXP) cout << "Demi did not receive XP" << endl;
    
    for (k = 0; k < loser->NumItems(); k++)
    {
        winner->AddItem(loser->GetItem(k));
        cout << "Received " << loser->GetItem(k).Uses << " ";
        if (loser->GetItem(k).Uses > 1)
            cout << DGITM.Name(loser->GetItem(k).Ind) << "." << endl;
        else
            cout << DGITM.Name(loser->GetItem(k).Ind) << "s." << endl;
    }
    loser->ItemsTaken();
}