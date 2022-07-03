
/**
 * This class handles different status types and their effect on characters.
 * Like <code>DBSTypeHandle</code>, this is a completely static class.
 * 
 * @author Evan Hildreth
 * @author root -1 Entertainment
 * @version 0.1 Java
 */
public class DBSStatusHandle
{
    public static final int TotNumStatus = 4;
    
    public static final int KO = 0;
    public static final int Normal = 1;
    public static final int Poison = 2;
    public static final int Sleep = 3;
    
    public static String Name(int status)
    {
        switch (status)
        {
            case KO:
                return "KO";
            case Normal:
                return "Normal";
            case Poison:
                return "Poison";
            case Sleep:
                return "Sleep";
        }
        return "None";
    }
    
    /** returns true if status is a given status in this class */
    public static boolean IsLegalStatus(int status)
    {
        return ((status == KO) || (status == Normal) ||
                (status == Poison) || (status == Sleep));
    }
    
    /**
     * Does stuff to the character based on status inflicted. Returns whether
     * or not character is allowed to have a turn.
     * 
     * @param   status  Status inflicted (use public constants)
     * @param   inflicted   <code>DBSCharacter</code> inflicted with said status
     * @return  If inflicted can have a turn
     */
    public static boolean Act(int status, DBSCharacter inflicted)
    {
        switch (status)
        {
            case KO: return false;
            case Normal: return true;
            case Poison:
                //inflicted.ModHP(-10);
                return true;
            case Sleep:
                /*if (Math.random() <= inflicted.Luck())
                {
                    inflicted.CureStatus(Sleep);
                    return true;
                }
                return false;*/
            default: return true;
        }
    }
}
