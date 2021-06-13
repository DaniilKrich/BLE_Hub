using System;
using System.Linq;
using System.Threading.Tasks;

namespace MainWebApplication
{
    public class Channel
    {
        public virtual BleService BleService { get; set; }

        public ulong ID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public Direction Direction { get; set; }
    }
}
