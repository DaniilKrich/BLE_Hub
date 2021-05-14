using System;
using System.Linq;
using System.Threading.Tasks;

namespace MainWebApplication
{
    public abstract class Channel
    {
        public ulong ID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public Direction Direction { get; set; }
    }
}
