#include <HardwareSerial.h>
#include <BLEClient.h>
#include "MyServerCallbacks.h"

void MyServerCallbacks::onConnect(BLEServer* pServer)
{
	BLEClient* client = (BLEClient*)pServer->getPeerDevices("true")[0].peer_device;
	Serial.println("Connected:");
	//Serial.println(client->toString().c_str());
}

void MyServerCallbacks::onDisconnect(BLEServer* pServer)
{
	Serial.println("Client Disconnected");
}
