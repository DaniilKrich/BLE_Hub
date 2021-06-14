using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace MainWebApplication.Models
{
    public class BleService
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public long BleServiceID { get; set; }

        [ForeignKey("BleServerID")]
        public virtual BleServer BleServer { get; set; }

        /// <summary>
        /// </summary>
        public Guid SUUID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public List<BleCharacteristic> BleCharacteristics { get; set; }

    }
}
