//
//  dgweapon.cpp
//  dagora
//
//  Created by eph on Thu Feb 27 2003.
//  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
//

#include "dgweapon.h"

DGWeapon::DGWeapon()
{
    Type = -1;
    HPUp = 0;
    MPUp = 0;
    AtkUp = 0;
    DefUp = 0;
    MagUp = 0;
    SpdUp = 0;
    AccUp = 0;
    Defined = false;
}

DGWeapon::DGWeapon(int typ, int hp, int mp, int atk, int def, int mag, int spd, int acc)
{
    Type = typ;
    HPUp = hp;
    MPUp = mp;
    AtkUp = atk;
    DefUp = def;
    MagUp = mag;
    SpdUp = spd;
    AccUp = acc;
    Defined = true;
}