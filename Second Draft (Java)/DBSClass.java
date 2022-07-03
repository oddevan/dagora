
/**
 * <p>You do want the characters to improve over time and learn new skills,
 * right? That's where DBSClass comes in. A character learns moves from this
 * class. When a character levels up, (s)he gains a skill point, or SP, that
 * goes to the class. When a character has accumulated enough SP, (s)he learns
 * a move.</p>
 * <p>When a character reaches a certain threshold of SP, (s)he can progress a
 * level in that class. Going up a level means the opprotunity to learn more
 * powerful versions of previous moves as well as gaining a new Adrenaline
 * Rush. However, a move cannot be learned in a higher level until it is
 * learned in a lower level.</p>
 * <p>For example, Ronyo, a level one White Mage can learn Heal, Cure,
 * Fireworks, and Life. The Adrenaline Rush for level one is
 * Flash. For level two, Ronyo can learn Heal2, Protect, Trance, and Life2,
 * with the Adrenaline being Pierce. However, Ronyo can't learn Life2 until
 * he's learned Life, or for that matter, he can't learn Protect until he's
 * learned Cure. In order to get to the high-powered moves, he must go back
 * to level one and learn the basic versions.</p>
 * 
 * @author Evan Hildreth (root -1 Entertainment) 
 * @version 0.1 Java
 */
public class DBSClass
{
    public static final int SP_Per_Level = 10;

    public DBSClass()
    {
        myLevel = -1;
        myNumLevels = 0;
        mySP = 0;
        myTotalSP = 0;
        myInfoMatrix = null;
        myRush = null;
    }

    public DBSClass(int numLevels, int atkPerLv, DBSAttack[] attacks,
                    int[] costs, DBSAttack[] rushes)
    {
        myLevel = 0;
        myNumLevels = numLevels;
        myAtkPerLevel = atkPerLv;
        mySP = 0;
        myTotalSP = 0;
        myInfoMatrix = new DataNode[myNumLevels][myAtkPerLevel];
        myRush = new DBSAttack[myNumLevels];
        
        if ((attacks.length >= (myNumLevels * myAtkPerLevel)) &&
            (costs.length >= (myNumLevels * myAtkPerLevel)) &&
            (rushes.length >= myNumLevels))
        {
            int i = 0;
            for (int k = 0; k < myNumLevels; k++)
            {
                for (int j = 0; j < myAtkPerLevel; j++)
                {
                    myInfoMatrix[k][j] = new DataNode(attacks[i], costs[i]);
                    i++;
                }
                myRush[k] = rushes[k];
            }
        }
    }
    
    /**
     * This constructor makes a brand new class using the
     * attacks from the given class. Used when making new
     * characters.
     */
    public DBSClass(DBSClass job)
    {
        myLevel = 0;
        myNumLevels = job.NumLevels();
        myAtkPerLevel = job.AtkPerLevel();
        mySP = 0;
        myTotalSP = 0;
        myInfoMatrix = new DataNode[myNumLevels][myAtkPerLevel];
        myRush = new DBSAttack[myNumLevels];
        
        for (int k = 0; k < myNumLevels; k++)
        {
            for (int j = 0; j < myAtkPerLevel; j++)
            {
                myInfoMatrix[k][j] = new DataNode(job.GetAttack(k,j),
                                                  job.GetCost(k,j));
            }
            myRush[k] = job.GetRush(k);
        }
        
    }

    public boolean LevelUp()
    {
        if ((myLevel + 1) < myNumLevels)
        {
            myLevel++;
            return true;
        }
        else return false;
    }
    
    public boolean LevelDown()
    {
        if ((myLevel - 1) >= 0)
        {
            myLevel--;
            return true;
        }
        else return false;
    }
    
    public void SPUp(DBSCharacter myChar)
    {
        mySP++;
        myTotalSP++;
    }

    
    public void Reset()
    {
        for (int k = 0; k < myNumLevels; k++)
            for (int j = 0; j < myAtkPerLevel; j++)
                myInfoMatrix[k][j].Learned = false;
        myLevel = 0;
        mySP = 0;
        myTotalSP = 0;
    }
    
    public int AdjustedLevel() { return myLevel + 1; }
    
    public boolean CanLevelUp()
    {
        return (((myLevel + 1) < myNumLevels) &&
                (myTotalSP >= (myLevel * SP_Per_Level)));
    }
    
    public DBSAttack GetCurrentRush()
    {
        return myRush[myLevel];
    }
    
    public int Level() { return myLevel; }
    public int NumLevels() { return myNumLevels; }
    public int AtkPerLevel() { return myAtkPerLevel; }
    public int SP() { return mySP; }
    public int TotalSP() { return myTotalSP; }
    public DBSAttack GetAttack(int level, int ind)
    {
        if ((level >=0) && (level < myNumLevels) && (ind >= 0) && (ind < myAtkPerLevel))
            return myInfoMatrix[level][ind].Atk;
        else return null;
    }
    public int GetCost(int level, int ind)
    {
        if ((level >=0) && (level < myNumLevels) && (ind >= 0) && (ind < myAtkPerLevel))
            return myInfoMatrix[level][ind].Cost;
        else return 0;
    }
    public boolean IsLearned(int level, int ind)
    {
        if ((level >=0) && (level < myNumLevels) && (ind >= 0) && (ind < myAtkPerLevel))
            return myInfoMatrix[level][ind].Learned;
        else return false;
    }
    public DBSAttack GetRush(int level)
    {
        if ((level >=0) && (level < myNumLevels)) return myRush[level];
        else return null;
    }

    //----------------------------------------------------------

    private class DataNode 
    {
        public DataNode()
        {
            Atk = null;
            Cost = 0;
            Learned = false;
        }
    
        public DataNode(DBSAttack nAtk, int nCost)
        {
            Atk = nAtk;
            Cost = nCost;
            Learned = false;
        }
    
        public final DBSAttack Atk;
        public final int Cost;
        public boolean Learned;
    }
    
    private int myLevel;
    private int myNumLevels;
    private int myAtkPerLevel;
    private int mySP;
    private int myTotalSP;
    private DataNode[][] myInfoMatrix;
    private DBSAttack[] myRush;
}
