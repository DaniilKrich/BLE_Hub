#pragma once
#include "BLEDevice.h"



class MyClientCallback : public BLEClientCallbacks {
public:
	MyClientCallback();
	bool connected;
	void onConnect(BLEClient* pclient);
	void onDisconnect(BLEClient* pclient);
};