
/**
 * This is the interface that should be implemented by all attack classes. It
 * contains the basic methods called by the battle system. How these methods
 * are implemented doesn't matter as long as they do what they're supposed to.
 * 
 * @author Evan Hildreth
 * @author root -1 Entertainment
 * @version 0.1 Java
 */

public interface DBSAttack
{
    /**
     * Gets the name of the attack
     * 
     * @return  Attack's name
     */
    public String Name();
    
    
    /**
     * Returns the type of the attack as given in the
     * <code>DBSTypeHandle</code> class.
     * 
     * @return  Attack's type 
     */
    public int Type();
    
    
    /**
     * Returns relative power of the attack
     * 
     * @return  Attack's power 
     */
    public int Pow();
    
    
    /**
     * Returns amount of MP needed to attack
     * 
     * @return  Attack's draw 
     */
    public int Draw();
    
    
    /**
     * Returns whether or not attack attacks a whole team or just one person
     * 
     * @return  If attack attacks whole team 
     */
    public boolean IsTeam();
    
    
    /**
     * Returns a string representation (the name) of any <code>DBSStatus</code>
     * possibly inflicted by this attack. Multiple statuses should be
     * seaperated by carrage returns ('\n'). "None" should be returned if there
     * are none.
     * 
     * @return  Name of any statuses inflicted by attack 
     */
    public String Status();
    
    /**
     * Whether this is a magic or physical based attack. If this method returns
     * true, then the Exe() method should use the GetMagAtkPow() method from the
     * character (if the attack depends on the character's Mag level).
     * 
     * @return true if magic-based attack
     */
    public boolean IsMagic();
    
	/**
	 * Executes the attack. What the attack does is anyone's guess, but it
	 * should involve the attacker performing some damage to either the
	 * defender or the defender's whole team.
	 * 
	 * @param  attacker	<code>DBSCharacter</code> making the attack
	 * @param  defender <code>DBSCharacter</code> defending against the attack
	 * @return	amount of damage done 
	 */
	public int Exe(DBSCharacter attacker, DBSCharacter defender, DBSBattle battle);
	
	public String toString();
}
