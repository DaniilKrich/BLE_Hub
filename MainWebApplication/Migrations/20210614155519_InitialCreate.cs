using System;
using Microsoft.EntityFrameworkCore.Migrations;

namespace MainWebApplication.Migrations
{
    public partial class InitialCreate : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "BleHubs",
                columns: table => new
                {
                    BleHubID = table.Column<long>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(nullable: true),
                    Description = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_BleHubs", x => x.BleHubID);
                });

            migrationBuilder.CreateTable(
                name: "BleServer",
                columns: table => new
                {
                    BleServerID = table.Column<long>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    BleHubID = table.Column<long>(nullable: true),
                    Name = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_BleServer", x => x.BleServerID);
                    table.ForeignKey(
                        name: "FK_BleServer_BleHubs_BleHubID",
                        column: x => x.BleHubID,
                        principalTable: "BleHubs",
                        principalColumn: "BleHubID",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateTable(
                name: "BleService",
                columns: table => new
                {
                    BleServiceID = table.Column<long>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    BleServerID = table.Column<long>(nullable: true),
                    SUUID = table.Column<Guid>(nullable: false),
                    Name = table.Column<string>(nullable: true),
                    Description = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_BleService", x => x.BleServiceID);
                    table.ForeignKey(
                        name: "FK_BleService_BleServer_BleServerID",
                        column: x => x.BleServerID,
                        principalTable: "BleServer",
                        principalColumn: "BleServerID",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateTable(
                name: "BleCharacteristic",
                columns: table => new
                {
                    BleCharacteristicID = table.Column<long>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    BleServiceID = table.Column<long>(nullable: true),
                    CUUID = table.Column<Guid>(nullable: false),
                    Name = table.Column<string>(nullable: true),
                    Description = table.Column<string>(nullable: true),
                    Direction = table.Column<int>(nullable: false),
                    Discriminator = table.Column<string>(nullable: false),
                    Unit = table.Column<int>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_BleCharacteristic", x => x.BleCharacteristicID);
                    table.ForeignKey(
                        name: "FK_BleCharacteristic_BleService_BleServiceID",
                        column: x => x.BleServiceID,
                        principalTable: "BleService",
                        principalColumn: "BleServiceID",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateTable(
                name: "StoredValue<bool>",
                columns: table => new
                {
                    Timestamp = table.Column<DateTime>(nullable: false),
                    BleCharacteristicID = table.Column<long>(nullable: true),
                    Value = table.Column<bool>(nullable: false),
                    DigitalBleCharacteristicBleCharacteristicID = table.Column<long>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_StoredValue<bool>", x => x.Timestamp);
                    table.ForeignKey(
                        name: "FK_StoredValue<bool>_BleCharacteristic_BleCharacteristicID",
                        column: x => x.BleCharacteristicID,
                        principalTable: "BleCharacteristic",
                        principalColumn: "BleCharacteristicID",
                        onDelete: ReferentialAction.Restrict);
                    table.ForeignKey(
                        name: "FK_StoredValue<bool>_BleCharacteristic_DigitalBleCharacteristicBleCharacteristicID",
                        column: x => x.DigitalBleCharacteristicBleCharacteristicID,
                        principalTable: "BleCharacteristic",
                        principalColumn: "BleCharacteristicID",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateTable(
                name: "StoredValue<float>",
                columns: table => new
                {
                    Timestamp = table.Column<DateTime>(nullable: false),
                    BleCharacteristicID = table.Column<long>(nullable: true),
                    Value = table.Column<float>(nullable: false),
                    AnalogBleCharacteristicBleCharacteristicID = table.Column<long>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_StoredValue<float>", x => x.Timestamp);
                    table.ForeignKey(
                        name: "FK_StoredValue<float>_BleCharacteristic_AnalogBleCharacteristicBleCharacteristicID",
                        column: x => x.AnalogBleCharacteristicBleCharacteristicID,
                        principalTable: "BleCharacteristic",
                        principalColumn: "BleCharacteristicID",
                        onDelete: ReferentialAction.Restrict);
                    table.ForeignKey(
                        name: "FK_StoredValue<float>_BleCharacteristic_BleCharacteristicID",
                        column: x => x.BleCharacteristicID,
                        principalTable: "BleCharacteristic",
                        principalColumn: "BleCharacteristicID",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateIndex(
                name: "IX_BleCharacteristic_BleServiceID",
                table: "BleCharacteristic",
                column: "BleServiceID");

            migrationBuilder.CreateIndex(
                name: "IX_BleServer_BleHubID",
                table: "BleServer",
                column: "BleHubID");

            migrationBuilder.CreateIndex(
                name: "IX_BleService_BleServerID",
                table: "BleService",
                column: "BleServerID");

            migrationBuilder.CreateIndex(
                name: "IX_StoredValue<bool>_BleCharacteristicID",
                table: "StoredValue<bool>",
                column: "BleCharacteristicID");

            migrationBuilder.CreateIndex(
                name: "IX_StoredValue<bool>_DigitalBleCharacteristicBleCharacteristicID",
                table: "StoredValue<bool>",
                column: "DigitalBleCharacteristicBleCharacteristicID");

            migrationBuilder.CreateIndex(
                name: "IX_StoredValue<float>_AnalogBleCharacteristicBleCharacteristicID",
                table: "StoredValue<float>",
                column: "AnalogBleCharacteristicBleCharacteristicID");

            migrationBuilder.CreateIndex(
                name: "IX_StoredValue<float>_BleCharacteristicID",
                table: "StoredValue<float>",
                column: "BleCharacteristicID");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "StoredValue<bool>");

            migrationBuilder.DropTable(
                name: "StoredValue<float>");

            migrationBuilder.DropTable(
                name: "BleCharacteristic");

            migrationBuilder.DropTable(
                name: "BleService");

            migrationBuilder.DropTable(
                name: "BleServer");

            migrationBuilder.DropTable(
                name: "BleHubs");
        }
    }
}
