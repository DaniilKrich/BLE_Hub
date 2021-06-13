#pragma once

#include <BLEServer.h>

class MyServerCallbacks : public BLEServerCallbacks
{
public:
	void onConnect(BLEServer* pServer);
	void onDisconnect(BLEServer* pServer);
};

