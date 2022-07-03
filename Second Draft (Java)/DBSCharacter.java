
/**
 * This is the class that does most of the work in the Dagora Battle System.
 * It's intended to be a superclass for any type of character needed.
 * 
 * @author Evan Hildreth (root -1 Entertainment)
 * @version 0.1 Java
 */
public class DBSCharacter
{
    /** Maximum number of attacks possible for the character */
    public static final int Num_Attacks = 25;
    
    /** Max number of weapons able to equip */
    public static final int Num_Weapons = 4;
    
    /** Max number of abilities able to learn */
    public static final int Num_Abilities = 3;
    
    /** Number of XP to rise to next level; current level is multiplied by this */
    public static final int XP_Lv = 50;
    
    /** When HP/MaxHP is less than this, char enters Adrenaline mode */
    public static final double Rush_Ratio = 0.2;
    
    /**
     * Default constructor
     */
    public DBSCharacter()
    {
        myName = new String("--empty--");
        myLevel = -1;
        myInRush = false;
        myHP = -1;
        myMP = -1;
        myMaxHP = -1;
        myMaxMP = -1;
        myAtkLv = -1;
        myDefLv = -1;
        myMagLv = -1;
        mySpdLv = -1;
        myAccLv = -1;
        myLuck = -1.0;
        myElement = -1;
        myIntel = null;
        myTeam = null;
        myStatus = DBSStatusHandle.Normal;
        myNumWeapons = 0;
        myWeapons = null;
        myNumAttacks = 0;
        myAttacks = null;
        myNumAbilities = 0;
        myAbilities = null;
        myClass = null;
        myStandardAttack = null;
    }
    
    /**
     * Main constructor
     */
    public DBSCharacter(String name, int level, int hp, int mp, int maxhp,
                       int maxmp, int atk, int def, int mag, int spd, int acc,
                       int luc, int element, DBSAttack stdAtk, DBSClass job)
    {
        myName = new String(name);
        myLevel = level;
        myInRush = false;
        myHP = hp;
        myMP = mp;
        myMaxHP = maxhp;
        myMaxMP = maxmp;
        myAtkLv = atk;
        myDefLv = def;
        myMagLv = mag;
        mySpdLv = spd;
        myAccLv = acc;
        myLuck = luc;
        myElement = element;
        myIntel = null;
        myTeam = null;
        myStatus = DBSStatusHandle.Normal;
        myNumWeapons = 0;
        myWeapons = new DBSWeapon[Num_Weapons];
        myNumAttacks = 0;
        myAttacks = new DBSAttack[Num_Attacks];
        myNumAbilities = 0;
        myAbilities = new int[Num_Abilities];
        myClass = new DBSClass(job);
        myStandardAttack = stdAtk;
    }
    
    /**
     * Gives the character's name
     * 
     * @return this.Name()
     */
    public String toString()
    {
        return myName;
    }
    
    //modifiers
    
    public void ModHP(int value)
    {
        myHP += value;
        if (myHP > myMaxHP) myHP = myMaxHP;
        else if (myHP <= 0)
        {
            myStatus = DBSStatusHandle.KO;
            myHP = 0;
            //cout << myName << " fell." << endl;
            if (myInRush) ExitRush();
        }
        
        if (myInRush)
        {
            if (!CheckRush()) ExitRush();
        }
        else
        {
            if (CheckRush()) EnterRush();
        }
    }
    
    public void ModMP(int value)
    {
        myMP += value;
        if (myMP > myMaxMP) myMP = myMaxMP;
        else if (myMP < 0) myMP = 0;
    }
    
    public void XPUp(int value)
    {
        myLvUp -= value;
        myXP += value;
        
        while (myLvUp <= 0) LevelUp();
    }
    
    public void Revive()
    {
        myStatus = DBSStatusHandle.Normal;
        myHP = 1;
        EnterRush();
    }
    
    public void ChangeStatus(int stat)
    {
        if (DBSStatusHandle.IsLegalStatus(stat)) myStatus = stat;
    }
    
    public void LevelUp()
    {
        final double STAT_INCREASE = 0.25;
        
        if (myLvUp > 0) return;
        
        myAtkLv += DBSUtils.RoundDouble((double)myAtkLv * STAT_INCREASE);
        myDefLv += DBSUtils.RoundDouble((double)myDefLv * STAT_INCREASE);
        myMagLv += DBSUtils.RoundDouble((double)myMagLv * STAT_INCREASE);
        mySpdLv += DBSUtils.RoundDouble((double)mySpdLv * STAT_INCREASE);
        myAccLv += DBSUtils.RoundDouble((double)myAccLv * STAT_INCREASE);
        
        int plusme = DBSUtils.RoundDouble((double)myMaxHP * STAT_INCREASE);
        myMaxHP += plusme;
        myHP += plusme;
        plusme = DBSUtils.RoundDouble((double)myMaxMP * STAT_INCREASE);
        myMaxMP += plusme;
        myMP += plusme;
        
        myStatus = DBSStatusHandle.Normal;
        myLevel++;
        myLvUp += myLevel*XP_Lv;
        
        //cout << myName << " grew to level " << myLevel << endl;
        
        myClass.SPUp(this);
    }
    
    public void SetTeam(DBSTeam newTeam)
    {
        myTeam = newTeam;
    }
    
    public boolean Equip(DBSWeapon newbie)
    {
        int slot = -1;
        
        for (int k = 0; k < Num_Weapons; k++)
        {
            if (!myWeapons[k].Defined)
            {
                slot = k;
                break;
            }
        }
        if (slot == -1) return false;
        
        if (newbie.Type == DBSWeapon.Atk_Wep)
        {
            if (!(myWeapons[DBSWeapon.Atk_Wep].Defined))
            {
                myWeapons[DBSWeapon.Atk_Wep] = newbie;
                myNumWeapons++;
            }
            else return false;
        }
        else if (newbie.Type == DBSWeapon.Def_Wep)
        {
            if (!(myWeapons[DBSWeapon.Def_Wep].Defined))
            {
                myWeapons[DBSWeapon.Def_Wep] = newbie;
                myNumWeapons++;
            }
            else return false;
        }
        else if ((slot != DBSWeapon.Atk_Wep) && (slot != DBSWeapon.Def_Wep))
        {
            myWeapons[slot] = newbie;
            myNumWeapons++;
        }
        else return false;
        
        myHP += newbie.HPUp;
        myMaxHP += newbie.HPUp;
        myMP += newbie.MPUp;
        myMaxMP += newbie.MPUp;
        myAtkLv += newbie.AtkUp;
        myDefLv += newbie.DefUp;
        myMagLv += newbie.MagUp;
        mySpdLv += newbie.SpdUp;
        myAccLv += newbie.AccUp;
        return true;
    }
    
    public DBSWeapon Dequip(int slot)
    {
        DBSWeapon dequipped;
    
        if ((slot < 0) || (slot > Num_Weapons)) return new DBSWeapon();
        dequipped = myWeapons[slot];
        myWeapons[slot] = new DBSWeapon();
        myNumWeapons--;
        return dequipped;
    }
    
    public boolean Learn(DBSAttack attack)
    {
        if (myNumAttacks == Num_Attacks) return false;
    
        myAttacks[myNumAttacks] = attack;
        myNumAttacks++;
        return true;
    }
    
    public boolean Learn(int ability)
    {
        if (myNumAbilities == Num_Abilities) return false;
        
        myAbilities[myNumAbilities] = ability;
        myNumAbilities++;
        return true;
    }
    
    public DBSAttack ForgetAttack(int ind)
    {
        if (myNumAttacks == 0) return new DBSSimpleAttack();
        
        DBSAttack forgot = myAttacks[ind];
        
        for (int k = ind; k < (myNumAttacks - 1); k++)
            myAttacks[k] = myAttacks[k+1];
        myNumAttacks--;
        return forgot;
    }
    
    public int ForgetAbility(int ind)
    {
        if (myNumAbilities == 0) return -1;
        
        int forgot = myAbilities[ind];
        
        for (int k = ind; k < (myNumAbilities - 1); k++)
            myAbilities[k] = myAbilities[k+1];
        myNumAbilities--;
        return forgot;
    }
    
    public void ClassLevelUp()
    {
        if (myClass.CanLevelUp()) myClass.LevelUp();
    }
    
    public void ClassLevelDown()
    {
        if (myClass.Level() != 0) myClass.LevelDown();
    }
    
    //info functions
    
    public boolean IsAlive()
    {
        return (myStatus != DBSStatusHandle.KO);
    }
    
    public int NormalAtkPow(int type, int pow)
    {
        int tab;
        
        tab = Atk() * pow;
        if (type == myElement) tab += (tab / 2);
        return tab;
    }
    
    public int MagicAtkPow(int type, int pow)
    {
        int tab;
        
        tab = Mag() * pow;
        if (type == myElement) tab += (tab / 2);
        return tab;
    }
    
    public int DefPow(int type)
    {
        int looked;
        double tab = (double)Def() / 2.0;
        
        looked = DBSTypeHandle.Lookup(type, myElement);
        if (looked == 1) tab *= 1.5;
        else if (looked == 2) tab /= 1.5;
        else if (looked == -1) tab *= -1.0;
            //negates defense, resultes in negative damage (absorb)
        
        return DBSUtils.RoundDouble(tab);
    }
    
    public boolean HasAbility(int ability)
    {
        for (int k = 0; k < myNumAbilities; k++)
            if (myAbilities[k] == ability) return true;
        return false;
    }
    
    public void PrintAttacks()
    {
        for (int k = 0; k < myNumAttacks; k++)
        {
            if (myAttacks[k] != null)
            {
                System.out.println(k + " " + myAttacks[k]);
            }
        }
    }
    
    //battle functions
    public int ChooseCommand(DBSBattle battle) { return myIntel.ChooseCommand(battle); }
    public int ChooseAttack(DBSBattle battle) { return myIntel.ChooseAttack(battle); }
    public int ChooseAttackVictim(DBSBattle battle, DBSAttack attack) { return myIntel.ChooseAttackVictim(battle, attack); }
    public int ChooseItem(DBSBattle battle) { return myIntel.ChooseItem(battle); }
    public int ChooseItemVictim(DBSBattle battle, DBSItem item) { return myIntel.ChooseItemVictim(battle, item); }
    
    public boolean StartTurn()
    {
        return (DBSStatusHandle.Act(myStatus, this) && IsAlive());
    }
    
    /** Mostly in place for subclass use */
    public DBSCharacter EndTurn()
    {
        return this;
    }
    
    //Subclass placeholders
    
    public DBSCharacter ChooseAndSummon(DBSBattle battle) { return this; }
    public DBSCharacter Return() { return this; }
    public int NumSummons(){ return 0; }
    public DBSCharacter GetSummons(int ind) { return null; }
    
    //Command functions - most characters cannot do these, but there are those who can.
    public boolean CanSummon() { return false; }
    public boolean CanTransform() { return false; }
    
    //Adjusted stats: using these is preferable to the below
    
    public int Atk()
    {
        if (!myInRush)
            return myAtkLv;
        else
            return DBSUtils.RoundDouble((double)myAtkLv * 1.25);
    }
    
    public int Def()
    {
        if (!myInRush)
            return myDefLv;
        else
            return DBSUtils.RoundDouble((double)myDefLv * 0.75);
    }
    
    public int Mag()
    {
        if (!myInRush)
            return myMagLv;
        else
            return DBSUtils.RoundDouble((double)myMagLv * 1.75);
    }
    
    public int Spd()
    {
        if (!myInRush)
            return mySpdLv;
        else
            return DBSUtils.RoundDouble((double)mySpdLv * 1.50);
    }
    
    public int Acc()
    {
        if (!myInRush)
            return myAccLv;
        else
            return DBSUtils.RoundDouble((double)myAccLv * 2.00);
    }
    
    public String Name() { return myName; }
    public int Level() { return myLevel; }
    public int LvUp() { return myLvUp;}
    public int XP() { return myXP;}
    public boolean InRush() { return myInRush; }
    public int HP() { return myHP; }
    public int MP() { return myMP; }
    public int MaxHP() { return myMaxHP; }
    public int MaxMP() { return myMaxMP; }
    public int AtkLv() { return myAtkLv; }
    public int DefLv() { return myDefLv; }
    public int MagLv() { return myMagLv; }
    public int SpdLv() { return mySpdLv; }
    public int AccLv() { return myAccLv; }
    public double Luck() { return myLuck; }
    public int Element() { return myElement; }
    public DBSIntel Intel() { return myIntel; }
    public DBSTeam Team() { return myTeam; }
    public int Status() { return myStatus; }
    public int NumWeapons() { return myNumWeapons; }
    public DBSWeapon GetWeapon(int ind) { return myWeapons[ind]; }
    public int NumAttacks() { return myNumAttacks; }
    public DBSAttack GetAttack(int ind) { return myAttacks[ind]; }
    public int NumAbilities() { return myNumAbilities; }
    public int GetAbility(int ind) { return myAbilities[ind]; }
    public DBSClass Class() { return myClass; }
    public DBSAttack StandardAttack() { return myStandardAttack; }

    //---------------------------------------------

    protected void SetIntel(DBSIntel intel) { myIntel = intel; }
    protected void SetStdAtk (DBSAttack atk) { myStandardAttack = atk;}

    //---------------------------------------------

    private void EnterRush() { myInRush = true; }
    private void ExitRush() { myInRush = false; }
    private boolean CheckRush()
    {
        return (((double)myHP / (double)myMaxHP) <= Rush_Ratio);
    }

    private String myName;
    private int myLevel;
    private int myLvUp;
    private int myXP;
    private boolean myInRush;
    private int myHP;
    private int myMP;
    private int myMaxHP;
    private int myMaxMP;
    private int myAtkLv;
    private int myDefLv;
    private int myMagLv;
    private int mySpdLv;
    private int myAccLv;
    private double myLuck;
    private int myElement;
    private DBSIntel myIntel;
    private DBSTeam myTeam;
    private int myStatus;
    private int myNumWeapons;
    private DBSWeapon[] myWeapons;
    private int myNumAttacks;
    private DBSAttack[] myAttacks;
    private int myNumAbilities;
    private int[] myAbilities;
    private DBSClass myClass;
    private DBSAttack myStandardAttack;
}
