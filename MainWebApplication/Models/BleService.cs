using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace MainWebApplication.Models
{
    public class BleService: BleCharacteristics
    {
        public virtual BleServer BleServer { get; set; }

        /// <summary>
        /// </summary>
        public Guid SUUID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
    }
}
