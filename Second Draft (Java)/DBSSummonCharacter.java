
/**
 *  A DGSummons is like a single-purpose character. They generally have only one attack that uses most, if not all,
 *  of their MP. The process is three-fold. A Playable summons the Summon, the Summon attacks, and then returns. At
 *  the end of the turn, if the Summons is out of MP, it automatically returns with no peanalty. When it returns, it
 *  automatically regains all MP.
 * 
 * @author Evan Hildreth (root -1 Entertainment) 
 * @version 0.1 Java
 */
public class DBSSummonCharacter extends DBSCharacter
{
    public DBSSummonCharacter()
    {
        super();
        mySumIntel = null;
        myChar = null;
    }
    
    public DBSSummonCharacter(String name, int level, int hp, int mp, int maxhp,
                              int maxmp, int atk, int def, int mag, int spd, int acc,
                              int luc, int element, DBSAttack stdAtk, DBSClass job,
                              DBSSummonsIntel intel)
    {
        super(name, level, hp, mp, maxhp, maxmp, atk, def, mag, spd, acc, luc, element, stdAtk, job);
        mySumIntel = intel.GetNewIntel(this);
        super.SetIntel(mySumIntel);
        
        SetStdAtk(stdAtk);
        
        myChar = null;
    }
    
    public boolean StartTurn()
    {
        if (MP() < StandardAttack().Draw()) return false;
        return super.StartTurn();
    }
    
    public DBSCharacter EndTurn()
    {
        if (MP() < StandardAttack().Draw()) return Return();
        else return super.EndTurn();
    }
        
    public DBSCharacter ChooseAndSummon(DBSBattle battle) { return this; }
    
    public DBSCharacter Return()
    {
        ModMP(MaxMP());
        if (IsAlive()) ChangeStatus(DBSStatusHandle.Normal);
        return myChar;
    }
        
    public void SetChar(DBSPlayableCharacter summoner)
    {
        myChar = summoner;
        SetTeam(summoner.Team());
    }
    
    public DBSPlayableCharacter GetLinked() { return myChar; }
    public DBSSummonsIntel GetSumIntel() { return mySumIntel; }
    
    private DBSPlayableCharacter myChar;
    private DBSSummonsIntel mySumIntel;
}
