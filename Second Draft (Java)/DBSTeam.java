
/**
 * Write a description of class DBSTeam here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class DBSTeam
{
    public static final int Max_Active = 4;
    public static final int Max_Bench = 5;
    public static final int Max_Items = 25;
    public static final int Max_Weapons = 10;

    public DBSTeam()
    {
        myActive =  new DBSPlayableCharacter[Max_Active];
        myNumActive = 0;
        myBench = new DBSPlayableCharacter[Max_Bench];
        myNumBench = 0;
        myInventory = new ItemNode[Max_Items];
        myNumItm = 0;
        myArsenal = new DBSWeapon[Max_Weapons];
        myNumWep = 0;
        myXPQueue = 0;
    }
    
    public boolean UseItem(int itmInd, DBSCharacter victim)
    {
        if ((itmInd >= myNumItm) || (itmInd < 0)) return false;
        
        if (myInventory[itmInd].Item.Use(victim))
        {
            myInventory[itmInd].Uses--;
            if (myInventory[itmInd].Uses <= 0)
            {
                for (int k = itmInd; k < myNumItm-1; k++)
                    myInventory[k] = myInventory[k+1];
                myNumItm--;
                myInventory[myNumItm] = null;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    
    public boolean Join(DBSPlayableCharacter joining)
    {
        if ((myNumActive + myNumBench) > (Max_Bench + 1)) return false;
        // max number of characters is NUM_BENCH + 1
        
        if (myNumActive == Max_Active) // active is full
        {
            if (myNumBench == Max_Bench) return false; //double-checking for out-of-bounds
            myBench[myNumBench] = joining;
            myNumBench++;
        }
        else //has space in active
        {
            myActive[myNumActive] = joining;
            myNumActive++;
        }
        joining.SetTeam(this);
    	if (joining.CanSummon())
    	{
    		for (int k = 0; k < joining.NumSummons(); k++)
    			joining.GetSummons(k).SetTeam(this);
    	}
        return true;
    }
    
    public DBSPlayableCharacter LeaveBench(int charInd)
    {
        if ((charInd >= myNumBench) || (charInd < 0)) return null;
        
        DBSPlayableCharacter left = myBench[charInd];
        
        myNumBench--;
        for (int k = charInd; k < myNumBench; k++)
            myBench[k] = myBench[k+1];
        myBench[myNumBench] = null;
        
        return left;
    }
    
    public boolean BenchActive(int charInd)
    {
        if ((charInd >= myNumActive) || (charInd < 0)) return false; //out-of-bounds
        if (myNumBench == Max_Bench) return false; //bench is full
        
        myBench[myNumBench] = myActive[charInd];
        myNumBench++;
        myNumActive--;
        for (int k = charInd; k < myNumActive; k++)
            myActive[k] = myActive[k+1];
        myActive[myNumActive] = null;
        
        return true;
    }
    
    public boolean CallFromBench(int charInd)
    {
        if ((charInd >= myNumBench) || (charInd < 0)) return false; //out-of-bounds
        if (myNumActive == Max_Active) return false; //active is full
        
        myActive[myNumActive] = myBench[charInd];
        myNumActive++;
        myNumBench--;
        for (int k = charInd; k < myNumBench; k++)
            myBench[k] = myBench[k+1];
        myBench[myNumBench] = null;
        
        return true;
    }
    
    public boolean AddItem(DBSItem item, int num)
    {
        int k = GetItmInd(item);
        if (k != -1)
        {
            myInventory[k].Uses += num;
            return true;
        }
            
        if (myNumItm == Max_Items) return false; //inventory is full
        myInventory[myNumItm].Item = item;
        myInventory[myNumItm].Uses = num;
        myNumItm++;
        return true;
    }
    
    public void ItemsTaken()
    {
        for (int k = 0; k < myNumItm; k++) myInventory[k] = null;
        myNumItm = 0;
    }
    
    public void QueueXP(int amt) { myXPQueue += amt;}
    
    public int GetXP()
    {
        int temp = myXPQueue;
        myXPQueue = 0;
        return temp;
    }
    
    public int GetItmInd(DBSItem itm)
    {
        for (int k = 0; k < myNumItm; k++)
            if (myInventory[k].Item == itm)
                return k;
        return -1;
    }
    
    public boolean IsAlive() //is someone on this team functional?
    {
        for (int k = 0; k < myNumActive; k++)
            if (myActive[k].IsAlive()) return true;
        return false;
    }
    
    public void PrintItems() // prints myInventory
    {
        for (int k = 0; k < myNumItm; k++)
        {
            System.out.print(k + " " + myInventory[k].Item);
            System.out.println(" " + myInventory[k].Uses);
        }
    }
    
    public DBSPlayableCharacter GetActive(int ind)
    {
        if ((ind >= 0) && (ind < myNumActive)) return myActive[ind];
        else return null;
    }
    public int NumActive() { return myNumActive; }
    public DBSPlayableCharacter GetBench(int ind)
    {
        if ((ind >= 0) && (ind < myNumBench)) return myBench[ind];
        else return null;
    }
    public int NumBench() { return myNumBench; }
    public DBSItem GetItem(int ind)
    {
        if ((ind >= 0) && (ind < myNumItm)) return myInventory[ind].Item;
        else return null;
    }
    public int GetItemUses(int ind)
    {
        if ((ind >= 0) && (ind < myNumItm)) return myInventory[ind].Uses;
        else return -1;
    }
    public int NumItems() { return myNumItm; }
    public DBSWeapon GetWeapon(int ind)
    {
        if ((ind >= 0) && (ind < myNumWep)) return myArsenal[ind];
        else return null;
    }
    public int NumWeapons() { return myNumWep; }
    public int XPQueue() { return myXPQueue; }
    
    //-----------------------------------------------------------
    
    private class ItemNode
    {
        public DBSItem Item;
        public int Uses;
    }
    
    private DBSPlayableCharacter[] myActive;
    private int myNumActive;
    private DBSPlayableCharacter[] myBench;
    private int myNumBench;
    private ItemNode[] myInventory;
    private int myNumItm;
    private DBSWeapon[] myArsenal;
    private int myNumWep;
    private int myXPQueue;
}
