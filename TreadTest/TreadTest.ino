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
	//  "Блок setup() выполняется на ядре "
	Serial.println(xPortGetCoreID());

	xTaskCreatePinnedToCore(
		Master, /* Функция, содержащая код задачи */
		"TaskM", /* Название задачи */
		10000, /* Размер стека в словах */
		NULL, /* Параметр создаваемой задачи */
		2, /* Приоритет задачи */
		&TaskM, /* Идентификатор задачи */
		0); /* Ядро, на котором будет выполняться задача */

	xTaskCreatePinnedToCore(
		TaskCode1, /* Функция, содержащая код задачи */
		"Task1", /* Название задачи */
		10000, /* Размер стека в словах */
		NULL, /* Параметр создаваемой задачи */
		1, /* Приоритет задачи */
		&Task1, /* Идентификатор задачи */
		1); /* Ядро, на котором будет выполняться задача */
	
	xTaskCreatePinnedToCore(
		TaskCode2, /* Функция, содержащая код задачи */
		"Task2", /* Название задачи */
		10000, /* Размер стека в словах */
		NULL, /* Параметр создаваемой задачи */
		1, /* Приоритет задачи */
		&Task2, /* Идентификатор задачи */
		1); /* Ядро, на котором будет выполняться задача */
}

// the loop function runs over and over again until power down or reset
void loop() {
	
}
