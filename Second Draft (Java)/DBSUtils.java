public class DBSUtils
{
    public static int RoundDouble(double roundMe)
    {
        int baseValue = (int)roundMe;
        double temp = roundMe - (double)baseValue;
        int roundKey = (int)(temp * 10);
        
        if (roundKey < 5) return baseValue;
        return baseValue + 1;
    }
    
    public static final double Chance_Of_Crit_Hit = 0.05;
    
    public static final double Chance_Of_Stat_Change = 0.25;
}
