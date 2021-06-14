using System;
using Microsoft.EntityFrameworkCore.Migrations;

namespace MainWebApplication.Migrations
{
    public partial class fixes : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_BleCharacteristic_BleService_BleServiceID",
                table: "BleCharacteristic");

            migrationBuilder.DropTable(
                name: "StoredValue<bool>");

            migrationBuilder.DropTable(
                name: "StoredValue<float>");

            migrationBuilder.AlterColumn<long>(
                name: "BleServiceID",
                table: "BleCharacteristic",
                nullable: false,
                oldClrType: typeof(long),
                oldType: "bigint",
                oldNullable: true);

            migrationBuilder.CreateTable(
                name: "AnalogValue",
                columns: table => new
                {
                    Timestamp = table.Column<DateTime>(nullable: false),
                    BleCharacteristicID = table.Column<long>(nullable: false),
                    Value = table.Column<float>(nullable: false),
                    AnalogBleCharacteristicBleCharacteristicID = table.Column<long>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_AnalogValue", x => x.Timestamp);
                    table.ForeignKey(
                        name: "FK_AnalogValue_BleCharacteristic_AnalogBleCharacteristicBleCharacteristicID",
                        column: x => x.AnalogBleCharacteristicBleCharacteristicID,
                        principalTable: "BleCharacteristic",
                        principalColumn: "BleCharacteristicID",
                        onDelete: ReferentialAction.Restrict);
                    table.ForeignKey(
                        name: "FK_AnalogValue_BleCharacteristic_BleCharacteristicID",
                        column: x => x.BleCharacteristicID,
                        principalTable: "BleCharacteristic",
                        principalColumn: "BleCharacteristicID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "DigitalValue",
                columns: table => new
                {
                    Timestamp = table.Column<DateTime>(nullable: false),
                    BleCharacteristicID = table.Column<long>(nullable: false),
                    Value = table.Column<bool>(nullable: false),
                    DigitalBleCharacteristicBleCharacteristicID = table.Column<long>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_DigitalValue", x => x.Timestamp);
                    table.ForeignKey(
                        name: "FK_DigitalValue_BleCharacteristic_BleCharacteristicID",
                        column: x => x.BleCharacteristicID,
                        principalTable: "BleCharacteristic",
                        principalColumn: "BleCharacteristicID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_DigitalValue_BleCharacteristic_DigitalBleCharacteristicBleCharacteristicID",
                        column: x => x.DigitalBleCharacteristicBleCharacteristicID,
                        principalTable: "BleCharacteristic",
                        principalColumn: "BleCharacteristicID",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateIndex(
                name: "IX_AnalogValue_AnalogBleCharacteristicBleCharacteristicID",
                table: "AnalogValue",
                column: "AnalogBleCharacteristicBleCharacteristicID");

            migrationBuilder.CreateIndex(
                name: "IX_AnalogValue_BleCharacteristicID",
                table: "AnalogValue",
                column: "BleCharacteristicID");

            migrationBuilder.CreateIndex(
                name: "IX_DigitalValue_BleCharacteristicID",
                table: "DigitalValue",
                column: "BleCharacteristicID");

            migrationBuilder.CreateIndex(
                name: "IX_DigitalValue_DigitalBleCharacteristicBleCharacteristicID",
                table: "DigitalValue",
                column: "DigitalBleCharacteristicBleCharacteristicID");

            migrationBuilder.AddForeignKey(
                name: "FK_BleCharacteristic_BleService_BleServiceID",
                table: "BleCharacteristic",
                column: "BleServiceID",
                principalTable: "BleService",
                principalColumn: "BleServiceID",
                onDelete: ReferentialAction.Cascade);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_BleCharacteristic_BleService_BleServiceID",
                table: "BleCharacteristic");

            migrationBuilder.DropTable(
                name: "AnalogValue");

            migrationBuilder.DropTable(
                name: "DigitalValue");

            migrationBuilder.AlterColumn<long>(
                name: "BleServiceID",
                table: "BleCharacteristic",
                type: "bigint",
                nullable: true,
                oldClrType: typeof(long));

            migrationBuilder.CreateTable(
                name: "StoredValue<bool>",
                columns: table => new
                {
                    Timestamp = table.Column<DateTime>(type: "datetime2", nullable: false),
                    BleCharacteristicID = table.Column<long>(type: "bigint", nullable: true),
                    DigitalBleCharacteristicBleCharacteristicID = table.Column<long>(type: "bigint", nullable: true),
                    Value = table.Column<bool>(type: "bit", nullable: false)
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
                    Timestamp = table.Column<DateTime>(type: "datetime2", nullable: false),
                    AnalogBleCharacteristicBleCharacteristicID = table.Column<long>(type: "bigint", nullable: true),
                    BleCharacteristicID = table.Column<long>(type: "bigint", nullable: true),
                    Value = table.Column<float>(type: "real", nullable: false)
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

            migrationBuilder.AddForeignKey(
                name: "FK_BleCharacteristic_BleService_BleServiceID",
                table: "BleCharacteristic",
                column: "BleServiceID",
                principalTable: "BleService",
                principalColumn: "BleServiceID",
                onDelete: ReferentialAction.Restrict);
        }
    }
}
