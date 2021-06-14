using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace MainWebApplication.Models
{
    public class DigitalBleCharacteristic : BleCharacteristic
    {
        public List<DigitalValue> DigitalValues { get; set; }



        //      public bool CurrentValue { get; set; }

    }


}
