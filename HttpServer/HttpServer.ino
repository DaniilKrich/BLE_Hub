/*
 Name:		HttpServer.ino
 Created:	25.05.2021 12:34:54
 Author:	dkric
*/

//TaskHandle_t TaskM;
//TaskHandle_t Task1;
//TaskHandle_t Task2;
//#define CONFIG_SW_COEXIST_ENABLE 1

#include <HardwareSerial.h>
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
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

DynamicJsonBuffer jsonBuffer;
JsonObject& BleEnvironment = jsonBuffer.createObject();


class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
	void onResult(BLEAdvertisedDevice advertisedDevice) {

		auto mac = advertisedDevice.getAddress().toString().c_str();
		BleEnvironment[mac]["Name"] = advertisedDevice.getName().c_str();
		BleEnvironment[mac]["ManufacturerData"] = advertisedDevice.getManufacturerData().c_str();

		for (int i = 0;i < advertisedDevice.getServiceDataCount();i++)
		{
			BleEnvironment[mac]["Services"][i] = advertisedDevice.getServiceData(i).c_str();
		}
	}
};

void BLEScanSetup()
{
	//Serial.println("Scanning...");

	BLEDevice::init("");
	pBLEScan = BLEDevice::getScan(); //create new scan
	pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
	pBLEScan->setInterval(100);
	pBLEScan->setWindow(99);  // less or equal setInterval value // less or equal setInterval value
//BLEScanLoop()
	/*BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
	Serial.print("Devices found: ");
	Serial.println(foundDevices.getCount());
	for (int i = 0;i < foundDevices.getCount(); i++)
	{
		auto dev = foundDevices.getDevice(i);
		Serial.println(dev.getAddress().toString().c_str());
	}

	Serial.println("=============================================");*/


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
	//GetScan
	HTTPServer.on("/StartScan", HTTP_GET, [](AsyncWebServerRequest* request)
		{
			StartScan = true;
			request->send(200, "text/plain", String(StartScan));
		});


	//GetScanResults
	HTTPServer.on("/GetScanResults", HTTP_GET, [](AsyncWebServerRequest* request) {
		AsyncResponseStream* response = request->beginResponseStream("application/json");
		BleEnvironment.printTo(*response);
		request->send(response);

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


//
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
//

//void TaskCode1(void* parameter)
//{
//		Serial.print("task1 core ");
//		Serial.println(xPortGetCoreID());
//		BLEScanSetup();
//}
//void TaskCode2(void* parameter)
//{
//
//		Serial.print("task2 core ");
//		Serial.println(xPortGetCoreID());
//		HttpSetup();
//}
//
//void Master(void* parameter)
//{
//	while (true)
//	{
//
//	}
//}

void setup()
{
	Serial.begin(115200);
	Serial.print("setup() running on core ");
	//  "Блок setup() выполняется на ядре "
	Serial.println(xPortGetCoreID());

	BLEScanSetup();
	HttpSetup();



	//xTaskCreatePinnedToCore(
	//	Master, /* Функция, содержащая код задачи */
	//	"TaskM", /* Название задачи */
	//	10000, /* Размер стека в словах */
	//	NULL, /* Параметр создаваемой задачи */
	//	2, /* Приоритет задачи */
	//	&TaskM, /* Идентификатор задачи */
	//	0); /* Ядро, на котором будет выполняться задача */

	//xTaskCreatePinnedToCore(
	//	TaskCode1, /* Функция, содержащая код задачи */
	//	"Task1", /* Название задачи */
	//	10000, /* Размер стека в словах */
	//	NULL, /* Параметр создаваемой задачи */
	//	1, /* Приоритет задачи */
	//	&Task1, /* Идентификатор задачи */
	//	1); /* Ядро, на котором будет выполняться задача */

	//xTaskCreatePinnedToCore(
	//	TaskCode2, /* Функция, содержащая код задачи */
	//	"Task2", /* Название задачи */
	//	10000, /* Размер стека в словах */
	//	NULL, /* Параметр создаваемой задачи */
	//	1, /* Приоритет задачи */
	//	&Task2, /* Идентификатор задачи */
	//	0); /* Ядро, на котором будет выполняться задача */

}

void loop() {
	if (StartScan) {
		pBLEScan->start(scanTime, false);
		StartScan = false;
	}
	delay(1000);
}