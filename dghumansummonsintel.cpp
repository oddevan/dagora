/*
    DGHumanSummonsIntel class implementation
    (c) 2003 root-1 Software
*/

#include "dghumansummonsintel.h"
#include "dginit.h"
#include <iostream.h>
#include <iomanip.h>

DGHumanSummonsIntel::DGHumanSummonsIntel()
 : DGSummonsIntel()
{
}

DGHumanSummonsIntel::DGHumanSummonsIntel(DGSummons* mine)
 : DGSummonsIntel(mine)
{
}

DGCommand DGHumanSummonsIntel::ChooseCommand(DGBattle* battle) const
{
    DGCommand commands[MAX_DGCOMMAND];
    int numCmd = 0, choice;
    
    commands[numCmd] = STATUS;
    numCmd++;
    commands[numCmd] = ATTACK;
    numCmd++;
    if (myChar->InRush())
    {
        commands[numCmd] = RUSH;
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
    if (commands[choice] == ATTACK) return SPECIAL;
    else return commands[choice];
}

int DGHumanSummonsIntel::ChooseAttack(DGBattle* battle) const
{
    return myChar->GetAttack(0);
}

int DGHumanSummonsIntel::ChooseAttackVictim(DGBattle* battle, bool isTeam) const
{
    int choice;
    int totVictims = DispVictims(battle);
    
    do
    {
        cout << "Choose a character";
        if (isTeam) cout << " (attacks team of character)";
        cout << ": ";
        cin >> choice;
    } while ((choice >= totVictims) || (choice < -1));
    return choice;
}
    
int DGHumanSummonsIntel::ChooseAttackVictim(DGBattle* battle, int atkInd) const
{
    cout << "Using attack " << DGATK.Name(atkInd) << " [" << DGATK.Draw(atkInd) << " MP]"<< endl;
    return ChooseAttackVictim(battle, DGATK.IsTeam(atkInd));
}

int DGHumanSummonsIntel::DispVictims(DGBattle* battle) const
{
    DGCharacter* current = NULL;
    DGTeam* charTeam = myChar->Team();
    int k = 0, j = 0;
    
    for (k = 0; k < battle->NumPlayers(); k++)
    {
        current = battle->GetFromQueue(k);
        cout << setw(2) << j << ": " << current->Name();
        if ((current->Team()) == (charTeam))
            cout << "  " << current->HP() << " / " << current->MaxHP();
        cout << endl;
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
    
    return (battle->NumPlayers() + myChar->Team()->NumDemi());
}