/*
 Name:		HttpServer.ino
 Created:	25.05.2021 12:34:54
 Author:	dkric
*/

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


void setup() {

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
				BLEDevice::getScan()->start(0);
				BLEAdvertisedDevice advertisedDevice;
				String json = "[";
				for (int i = 0; i < 5; ++i)
				{
					if (i) json += ",";
					json += "{";
					json += "\"BLEAddress \":" + String(advertisedDevice.getAddress().toString().c_str());
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

void loop() {
}