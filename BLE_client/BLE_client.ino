#include "SensorBleClient.h"

SensorBleClient* client;

void setup() {
	Serial.begin(115200);
	Serial.println("Starting Arduino BLE Client application...");
	
	client = new SensorBleClient();

} // End of setup.


// This is the Arduino main loop function.
void loop() {
	client->LoopFunc();
	delay(10000);
} // End of loop
