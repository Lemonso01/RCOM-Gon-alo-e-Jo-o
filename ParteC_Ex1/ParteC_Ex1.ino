#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t mutex;

int var_global = 0;

void TaskInc( void *pvParameters );

void setup() {
  Seria.begin(9600);

  mutex = xSemaphoreCreateMutex();
  if (mutex != NULL) {
    Serial.println("Mutex created");
  }

  xTaskCreate(TaskInc, "Task1", 128, NULL, 1, NULL);
  xTaskCreate(TaskInc, "Task2", 128, NULL, 2, NULL);

  vTaskStartScheduler();
}

void TaskInc( void *PvParameters )
{
  int var_local = var_global;
  
  while(1)
  {
    
    if (xSemaphoreTake(mutex, 10) == pdTRUE)
    {
      delay(100);
      globalCount++;
      var_local++;
      vTaskDelay( random(80, 200)/ portTICK_PERIOD_MS );
      var_global = var_local;

      Serial.println(var_global);

      xSemaphoreGive(mutex);
    }
  }
}

