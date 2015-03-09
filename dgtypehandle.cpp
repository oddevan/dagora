/*
    DGTypeHandle class implementation
    (c) 2003 root-1 Software
*/

#include <iostream>
#include "dgtypehandle.h"

//0 = nothing special  1 = weak attack  2 = strong attack
DGTypeHandle::DGTypeHandle()
{
    //cout << "Initializing Types... ";
    
        for (int k = 0; k < TOT_NUM_TYP; k++)
            for (int j = 0; j < TOT_NUM_TYP; j++)
                myTypeMatrix[k][j] = 0;
    
        //normal
        myTypeMatrix[0][3] = 1;
        myTypeMatrix[0][4] = 1;
        myTypeMatrix[0][5] = 1;
        myTypeMatrix[0][6] = 1;
        myTypeMatrix[0][7] = 2;
        myTypeMatrix[0][12] = 1;
    
        //sword
        myTypeMatrix[1][1] = 1;
        myTypeMatrix[1][7] = 2;
        myTypeMatrix[1][8] = 1;
    
        //fighting
        myTypeMatrix[2][0] = 2;
        myTypeMatrix[2][2] = 1;
        myTypeMatrix[2][5] = 1;
        myTypeMatrix[2][6] = 1;
    
        //flying
        myTypeMatrix[3][3] = 1;
        myTypeMatrix[3][4] = 2;
    
        //remote
        myTypeMatrix[4][3] = 2;
        myTypeMatrix[4][4] = 1;
    
        //whitemagic
        myTypeMatrix[5][2] = 2;
        myTypeMatrix[5][5] = -1;
        myTypeMatrix[5][6] = 2;
        myTypeMatrix[5][12] = 2;
    
        //blackmagic
        myTypeMatrix[6][2] = 2;
        myTypeMatrix[6][5] = 2;
        myTypeMatrix[6][6] = -1;
        myTypeMatrix[6][12] = 2;
    
        //wood
        myTypeMatrix[7][1] = 1;
        myTypeMatrix[7][7] = -1;
        myTypeMatrix[7][8] = 2;
        myTypeMatrix[7][11] = 1;
    
        //metal
        myTypeMatrix[8][1] = 1;
        myTypeMatrix[8][2] = 1;
        myTypeMatrix[8][8] = -1;
        myTypeMatrix[8][9] = 1;
        myTypeMatrix[8][10] = 2;
    
        //fire
        myTypeMatrix[9][7] = 2;
        myTypeMatrix[9][9] = -1;
        myTypeMatrix[9][10] = 1;
    
        //wind
        myTypeMatrix[10][4] = 1;
        myTypeMatrix[10][7] = 1;
        myTypeMatrix[10][10] = -1;
        myTypeMatrix[10][11] = 2;
    
        //water
        myTypeMatrix[11][8] = 1;
        myTypeMatrix[11][9] = 2;
        myTypeMatrix[11][11] = -1;
    
        //enhanced
        myTypeMatrix[12][0] = 1;
        myTypeMatrix[12][12] = 1;
    
    //cout << "done." << endl;
}

int DGTypeHandle::Lookup(int atkTyp, int defTyp) const
{
    if ((atkTyp < TOT_NUM_TYP) && (defTyp < TOT_NUM_TYP) && (atkTyp >= 0) && (defTyp >= 0))
        return myTypeMatrix[atkTyp][defTyp];
    else return 0; // replace with die() or exit()
}

char* DGTypeHandle::TypName(int typ) const
{
    switch (typ)
    {
        case 0: return "Normal";
        case 1: return "Sword";
        case 2: return "Fighting";
        case 3: return "Flying";
        case 4: return "Remote";
        case 5: return "WhiteMagic";
        case 6: return "BlackMagic";
        case 7: return "Wood";
        case 8: return "Metal";
        case 9: return "Fire";
        case 10: return "Wind";
        case 11: return "Water";
        case 12: return "Enhanced";
        default: return "Bug01";
    }
    return "Bug01";
}