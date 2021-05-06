#include "HardwareSerial.h"
#include "MyClientCallback.h"

MyClientCallback::MyClientCallback()
{
	connected = false;
}

void MyClientCallback::onConnect(BLEClient* pclient)
{
}

void MyClientCallback::onDisconnect(BLEClient* pclient)
{
	connected = false;
	Serial.println("onDisconnect");
}
