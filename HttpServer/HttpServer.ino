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
const char* ssid = "Keenetic-9075";
const char* password = "x9Wd86wG";

const char* PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest* request) {
	request->send(404, "text/plain", "Not found");
}

int i;

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
		serializeJson(BleEnvironment,*response);
		request->send(response);
		Serial.println("GetScanResults stop");
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
	delay(1000);
}