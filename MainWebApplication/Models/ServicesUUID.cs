using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Threading.Tasks;

namespace MainWebApplication.Models
{
    public class ServicesUUID : Dictionary<string, Guid>
    {
        private ServicesUUID()
        {
            base["MyService"] = new Guid("94ec923e-b5a6-11eb-8529-0242ac130003"); // 4fafc201-1fb5-459e-8fcc-c5c9c331914b
        }

        private static ServicesUUID instance;
        private static object instanceLock = new object();
        public static ServicesUUID Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (instanceLock)
                    {
                        if (instance == null)
                        {
                            instance = new ServicesUUID();
                        }
                    }
                }

                return instance;
            }
        }
    }

    public class CharacteristicsUUID : Dictionary<string, Guid>
    {
        public CharacteristicsUUID():base()
        {
            //base.["Tempreture"] = new Guid("94ec96e4-b5a6-11eb-8529-0242ac130003"); // beb5483e-36e1-4688-b7f5-ea07361b26a8
            //this.["HumidityGround"] = new Guid("94ec97de-b5a6-11eb-8529-0242ac130003"); // beb5483e-36e1-4688-b7f5-ea07361b26a9
            //this.["HumidityAir"] = new Guid("94ec989c-b5a6-11eb-8529-0242ac130003"); // beb5483e-36e1-4688-b7f5-ea07361b26aa
            //this.["Voltage"] = new Guid("94ec9964-b5a6-11eb-8529-0242ac130003");// beb5483e-36e1-4688-b7f5-ea07361b26ab
            //this.["Test"] = new Guid("94ec9a22-b5a6-11eb-8529-0242ac130003"); // beb5483e-36e1-4688-b7f5-ea07361b26ac
            //this.["Pressure"] = new Guid("94ec9cac-b5a6-11eb-8529-0242ac130003"); // beb5483e-36e1-4688-b7f5-ea07361b26ad
        }

        private static CharacteristicsUUID instance;
        private static object instanceLock = new object();
        public static CharacteristicsUUID Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (instanceLock)
                    {
                        if (instance == null)
                        {
                            instance = new CharacteristicsUUID();
                        }
                    }
                }

                return instance;
            }
        }
    }
}
