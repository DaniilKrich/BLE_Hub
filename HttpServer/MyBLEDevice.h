#pragma once
#include <ArduinoJson.h>
#include <BLEDevice.h>
#include <WString.h>
#include "MyClientCallback.h"
#include "MyAdvertisedDeviceCallbacks.h"


class MyBLEDevice
{
public:
	void startScan();
	MyBLEDevice();
	MyClientCallback* clientcallbacks;
	MyAdvertisedDeviceCallbacks* myAdvertisedDeviceCallbacks;
	BLEScan* pBLEScan;
	void BLEScanSetup();
	bool connectToServer(String BLEmac);
	ArduinoJson::StaticJsonDocument<1024> JsonChar;
private:
	std::string TestValue;
	bool JsonCharacteristicsResult();
	BLERemoteCharacteristic* Tempreture_CHARACTERISTIC;// = NULL;
	BLERemoteCharacteristic* HumiditiGround_CHARACTERISTIC;// = NULL;
	BLERemoteCharacteristic* HumiditiAir_CHARACTERISTIC;//= NULL;
	BLERemoteCharacteristic* Voltage_CHARACTERISTIC;//= NULL;
	BLERemoteCharacteristic* Test_CHARACTERISTIC;//= NULL;
	BLERemoteCharacteristic* Pressure_CHARACTERISTIC;// = NULL;
	const int scanTime = 5; //In seconds
};

