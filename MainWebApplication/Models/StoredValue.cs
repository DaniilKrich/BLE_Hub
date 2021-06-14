using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Threading.Tasks;

namespace MainWebApplication.Models
{
    public class StoredValue<T> 
    {
        public virtual BleCharacteristic BleCharacteristic { get; set; }


        [ForeignKey("BleCharacteristic")]
        public long BleCharacteristicID { get; set; }


        /// <summary>
        /// Sample Timestamp
        /// </summary>
        [Key]
        [DataType(DataType.Date)]
        [DisplayFormat(DataFormatString = "{0:yyyy-MM-dd HH:mm:ss.ffffff}")]
        public DateTime Timestamp { get; set; }
        public T Value { get; set; }
    }
}
