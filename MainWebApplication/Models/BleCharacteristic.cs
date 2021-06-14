using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Threading.Tasks;

namespace MainWebApplication.Models
{
    public class BleCharacteristic
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public long BleCharacteristicID { get; set; }

        [ForeignKey("BleService")]
        public long BleServiceID { get; set; }

        public string Discriminator { get; set; }

        public virtual BleService BleService { get; set; }

        public Guid CUUID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public Direction Direction { get; set; }
    }
}
