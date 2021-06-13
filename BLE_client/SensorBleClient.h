#pragma once

#include <BLEDevice.h>
#include "MyAdvertisedDeviceCallbacks.h"
#include "MyClientCallback.h"


#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define Tempreture_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define HumidityGround_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a9"
#define HumidityAir_UUID "beb5483e-36e1-4688-b7f5-ea07361b26aa"
#define Voltage_UUID "beb5483e-36e1-4688-b7f5-ea07361b26ab"
#define Test_UUID "beb5483e-36e1-4688-b7f5-ea07361b26ac"
#define Pressure_UUID "beb5483e-36e1-4688-b7f5-ea07361b26ad"

class SensorBleClient
{
public:

	SensorBleClient();

	MyAdvertisedDeviceCallbacks* ad_callback;
	MyClientCallback* cl_callback;

	// The remote service we wish to connect to.
	static	BLEUUID serviceUUID;// ("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
	// The characteristic of the remote service we are interested in.
	static	BLEUUID    Tempreture_CHARACTERISTIC_UUID;// ("beb5483e-36e1-4688-b7f5-ea07361b26a8");
	static	BLEUUID    HumidityGround_CHARACTERISTIC_UUID;// ("beb5483e-36e1-4688-b7f5-ea07361b26a9");
	static	BLEUUID    HumidityAir_CHARACTERISTIC_UUID;// ("beb5483e-36e1-4688-b7f5-ea07361b26aa");
	static	BLEUUID    Voltage_CHARACTERISTIC_UUID;// ("beb5483e-36e1-4688-b7f5-ea07361b26ab");
	static	BLEUUID    Test_CHARACTERISTIC_UUID;// ("beb5483e-36e1-4688-b7f5-ea07361b26ac");
	static	BLEUUID    Pressure_CHARACTERISTIC_UUID;// ("beb5483e-36e1-4688-b7f5-ea07361b26ac");

	static bool doConnect;
	static bool doScan;
	static BLERemoteCharacteristic* Tempreture_CHARACTERISTIC;
	static BLERemoteCharacteristic* HumidityGround_CHARACTERISTIC;
	static BLERemoteCharacteristic* HumidityAir_CHARACTERISTIC;
	static BLERemoteCharacteristic* Voltage_CHARACTERISTIC;
	static BLERemoteCharacteristic* Test_CHARACTERISTIC;
	static BLERemoteCharacteristic* Pressure_CHARACTERISTIC;



	static BLEAdvertisedDevice* myDevice;

	static void notifyCallback(
		BLERemoteCharacteristic* pBLERemoteCharacteristic,
		uint8_t* pData,
		size_t length,
		bool isNotify);

	void LoopFunc();
	bool connectToServer();
};

