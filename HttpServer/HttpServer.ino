/*
 Name:		HttpServer.ino
 Created:	25.05.2021 12:34:54
 Author:	dkric
*/

//#define CONFIG_SW_COEXIST_ENABLE 1

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <AsyncJson.h>
#include "ArduinoJson.h"
#include <ESPAsyncWebServer.h>
#include <BLEDevice.h>

AsyncWebServer HTTPServer(80);

const char* ssid = "Keenetic-9075";
const char* password = "x9Wd86wG";

const char* PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest* request) {
	request->send(404, "text/plain", "Not found");
}

int i;

//Ble Scan
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; //In seconds

BLEScan* pBLEScan;


class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
	void onResult(BLEAdvertisedDevice advertisedDevice) {
		Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
	}
};




void BLEScanLoop()
{	//BLEScanSetup();
	Serial.begin(115200);
	Serial.println("Scanning...");
	Serial.println("1");
	BLEDevice::init("");
	Serial.println("2");
	pBLEScan = BLEDevice::getScan(); //create new scan рср опнцпюлю ярнохряъ
	Serial.println("3");
	pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	Serial.println("4");
	pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
	Serial.println("5");
	pBLEScan->setInterval(100);
	Serial.println("6");
	pBLEScan->setWindow(99);  // less or equal setInterval value
	// BLEScanLoop
	BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
	Serial.print("Devices found: ");
	Serial.println(foundDevices.getCount());
	Serial.println("Scan done!");
	pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
	i = 0;
}

void HttpSetup()
{
	Serial.println("Start HTTP server");

	Serial.begin(115200);
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
	//GetScan
	HTTPServer.on("/GetScan", HTTP_GET, [](AsyncWebServerRequest* request)
		{
			String json = "[";
			for (int i = 0; i < 5; ++i)
			{
				if (i) json += ",";
				json += "{";
				//json += "\"BLEAddress \":" + String(advertisedDevice.getAddress().toString().c_str());
				json += "}";
				json += "]";
			}
			request->send(200, "application/json", json);
			//request->send(200, "text/plain", +advertisedDevice.getAddress().toString().c_str());
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

void setup()
{
	HttpSetup();

}

void loop() {
	BLEScanLoop();
}