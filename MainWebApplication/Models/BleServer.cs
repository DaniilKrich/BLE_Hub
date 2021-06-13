using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MainWebApplication.Models
{
    public class BleServer : BleServices
    {
        public virtual BleHub BleHub { get; set; }



        /// 
        //public int ID { get; set; }
        public byte[] BleAdr { get; } = new byte[6];
        public string Name { get; set; }
        public BleServices GetBleServices()
        {
            return new BleServices();// GetBleServices(BleAdr);
        }
    }
}
