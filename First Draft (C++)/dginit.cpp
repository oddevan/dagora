/*
    Dagora Battle System initilization/useful functions
    (c) 2003 root-1 Software
*/

#include "dginit.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

void InitDagora()
{
    cout << "Starting Dagora Battle System..." << endl;
    srand(time(0));
}

int DGRoundDouble(double roundMe)
{
    int baseValue = int(roundMe);
    double temp = roundMe - double(baseValue);
    int roundKey = int(temp * 10);
    
    if (roundKey < 5) return baseValue;
    return baseValue + 1;
}

double DGRandomDouble()
{
    double working = double(rand());
    
    while (working > 1) working /= 10.0;
    
    return working;
}

int DGRandomInt(int max)
{
    return (rand() % max);
}

/*void KillDagora()
{
}*/