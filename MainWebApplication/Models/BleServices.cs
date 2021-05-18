using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Text.Json;
using System.Collections;

namespace MainWebApplication
{
    public class BleServices : List<BleService>
    {
        public BleServices()
        {
        }


        /*
         
         
         */
        public BleServices(string json)
        {
            var tmp = JsonSerializer.Deserialize<List<BleService>>(json);
            this.AddRange(tmp);
        }
    }
}
