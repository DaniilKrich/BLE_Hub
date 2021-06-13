using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using MainWebApplication;

namespace MainWebApplication.Data
{
    public class MainWebApplicationContext : DbContext
    {
        public MainWebApplicationContext (DbContextOptions<MainWebApplicationContext> options)
            : base(options)
        {
        }

        public DbSet<MainWebApplication.BleHub> BleHub { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<BleHub>()
                .HasKey(c => new { c.State, c.LicensePlate });
        }


    }
}
