using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;

namespace MainWebApplication.Models
{
    public class BleServer
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public long BleServerID { get; set; }


        [ForeignKey("BleHubID")]
        public virtual BleHub BleHub { get; set; }



        public List<BleService> BleServices { get; set; }

        /*
         * 

            Reformat a string to display it as a MAC address:

            var macadres = "0018103AB839";

            var regex = "(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})";
            var replace = "$1:$2:$3:$4:$5:$6";
            var newformat = Regex.Replace(macadres, regex, replace);    

            // newformat = "00:18:10:3A:B8:39"

            If you want to validate the input string use this regex (thanks to J0HN):

            var regex = String.Concat(Enumerable.Repeat("([a-fA-F0-9]{2})", 6));

        _________________
        mac = string.Join (":", nic.GetPhysicalAddress().GetAddressBytes().Select(b => b.ToString("X2")));
         */


        [MaxLength(6)]
        [MinLength(6)]
        public byte[] BleAdr { get; } = new byte[6];
        public string Name { get; set; }



        //public BleServices GetBleServices()
        //{
        //    return new BleServices();// GetBleServices(BleAdr);
        //}

        //public void GetBleServices(string json)
        //{
        //    var tmp = JsonSerializer.Deserialize<List<BleService>>(json);
        //    this.AddRange(tmp);
        //}
    }
}
