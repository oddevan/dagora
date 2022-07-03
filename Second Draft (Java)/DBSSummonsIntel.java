/**
 * Abstract class DBSSummonsIntel - write a description of the class here
 * 
 * @author: 
 * Date: 
 */
public abstract class DBSSummonsIntel implements DBSIntel
{
    public DBSSummonsIntel() { myChar = null; }
    public DBSSummonsIntel(DBSSummonCharacter mine) { myChar = mine; }

    public abstract DBSSummonsIntel GetNewIntel(DBSSummonCharacter mine);
    
    void SetChar(DBSSummonCharacter mine) { myChar = mine; }
    
    public abstract int ChooseCommand(DBSBattle battle);
    
    public int ChooseAttack(DBSBattle battle) { return -1;}
    
    public abstract int ChooseAttackVictim(DBSBattle battle, DBSAttack attack);
    
    public int ChooseItem(DBSBattle battle) { return -1;}
    
    public int ChooseItemVictim(DBSBattle battle, DBSItem itm) { return -1;}
    
    public int ChooseSummons(DBSBattle battle) { return -1; }
    
    protected DBSSummonCharacter myChar;
}
