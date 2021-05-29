/*
 Name:		BluetoothHub.ino
 Created:	06.05.2021 14:14:43
 Author:	dkric
*/



#include "SensorBleClient.h"

SensorBleClient* client;

#pragma region WiFi

#define ESP32
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#define TRIGGER_PIN 39
//#define LED_PIN 19

WiFiManager wm; // global wm instance
WiFiManagerParameter custom_field; // global param ( for non blocking w params )

// Generate random string in "str" of length "len" chars
static void get_random_string(char* str, unsigned int len)
{
	unsigned int i;

	// reseed the random number generator
	srand(time(NULL));

	for (i = 0; i < len; i++)
	{
		// Add random printable ASCII char
		str[i] = (rand() % ('~' - ' ')) + ' ';
	}
	str[i] = '\0';
}

#define LILYGO_T5_V213

#include <qrcode.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <boards.h>
#include <GxEPD.h>

GxIO_Class io(SPI, EPD_CS, EPD_DC, EPD_RSET);
GxEPD_Class display(io, EPD_RSET, EPD_BUSY);

QRcode qrcode(&display);

const char* AccessPointPassword;
const char* AccessPointName;

void OnStartAP(WiFiManager* wm)
{
	wifi_config_t conf_config;
	esp_wifi_get_config(WIFI_IF_AP, &conf_config); // == ESP_OK
	wifi_ap_config_t config = conf_config.ap;



	char* ssid = (char*)config.ssid;
	char* pwd = (char*)config.password;
	char buf[100];

	//"WIFI:T:WPA;S:MyNetworkName;P:ThisIsMyPassword;"
	sprintf(buf, "WIFI:T:WPA;S:%s;P:%s;", ssid, pwd);
	qrcode.create(String((const char*)buf));

}

void OnSaveConfig()
{
	qrcode.init();
}

void checkButton() {
	// check for button press
	if (digitalRead(TRIGGER_PIN) == LOW) {
		// poor mans debounce/press-hold, code not ideal for production
		delay(50);
		if (digitalRead(TRIGGER_PIN) == LOW) {
			Serial.println("Button Pressed");
			// still holding button for 3000 ms, reset settings, code not ideaa for production
			delay(3000); // reset delay hold
			if (digitalRead(TRIGGER_PIN) == LOW) {
				Serial.println("Button Held");
				Serial.println("Erasing Config, restarting");
				wm.resetSettings();
				ESP.restart();
			}

			// start portal w delay
			Serial.println("Starting config portal");
			wm.setConfigPortalTimeout(120);

			if (!wm.startConfigPortal(AccessPointName, AccessPointPassword)) {
				Serial.println("failed to connect or hit timeout");
				delay(3000);
				// ESP.restart();
			}
			else {
				//if you get here you have connected to the WiFi
				Serial.println("connected...yeey :)");
			}
		}
	}
}


String getParam(String name) {
	//read parameter from server, for customhmtl input
	String value;
	if (wm.server->hasArg(name)) {
		value = wm.server->arg(name);
	}
	return value;
}
WiFiServer server = NULL;

void saveParamCallback() {
	Serial.println("[CALLBACK] saveParamCallback fired");

	// Set web server port number to 80
	server = WiFiServer(80);
}


unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Variable to store the HTTP request
String header;
// Auxiliar variables to store the current output state
String output19State = "off";

#pragma endregion // WiFI

#pragma region HttpServer

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <AsyncJson.h>
#include "ArduinoJson.h"
#include <ESPAsyncWebServer.h>

AsyncWebServer HTTPServer(80);

const char* PARAM_MESSAGE = "message";

void HttpServerSetup()
{

	HTTPServer.on("/", HTTP_GET, [](AsyncWebServerRequest* request)
		{
			request->send(200, "text/plain", "Hello, world");
		});

	// Send a GET request to <IP>/get?message=<message>
	HTTPServer.on("/get", HTTP_GET, [](AsyncWebServerRequest* request)
		{
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
			}
			//request->send(200, "application/json", json);
			request->send(200, "text/plain", +advertisedDevice.getAddress().toString().c_str());
		});
	//GetTempreture
	HTTPServer.on("/GetTempreture", HTTP_GET, [](AsyncWebServerRequest* request)
		{
			String json = "[";
			for (int i = 0; i < 5; ++i) {
				if (i) json += ",";
				json += "{";
				json += "\"Tempreture \":" + String();
				json += "}";
			}
			request->send(200, "application/json", json);
		});
	// Send a POST request to <IP>/post with a form field message set to <message>
	HTTPServer.on("/post", HTTP_POST, [](AsyncWebServerRequest* request)
		{
			String message;
			if (request->hasParam(PARAM_MESSAGE, true)) {
				message = request->getParam(PARAM_MESSAGE, true)->value();
			}
			else {
				message = "No message sent";
			}
			request->send(200, "text/plain", "Hello, POST: " + message);
		});




	//HTTPServer.onNotFound(notFound);

	HTTPServer.begin();
}

#pragma endregion //HttpServer

// the setup function runs once when you press reset or power the board
void setup()
{
#pragma region //WiFi-M-Setup
	setlocale(LC_ALL, "");

	WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

	Serial.begin(115200);
	Serial.setDebugOutput(true);
	display.init();
	delay(3000);
	// Initialize QRcode display using library
	qrcode.init();

	wm.setAPCallback(OnStartAP);
	wm.setSaveConfigCallback(OnSaveConfig);

	Serial.println("\n Starting");

	pinMode(TRIGGER_PIN, INPUT);

	std::vector<const char*> menu = { "wifi","info",/*"param",*/"sep","restart","exit" };
	wm.setMenu(menu);

	wm.setClass("invert");

	wm.setConfigPortalTimeout(300);

	bool res;

	String ssid = wm.getDefaultAPName();

	AccessPointName = ssid.c_str();

	char random_password[21];

	get_random_string(random_password, 10); // Get random string of length 10
	AccessPointPassword = (const char*)random_password;
	Serial.print("password = ");
	Serial.println(AccessPointPassword);

	res = wm.autoConnect(AccessPointName, AccessPointPassword);

	if (!res) {
		Serial.println("Failed to connect or hit timeout");
		// ESP.restart();
	}
	else {
		//if you get here you have connected to the WiFi
		char* msg1 = new char[100];
		sprintf(msg1, "connected to %s", wm.getWiFiSSID(true));
		Serial.println((const char*)msg1);
	}
#pragma endregion // WiFi-M-Setup


	HttpServerSetup();

	//bleSetup


	//setlocale(LC_ALL, "");
	//WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  

	//Serial.begin(115200);
	//Serial.setDebugOutput(true);
	//display.init();
	//delay(3000);
	//// Initialize QRcode display using library
	//qrcode.init();

	//wm.setAPCallback(OnStartAP);
	//wm.setSaveConfigCallback(OnSaveConfig);

	//Serial.println("\n Starting");

	//pinMode(TRIGGER_PIN, INPUT);

	//Serial.println("Starting Arduino BLE Client application...");
	//std::vector<const char*> menu = { "wifi","info",/*"param",*/"sep","restart","exit" };
	//wm.setMenu(menu);

	//// set dark theme
	//wm.setClass("invert");
	//wm.setConfigPortalTimeout(300); // auto close configportal after n seconds
	//bool res;
	//String ssid = wm.getDefaultAPName();
	////const char* AccessPointName = "AutoConnectAP";
	//AccessPointName = ssid.c_str();

	//char random_password[21];

	//get_random_string(random_password, 10); // Get random string of length 10
	//AccessPointPassword = (const char*)random_password;
	//Serial.print("password = ");
	//Serial.println(AccessPointPassword);

	//res = wm.autoConnect(AccessPointName, AccessPointPassword); // password protected ap

	//if (!res) {
	//	Serial.println("Failed to connect or hit timeout");
	//	// ESP.restart();
	//}
	//else {
	//	//if you get here you have connected to the WiFi
	//	char* msg1 = new char[100];
	//	sprintf(msg1, "connected to %s", wm.getWiFiSSID(true));
	//	Serial.println((const char*)msg1);
	//}

	///// <summary>
	///// Ble Client
	///// </summary>
	//client = new SensorBleClient();

}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.println("\n start checkButton \n");
	checkButton();
	Serial.println("\n start client->LoopFunc\n ");
	client->LoopFunc();
}
