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

//void notFound(AsyncWebServerRequest* request)
//{
//	request->send(404, "text/plain", "Not found");
//};

// the setup function runs once when you press reset or power the board
void setup()
{

	HttpServerSetup();

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

	Serial.println("Starting Arduino BLE Client application...");
	std::vector<const char*> menu = { "wifi","info",/*"param",*/"sep","restart","exit" };
	wm.setMenu(menu);

	// set dark theme
	wm.setClass("invert");
	wm.setConfigPortalTimeout(300); // auto close configportal after n seconds
	bool res;
	String ssid = wm.getDefaultAPName();
	//const char* AccessPointName = "AutoConnectAP";
	AccessPointName = ssid.c_str();

	char random_password[21];

	get_random_string(random_password, 10); // Get random string of length 10
	AccessPointPassword = (const char*)random_password;
	Serial.print("password = ");
	Serial.println(AccessPointPassword);

	res = wm.autoConnect(AccessPointName, AccessPointPassword); // password protected ap

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


	client = new SensorBleClient();

	pinMode(LED_PIN, OUTPUT);
	// Set outputs to LOW
	digitalWrite(LED_PIN, LOW);

}
// the loop function runs over and over again until power down or reset
void loop() {
	//checkButton();

	client->LoopFunc();



	String temperature = String(client->temperature);
	String HumiditiGround = String(client->HumiditiGround);

	if (server == NULL) {
		server = WiFiServer(80);
		Serial.println("Web Server Init");          // print a message out in the serial port
		server.begin(80);

	}
	else {

		WiFiClient client = server.available();   // Listen for incoming clients

		if (client) {                             // If a new client connects,
			currentTime = millis();
			previousTime = currentTime;
			Serial.println("New Client.");          // print a message out in the serial port
			String currentLine = "";                // make a String to hold incoming data from the client
			while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
				currentTime = millis();
				if (client.available()) {             // if there's bytes to read from the client,
					char c = client.read();             // read a byte, then
					Serial.write(c);                    // print it out the serial monitor
					header += c;
					/*if (c == '\n') { */                   // if the byte is a newline character
					  // if the current line is blank, you got two newline characters in a row.
					  // that's the end of the client HTTP request, so send a response:
						/*if (currentLine.length() == 0) {*/
							// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
							// and a content-type so the client knows what's coming, then a blank line:
							//client.println("HTTP/1.1 200 OK");
							//client.println("Content-type:text/html");
							//client.println("Connection: close");
							//client.println();

							//// turns the GPIOs on and off
							//if (header.indexOf("GET /19/on") >= 0) {
							//	Serial.println("GPIO 19 on");
							//	output19State = "on";
							//	digitalWrite(LED_PIN, HIGH);
							//}
							//else if (header.indexOf("GET /19/off") >= 0) {
							//	Serial.println("GPIO 19 off");
							//	output19State = "off";
							//	digitalWrite(LED_PIN, LOW);
							//}

							//client.println("_Layout.cshtml");
							// Display the HTML web page
							//client.println("<!DOCTYPE html><html>");
							//client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
							//client.println("<link rel=\"icon\" href=\"data:,\">");
							//// CSS to style the on/off buttons 
							//// Feel free to change the background-color and font-size attributes to fit your preferences
							//client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
							//client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
							//client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
							//client.println(".button2 {background-color: #555555;}</style>");


							//// Web Page Heading
							//client.println("<body><h1>ESP32 Web Server</h1>");

							//// Display current state, and ON/OFF buttons for GPIO 19  
							//client.println("<p>GPIO 19 - State " + output19State + "</p>");
							//// If the output19State is off, it displays the ON button       
							//if (output19State == "off") {
							//	client.println("<p><a href=\"/19/on\"><button class=\"button\">ON</button></a></p>");
							//}
							//else {
							//	client.println("<p><a href=\"/19/off\"><button class=\"button button2\">OFF</button></a></p>");
							//}
							//client.println("<table border='1'><tr><th>Temp</th><th>HumGr</th><th>Volt</th></tr>");
							//client.println("<tr><td>" + temperature + "</td><td>" + HumiditiGround + "</td></tr></table>");
							//client.println("</body></html>");

							//// The HTTP response ends with another blank line
							//client.println();
							// Break out of the while loop
							/*break;*/
						//}
						//else { // if you got a newline, then clear currentLine
						//	currentLine = "";
					//	//}
					//}
					//else if (c != '\r') {  // if you got anything else but a carriage return character,
					//	currentLine += c;      // add it to the end of the currentLine
					//}
				}
			}
			// Clear the header variable
			header = "";
			// Close the connection
			client.stop();
			Serial.println("Client disconnected.");
			Serial.println("");
		}
		//else {
		//	Serial.println("No Client.");          // print a message out in the serial port
		//}
	}
	//delay(10000);
	//digitalWrite(LED_PIN, HIGH);
}
