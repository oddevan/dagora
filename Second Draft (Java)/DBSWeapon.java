
/**
 * DGWeapon is designed to model a weapon or other piece of equipment the
 * character can carry. All fields must be set at construction; the fields
 * are all public fields therefore there are no accessors.
 * 
 * @author Evan Hildreth (root -1 Entertainment) 
 * @version 0.1 Java
 */
public class DBSWeapon
{
    /**
     * Type value for all attack weapons (swords, knives, etc.). This allows the
     * Character class to prevent two many attack weapons being equipped at once.
     */
    public static final int Atk_Wep = 0;
    /**
     * Type value for all defense weapons (shields, mail, etc.). This allows the
     * Character class to prevent two many defense weapons being equipped at once.
     */
    public static final int Def_Wep = 1;
    
    /** The type of weapon (see Atk_Wep and Def_Wep) */
    public final int Type;
    /** Increase HP by this much (ignore 0) */
    public final int HPUp;
    /** Increase MP by this much (ignore 0) */
    public final int MPUp;
    /** Increase Attack by this much (ignore 0) */
    public final int AtkUp;
    /** Increase Magic by this much (ignore 0) */
    public final int MagUp;
    /** Increase Defense by this much (ignore 0) */
    public final int DefUp;
    /** Increase Speed by this much (ignore 0) */
    public final int SpdUp;
    /** Increase Accuracy by this much (ignore 0) */
    public final int AccUp;
    /** True if a defined weapon is present, false if not */
    public final boolean Defined;
    
    /** Default constructor. Sets defined to false and all mods to -1 */
    public DBSWeapon()
    {
        Type = -1;
        HPUp = -1;
        MPUp = -1;
        AtkUp = -1;
        MagUp = -1;
        DefUp = -1;
        SpdUp = -1;
        AccUp = -1;
        Defined = false;
    }
    
    /**
     * The main constructor. Use this one to actually set values.
     * 
     * @param typ Sets Type
     * @param hp  Sets HPUp
     * @param mp  Sets MPUp
     * @param atk Sets AtkUp
     * @param mag Sets MagUp
     * @param def Sets DefUp
     * @param spd Sets SpdUp
     * @param acc Sets AccUp
     */
    public DBSWeapon(int typ, int hp, int mp, int atk, int mag,
                    int def, int spd, int acc)
    {
        Type = typ;
        HPUp = hp;
        MPUp = mp;
        AtkUp = atk;
        MagUp = mag;
        DefUp = def;
        SpdUp = spd;
        AccUp = acc;
        Defined = true;
    }
}
