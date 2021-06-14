using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace MainWebApplication.Models
{
    public class BleHub
    {
        private string webRequestRoot => $"http://{Name}/";

        /// <summary>
        /// MAC or physical address
        /// </summary>
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public long BleHubID { get; set; }

        public string Name { get; set; }
        public string Description { get; set; }

        public List<BleServer> BleServers { get; set; }



        public BleHub()
        {
        }


        public BleHub(string name)
        {
            Name = name;
        }

        private string GetNameFromBleHub()
        {
            WebRequest request =
               WebRequest
               .Create($"{webRequestRoot}GetHubName");

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


        //internal BleServices GetBleServices(byte[] bleAdr)
        //{
        //    WebRequest request =
        //        WebRequest
        //        .Create($"http://{Name}/GetBleServices");

        //    var response = request.GetResponse();

        //    if (response.ContentType == "application/json; charset=utf-8")
        //    {
        //        // Get the stream associated with the response.
        //        Stream receiveStream = response.GetResponseStream();

        //        // Pipes the stream to a higher level stream reader with the required encoding format.
        //        StreamReader readStream = new StreamReader(receiveStream, Encoding.UTF8);

        //        var json = readStream.ReadToEnd();

        //        return new BleServices(json);

        //    }
        //    return null;




        //}
    }
}
