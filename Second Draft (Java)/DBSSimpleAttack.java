
/**
 * A class that implements the DBSAttack interface. Everything is controlled with variables, and
 * the method of calculating the damage is generic. If an attack only requires a simple animation
 * (such as a character's standard attack) and does not need unique damage calculation (such as
 * a heal or esuna spell) then use an instance of this class instead.
 * 
 * @author Evan Hildreth (root -1 Entertainment) 
 * @version 0.1 Java
 */

import java.util.Random;

public class DBSSimpleAttack implements DBSAttack
{
    private String myName;
    private int myType;
    private int myPow;
    private int myDraw;
    private boolean myIsTeam;
    private int myStatus;
    private boolean myIsMagic;
    private Random cheese;

    /**
     * Default constructor
     */
    public DBSSimpleAttack()
    {
        myName = "";
        myType = 0;
        myPow = 0;
        myDraw = 0;
        myIsTeam = false;
        myStatus = 0;
        myIsMagic = false;
        cheese = new Random();
    }
    
    /**
     * Main constructor
     */
    public DBSSimpleAttack(String name, int type, int pow, int draw, boolean isTeam, int status, boolean isMagic)
    {
        myName = name;
        myType = type;
        myPow = pow;
        myDraw = draw;
        myIsTeam = isTeam;
        myStatus = status;
        myIsMagic = isMagic;
        cheese = new Random();
    }

    /**
     * Overrides Object.toString(). Prints out as follows<br>
     * [AttackName] [AttackType] MP: [Draw] [Norm or Magic] [IsTeam or not]
     * 
     * @return  String representation of attack
     */
    public String toString()
    {
        String bob = new String("");
        
        if (myIsMagic) bob = "[m]";
        else bob = "[n]";
        
        if (myIsTeam) bob += " [t]";
        
        return (myName + " " + DBSTypeHandle.Name(myType) + " MP:" + myDraw + " " + bob);
    }
    
    //Methods from DBSAttack interface
    /**
     * Gets the name of the attack
     * 
     * @return  Attack's name
     */
    public String Name() { return myName; }
    
    
    /**
     * Returns the type of the attack as given in the
     * <code>DBSTypeHandle</code> class.
     * 
     * @return  Attack's type 
     */
    public int Type() { return myType; }
    
    
    /**
     * Returns relative power of the attack
     * 
     * @return  Attack's power 
     */
    public int Pow() { return myPow; }
    
    
    /**
     * Returns amount of MP needed to attack
     * 
     * @return  Attack's draw 
     */
    public int Draw() { return myDraw; }
    
    
    /**
     * Returns whether or not attack attacks a whole team or just one person
     * 
     * @return  If attack attacks whole team 
     */
    public boolean IsTeam() { return myIsTeam; }
    
    
    /**
     * Returns a string representation (the name) of any <code>DBSStatus</code>
     * possibly inflicted by this attack. This attack class only has room for
     * one status.
     * 
     * @return  Name of status inflicted by attack (if any)
     */
    public String Status()
    {
        if (myStatus == 0) return "None";
        else return DBSStatusHandle.Name(myStatus);
    }
    
    /**
     * Whether this is a magic or physical based attack. This is determined by the
     * instance variables again
     * 
     * @return true if magic-based attack
     */
    public boolean IsMagic() { return myIsMagic; }
    
    
    /**
     * Executes the attack. What the attack does is anyone's guess, but it
     * should involve the attacker performing some damage to either the
     * defender or the defender's whole team.
     * 
     * @param  attacker <code>DBSCharacter</code> making the attack
     * @param  defender <code>DBSCharacter</code> defending against the attack
     * @return  amount of damage done 
     */
    public int Exe(DBSCharacter attacker, DBSCharacter defender, DBSBattle battle)
    {
        double hitProb = (double)(attacker.Acc()) / (double)(defender.Spd());
        if (cheese.nextDouble() >= hitProb)
        {
            System.out.println("Attack missed!");
            return 0;
        }
        
        int atkPow, defPow, totDamage, hpBefore;
        boolean isNegDamage;
        
        atkPow = attacker.Level() * attacker.NormalAtkPow(myType, myPow);
        defPow = defender.DefPow(myType);
        hpBefore = defender.HP();
        
        if (atkPow > 0)
        {
            isNegDamage = (defPow < 0);
            if (cheese.nextDouble() <= attacker.Luck())
            {
                defPow = 0;
                System.out.println("Critical hit!");
            }
            totDamage = atkPow - defPow;
            if (isNegDamage)
            {
                defender.ModHP(totDamage);
                System.out.println(defender + " gained " + (defender.HP() - hpBefore) + " HP.");
            }
            else
            {
                defender.ModHP(-1 * totDamage);
                System.out.println(defender + " took " + (hpBefore - defender.HP()) + " damage.");
            }
        }
        
        if (myStatus != DBSStatusHandle.Normal)
        {
            if (cheese.nextDouble() <= attacker.Luck())
            {
                defender.ChangeStatus(myStatus);
                System.out.println(defender + "'s status: " + DBSStatusHandle.Name(myStatus));
            }
        }
        return (hpBefore - defender.HP());
    }
}
