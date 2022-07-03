
/**
 * This class provides a simple way to see how different types interact
 * with each other. All types are available as final variables, and all variables
 * and functions are static, so you should never have to allocate one of these
 * objects. Which is good, because it's a fairly large array...
 * 
 * @author Evan Hildreth
 * @author root -1 Entertainment
 * @version 0.1 Java
 */
public class DBSTypeHandle
{
    public static final int TotNumTypes = 13;
    
    public static final int Normal = 0;
    public static final int Sword = 1;
    public static final int Fighting = 2;
    public static final int Flying = 3;
    public static final int Remote = 4;
    public static final int WhiteMagic = 5;
    public static final int BlackMagic = 6;
    public static final int Earth = 7;
    public static final int Fire = 8;
    public static final int Wind = 9;
    public static final int Water = 10;
    public static final int Enhanced = 11;
    
    public static String Name(int type)
    {
    
        switch (type)
        {
            case Normal:
                return "Normal";
            case Sword:
                return "Sword";
            case Fighting:
                return "Fighting";
            case Flying:
                return "Flying";
            case Remote:
                return "Remote";
            case WhiteMagic:
                return "WhiteMagic";
            case BlackMagic:
                return "BlackMagic";
            case Earth:
                return "Earth";
            case Fire:
                return "Fire";
            case Wind:
                return "Wind";
            case Water:
                return "Water";
            case Enhanced:
                return "Enhanced";
        }
        return "None";
    }
    
    private static int[][] TypeArray;
    
    public static void Init()
    {
        TypeArray = new int[TotNumTypes][TotNumTypes];
        
        for (int k = 0; k < TotNumTypes; k++)
            for (int j = 0; j < TotNumTypes; j++)
                TypeArray[k][j] = 0;
    
        //normal
        TypeArray[0][3] = 1;
        TypeArray[0][4] = 1;
        TypeArray[0][5] = 1;
        TypeArray[0][6] = 1;
        TypeArray[0][7] = 1;
        TypeArray[0][11] = 1;
    
        //sword
        TypeArray[1][1] = 1;
        TypeArray[1][7] = 2;
    
        //fighting
        TypeArray[2][0] = 2;
        TypeArray[2][2] = 1;
        TypeArray[2][5] = 1;
        TypeArray[2][6] = 1;
    
        //flying
        TypeArray[3][3] = 1;
        TypeArray[3][4] = 2;
        TypeArray[3][7] = 1;
    
        //remote
        TypeArray[4][3] = 2;
        TypeArray[4][4] = 1;
    
        //whitemagic
        TypeArray[5][2] = 2;
        TypeArray[5][5] = -1;
        TypeArray[5][6] = 2;
        TypeArray[5][11] = 2;
    
        //blackmagic
        TypeArray[6][2] = 2;
        TypeArray[6][5] = 2;
        TypeArray[6][6] = -1;
        TypeArray[6][11] = 2;
    
        //earth
        TypeArray[7][1] = 1;
        TypeArray[7][3] = 1;
        TypeArray[7][7] = -1;
        TypeArray[7][8] = 1;
        TypeArray[7][9] = 2;
    
        //fire
        TypeArray[8][7] = 2;
        TypeArray[8][8] = -1;
        TypeArray[8][10] = 1;
    
        //wind
        TypeArray[9][4] = 1;
        TypeArray[9][7] = 1;
        TypeArray[9][9] = -1;
        TypeArray[9][10] = 2;
    
        //water
        TypeArray[10][8] = 2;
        TypeArray[10][9] = 1;
        TypeArray[10][10] = -1;
    
        //enhanced
        TypeArray[11][0] = 1;
        TypeArray[11][11] = 1;
    }
    
    public static int Lookup(int atkType, int defType)
    {
        if ((atkType >= 0) && (atkType < TotNumTypes)
            && (defType >= 0) && (defType < TotNumTypes))
        {
            return TypeArray[atkType][defType];
        }
        else return 0;
    }
}
