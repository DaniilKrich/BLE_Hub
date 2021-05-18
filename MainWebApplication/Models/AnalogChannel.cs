namespace MainWebApplication
{
    public class AnalogChannel : Channel
    {
        public double CurrentValue { get; set; }
        public Unit Unit { get; set; }
    }

    public enum Unit
    {
        DegreesCelsius,
        Bar,
        Percent
    }
}
