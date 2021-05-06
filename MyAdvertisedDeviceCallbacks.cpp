#include "HardwareSerial.h"
#include "SensorBleClient.h"

void MyAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice)
{
	Serial.print("BLE Advertised Device found: ");
	Serial.println(advertisedDevice.toString().c_str());

	// We have found a device, let us now see if it contains the service we are looking for.
	if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(SensorBleClient::serviceUUID)); {
		BLEDevice::getScan()->stop();
		SensorBleClient::myDevice = new BLEAdvertisedDevice(advertisedDevice);
		SensorBleClient::doConnect = true;
		SensorBleClient::doScan = true;
	} // Found our server
} // onResult
