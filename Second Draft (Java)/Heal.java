
/**
 * A simple Heal spell. This is a class that implements the
 * <code>DBSAttack</code> interface.
 * 
 * @author Evan Hildreth 
 * @version 1.0
 */
public class Heal implements DBSAttack
{
    /**
     * Gets the name of the attack
     * 
     * @return  "Heal"
     */
    public String Name() { return "Heal"; }
    
    
    /**
     * Returns the type of the attack as given in the
     * <code>DBSTypeHandle</code> class.
     * 
     * @return  <code>DBSTypeHandle.WhiteMagic</code> 
     */
    public int Type() { return DBSTypeHandle.WhiteMagic; }
    
    
    /**
     * Returns relative power of the attack
     * 
     * @return  1 
     */
    public int Pow() { return 1; }
    
    
    /**
     * Returns amount of MP needed to attack
     * 
     * @return  3 
     */
    public int Draw() { return 3; }
    
    
    /**
     * Returns whether or not attack attacks a whole team or just one person
     * 
     * @return  false 
     */
    public boolean IsTeam() { return false; }
    
    
    /**
     * Returns a string representation (the name) of any <code>DBSStatus</code>
     * possibly inflicted by this attack.
     * 
     * @return  "None" 
     */
    public String Status() { return "None"; }
    
    /**
     * This is a magic attack, so it returns true
     * 
     * @return true
     */
    public boolean IsMagic() { return true;}
    
    
	/**
	 * Has attacker heal defender. Uses Attacker's <code>GetMagicPow</code>
	 * method, since this is a magic-based attack.
	 * 
	 * @param  attacker	<code>DBSCharacter</code> healer
	 * @param  defender <code>DBSCharacter</code> getting healed
	 * @return	amount defender was healed 
	 */
	public int Exe(DBSCharacter attacker, DBSCharacter defender, DBSBattle battle)
	{
       attacker.ModMP(-3);
       if (defender.HP() == defender.MaxHP())
       {
           System.out.println("No Effect.");
           return 0;
       }
       else
       {
           int origHP = defender.HP();
           defender.ModHP(250);
           int xp = defender.HP() - origHP;
           System.out.println(defender + " regained " + xp + " HP.");
           return xp;
       }
	}
}
