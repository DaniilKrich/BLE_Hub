using System.Collections.Generic;

namespace MainWebApplication
{
    public class BleService
    {
        public string GUID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public List<Channel> Channels { get; set; }
    }
}
