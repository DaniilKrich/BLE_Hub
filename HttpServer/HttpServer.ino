/*
 Name:		HttpServer.ino
 Created:	25.05.2021 12:34:54
 Author:	dkric
*/

//#define CONFIG_SW_COEXIST_ENABLE 1


#include <ArduinoJson.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <AsyncJson.h>
#include <ESPAsyncWebServer.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

AsyncWebServer HTTPServer(80);

bool StartScan = false;
bool BLEConnect = false;
bool GetCharacteristics = false;

const char* ssid = "Keenetic-9075";
const char* password = "x9Wd86wG";

const char* PARAM_MESSAGE = "message";
const char* PARAM_MESSAGE1 = "mac";
const char* PARAM_MESSAGE2 = "UUID";

BLEClient* pClient;

void notFound(AsyncWebServerRequest* request) {
	request->send(404, "text/plain", "Not found");
}

int i;

//ble connect

#define SERVICE_UUID "94ec923e-b5a6-11eb-8529-0242ac130003" // 4fafc201-1fb5-459e-8fcc-c5c9c331914b
#define Tempreture_UUID "94ec96e4-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26a8
#define HumiditiGround_UUID "94ec97de-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26a9
#define HumiditiAir_UUID "94ec989c-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26aa
#define Voltage_UUID "94ec9964-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26ab
#define Test_UUID "94ec9a22-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26ac
#define Pressure_UUID "94ec9cac-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26ad

BLEUUID SensorBleClient::serviceUUID = BLEUUID(SERVICE_UUID);
BLEUUID SensorBleClient::Tempreture_CHARACTERISTIC_UUID = BLEUUID(Tempreture_UUID);
BLEUUID SensorBleClient::HumiditiGround_CHARACTERISTIC_UUID = BLEUUID(HumiditiGround_UUID);
BLEUUID SensorBleClient::HumiditiAir_CHARACTERISTIC_UUID = BLEUUID(HumiditiAir_UUID);
BLEUUID SensorBleClient::Voltage_CHARACTERISTIC_UUID = BLEUUID(Voltage_UUID);
BLEUUID SensorBleClient::Test_CHARACTERISTIC_UUID = BLEUUID(Test_UUID);
BLEUUID SensorBleClient::Pressure_CHARACTERISTIC_UUID = BLEUUID(Pressure_UUID);

BLERemoteCharacteristic* SensorBleClient::Tempreture_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::HumiditiGround_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::HumiditiAir_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::Voltage_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::Test_CHARACTERISTIC = NULL;
BLERemoteCharacteristic* SensorBleClient::Pressure_CHARACTERISTIC = NULL;


String BLEmac;
String BLEUUID;


class MyClientCallback : public BLEClientCallbacks {
public:
	MyClientCallback();
	bool connected;
	void onConnect(BLEClient* pclient);
	void onDisconnect(BLEClient* pclient);
};

MyClientCallback::MyClientCallback() {
	connected = false;

};



void MyClientCallback::onConnect(BLEClient* pclient) {
	connected = true;
	Serial.print("connected");
}

void MyClientCallback::onDisconnect(BLEClient* pclient) {
	connected = false;
	Serial.print("disconnected");
}


bool connectToServer() {

	std::string bLEmac = std::string(BLEmac.c_str());

	pClient = BLEDevice::createClient();
	Serial.println(" - Created client");
	pClient->setClientCallbacks(new MyClientCallback());
	pClient->connect(bLEmac, BLE_ADDR_TYPE_PUBLIC);
	return true;
}

void disconnectFromServer()
{
	pClient->disconnect();
}

bool GetBLECharacteristics() {
	BLERemoteService* pRemoteService = pClient->getService(serviceUUID);

	return true;
}

//Ble Scan

int scanTime = 5; //In seconds

BLEScan* pBLEScan;

StaticJsonDocument<1024> BleEnvironment;


class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
	void onResult(BLEAdvertisedDevice advertisedDevice) {
		//Serial.println("start create json");
		auto mac = advertisedDevice.getAddress().toString().c_str();

		BleEnvironment.add(mac);
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
};

void BLEScanSetup()
{
	//Serial.println("Scanning...");
	Serial.println("BLEScanSetup start");
	BLEDevice::init("");
	pBLEScan = BLEDevice::getScan(); //create new scan
	pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
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

void HttpSetup()
{
	Serial.println("Start HTTP server");

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.printf("WiFi Failed!\n");
		return;
	}

	Serial.print("IP Address: ");
	Serial.println(WiFi.localIP());

	HTTPServer.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(200, "text/plain", "Hello, world");
		});


	// Send a GET request to <IP>/get?message=<message>
	HTTPServer.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
		String message;
		if (request->hasParam(PARAM_MESSAGE)) {
			message = request->getParam(PARAM_MESSAGE)->value();
		}
		else {
			message = "No message sent";
		}
		request->send(200, "text/plain", "Hello, GET: " + message);
		});
	//StartScan
	HTTPServer.on("/StartScan", HTTP_GET, [](AsyncWebServerRequest* request)
		{
			StartScan = true;
			Serial.println("request - StartScan");
			request->send(200, "text/plain", String(StartScan));
		});


	//GetScanResults
	HTTPServer.on("/GetScanResults", HTTP_GET, [](AsyncWebServerRequest* request) {
		Serial.println("GetScanResults start");
		AsyncResponseStream* response = request->beginResponseStream("application/json");
		serializeJson(BleEnvironment, *response);
		request->send(response);
		Serial.println("GetScanResults stop");
		});
	//GetCharacteristics <IP>/GetCharacteristics?mac=<mac>&UUIDs=<UUID>,<UUID>
http://192.168.1.49/GetCharacteristics?mac=c4:4f:33:7f:cb:9b&UUID=94ec923e-b5a6-11eb-8529-0242ac130003&UUID=94ec923e-b5a6-11eb-8529-0242ac130003&UUID=94ec923e-b5a6-11eb-8529-0242ac130003
	HTTPServer.on("/GetCharacteristics", HTTP_GET, [](AsyncWebServerRequest* request) {
		Serial.println("GetCharacteristics start");

		if (request->hasParam(PARAM_MESSAGE1)) {
			BLEmac = request->getParam(PARAM_MESSAGE1)->value();
			BLEUUID = request->getParam(PARAM_MESSAGE2)->value();
		}

		request->send(200, "text/plain", "Hello, GET: " + BLEmac + BLEUUID);
		BLEConnect = true;
		Serial.println("GetCharacteristics  stop");
		});
	// Send a POST request to <IP>/post with a form field message set to <message>
	HTTPServer.on("/post", HTTP_POST, [](AsyncWebServerRequest* request) {
		String message;
		if (request->hasParam(PARAM_MESSAGE, true)) {
			message = request->getParam(PARAM_MESSAGE, true)->value();
		}
		else {
			message = "No message sent";
		}
		request->send(200, "text/plain", "Hello, POST: " + message);
		});

	HTTPServer.onNotFound(notFound);

	HTTPServer.begin();
}



//String GetScan(uint8_t* buffer, size_t maxLen) {
//
//
//	BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
//	Serial.print("Devices found: ");
//	Serial.println(foundDevices.getCount());
//	for (int i = 0;i < foundDevices.getCount(); i++)
//
//	{
//		auto dev = foundDevices.getDevice(i);
//		Serial.println(dev.getAddress().toString().c_str());
//	}
//
//	Serial.println("=============================================");
//	Serial.println("Scan done!");
//	pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
//
//
//	auto len = BleEnvironment.size();
//
//	String json = "[";
//	int i = 0;
//	for (BLEAdvertisedDevice dev : BleEnvironment)
//	{
//		if (i++)
//		{
//			json += ",";
//		}
//
//		json += "{";
//		json += "\"BLEAddress \":";
//		json += dev.getAddress().toString().c_str();
//		json += "}";
//		json += "]";
//	}
//
//	return json;
//}



void setup()
{
	Serial.begin(115200);
	Serial.print("setup() running");
	//  "Блок setup() выполняется на ядре "


	BLEScanSetup();
	HttpSetup();

}

void loop() {
	if (StartScan) {
		Serial.println("loop - StartScan");
		delay(50);
		//jsonBuffer.clear();
		pBLEScan->start(scanTime, false);
		Serial.println("loop - EndScan");

		StartScan = false;
	}
	if (BLEConnect)
	{
		if (connectToServer())
		{
			GetBLECharacteristics();
		}
		disconnectFromServer();
	}
	delay(1000);
}