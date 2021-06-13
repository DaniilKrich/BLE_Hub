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

        public DbSet<BleHub> BleHub { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<BleHub>()
                .HasKey(c => new { c.Name });

            modelBuilder.Entity<BleServer>()
                .HasOne(b => b.BleHub)
                .WithMany(h => h)
                .HasForeignKey(c => new { c.BleHub.Name, c.BleAdr });

            modelBuilder.Entity<BleService>()
                .HasOne(b => b.BleServer)
                .WithMany(b => b)
                .HasForeignKey(c => new { c.BleServer.BleHub.Name, c.BleServer.BleAdr, c.SUUID });

            modelBuilder.Entity<BleCharacteristic>()
                .HasOne(c=>c.BleService)
                .WithMany(b=>b)
                .HasForeignKey(c => new { c.BleService.BleServer.BleHub.Name, c.BleService.BleServer.BleAdr, c.BleService.SUUID, c.CUUID });
        }


    }
}
