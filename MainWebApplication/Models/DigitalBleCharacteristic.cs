using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace MainWebApplication.Models
{
    public class DigitalBleCharacteristic:BleCharacteristic 
    {
        public List<StoredValue<bool>> DigitalValues { get; set; }



  //      public bool CurrentValue { get; set; }

    }


}
