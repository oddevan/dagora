/*
    DGItemHandle class implementation
    (c) 2003 root-1 Software
*/

#include "dgitemhandle.h"

DGItemHandle::DGItemHandle()
{
}

char* DGItemHandle::Name(int ind) const
{
    switch (ind)
    {
        case 0: return "Potion";
        case 1: return "Ether";
        case 2: return "Phoenix Down";
        case 3: return "Cure";
        case 4: return "Rest Potion";
        default: return "Bug02";
    }
    return "Bug02";
}

   
bool DGItemHandle::Use(DGCharacter* victim, int ind) const
{
    switch (ind)
    {
        case 0: //Potion
            if (victim->HP() == victim->MaxHP()) return false;
            victim->HPUp(30);
            return true;
        case 1: //Ether
            if (victim->MP() == victim->MaxMP()) return false;
            victim->MPUp(30);
            return true;
        case 2: //Phoenix Down
            if (victim->Status() != 'k') return false;
            victim->Revive();
            return true;
        case 3: //Cure
            if (victim->Status() == ('n' || 'k')) return false;
            victim->ChangeStatus('n');
            return true;
        case 4: //Rest Potion
            if (victim->Status() == 'k') victim->Revive();
            victim->HPUp(victim->MaxHP());
            victim->MPUp(victim->MaxMP());
            victim->ChangeStatus('n');
            return true;
        default: return false;
    }
    return false;
}
