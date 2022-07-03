
/**
 * Write a description of class DBSHumanSummonsIntel here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class DBSHumanSummonsIntel extends DBSSummonsIntel
{
    private EasyReader io;

    public DBSHumanSummonsIntel()
    {
        super();
        io = new EasyReader();
    }
    
    public DBSHumanSummonsIntel(DBSSummonCharacter mine)
    {
        super(mine);
        io = new EasyReader();
    }
    
    public DBSSummonsIntel GetNewIntel(DBSSummonCharacter mine)
    {
        return new DBSHumanSummonsIntel(mine);
    }
    
    public int ChooseCommand(DBSBattle battle)
    {
        int[] commands = new int[DBSCommandHandle.Total_Number];
        int numCmd = 0, choice;
        
        commands[numCmd] = DBSCommandHandle.Status;
        numCmd++;
        
        commands[numCmd] = DBSCommandHandle.Attack;
        numCmd++;
        
        if (myChar.InRush())
        {
            commands[numCmd] = DBSCommandHandle.Adrenaline;
            numCmd++;
        }
        
        commands[numCmd] = DBSCommandHandle.Return;
        numCmd++;
        
        System.out.print(myChar + ": HP " + myChar.HP());
        System.out.print(" MP " + myChar.MP() + "\n");
        
        for (int k = 0; k < numCmd; k++)
            System.out.println(k + ": " + DBSCommandHandle.Name(commands[k]));
        
        do
        {
            System.out.print("Choose an option: ");
            choice = io.readInt();
            io.readLine();
        } while ((choice >= numCmd) || (choice < 0));
        return commands[choice];   
    }
    
    public int ChooseAttackVictim(DBSBattle battle, DBSAttack attack)
    {
        int choice;
        int totVictims = DispVictims(battle);
        
        if (attack != null) System.out.println("Using attack " + attack.Name());
        do
        {
            System.out.print("Choose a character");
            if (attack.IsTeam())
                System.out.print(" (attacks team of this character)");
            System.out.print(": ");
            choice = io.readInt();
            io.readLine();
        } while ((choice >= totVictims) || (choice < -1));
        return choice;
    }
    
    private int DispVictims(DBSBattle battle)
    {
        DBSCharacter current = null;
        int k = 0, j = 0;
        
        for (k = 0; k < battle.NumPlayers(); k++)
        {
            current = battle.GetFromQueue(k);
            System.out.print(j + ": " + current);
            if ((current.Team()) == (myChar.Team()))
                System.out.print("  " + current.HP() + " / " + current.MaxHP());
            System.out.println();
            j++;
        }
        
        return (battle.NumPlayers());
    }
}
