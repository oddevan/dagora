/**
 * Abstract class DBSPlayableIntel - write a description of the class here
 * 
 * @author: 
 * Date: 
 */
public abstract class DBSPlayableIntel implements DBSIntel
{
    public DBSPlayableIntel() { myChar = null; }
    public DBSPlayableIntel(DBSPlayableCharacter mine) { myChar = mine; }

    public abstract DBSPlayableIntel GetNewIntel(DBSPlayableCharacter mine);
    
    void SetChar(DBSPlayableCharacter mine) { myChar = mine; }
    
    public abstract int ChooseCommand(DBSBattle battle);
    
    public abstract int ChooseAttack(DBSBattle battle);
    
    public abstract int ChooseAttackVictim(DBSBattle battle, DBSAttack attack);
    
    public abstract int ChooseItem(DBSBattle battle);
    
    public abstract int ChooseItemVictim(DBSBattle battle, DBSItem itm);
    
    public abstract int ChooseSummons(DBSBattle battle);
    
    protected DBSPlayableCharacter myChar;
}
