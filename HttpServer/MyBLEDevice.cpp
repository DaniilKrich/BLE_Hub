#include "MyBLEDevice.h"
#include <HardwareSerial.h>


void MyBLEDevice::startScan()
{
	pBLEScan->start(scanTime, false);
}

MyBLEDevice::MyBLEDevice()
{
	BLEDevice::init("");
}

void MyBLEDevice::BLEScanSetup()
{
	//Serial.println("Scanning...");
	Serial.println("BLEScanSetup start");
	
	pBLEScan = BLEDevice::getScan(); //create new scan

	myAdvertisedDeviceCallbacks = new MyAdvertisedDeviceCallbacks();
	pBLEScan->setAdvertisedDeviceCallbacks(myAdvertisedDeviceCallbacks);
	pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
	pBLEScan->setInterval(100);
	pBLEScan->setWindow(99);  // less or equal setInterval value // less or equal setInterval value
	Serial.println("BLEScanSetup end");
	//BLEScanLoop()
		//BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
		/*Serial.print("Devices found: ");
		Serial.println(foundDevices.getCount());*/
		/*for (int i = 0;i < foundDevices.getCount(); i++)
		{
			auto dev = foundDevices.getDevice(i);
			Serial.println(dev.getAddress().toString().c_str());
		}*/

	Serial.println("=============================================");


	//Serial.println("Scan done!");
	//pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
	//i = 0;
}


bool MyBLEDevice::connectToServer(String BLEmac)
{
	BLEClient* pClient = BLEDevice::createClient();
	Serial.println(" - Created client");
	clientcallbacks = new MyClientCallback();
	pClient->setClientCallbacks(clientcallbacks);

	std::string bLEmac = std::string(BLEmac.c_str());
	BLEAddress bleaddress(bLEmac);
	pClient->connect(bleaddress, BLE_ADDR_TYPE_PUBLIC);
	//Serial.println(pClient->getConnId());//это выводит 0

	BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
	Serial.println(SERVICE_UUID);

	if (pRemoteService == nullptr) {
		Serial.print("Failed to find our service UUID: ");
		Serial.println(SERVICE_UUID);
		pClient->disconnect();
		return false;
	}
	Serial.println(" - Found our service");

	std::string c = pClient->getValue(BLEUUID(SERVICE_UUID), BLEUUID(Tempreture_UUID));

	Serial.println(String(c.c_str()));

	//std::map<std::string, BLERemoteCharacteristic*>* allCharacteristics = 
	//	pRemoteService->getCharacteristics();

	//Serial.println(" - getCharacteristics");

	//for (auto const& ch : *allCharacteristics) {
	//	Serial.println(ch.first.c_str());
	//}

	//Tempreture_CHARACTERISTIC = pRemoteService->getCharacteristic(Tempreture_UUID);
	//if (Tempreture_CHARACTERISTIC == nullptr)
	//{
	//	Serial.print("Failed to find our CHARACTERISTIC UUID: ");
	//	Serial.println(Tempreture_UUID);
	//	pClient->disconnect();
	//	return false;
	//}
	//Serial.println(" - Found Tempreture_CHARACTERISTIC");




	//HumiditiGround_CHARACTERISTIC = pRemoteService->getCharacteristic(HumiditiGround_CHARACTERISTIC_UUID);
	//HumiditiAir_CHARACTERISTIC = pRemoteService->getCharacteristic(HumiditiAir_CHARACTERISTIC_UUID);
	//Voltage_CHARACTERISTIC = pRemoteService->getCharacteristic(Voltage_CHARACTERISTIC_UUID);
	//Pressure_CHARACTERISTIC = pRemoteService->getCharacteristic(Pressure_CHARACTERISTIC_UUID);
	//Test_CHARACTERISTIC = pRemoteService->getCharacteristic(Test_CHARACTERISTIC_UUID);


	//JsonChar["TempretureValue"] = (float)Tempreture_CHARACTERISTIC->readUInt32();

	//JsonChar["HumiditiGroundValue"] = HumiditiGroundValue;
	//JsonChar["HumiditiAirValue"] = HumiditiAirValue;
	//JsonChar["VoltageValue"] = VoltageValue;
	//JsonChar["PressureValue"] = PressureValue;
	//JsonChar["TestValue"] = TestValue;



	//HumiditiGroundValue = (float)HumiditiGround_CHARACTERISTIC->readUInt32();
	//HumiditiAirValue = (float)HumiditiAir_CHARACTERISTIC->readUInt32();
	//VoltageValue = (float)Voltage_CHARACTERISTIC->readUInt32();
	//TestValue = Test_CHARACTERISTIC->readValue();
	//PressureValue = (float)Pressure_CHARACTERISTIC->readUInt32();



	Serial.println("GetBLECharacteristics-end Work");
	pClient->disconnect();
	JsonCharacteristicsResult();
	Serial.println("JsonCharacteristicsResult-end Work");


	return true;
}



bool MyBLEDevice::JsonCharacteristicsResult()
{
	Serial.println("StartJsonChar");
	ARDUINOJSON_NAMESPACE::serializeJson(JsonChar, Serial);
	Serial.println("EndJsonChar");
	return true;
}
