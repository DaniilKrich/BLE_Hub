using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using MainWebApplication;
using MainWebApplication.Models;

namespace MainWebApplication.Data
{
    public class MainWebApplicationContext : DbContext
    {
        public MainWebApplicationContext(DbContextOptions<MainWebApplicationContext> options)
            : base(options)
        {
        }

        public DbSet<BleHub> BleHubs { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<BleHub>();

            modelBuilder.Entity<BleServer>()
                .HasOne(b => b.BleHub)
                .WithMany(h => h.BleServers);
            //.HasForeignKey(c => new { c.BleHub.Name, c.BleAdr });

            modelBuilder.Entity<BleService>()
                .HasOne(b => b.BleServer)
                .WithMany(b => b.BleServices);
            //.HasForeignKey(c => new { c.BleServer.BleHub.Name, c.BleServer.BleAdr, c.SUUID });

            modelBuilder.Entity<DigitalBleCharacteristic>();
            modelBuilder.Entity<AnalogBleCharacteristic>();
            modelBuilder.Entity<BleCharacteristic>()
                .HasOne(c => c.BleService)
                .WithMany(b => b.BleCharacteristics);
                //.HasForeignKey(c => new { c.BleService.BleServer.BleHub.Name, c.BleService.BleServer.BleAdr, c.BleService.SUUID, c.CUUID });
        }

        public DbSet<MainWebApplication.Models.BleServer> BleServer { get; set; }

        public DbSet<MainWebApplication.Models.BleService> BleService { get; set; }


    }
}
