/*
 Name:		HttpServer.ino
 Created:	25.05.2021 12:34:54
 Author:	dkric
*/

#include "Arduino.h"
#include "MyAdvertisedDeviceCallbacks.h"
#include <ArduinoJson.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiClient.h>
//#include <ESPAsyncWebServer.h>
#include <WebServer.h>
#include <BLEDevice.h>
#include "MyBLEDevice.h"

//AsyncWebServer HTTPServer(80);
WebServer HTTPServer(80);

bool StartScan = false;
bool BLEConnect = false;
bool GetCharacteristics = false;
String BLEmac;

const char *ssid = "Keenetic-9075";
const char *password = "x9Wd86wG";

const char *PARAM_MESSAGE = "message";
String PARAM_MESSAGE1 = "mac";

//void notFound(AsyncWebServerRequest* request) {
//	request->send(404, "text/plain", "Not found");
//}

int i;

MyBLEDevice *device; // = new MyBLEDevice();

//void JsonCharacteristicsResult()
//{
//	JsonChar["TempretureValue"] = device->clientcallbacks->TempretureValue;
//	JsonChar["HumiditiGroundValue"] = device->clientcallbacks->HumiditiGroundValue;
//	JsonChar["HumiditiAirValue"] = device->clientcallbacks->HumiditiAirValue;
//	JsonChar["VoltageValue"] = device->clientcallbacks->VoltageValue;
//	JsonChar["PressureValue"] = device->clientcallbacks->PressureValue;
//	JsonChar["TestValue"] = device->clientcallbacks->TestValue;
//}

//Ble Scan

void HttpSetup()
{
	Serial.println("Start HTTP server");

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		Serial.printf("WiFi Failed!\n");
		return;
	}

	Serial.print("IP Address: ");
	Serial.println(WiFi.localIP());

	HTTPServer.on("/", HTTP_GET, []()
				  { HTTPServer.send(200, "text/plain", "Hello, world"); });

	// Send a GET request to <IP>/get?message=<message>
	//HTTPServer.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
	//	String message;
	//	if (request->hasParam(PARAM_MESSAGE)) {
	//		message = request->getParam(PARAM_MESSAGE)->value();
	//	}
	//	else {
	//		message = "No message sent";
	//	}
	//	request->send(200, "text/plain", "Hello, GET: " + message);
	//	});
	////StartScan
	HTTPServer.on("/StartScan", HTTP_GET, []()
				  {
					  StartScan = true;
					  Serial.println("request - StartScan");
					  HTTPServer.send(200, "text/plain", String(StartScan));
				  });

	////GetScanResults
	HTTPServer.on("/GetScanResults", HTTP_GET, []()
				  {
					  Serial.println("GetScanResults start");
					  String response;
					  ARDUINOJSON_NAMESPACE::serializeJson(device->myAdvertisedDeviceCallbacks->BleEnvironment, response);
					  HTTPServer.send(200, "application/json", response);
					  Serial.println("GetScanResults stop");
				  });

	//GetCharacteristics <IP>/GetCharacteristics?mac=<mac>
	//GetCharacteristics?mac=c4:4f:33:7f:cb:9b
	//&UUID=94ec923e-b5a6-11eb-8529-0242ac130003&UUID=94ec923e-b5a6-11eb-8529-0242ac130003&UUID=94ec923e-b5a6-11eb-8529-0242ac130003
	HTTPServer.on("/GetCharacteristics", HTTP_GET, []()
				  {
					  Serial.println("GetCharacteristics start");

					  if (HTTPServer.hasArg(PARAM_MESSAGE1))
					  {
						  BLEmac = HTTPServer.arg(PARAM_MESSAGE1);
					  }

					  HTTPServer.send(200, "text/plain", "Hello, BLEmac: " + BLEmac);
					  BLEConnect = true;
					  Serial.println("GetCharacteristics  stop");
				  });

	//GetCharacteristicsResult
	HTTPServer.on("/GetCharacteristicsResult", HTTP_GET, []()
				  {
					  Serial.println("GetCharacteristicsResult");
					  String response;
					  ARDUINOJSON_NAMESPACE::serializeJson(device->JsonChar, response);
					  HTTPServer.send(200, "application/json", response);
				  });
	////restart
	HTTPServer.on("/restart", HTTP_GET, []()
				  {
					  HTTPServer.send(200, "text/plain", "RESTART");
					  ESP.restart();
				  });
	//// Send a POST request to <IP>/post with a form field message set to <message>
	//HTTPServer.on("/post", HTTP_POST, [](AsyncWebServerRequest* request) {
	//	String message;
	//	if (request->hasParam(PARAM_MESSAGE, true)) {
	//		message = request->getParam(PARAM_MESSAGE, true)->value();
	//	}
	//	else {
	//		message = "No message sent";
	//	}
	//	request->send(200, "text/plain", "Hello, POST: " + message);
	//	});

	//HTTPServer.onNotFound(notFound);

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
	device = new MyBLEDevice();
	//BLEScanSetup();
	HttpSetup();
}

void loop()
{
	HTTPServer.handleClient();
	delay(20);

	if (StartScan)
	{
		StartScan = false;
		Serial.println("loop - StartScan");
		delay(50);
		device->startScan();
		Serial.println("loop - EndScan");
	}

	if (BLEConnect)
	{
		BLEConnect = false;
		Serial.println("StartBLEConnect");
		delay(50);
		device->connectToServer(BLEmac);
		Serial.println("EndBLEConnect");
	}

	delay(20);
}

void app_main()
{
	setup();
	while (true)
	{
		loop();
	}
}
