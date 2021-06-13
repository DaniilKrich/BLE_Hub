// MyAdvertisedDeviceCallbacks.h
#pragma once

//#include "arduino.h"
#include "BLEDevice.h"
#include "ArduinoJson.h"
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
public:
	void onResult(BLEAdvertisedDevice advertisedDevice);
	ArduinoJson::StaticJsonDocument<1024> BleEnvironment;
};