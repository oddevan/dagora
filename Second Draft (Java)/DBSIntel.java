
/**
 * This interface is designed to give a framework for all intelligence modules
 * working with a character. In other words, each intelligence should perform
 * the following actions in some way shape or form. This can be intelligent
 * problem-solving, or it can be as simple as throwing some menus on the screen
 * to prompt a human player.
 * 
 * @author Evan Hildreth (root -1 Entertainment)
 * @version 0.1 Java
 */

public interface DBSIntel
{
    /**
     * Chooses the action for the character to perform
     * 
     * @param  battle   <code>DBSBattle</code> the character is acting in
     * @return      action for character to perform 
     */
    public int ChooseCommand(DBSBattle battle);
    
    /**
     * Chooses the special attack for the character to perform
     * 
     * @param  battle   <code>DBSBattle</code> the character is acting in
     * @return      index in character's GetAttack(int) method 
     */
    public int ChooseAttack(DBSBattle battle);
    
    /**
     * Chooses the victim for the character to attack. This can include
     * any character in the given battle. The intel module must make sure
     * the attacking character has enough MP to perform the attack.
     * 
     * @param  battle   <code>DBSBattle</code> the character is acting in
     * @param  attack   attack the character is using
     * @return      index in the battle's GetFromQueue(int) method
     */
    public int ChooseAttackVictim(DBSBattle battle, DBSAttack attack);
    
    /**
     * Chooses an item for the character to use. Although not required,
     * it is recommended that the intel module make sure the item can be
     * used at the time before attempting to use it.
     * 
     * @param  battle   DBSBattle the character is acting in
     * @return      index in the character's team's GetItem(int) method
     */
    public int ChooseItem(DBSBattle battle);
    
    /**
     * Chooses a character for the character to use the given item on.
     * Although not required, it is recommended that the intel module
     * make sure the item can be used at the time before attempting to
     * use it.
     * 
     * @param  battle   DBSBattle the character is acting in
     * @param  itm      item the character is using
     * @return      index in battle's GetFromQueue(int) method
     */
    public int ChooseItemVictim(DBSBattle battle, DBSItem itm);
    
    /**
     * Chooses a monster for the character to summon. This is only useful
     * for certain types of characters; all others should return -1 instead.
     * Those that can summon, it should return the index of the monster
     * to be summoned.
     * 
     * @param  battle   DBSBattle the character is acting in
     * @return      index in character's GetSummon(int) method
     */
    public int ChooseSummons(DBSBattle battle);

}
