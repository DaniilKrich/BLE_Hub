// <auto-generated />
using System;
using MainWebApplication.Data;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;

namespace MainWebApplication.Migrations
{
    [DbContext(typeof(MainWebApplicationContext))]
    partial class MainWebApplicationContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "3.1.15")
                .HasAnnotation("Relational:MaxIdentifierLength", 128)
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("MainWebApplication.Models.AnalogValue", b =>
                {
                    b.Property<DateTime>("Timestamp")
                        .HasColumnType("datetime2");

                    b.Property<long?>("AnalogBleCharacteristicBleCharacteristicID")
                        .HasColumnType("bigint");

                    b.Property<long>("BleCharacteristicID")
                        .HasColumnType("bigint");

                    b.Property<float>("Value")
                        .HasColumnType("real");

                    b.HasKey("Timestamp");

                    b.HasIndex("AnalogBleCharacteristicBleCharacteristicID");

                    b.HasIndex("BleCharacteristicID");

                    b.ToTable("AnalogValue");
                });

            modelBuilder.Entity("MainWebApplication.Models.BleCharacteristic", b =>
                {
                    b.Property<long>("BleCharacteristicID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint")
                        .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

                    b.Property<long>("BleServiceID")
                        .HasColumnType("bigint");

                    b.Property<Guid>("CUUID")
                        .HasColumnType("uniqueidentifier");

                    b.Property<string>("Description")
                        .HasColumnType("nvarchar(max)");

                    b.Property<int>("Direction")
                        .HasColumnType("int");

                    b.Property<string>("Discriminator")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Name")
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("BleCharacteristicID");

                    b.HasIndex("BleServiceID");

                    b.ToTable("BleCharacteristic");

                    b.HasDiscriminator<string>("Discriminator").HasValue("BleCharacteristic");
                });

            modelBuilder.Entity("MainWebApplication.Models.BleHub", b =>
                {
                    b.Property<long>("BleHubID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint")
                        .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

                    b.Property<string>("Description")
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Name")
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("BleHubID");

                    b.ToTable("BleHubs");
                });

            modelBuilder.Entity("MainWebApplication.Models.BleServer", b =>
                {
                    b.Property<long>("BleServerID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint")
                        .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

                    b.Property<long?>("BleHubID")
                        .HasColumnType("bigint");

                    b.Property<string>("Name")
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("BleServerID");

                    b.HasIndex("BleHubID");

                    b.ToTable("BleServer");
                });

            modelBuilder.Entity("MainWebApplication.Models.BleService", b =>
                {
                    b.Property<long>("BleServiceID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint")
                        .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

                    b.Property<long?>("BleServerID")
                        .HasColumnType("bigint");

                    b.Property<string>("Description")
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Name")
                        .HasColumnType("nvarchar(max)");

                    b.Property<Guid>("SUUID")
                        .HasColumnType("uniqueidentifier");

                    b.HasKey("BleServiceID");

                    b.HasIndex("BleServerID");

                    b.ToTable("BleService");
                });

            modelBuilder.Entity("MainWebApplication.Models.DigitalValue", b =>
                {
                    b.Property<DateTime>("Timestamp")
                        .HasColumnType("datetime2");

                    b.Property<long>("BleCharacteristicID")
                        .HasColumnType("bigint");

                    b.Property<long?>("DigitalBleCharacteristicBleCharacteristicID")
                        .HasColumnType("bigint");

                    b.Property<bool>("Value")
                        .HasColumnType("bit");

                    b.HasKey("Timestamp");

                    b.HasIndex("BleCharacteristicID");

                    b.HasIndex("DigitalBleCharacteristicBleCharacteristicID");

                    b.ToTable("DigitalValue");
                });

            modelBuilder.Entity("MainWebApplication.Models.AnalogBleCharacteristic", b =>
                {
                    b.HasBaseType("MainWebApplication.Models.BleCharacteristic");

                    b.Property<int>("Unit")
                        .HasColumnType("int");

                    b.HasDiscriminator().HasValue("AnalogBleCharacteristic");
                });

            modelBuilder.Entity("MainWebApplication.Models.DigitalBleCharacteristic", b =>
                {
                    b.HasBaseType("MainWebApplication.Models.BleCharacteristic");

                    b.HasDiscriminator().HasValue("DigitalBleCharacteristic");
                });

            modelBuilder.Entity("MainWebApplication.Models.AnalogValue", b =>
                {
                    b.HasOne("MainWebApplication.Models.AnalogBleCharacteristic", null)
                        .WithMany("AnalogValues")
                        .HasForeignKey("AnalogBleCharacteristicBleCharacteristicID");

                    b.HasOne("MainWebApplication.Models.BleCharacteristic", "BleCharacteristic")
                        .WithMany()
                        .HasForeignKey("BleCharacteristicID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();
                });

            modelBuilder.Entity("MainWebApplication.Models.BleCharacteristic", b =>
                {
                    b.HasOne("MainWebApplication.Models.BleService", "BleService")
                        .WithMany("BleCharacteristics")
                        .HasForeignKey("BleServiceID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();
                });

            modelBuilder.Entity("MainWebApplication.Models.BleServer", b =>
                {
                    b.HasOne("MainWebApplication.Models.BleHub", "BleHub")
                        .WithMany("BleServers")
                        .HasForeignKey("BleHubID");
                });

            modelBuilder.Entity("MainWebApplication.Models.BleService", b =>
                {
                    b.HasOne("MainWebApplication.Models.BleServer", "BleServer")
                        .WithMany("BleServices")
                        .HasForeignKey("BleServerID");
                });

            modelBuilder.Entity("MainWebApplication.Models.DigitalValue", b =>
                {
                    b.HasOne("MainWebApplication.Models.BleCharacteristic", "BleCharacteristic")
                        .WithMany()
                        .HasForeignKey("BleCharacteristicID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("MainWebApplication.Models.DigitalBleCharacteristic", null)
                        .WithMany("DigitalValues")
                        .HasForeignKey("DigitalBleCharacteristicBleCharacteristicID");
                });
#pragma warning restore 612, 618
        }
    }
}
