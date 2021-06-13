//include sensor
#include <algorithm>
#include <iostream>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <Button2.h>


//include server
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "MyServerCallbacks.h"

//sensor
#define SOFTAP_MODE

#define I2C_SDA             25
#define I2C_SCL             26
#define DHT12_PIN           16
#define BAT_ADC             33
#define SALT_PIN            34
#define SOIL_PIN            32

#define POWER_CTRL          4


Adafruit_BME280 bmp;     //0x77

bool bme_found = false;

void sleepHandler(Button2& b)
{
	Serial.println("Enter Deepsleep ...");
	esp_sleep_enable_ext1_wakeup(GPIO_SEL_35, ESP_EXT1_WAKEUP_ALL_LOW);
	delay(1000);
	esp_deep_sleep_start();
}


//server
#define SEALEVELPRESSURE_HPA (1013.25)

#define SERVICE_UUID "94ec923e-b5a6-11eb-8529-0242ac130003" // 4fafc201-1fb5-459e-8fcc-c5c9c331914b
#define Tempreture_UUID "94ec96e4-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26a8
#define HumiditiGround_UUID "94ec97de-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26a9
#define HumiditiAir_UUID "94ec989c-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26aa
#define Voltage_UUID "94ec9964-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26ab
#define Test_UUID "94ec9a22-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26ac
#define Pressure_UUID "94ec9cac-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26ad

BLECharacteristic* Test_CHARACTERISTIC;
BLECharacteristic* Tempreture_CHARACTERISTIC;
BLECharacteristic* HumiditiGround_CHARACTERISTIC;
BLECharacteristic* HumiditiAir_CHARACTERISTIC;
BLECharacteristic* Voltage_CHARACTERISTIC;
BLECharacteristic* Pressure_CHARACTERISTIC;

BLEServer *pServer;
BLEService* pService;




void setup() {
	Serial.begin(115200);
	//setup sensor
	Wire.begin(I2C_SDA, I2C_SCL);

	//! Sensor power control pin , use deteced must set high
	pinMode(POWER_CTRL, OUTPUT);
	digitalWrite(POWER_CTRL, 1);
	delay(1000);

	if (!bmp.begin()) {
		Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
		bme_found = false;
	}
	else {
		bme_found = true;
	}

	//setup server

	Serial.println("Starting BLE work");

	/*float Tempreture = 15.,
		HumiditiGround = 70.,
		HumiditiAir = 15.,
		Voltage = 3.8,
		Pressure = 4.;*/


	BLEDevice::init("sensor_server");
	Serial.print(BLEDevice::getAddress().toString().c_str());
	pServer = BLEDevice::createServer();





	pServer->setCallbacks(new MyServerCallbacks());


	pService = pServer->createService(SERVICE_UUID);
	Test_CHARACTERISTIC = pService->createCharacteristic(
		Test_UUID,
		BLECharacteristic::PROPERTY_READ /*||
		BLECharacteristic::PROPERTY_WRITE*/);
		//Test_CHARACTERISTIC->addDescriptor(new BLE2902());    

	Tempreture_CHARACTERISTIC = pService->createCharacteristic(
		Tempreture_UUID,
		BLECharacteristic::PROPERTY_READ);
	// Tempreture_CHARACTERISTIC->addDescriptor(new BLE2902());  

	HumiditiGround_CHARACTERISTIC = pService->createCharacteristic(
		HumiditiGround_UUID,
		BLECharacteristic::PROPERTY_READ);
	// HumiditiGround_CHARACTERISTIC->addDescriptor(new BLE2902());

	HumiditiAir_CHARACTERISTIC = pService->createCharacteristic(
		HumiditiAir_UUID,
		BLECharacteristic::PROPERTY_READ);
	//HumiditiAir_CHARACTERISTIC->addDescriptor(new BLE2902()); 

	Voltage_CHARACTERISTIC = pService->createCharacteristic(
		Voltage_UUID,
		BLECharacteristic::PROPERTY_READ);

	//Voltage_CHARACTERISTIC->addDescriptor(new BLE2902());

	Pressure_CHARACTERISTIC = pService->createCharacteristic(
		Pressure_UUID,
		BLECharacteristic::PROPERTY_READ);
	//Pressure_CHARACTERISTIC->addDescriptor(new BLE2902()); 

	Test_CHARACTERISTIC->setValue("Hello World says Daniil");
	
	pService->start();
	// BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
	BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
	pAdvertising->addServiceUUID(SERVICE_UUID);
	pAdvertising->setScanResponse(true);
	pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
	pAdvertising->setMinPreferred(0x12);
	BLEDevice::startAdvertising();
	Serial.println("Characteristic defined! Now you can read it in your phone!");
}

//function sensor
float readSalt()
{
	uint8_t samples = 120;
	float salt = 0;
	uint16_t array[120];

	for (int i = 0; i < samples; i++) {
		array[i] = analogRead(SALT_PIN);
		delay(2);
	}
	std::sort(array, array + samples);
	for (int i = 0; i < samples; i++) {
		if (i == 0 || i == samples - 1)continue;
		salt += array[i];
	}
	salt /= (float)(samples - 2);
	return salt;
}

float readSoil()
{
	uint16_t soil = analogRead(SOIL_PIN);
	return 100.0*(1.0-(float)soil / 4095.0);//map(soil, 0, 4095, 100, 0);
}

float readBattery()
{
	int vref = 1100;
	uint16_t volt = analogRead(BAT_ADC);
	float battery_voltage = ((float)volt / 4095.0) * 2.0 * 3.3 * (vref);
	return battery_voltage;
}

void SetCHARACTERISTIC(float HumiditiGround, float HumiditiAir, float Tempreture, float Voltage, float Pressure)
{
	Tempreture_CHARACTERISTIC->setValue(Tempreture);
	HumiditiGround_CHARACTERISTIC->setValue(HumiditiGround);
	HumiditiAir_CHARACTERISTIC->setValue(HumiditiAir);
	Voltage_CHARACTERISTIC->setValue(Voltage);
	Pressure_CHARACTERISTIC->setValue(Pressure);
}
void loop()
{
	

	float HumiditiGround = readSoil();
	float HumiditiAir = readSalt();
	float Tempreture = bmp.readTemperature();
	float Voltage = readBattery();
	float Pressure = (bmp.readPressure() / 100.0F);

	SetCHARACTERISTIC(HumiditiGround, HumiditiAir, Tempreture, Voltage, Pressure);
	/*float bme_temp = bmp.readTemperature();
	float bme_pressure = (bmp.readPressure() / 100.0F);
	float bme_altitude = bmp.readAltitude(1013.25);*/

	//uint16_t soil = readSoil();
	//uint32_t salt = readSalt();
	//float bat = readBattery();

	Serial.println("__________________________");
	Serial.print("T=");
	Serial.println(Tempreture);
	Serial.print("HG=");
	Serial.println(HumiditiGround);
	/*Serial.print("HA=");
	Serial.println(HumiditiAir);*/
	Serial.print("P=");
	Serial.println(Pressure);
	Serial.print("V=");
	Serial.println(Voltage);
	delay(4000);
}
