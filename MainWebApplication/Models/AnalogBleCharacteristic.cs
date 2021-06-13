namespace MainWebApplication.Models
{
    public class AnalogBleCharacteristic:Values<float>
    {
        public virtual BleCharacteristic BleCharacteristic { get; set; }
        //public double CurrentValue { get; set; }
        public Unit Unit { get; set; }
    }
}
