#pragma once
#include <BLEDevice.h>


class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
	/**
	  * Called for each advertising BLE server.
	  */
	void onResult(BLEAdvertisedDevice advertisedDevice);
}; // MyAdvertisedDeviceCallbacks