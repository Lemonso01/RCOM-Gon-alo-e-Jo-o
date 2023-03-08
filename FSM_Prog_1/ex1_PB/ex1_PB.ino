#include <Arduino_FreeRTOS.h>
#include <TimerOne.h>
#include <MultiFuncShield.h>
#include <Wire.h>
#include <avr/interrupt.h>

void taskBlink1 (void *pvParameters);
void taskPrint (void *pvParameters);

void setup() {
 //Initialize the shield
 Timer1.initialize();
 MFS.initialize(&Timer1);
 
//Initialize the Serial interface
 Serial.begin(9600);
 xTaskCreate (taskBlink1, //Function
              "Led1", //Description
              128, //Stack "size"
              NULL, //Parameters for the function
              1, //Priority
              NULL); //Task handler
 
 xTaskCreate (taskPrint1, "Print", 128, NULL, 1, NULL);

  xTaskCreate (taskBlink2, //Function
              "Led2", //Description
              128, //Stack "size"
              NULL, //Parameters for the function
              2, //Priority
              NULL); //Task handler

   xTaskCreate (taskPrint1, "Print", 128, NULL, 2, NULL);
 
 vTaskStartScheduler();
}

void taskBlink1 (void *pvParameters)
{
 while(1)
 {
  MFS.writeLeds (LED_1, ON);
  vTaskDelay (1000 / portTICK_PERIOD_MS);
  MFS.writeLeds (LED_1, OFF);
  vTaskDelay (1000 / portTICK_PERIOD_MS);
 }
}

void taskPrint1 (void *pvParameters)
{
 int countTime = 0;
 while(1)
 {
  countTime++;
  Serial.println(countTime);
  vTaskDelay (1000 / portTICK_PERIOD_MS);
 }
}

void taskBlink2(void *pvParameters)
{
  while(1) {
    MFS.writeLeds (LED_2, ON);
    vTaskDelay (2500 / portTICK_PERIOD_MS);
    MFS.writeLeds (LED_2, OFF);
    vTaskDelay (2500 / portTICK_PERIOD_MS);
  }
}

void loop() {
}

