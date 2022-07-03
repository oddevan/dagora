
/**
 * The Driver Class
 * 
 * This system isn't quite done, there are still a few C++ kinks to work out, but most of it
 * is here!
 * 
 * @author Evan Hildreth (root -1 Entertainment) 
 * @version 0.1 Java
 */
public class Driver
{
    public static void main(String[] args)
    {
        System.out.println("DBS testing... (version 0.1 Java)");
        System.out.println("All output is (c) root -1 Entertainment! Don't touch!");
        
        DBSPlayableCharacter Ereb, Ronyo, Kyrra, Zach, Omri;
        DBSSummonCharacter Dragon, Phoenix;
        
        DBSAttack[] atkData = new DBSAttack[2];
        atkData[0] = new DBSSimpleAttack("Punch", DBSTypeHandle.Normal, 2, 3, false, DBSStatusHandle.Normal, false);
        atkData[1] = new DBSSimpleAttack("Kick", DBSTypeHandle.Normal, 3, 5, false, DBSStatusHandle.Normal, false);
        int[] costData = {5, 5};
        DBSAttack[] rushData = new DBSAttack[2];
        atkData[0] = new DBSSimpleAttack("SuperPunch", DBSTypeHandle.Normal, 5, 0, false, DBSStatusHandle.Normal, false);
        atkData[1] = new DBSSimpleAttack("SuperKick", DBSTypeHandle.Normal, 5, 0, false, DBSStatusHandle.Normal, false);
        DBSClass data = new DBSClass(2, 1, atkData, costData, rushData);
        
        DBSHumanPlayableIntel playIntel = new DBSHumanPlayableIntel();
        DBSHumanSummonsIntel sumIntel = new DBSHumanSummonsIntel();
            
        DBSTeam goodGuys, badGuy;
        
        goodGuys = new DBSTeam();
        /*goodGuys.Join(Ereb);
        goodGuys.Join(Ronyo);
        goodGuys.Join(Kyrra);
        goodGuys.Join(Zach);
        goodGuys.AddItem(0, 10);
        goodGuys.AddItem(1, 5);
        goodGuys.AddItem(2, 3);*/
        
        badGuy = new DBSTeam();
        //badGuy.Join(Omri);
        //badGuy.AddItem(3, 5);
        
        DBSBattle battle = new DBSBattle(goodGuys, badGuy);
        
        /*if (battle.ExecuteStandardBattle())
        {
            cout << "You Won! The evil tyrant was vanguished and all was made right again." << endl;
        }
        else
        {
            cout << "You lost and your charred carcasses were scattered as an example to" << endl;
            cout << "all who oppose the mighty wrath of Omri. Muahahaha!" << endl;
        }*/
    }
}
