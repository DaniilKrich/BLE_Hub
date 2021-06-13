using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace MainWebApplication.Models
{
    public class DigitalBleCharacteristic: Values<bool>
    {
        public virtual BleCharacteristic BleCharacteristic { get; set; }

  //      public bool CurrentValue { get; set; }

  //      /// <summary>
		///// Sample Timestamp
		///// </summary>
		//[DataType(DataType.Date)]
  //      [DisplayFormat(DataFormatString = "{0:yyyy-MM-dd HH:mm:ss.ffffff}")]
  //      public DateTime TimeStamp { get; set; }
    }


}
