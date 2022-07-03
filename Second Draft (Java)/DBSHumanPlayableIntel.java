
/**
 * Write a description of class DBSHumanPlayableIntel here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class DBSHumanPlayableIntel extends DBSPlayableIntel
{
    private EasyReader io;

    public DBSHumanPlayableIntel()
    {
        super();
        io = new EasyReader();
    }
    
    public DBSHumanPlayableIntel(DBSPlayableCharacter mine)
    {
        super(mine);
        io = new EasyReader();
    }
    
    public DBSPlayableIntel GetNewIntel(DBSPlayableCharacter mine)
    {
        return new DBSHumanPlayableIntel(mine);
    }
    
    public int ChooseCommand(DBSBattle battle)
    {
        int[] commands = new int[DBSCommandHandle.Total_Number];
        int numCmd = 0, choice;
        
        commands[numCmd] = DBSCommandHandle.Status;
        numCmd++;
        
        commands[numCmd] = DBSCommandHandle.Attack;
        numCmd++;
        
        if (myChar.NumAttacks() > 0)
        {
            commands[numCmd] = DBSCommandHandle.Special;
            numCmd++;
        }
        
        if (myChar.InRush())
        {
            commands[numCmd] = DBSCommandHandle.Adrenaline;
            numCmd++;
        }
        
        commands[numCmd] = DBSCommandHandle.Item;
        numCmd++;
        
        if (myChar.CanSummon())
        {
            commands[numCmd] = DBSCommandHandle.Summon;
            numCmd++;
        }
        
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
    
    public int ChooseAttack(DBSBattle battle)
    {
        int choice;
        DBSAttack attack;
        
        System.out.println(myChar + "'s Attacks:");
        while (true)
        {
            myChar.PrintAttacks();
            System.out.print("Choose Attack: ");
            choice = io.readInt();
            io.readLine();
            if (choice == -1) return -1;
            attack = myChar.GetAttack(choice);
            if (attack != null)
            {
                if (attack.Draw() > myChar.MP())
                    System.out.println("Not enough MP");
                else return choice;
            }
        }
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
    
    public int ChooseItem(DBSBattle battle)
    {
        int choice;
    
        myChar.Team().PrintItems();
        do
        {
            System.out.print("Choose Item: ");
            choice = io.readInt();
            io.readLine();
        } while ((choice >= myChar.Team().NumItems()) || (choice < -1));
        return choice;
    }
    
    public int ChooseItemVictim(DBSBattle battle, DBSItem itm)
    {
        int choice;
        
        System.out.println("Using item " + itm.Name());
        int totVictims = DispVictims(battle);
        do
        {
            System.out.print("Choose a character: ");
            choice = io.readInt();
            io.readLine();
        } while ((choice >= totVictims) || (choice < -1));
        return choice;
    }
    
    public int ChooseSummons(DBSBattle battle)
    {
        int choice;
        DBSSummonCharacter current;
        for (int k = 0; k < myChar.NumSummons(); k++)
        {
            current = myChar.GetRealSummons(k);
            System.out.print(k + ": " + current.Name());
            System.out.println(" " + current.HP() + " / " + current.MaxHP());
        }
        do
        {
            System.out.print("Choose a summons: ");
            choice = io.readInt();
            io.readLine();
        } while ((choice >= myChar.NumSummons()) || (choice < -1));
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
            System.out.println("");
            j++;
        }
        if (myChar.CanSummon())
        {
            System.out.println("  ----------");
            for (k = 0; k < myChar.NumSummons(); k++)
            {
                current = myChar.GetSummons(k);
                System.out.print(j + ": " + current);
                System.out.println(" " + current.HP() + " / " + current.MaxHP());
                j++;
            }
        }
        
        return (battle.NumPlayers() + myChar.NumSummons());
    }
}
