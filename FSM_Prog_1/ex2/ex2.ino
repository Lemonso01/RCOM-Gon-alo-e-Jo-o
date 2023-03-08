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
              2, //Priority
              NULL); //Task handler
 
 xTaskCreate (taskPrint, "Print", 128, NULL, 1, NULL);

  xTaskCreate (taskDisplay, //Function
               "UART", //Description
               128, //Tasksize
               NULL, //Parameters for the function
               1, //priority
               NULL); //Task handler

  xTaskCreate (taskBuzz, //Function
               "BuzzLightyear", //Description
               128, //Tasksize
               NULL, //Parameters for the function
               1, //priority
               NULL); //Task handler
 
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

void taskPrint (void *pvParameters)
{
 int countTime = 0;
 while(1)
 {
  countTime++;
  Serial.println(countTime);
  vTaskDelay (1000 / portTICK_PERIOD_MS);
 }
}

void taskDisplay (void *pvParameters)
{
 int countClicks = 0;
 while(1)
 {
  byte btn = MFS.getButton();
  if (btn == BUTTON_1_PRESSED)
  {
  countClicks++;
  MFS.write(countClicks);
  }
 }
}

void taskBuzz (void *pvParameters)
{
  while(1)
 {
  byte btn = MFS.getButton();
  if (btn == BUTTON_3_PRESSED)
  {
  MFS.write("ALPS");
  
  }
}
}

void loop() {
}

