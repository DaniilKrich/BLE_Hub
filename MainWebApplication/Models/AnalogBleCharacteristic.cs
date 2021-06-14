using System.Collections.Generic;

namespace MainWebApplication.Models
{
    public class AnalogBleCharacteristic: BleCharacteristic
    {
        public List<StoredValue<float>> AnalogValues { get; set; }

        //public double CurrentValue { get; set; }
        public Unit Unit { get; set; }
    }
}
