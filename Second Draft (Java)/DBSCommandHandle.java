
/**
 * This is a static class that holds constants for each different command.
 * To add a new command, give it a int value here and add a corresponding
 * block of code in the DBSBattle class.
 * 
 * @author Evan Hildreth, root -1 Entertainment 
 * @version 0.1 Java
 */
public class DBSCommandHandle
{
    /**
     * Total number of commands in this class
     */
    public static final int Total_Number = 7;
    
    public static final int Status = 0;
    public static final int Attack = 1;
    public static final int Special = 2;
    public static final int Item = 3;
    public static final int Adrenaline = 4;
    public static final int Summon = 5;
    public static final int Return = 6;
    
    /**
     * Returns a string representation of the command with the corresponding
     * number.
     * 
     * @param   ind     int value of command in question
     * @return          String representation of command
     */
    public static final String Name(int ind)
    {
        switch (ind)
        {
            case Status: return "Status";
            case Attack: return "Attack";
            case Special: return "Special";
            case Item: return "Item";
            case Adrenaline: return "Adrenaline";
            case Summon: return "Summon";
            case Return: return "Return";
            default: return "OutOfBound";
        }
    }
}
