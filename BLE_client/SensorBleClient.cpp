#include "HardwareSerial.h"
#include "SensorBleClient.h"
#include "C:/Users/dkric/AppData/Local/Arduino15/packages/esp32/hardware/esp32/1.0.6/libraries/BLE/src/BLEClient.h"



BLEAdvertisedDevice* SensorBleClient::myDevice = NULL;

bool SensorBleClient::doConnect = false;
bool SensorBleClient::doScan = false;

BLEUUID SensorBleClient::serviceUUID = BLEUUID(SERVICE_UUID);
BLEUUID SensorBleClient::Tempreture_CHARACTERISTIC_UUID = BLEUUID(Tempreture_UUID);
BLEUUID SensorBleClient::HumidityGround_CHARACTERISTIC_UUID = BLEUUID(HumidityGround_UUID);
BLEUUID SensorBleClient::HumidityAir_CHARACTERISTIC_UUID = BLEUUID(HumidityAir_UUID);
BLEUUID SensorBleClient::Voltage_CHARACTERISTIC_UUID = BLEUUID(Voltage_UUID);
BLEUUID SensorBleClient::Test_CHARACTERISTIC_UUID = BLEUUID(Test_UUID);
BLEUUID SensorBleClient::Pressure_CHARACTERISTIC_UUID = BLEUUID(Pressure_UUID);

BLERemoteCharacteristic* SensorBleClient::Tempreture_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::HumidityGround_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::HumidityAir_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::Voltage_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::Test_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::Pressure_CHARACTERISTIC = NULL;


SensorBleClient::SensorBleClient()
{

	BLEDevice::init("");

	// Retrieve a Scanner and set the callback we want to use to be informed when we
	// have detected a new device.  Specify that we want active scanning and start the
	// scan to run for 5 seconds.
	BLEScan* pBLEScan = BLEDevice::getScan();
	ad_callback = new MyAdvertisedDeviceCallbacks();
	pBLEScan->setAdvertisedDeviceCallbacks(ad_callback);
	pBLEScan->setInterval(1349);
	pBLEScan->setWindow(449);
	pBLEScan->setActiveScan(true);
	pBLEScan->start(5, false);

}

void SensorBleClient::notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify)
{
	Serial.print("Notify callback for characteristic ");
	Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
	Serial.print(" of data length ");
	Serial.println(length);
	Serial.print("data: ");
	Serial.println((char*)pData);
}

void SensorBleClient::LoopFunc()
{
	// If the flag "doConnect" is true then we have scanned for and found the desired
	// BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
	// connected we set the connected flag to be true.
	if (doConnect == true) {
		if (connectToServer()) {
			Serial.println("We are now connected to the BLE Server.");
		}
		else {
			Serial.println("We have failed to connect to the server; there is nothin more we will do.");
		}
		doConnect = false;
	}

	// If we are connected to a peer BLE Server, update the characteristic each time we are reached
	// with the current time since boot.
	if (cl_callback->connected) {
		//String newValue = "Time since boot: " + String(millis() / 1000);
		//Serial.println("Setting new characteristic value to \"" + newValue + "\"");
		// Set the characteristic's value to be the array of bytes that is actually a string.
		/*pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());*/
	}
	else if (doScan) {
		BLEDevice::getScan()->start(0);  // this is just eample to start scan after disconnect, most likely there is better way to do it in arduino
	}

	delay(1000); // Delay a second between loops.
}


bool SensorBleClient::connectToServer() {
	Serial.print("Forming a connection to ");
	Serial.println(myDevice->getAddress().toString().c_str());

	BLEClient* pClient = BLEDevice::createClient();
	Serial.println(" - Created client");

	cl_callback = new MyClientCallback();
	pClient->setClientCallbacks(cl_callback);

	// Connect to the remove BLE Server.
	pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
	Serial.println(" - Connected to server");

	// Obtain a reference to the service we are after in the remote BLE server.
	BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
	if (pRemoteService == nullptr) {
		Serial.print("Failed to find our service UUID: ");
		Serial.println(serviceUUID.toString().c_str());
		pClient->disconnect();
		return false;
	}
	Serial.println(" - Found our service");


	// Obtain a reference to the characteristic in the service of the remote BLE server.
	Serial.println("Get Temperature");
	Tempreture_CHARACTERISTIC = pRemoteService->getCharacteristic(Tempreture_CHARACTERISTIC_UUID);
	HumidityGround_CHARACTERISTIC = pRemoteService->getCharacteristic(HumidityGround_CHARACTERISTIC_UUID);
	HumidityAir_CHARACTERISTIC = pRemoteService->getCharacteristic(HumidityAir_CHARACTERISTIC_UUID);
	Voltage_CHARACTERISTIC = pRemoteService->getCharacteristic(Voltage_CHARACTERISTIC_UUID);
	Pressure_CHARACTERISTIC = pRemoteService->getCharacteristic(Pressure_CHARACTERISTIC_UUID);
	
	if (Tempreture_CHARACTERISTIC == nullptr) {
		Serial.println("Failed to find Tempreture characteristic");
	}
	else
	{
		Serial.print("Tempreture: ");

		uint32_t tmp = Tempreture_CHARACTERISTIC->readUInt32();
		float temperature = *((float*)&tmp);
		Serial.println(temperature);
	}

	if (HumidityGround_CHARACTERISTIC == nullptr)
	{
		Serial.println("Failed to find HumidityGround characteristic");
	}
	else
	{
		Serial.print("HumidityGround: ");
		uint32_t HMG = HumidityGround_CHARACTERISTIC->readUInt32();
		float HumidityGround = *((float*)&HMG);
		Serial.println(HumidityGround);
	}

	if (HumidityAir_CHARACTERISTIC == nullptr)
	{
		Serial.println("Failed to find HumidityAir characteristic");
	}
	else
	{
		Serial.print("HumidityAir: ");
		uint32_t HMA = HumidityAir_CHARACTERISTIC->readUInt32();
		float HumidityAir = *((float*)&HMA);
		Serial.println(HumidityAir);
	}

	if (Voltage_CHARACTERISTIC == nullptr)
	{
		Serial.println("Failed to find Voltage characteristic");
	}
	else
	{
		Serial.print("Voltage: ");
		uint32_t Vol = Voltage_CHARACTERISTIC->readUInt32();
		float Voltage = *((float*)&Vol);
		Serial.println(Voltage);
	}

	if (Pressure_CHARACTERISTIC == nullptr)
	{
		Serial.println("Failed to find Pressure characteristic");
	}
	else
	{
		Serial.print("Pressure: ");
		uint32_t Prs = Pressure_CHARACTERISTIC->readUInt32();
		float Pressure = *((float*)&Prs);
		Serial.println(Pressure);
	}
	
	



	//if (Tempreture_CHARACTERISTIC == nullptr) {
	//	Serial.println("Failed to find Tempreture characteristic");
	//}
	//else
	//{
	//	Serial.println(Tempreture_CHARACTERISTIC->readValue().c_str());
	//}



	//Serial.println(HumidityGround_CHARACTERISTIC_UUID.toString().c_str());
	//Serial.println(HumidityAir_CHARACTERISTIC_UUID.toString().c_str());
	//Serial.println(Voltage_CHARACTERISTIC_UUID.toString().c_str());
	//Serial.println(Test_CHARACTERISTIC_UUID.toString().c_str());
	//Serial.println(" - Found our characteristic");

	// Read the value of the characteristic.

	//if (pRemoteCharacteristic->canRead()) {
	//	std::string value = pRemoteCharacteristic->readValue();
	//	Serial.print("The characteristic value was: ");
	//	Serial.println(value.c_str());
	//}

	/*if (pRemoteCharacteristic->canNotify())
		pRemoteCharacteristic->registerForNotify(notifyCallback);*/

	cl_callback->connected = true;
	return true;
}
