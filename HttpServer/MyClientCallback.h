#pragma once


#define SERVICE_UUID "94ec923e-b5a6-11eb-8529-0242ac130003" // 4fafc201-1fb5-459e-8fcc-c5c9c331914b
#define Tempreture_UUID  "94ec96e4-b5a6-11eb-8529-0242ac130003"// beb5483e-36e1-4688-b7f5-ea07361b26a8
#define HumiditiGround_UUID  "94ec97de-b5a6-11eb-8529-0242ac130003"// beb5483e-36e1-4688-b7f5-ea07361b26a9
#define HumiditiAir_UUID  "94ec989c-b5a6-11eb-8529-0242ac130003"// beb5483e-36e1-4688-b7f5-ea07361b26aa
#define Voltage_UUID "94ec9964-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26ab
#define Test_UUID "94ec9a22-b5a6-11eb-8529-0242ac130003" // beb5483e-36e1-4688-b7f5-ea07361b26ac
#define Pressure_UUID "94ec9cac-b5a6-11eb-8529-0242ac130003"// beb5483e-36e1-4688-b7f5-ea07361b26ad

//ble connect
#include <BLEDevice.h>


class MyClientCallback : public BLEClientCallbacks {
public:
	MyClientCallback();
	bool connected;
	void onConnect(BLEClient* pclient);
	void onDisconnect(BLEClient* pclient);
};
