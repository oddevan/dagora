
/**
 * This is the interface that should be implemented by all items. Be creative!
 * 
 * @author Evan Hildreth
 * @author root -1 Entertainment
 * @version 0.1 Java
 */

public interface DBSItem
{
    /**
     * Returns the item's name. This name should be unique to any other in the
     * program
     * 
     * @return  item's name 
     */
    public String Name();
    
    /**
     * Uses the item on the given <code>DBSCharacter</code>. If this method
     * returns false, then the number of items <b>should not be
     * decremented</b>!
     * 
     * @param   victim  <code>DBSCharacter</code> to have the item used on
     * @return  if item can be used.
     */
    public boolean Use(DBSCharacter victim);
    
    public String toString();
}
