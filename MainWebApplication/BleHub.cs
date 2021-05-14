using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;

namespace MainWebApplication
{
    public class BleHub
    {
        public IPAddress IpAddress { get; set; }

        public string Name { get; set; }
        public string Description { get; set; }

        public List<BleService> BleServices {get;set;}
    }
}
