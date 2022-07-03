
/**
 * A simple health potion! Perfect for when you need that quick
 * get-up-and-go. Instantly heals 50 HP, so you can keep going after
 * that critical hit.
 * 
 * @author Evan Hildreth 
 * @version 0.1 Java
 */
public class Potion implements DBSItem
{
    /**
     * This is a special, one-of-a-kind potion, but I'll keep things simple.
     * 
     * @return  "Potion" 
     */
    public String Name() { return "Potion"; }
    
    public String toString() { return "Potion"; }
    
    /**
     * Uses the potion on the given <code>DBSCharacter</code>. If this method
     * returns false, then the number of items <b>should not be
     * decremented</b>!
     * 
     * @param   victim  <code>DBSCharacter</code> to have the item used on
     * @return  if item can be used.
     */
    public boolean Use(DBSCharacter victim)
    {
        return false;
    }
}
