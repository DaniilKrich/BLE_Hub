using System;
using System.Linq;
using System.Threading.Tasks;

namespace MainWebApplication.Models
{
    public class BleCharacteristic
    {
        public virtual BleService BleService { get; set; }

        public Guid CUUID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public Direction Direction { get; set; }
    }
}
