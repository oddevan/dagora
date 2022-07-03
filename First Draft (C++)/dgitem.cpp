/*
    DGItem class implementation
    (c) 2003 root-1 Software
*/

#include "dgitem.h"

DGItem::DGItem()
{
    Ind = -1;
    Uses = 0;
}

DGItem::DGItem(int itInd, int itUse)
{
    Ind = itInd;
    Uses = itUse;
}