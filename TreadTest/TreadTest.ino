/*
 Name:		TreadTest.ino
 Created:	29.05.2021 1:25:27
 Author:	dkric
*/
#include <HardwareSerial.h>

TaskHandle_t TaskM;
TaskHandle_t Task1;
TaskHandle_t Task2;
int i=0;

void TaskCode1(void* parameter)
{
	for (;;) {
		Serial.print("task1 core ");
		Serial.println(xPortGetCoreID());
		delay(1000);
		i = 1;
	}
}
void TaskCode2(void* parameter)
{
	for (;;) {
		Serial.print("task2 core ");
		Serial.println(xPortGetCoreID());
		delay(1000);
		i = 0;
	}
}

void Master(void* parameter)
{
	while (true)
	{
		vTaskSta
	}
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	Serial.print("setup() running on core ");
	//  "���� setup() ����������� �� ���� "
	Serial.println(xPortGetCoreID());

	xTaskCreatePinnedToCore(
		Master, /* �������, ���������� ��� ������ */
		"TaskM", /* �������� ������ */
		10000, /* ������ ����� � ������ */
		NULL, /* �������� ����������� ������ */
		2, /* ��������� ������ */
		&TaskM, /* ������������� ������ */
		0); /* ����, �� ������� ����� ����������� ������ */

	xTaskCreatePinnedToCore(
		TaskCode1, /* �������, ���������� ��� ������ */
		"Task1", /* �������� ������ */
		10000, /* ������ ����� � ������ */
		NULL, /* �������� ����������� ������ */
		1, /* ��������� ������ */
		&Task1, /* ������������� ������ */
		1); /* ����, �� ������� ����� ����������� ������ */
	
	xTaskCreatePinnedToCore(
		TaskCode2, /* �������, ���������� ��� ������ */
		"Task2", /* �������� ������ */
		10000, /* ������ ����� � ������ */
		NULL, /* �������� ����������� ������ */
		1, /* ��������� ������ */
		&Task2, /* ������������� ������ */
		1); /* ����, �� ������� ����� ����������� ������ */
}

// the loop function runs over and over again until power down or reset
void loop() {
	
}
