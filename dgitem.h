#ifndef dgitem_H
#define dgitem_H

/*
    DGItem class decleration
    (c) 2003 root-1 Software
*/

struct DGItem
{
    DGItem();
    DGItem(int itInd, int itUse);
        
    int Ind;
    int Uses;
};

//#include dgitem.cpp

#endif