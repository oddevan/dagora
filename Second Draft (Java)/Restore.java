
/**
 * Adds 200HP and restores status of an entire team.
 * This is a class that implements the <code>DBSAttack</code> interface.
 * 
 * @author Evan Hildreth 
 * @version 1.0
 */
public class Restore implements DBSAttack
{
    /**
     * Gets the name of the attack
     * 
     * @return  "Restore"
     */
    public String Name() { return "Restore"; }
    
    
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
    public int Pow() { return 0; }
    
    
    /**
     * Returns amount of MP needed to attack
     * 
     * @return  3 
     */
    public int Draw() { return 7; }
    
    
    /**
     * Returns whether or not attack attacks a whole team or just one person
     * 
     * @return  false 
     */
    public boolean IsTeam() { return true; }
    
    
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
	   DBSTeam defendingTeam = defender.Team();
	   attacker.ModMP(-7);
	   
	   int HPbefore, totHPlost = 0;
	   
	   for (int k = 0; k < battle.NumPlayers(); k++)
	   {
	       defender = battle.GetFromQueue(k);
	       if ((defender.IsAlive()) && (defender.Team() == defendingTeam))
	       {
	           HPbefore = defender.HP();
	           defender.ModHP(30);
	           System.out.println(defender + " gained " + (defender.HP() - HPbefore) + " HP.");
	           if (defender.Status() != DBSStatusHandle.Normal)
	           {
	               defender.ChangeStatus(DBSStatusHandle.Normal);
	               System.out.println(defender + "'s health returned.");
	           }
	           totHPlost += (defender.HP() - HPbefore);
	       }
	   }
	   return totHPlost;
	}
}
