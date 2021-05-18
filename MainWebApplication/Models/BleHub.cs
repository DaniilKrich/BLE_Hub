using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace MainWebApplication
{
    public class BleHub
    {
        public BleHub()
        {
        }

        public BleHub(IPAddress iPAddress)
        {
            IpAddress = iPAddress;
            Name = GetNameFromBleHub();
        }

        private string GetNameFromBleHub()
        {
            WebRequest request =
               WebRequest
               .Create($"http://{IpAddress}/GetHubName");

            var response = request.GetResponse();

            if (response.ContentType == "application/json; charset=utf-8")
            {
                // Get the stream associated with the response.
                Stream receiveStream = response.GetResponseStream();

                // Pipes the stream to a higher level stream reader with the required encoding format.
                StreamReader readStream = new StreamReader(receiveStream, Encoding.UTF8);

                var name = readStream.ReadToEnd();

                return name;

            }
            return null;


        }

        public int ID { get; set; }

        public IPAddress IpAddress { get; set; }

        public string Name { get; set; }
        public string Description { get; set; }

        public List<Node> Nodes { get; set; }

        internal BleServices GetBleServices(byte[] bleAdr)
        {
            WebRequest request =
                WebRequest
                .Create($"http://{IpAddress}/GetBleServices");

            var response = request.GetResponse();

            if (response.ContentType == "application/json; charset=utf-8")
            {
                // Get the stream associated with the response.
                Stream receiveStream = response.GetResponseStream();

                // Pipes the stream to a higher level stream reader with the required encoding format.
                StreamReader readStream = new StreamReader(receiveStream, Encoding.UTF8);

                var json = readStream.ReadToEnd();

                return new BleServices(json);

            }
            return null;




        }
    }
}
