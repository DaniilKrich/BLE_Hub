using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace MainWebApplication
{
    public class BleService
    {
        public virtual BleServices BleServices { get; set; }



        /// <summary>
        /// </summary>
        [Key]
        public string GUID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public List<Channel> Channels { get; set; }
    }
}
