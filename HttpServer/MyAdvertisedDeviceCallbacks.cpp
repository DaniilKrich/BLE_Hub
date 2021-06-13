#include "MyAdvertisedDeviceCallbacks.h"
#include <HardwareSerial.h>


void MyAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
	Serial.println("start create json");
	std::string mac = advertisedDevice.getAddress().toString().c_str();
	auto dev = BleEnvironment.createNestedObject(mac);

	std::string name = advertisedDevice.getName();
	dev["Name"] = name;


	//Serial.println(mac);

	Serial.println(advertisedDevice.toString().c_str());

	//auto& jo2 = BleEnvironment.createNestedObject(mac);

	//jo2["Name"] = advertisedDevice.getName().c_str();
	//jo2["ManufacturerData"] = advertisedDevice.getManufacturerData().c_str();

	//BleEnvironment[mac] = jo2;


	//for (int i = 0;i < advertisedDevice.getServiceDataCount();i++)
	//{
	//	auto& serv = jo2.createNestedArray("Services");
	//	
	//	serv[i] = advertisedDevice.getServiceData(i).c_str();
	//	//Serial.println(advertisedDevice.getServiceData(i).c_str());
	//}
	//Serial.println("end create json");
	//String str;
	//BleEnvironment.printTo(str);

	//Serial.println(str);
}
