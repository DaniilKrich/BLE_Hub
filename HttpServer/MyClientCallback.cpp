#include "MyClientCallback.h"
#include <HardwareSerial.h>

MyClientCallback::MyClientCallback() {
	connected = false;
};

void MyClientCallback::onConnect(BLEClient* pclient) {
	connected = true;
	Serial.println("connected");
}

void MyClientCallback::onDisconnect(BLEClient* pclient) {
	connected = false;
	Serial.print("disconnected");
}