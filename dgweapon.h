#ifndef dgweapon_H
#define dgweapon_H

//
//  dgweapon.h
//  dagora
//
//  Created by eph on Thu Feb 27 2003.
//  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
//

struct DGWeapon
{
    DGWeapon();
    DGWeapon(int typ, int hp, int mp, int atk, int def, int mag, int spd, int acc);
    
    int Type;		//Which slot to equip to?
        //0: Attacking weapon (sword, bow, etc)
        //1: Defense armor (Mythril mail, silk shirt, etc)
        //Anything else: Accessory (Speed ring, etc)
    int HPUp;		//Increases MaxHP by this
    int MPUp;		//Increases MaxMP by this
    int AtkUp;		//Increases Atk by this
    int DefUp;		//Increases Def by this
    int MagUp;
    int SpdUp;		//Increases Spd by this
    int AccUp;		//Increases Acc by this
    bool Defined;	//Is there a weapon here?
};

//#include dgweapon.cpp

#endif