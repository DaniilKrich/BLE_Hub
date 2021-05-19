﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MainWebApplication
{
    public class Node
    {
        /// <summary>
        /// BLEHUB содержащий эту конкретную node
        /// </summary>
        public BleHub BleHub { get; set; }
        public int ID { get; set; }
        public byte[] BleAdr { get; } = new byte[6];
        public string Name { get; set; }
        public BleServices BleServices { get; set; }
        public BleServices GetBleServices()
        {
           return BleHub.GetBleServices(BleAdr);
        }
    }
}