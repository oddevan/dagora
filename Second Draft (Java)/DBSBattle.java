
/**
 * Write a description of class DBSBattle here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class DBSBattle
{
    public static int Queue_Size = (2 * DBSTeam.Max_Active);

    public DBSBattle()
    {
        Team1 = null;
        Team2 = null;
        myNumPlayers = 0;
        myQueue = new DBSCharacter[Queue_Size];
        
        NullQueue();
    }
    
    public DBSBattle(DBSTeam firstTeam, DBSTeam secondTeam)
    {
        Team1 = firstTeam;
        Team2 = secondTeam;
        myNumPlayers = Team1.NumActive() + Team2.NumActive();
        myQueue = new DBSCharacter[Queue_Size];
        
        NullQueue();
        
        // load queue
        int k;
        
        for (k = 0; k < Team1.NumActive(); k++)
            myQueue[k] = Team1.GetActive(k);
        k = Team1.NumActive();
        for (int j = 0; j < Team2.NumActive(); j++)
        {
            myQueue[k] = Team2.GetActive(j);
            k++;
        }
    }
        
    /** true if team1 won, false if team2 won */
    public boolean ExecuteStandardBattle()
    {
        System.out.println("[insert cool opening sequence here :p]\n");
        
        while (!StopBattle())
        {
            SortQueue();
            
            for (int k = 0; k < myNumPlayers; k++)
            {
                StandardTurn(myQueue[k]);
                if (StopBattle()) break;
            }
        }
        if (Team1.IsAlive()) FinishBattle(Team1, Team2);
        else FinishBattle(Team2, Team1);
        
        return Team1.IsAlive();
    }
        
    public void StandardTurn(DBSCharacter player)
    {
        if (StopBattle()) return;
        
        int victim, ind, xp = 0, myInd;
        boolean endTurn = !(player.StartTurn());
        DBSCharacter aChar;
        
        myInd = FindPlayer(player);
        
        while (!endTurn)
        {
            int cmd = player.ChooseCommand(this);
            switch (cmd)
            {
                case DBSCommandHandle.Status:
                    victim = player.ChooseAttackVictim(this, null);
                    if (victim != -1)
                    {
                        aChar = FindPlayer(victim, player);
                        if (aChar.Team() != player.Team())
                        {
                            System.out.println("Hey, no cheating!");
                        }
                        else
                        {
                            System.out.println(aChar + " Level: " + aChar.Level());
                            System.out.println("Status: " + DBSStatusHandle.Name(aChar.Status()));
                            System.out.print("HP: " + aChar.HP() + " / " + aChar.MaxHP());
                            System.out.println("  MP: " + aChar.MP() + " / " + aChar.MaxMP());
                            System.out.println("XP to level " + (aChar.Level() + 1) + ": " + aChar.LvUp());
                        }
                    }
                    break;
                default:
                case DBSCommandHandle.Attack:
                    victim = player.ChooseAttackVictim(this, player.StandardAttack());
                    if (victim != -1)
                    {
                        xp = player.StandardAttack().Exe(player, FindPlayer(victim, player), this);
                        endTurn = true;
                    }
                    break;
                case DBSCommandHandle.Special:
                    ind = player.ChooseAttack(this);
                    if (ind != -1)
                    {
                        victim = player.ChooseAttackVictim(this, player.GetAttack(ind));
                        if (victim != -1)
                        {
                            xp = player.GetAttack(ind).Exe(player, FindPlayer(victim, player), this);
                            endTurn = true;
                        }
                    }
                    break;
                case DBSCommandHandle.Adrenaline:
                    victim = player.ChooseAttackVictim(this, player.Class().GetCurrentRush());
                    if (victim != -1)
                    {
                        xp = player.Class().GetCurrentRush().Exe(player, FindPlayer(victim, player), this);
                        endTurn = true;
                    }
                    break;
                case DBSCommandHandle.Item:
                    ind = player.ChooseItem(this);
                    if (ind != -1)
                    {
                        victim = player.ChooseItemVictim(this, player.Team().GetItem(ind));
                        if (victim != -1)
                        {
                            if (player.Team().UseItem(ind, FindPlayer(victim, player)))
                                endTurn = true;
                            else System.out.println("No Effect.");
                        }
                    }
                    break;
                case DBSCommandHandle.Summon:
                    victim = FindPlayer(player);
                    if (victim != -1)
                    {
                        myQueue[victim] = player.ChooseAndSummon(this);
                        endTurn = true;
                    }
                    break;
                case DBSCommandHandle.Return:
                    victim = FindPlayer(player);
                    if (victim != -1)
                    {
                        myQueue[victim] = player.Return();
                        endTurn = true;
                    }
                    break;
            }
            player.XPUp(xp / 2);
            player.Team().QueueXP((xp / 2) + (xp % 2));
            System.out.println(player + " gained " + (xp / 2) + " XP");
            System.out.print("\n");
        }
        if (FindPlayer(player) == myInd) myQueue[myInd] = player.EndTurn();
    }
        
    public DBSTeam GetTeam1() { return Team1; }
    public DBSTeam GetTeam2() { return Team2; }
    public int NumPlayers() { return myNumPlayers; }
    public DBSCharacter GetFromQueue(int ind)
    {
        if ((ind >= 0) && (ind < myNumPlayers)) return myQueue[ind];
        else return null;
    }
    
    //------------------------------------------------------------
    
    private void NullQueue()
    {
        for (int k = 0; k < Queue_Size; k++) myQueue[k] = null;
    }
    
    private void SortQueue()
    {
        DBSCharacter temp;
       
        for (int j = 0; j < myNumPlayers - 1; j++)
        { 
            for (int k = myNumPlayers-1; k > 0; k--)
            {
                if (myQueue[k-1].Spd() < myQueue[k].Spd())
                {
                    temp = myQueue[k];
                    myQueue[k] = myQueue[k-1];
                    myQueue[k-1] = temp;
                }
            }
        }
    }
    
    private int FindPlayer(DBSCharacter player)
    {
        for (int k = 0; k < myNumPlayers; k++) if (myQueue[k] == player) return k;
        return -1;
    }
    
    private DBSCharacter FindPlayer(int victim, DBSCharacter player)
    {
        if (victim < myNumPlayers) return myQueue[victim];
        else
        {
            victim -= myNumPlayers;
            if (victim < player.NumSummons()) return player.GetSummons(victim);
        }
        return null;
    }
    
    private boolean StopBattle()
    {
        return (!((Team1.IsAlive()) && (Team2.IsAlive())));
    }
    
    private void FinishBattle(DBSTeam winner, DBSTeam loser)
    {
        int xp = winner.GetXP();
        int k, j;
        DBSCharacter battleChar;
        DBSPlayableCharacter character;
        
        for (k = 0; k < myNumPlayers; k++)
        {
            battleChar = myQueue[k];
            battleChar.Return();
        }
        
        for (k = 0; k < winner.NumActive(); k++)
        {
            character = winner.GetActive(k);
            
            if (character.IsAlive())
            {
                character.XPUp(xp);
                System.out.println(character + " gained " + xp + " XP");
                if (character.CanSummon())
                {
                    for (j = 0; j < character.NumSummons(); j++)
                    {
                        if (character.GetSummons(j).IsAlive())
                        {
                            character.GetSummons(j).XPUp(xp);
                            System.out.println("    " + character.GetSummons(j) + " gained " + xp + " XP");
                        }
                        else
                        {
                            System.out.println("    " + character.GetSummons(j) + " did not receive XP");
                        }
                    }
                }
            }
            else
            {
                System.out.println(character + " did not receive XP");
                if (character.CanSummon()) System.out.println("    " + character + "'s summons did not receive XP");
            }
        }
        
        for (k = 0; k < loser.NumItems(); k++)
        {
            winner.AddItem(loser.GetItem(k), loser.GetItemUses(k));
            System.out.print("Received " + loser.GetItemUses(k) + " ");
            if (loser.GetItemUses(k) > 1)
                System.out.println(loser.GetItem(k) + ".");
            else
                System.out.println(loser.GetItem(k) + "s.");
        }
        loser.ItemsTaken();
    }
    
    //-----------------------------------------------------------------
    
    private DBSTeam Team1;
    private DBSTeam Team2;
    private int myNumPlayers;
    private DBSCharacter[] myQueue;
}
