/*
    dghumanplayableintel class implementation
    (c) 2003 root-1 Software
*/

#include "dghumanplayableintel.h"
#include "dgplayable.h"
#include "dgcommand.h"
#include "dginit.h"
#include "dgteam.h"
#include "dgbattle.h"
#include <iostream.h>
#include <iomanip.h>

DGHumanPlayableIntel::DGHumanPlayableIntel()
 : DGPlayableIntel()
{
}

DGHumanPlayableIntel::DGHumanPlayableIntel(DGPlayable* mine)
 : DGPlayableIntel(mine)
{
}

DGCommand DGHumanPlayableIntel::ChooseCommand(DGBattle* battle) const
{
    DGCommand commands[MAX_DGCOMMAND];
    int numCmd = 0, choice;
    
    commands[numCmd] = STATUS;
    numCmd++;
    commands[numCmd] = ATTACK;
    numCmd++;
    commands[numCmd] = SPECIAL;
    numCmd++;
    if (myChar->InRush())
    {
        commands[numCmd] = RUSH;
        numCmd++;
    }
    commands[numCmd] = ITEM;
    numCmd++;
    if (myChar->CanFuse())
    {
        commands[numCmd] = FUSE;
        numCmd++;
    }
    if (myChar->IsFused())
    {
        commands[numCmd] = DEFUSE;
        numCmd++;
    }
    if (myChar->CanSummon())
    {
        commands[numCmd] = SUMMON;
        numCmd++;
    }
    if (myChar->CanTransform())
    {
        commands[numCmd] = TRANSFORM;
        numCmd++;
    }
    
    cout << setw(10) << myChar->Name() << ": HP " << setw(4) << myChar->HP();
    cout << " MP " << setw(4) << myChar->MP() << endl;
    
    for (int k = 0; k < numCmd; k++) cout << setw(2) << k << ": " << commands[k] << endl;
    
    do
    {
        cout << "Choose an option: ";
        cin >> choice;
    } while ((choice >= numCmd) || (choice < 0));
    return commands[choice];
}

int DGHumanPlayableIntel::ChooseAttack(DGBattle* battle) const
{
    int choice;
    int atkInd;
    
    cout << myChar->Name() << "'s Attacks:" << endl;
    while (true)
    {
        myChar->PrintAttacks();
        cout << "Choose Attack: ";
        cin >> choice;
        if (choice == -1) return -1;
        atkInd = myChar->GetAttack(choice);
        if (atkInd != -1)
        {
            if (DGATK.Draw(atkInd) > myChar->MP())
                cout << "Not enough MP" << endl;
            else return atkInd;
        }
    }
}

int DGHumanPlayableIntel::ChooseAttackVictim(DGBattle* battle, bool isTeam) const
{
    int choice;
    int totVictims = DispVictims(battle);
    
    do
    {
        cout << "Choose a character";
        if (isTeam) cout << " (attacks team of this character)";
        cout << ": ";
        cin >> choice;
    } while ((choice >= totVictims) || (choice < -1));
    return choice;
}
    
int DGHumanPlayableIntel::ChooseAttackVictim(DGBattle* battle, int atkInd) const
{
    cout << "Using attack " << DGATK.Name(atkInd) << endl;
    return ChooseAttackVictim(battle, DGATK.IsTeam(atkInd));
}

int DGHumanPlayableIntel::ChooseItem(DGBattle* battle) const
{
    int choice;

    myChar->Team()->PrintItems();
    do
    {
        cout << "Choose Item: ";
        cin >> choice;
    } while ((choice >= myChar->Team()->NumItems()) || (choice < -1));
    return choice;
}

int DGHumanPlayableIntel::ChooseItemVictim(DGBattle* battle, int itmInd) const
{
    int choice;
    
    int totVictims = DispVictims(battle);
    do
    {
        cout << "Choose a character: ";
        cin >> choice;
    } while ((choice >= totVictims) || (choice < -1));
    return choice;
}
        
int DGHumanPlayableIntel::ChooseDemi(DGBattle* battle) const
{
    int choice;
    DGTeam* charTeam = myChar->Team();
    DGDemi* current;
    
    for (int k = 0; k < charTeam->NumDemi(); k++)
    {
        current = charTeam->GetDemi(k);
        cout << setw(2) << k << ": " << current->Name();
        cout << "  " << current->HP() << " / " << current->MaxHP() << endl;
    }
    do
    {
        cout << "Choose a demi: ";
        cin >> choice;
    } while ((choice >= charTeam->NumDemi()) || (choice < -1));
    return choice;
    
}

int DGHumanPlayableIntel::ChooseSummons(DGBattle* battle) const
{
    int choice;
    DGSummons* current;
    for (int k = 0; k < myChar->NumSummons(); k++)
    {
        current = myChar->GetRealSummons(k);
        cout << setw(2) << k << ": " << current->Name();
        cout << " " << current->HP() << " / " << current->MaxHP() << endl;
    }
    do
    {
        cout << "Choose a summons: ";
        cin >> choice;
    } while ((choice >= myChar->NumSummons()) || (choice < -1));
    return choice;
}

int DGHumanPlayableIntel::DispVictims(DGBattle* battle) const
{
    DGCharacter* current = NULL;
    DGTeam* charTeam = myChar->Team();
    int k = 0, j = 0;
    
    for (k = 0; k < battle->NumPlayers(); k++)
    {
        current = battle->GetFromQueue(k);
        if (current != NULL)
        {
            cout << setw(2) << j << ": " << current->Name();
            if ((current->Team()) == (charTeam))
                cout << "  " << current->HP() << " / " << current->MaxHP();
            cout << endl;
            j++;
        }
    }
    cout << "  ----------" << endl;
    for (k = 0; k < myChar->NumSummons(); k++)
    {
        current = myChar->GetSummons(k);
        cout << setw(2) << j << ": " << current->Name();
        cout << " " << current->HP() << " / " << current->MaxHP() << endl;
        j++;
    }
    cout << "  ----------" << endl;
    for (k = 0; k < charTeam->NumDemi(); k++)
    {
        current = charTeam->GetDemi(k);
        cout << setw(2) << j << ": " << current->Name();
        cout << "  " << current->HP() << " / " << current->MaxHP() << endl;
        j++;
    }
    
    return (battle->NumPlayers() + myChar->NumSummons() + myChar->Team()->NumDemi());
}