
/**
 * A typical human-controlled character.
 * 
 * @author Evan Hildreth (root -1 Entertainment)
 * @version 0.1 Java
 */
public class DBSPlayableCharacter extends DBSCharacter
{
    public static final int Num_Sum = 5;
    
    public DBSPlayableCharacter()
    {
        super();
        myPlayIntel = null;
        myNumSummons = -1;
        mySummons = null;
    }
    
    public DBSPlayableCharacter(String name, int level, int hp, int mp, int maxhp,
                                int maxmp, int atk, int def, int mag, int spd, int acc,
                                int luc, int element, DBSAttack stdAtk, DBSClass job,
                                DBSPlayableIntel intel)
    {
        super(name, level, hp, mp, maxhp, maxmp, atk, def, mag, spd, acc, luc, element, stdAtk, job);
        myPlayIntel = intel.GetNewIntel(this);
        super.SetIntel(myPlayIntel);
        
        myNumSummons = 0;
        mySummons = new DBSSummonCharacter[Num_Sum];
    }
    
    // Useful stuff
    
    public boolean Link(DBSSummonCharacter summon)
    {
        if (myNumSummons >= Num_Sum) return false;
        
        mySummons[myNumSummons] = summon;
        myNumSummons++;
    	summon.SetChar(this);
        return true;
    }
    
    public DBSSummonCharacter UnLink(int ind)
    {
        DBSSummonCharacter summon;
        
        summon = mySummons[ind];
        for (int k = ind; k < (myNumSummons - 1); k++)
            mySummons[k] = mySummons[k+1];
        myNumSummons--;
        return summon;
    }
    
    public DBSCharacter ChooseAndSummon(DBSBattle battle)
    {
        return mySummons[myPlayIntel.ChooseSummons(battle)];
    }
    
    public boolean CanSummon()
    {
        return (HasAbility(DBSCommandHandle.Summon) && (myNumSummons > 0));
    }
    
    public int NumSummons(){ return myNumSummons; }
    
    public DBSCharacter GetSummons(int ind) { return GetRealSummons(ind); }
    
    public DBSPlayableIntel GetPlayIntel() { return myPlayIntel; }
    
    public DBSSummonCharacter GetRealSummons(int ind)
    {
        if ((myNumSummons > 0) && ((ind >= 0) && (ind < myNumSummons)))
        {
            return mySummons[ind];
        }
        return null;
    }
    
    private DBSPlayableIntel myPlayIntel;
    private int myNumSummons;
    private DBSSummonCharacter[] mySummons;
}
