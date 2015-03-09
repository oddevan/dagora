#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "dgplayable.h"
#include "dgsummons.h"
#include "dgweapon.h"
#include "dgteam.h"
#include "dginit.h"
#include "dgbattle.h"
#include "dgcommand.h"
#include "dghumanplayableintel.h"
#include "dghumansummonsintel.h"

int main (int argc, const char* argv[])
{
    InitDagora();
    
    cout << "DBS testing... Last changed 20 November"<< endl;
    cout << "All output is (c) root -1 Entertainment! Don't touch!" << endl;
    
    DGPlayable *Ereb, *Ronyo, *Kyrra, *Zach, *Omri;
    DGSummons *Dragon, *Phoenix;
    
    int data[4] = {19, 19, 19, 19};
    DGClassLevelData level(data, 2);
    DGAttack attack("Standard", 0, 1, 0, false, 'n');
    
    DGHumanPlayableIntel* playIntel = new DGHumanPlayableIntel();
    DGHumanSummonsIntel* sumIntel = new DGHumanSummonsIntel();
    
    level.Rush = 2;
    Ereb = new DGPlayable("Ereb", 5, 240, 10, 19, 20, 8, 10, 17, 10, DGClass(level), attack, playIntel);
    Ereb->Learn(0);
    Ereb->Learn(1);
    
    level.Rush = 6;
    Ronyo = new DGPlayable("Ronyo", 5, 220, 20, 11, 10, 25, 8, 9, 5, DGClass(level), attack, playIntel);
    Ronyo->Learn(3);
    Ronyo->Learn(4);
    Ronyo->Learn(5);
    
    level.Rush = 9;
    Kyrra = new DGPlayable("Kyrra", 5, 240, 10, 16, 19, 10, 20, 30, 11, DGClass(level), attack, playIntel);
    Kyrra->Learn(7);
    Kyrra->Learn(8);
    
    level.Rush = 11;
    Zach = new DGPlayable("Zach", 5, 200, 10, 11, 9, 26, 8, 9, 0, DGClass(level), attack, playIntel);
    Zach->Learn(10);
    Zach->Learn(SUMMON);
    
    level.Rush = 18;
    Omri = new DGPlayable("Omri", 7, 1000, 50, 27, 15, 30, 5, 10, 6, DGClass(level), attack, playIntel);
    Omri->Learn(15);
    Omri->Learn(16);
    Omri->Learn(17);
    
    level.Rush = 11;
    Dragon = new DGSummons("Dragon", 7, 300, 300, 12, 12, 30, 10, 40, 30, 20, 9, DGClass(level), sumIntel, 12);
    Zach->Junction(Dragon);
    
    level.Rush = 14;
    Phoenix = new DGSummons("Phoenix", 7, 300, 300, 15, 15, 15, 10, 30, 30, 20, 5, DGClass(level), sumIntel, 13);
    Zach->Junction(Phoenix);
        
    DGTeam *goodGuys, *badGuy;
    
    goodGuys = new DGTeam();
    goodGuys->Join(Ereb);
    goodGuys->Join(Ronyo);
    goodGuys->Join(Kyrra);
    goodGuys->Join(Zach);
    goodGuys->AddItem(0, 10);
    goodGuys->AddItem(1, 5);
    goodGuys->AddItem(2, 3);
    
    badGuy = new DGTeam();
    badGuy->Join(Omri);
    badGuy->AddItem(3, 5);
    
    DGBattle* battle = new DGBattle(goodGuys, badGuy);
   
    if (battle->ExecuteStandardBattle())
    {
        cout << "You Won! If this were a real game you would find some enlightening dialogue here!" << endl;
    }
    else
    {
        cout << "You lost and your charred carcasses were scattered for the world to see." << endl;
    }
    
    return 0;
}