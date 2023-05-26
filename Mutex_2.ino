#include <Arduino_FreeRTOS.h> 
#include <semphr.h> 
 
SemaphoreHandle_t mutex_1; 
SemaphoreHandle_t mutex_2; 
void setup() 
{ 
    Serial.begin(9600); 
    mutex_1 = xSemaphoreCreateMutex(); 
    mutex_2 = xSemaphoreCreateMutex(); 
    if (mutex_1 == NULL) { 
        Serial.println("Mutex can not be created"); 
    } 
     if (mutex_2 == NULL) { 
        Serial.println("Mutex can not be created"); 
    } 
    xTaskCreate(Task1, "Task1", 128, NULL, 1, NULL); 
    xTaskCreate(Task2, "Task2", 128, NULL, 1, NULL); 
} 
 
void Task1(void *pvParameters) { 
    while(1) { 
        xSemaphoreTake(mutex_1, portMAX_DELAY); 
        Serial.println("Hi from Task1"); 
        xSemaphoreGive(mutex_1); 
        vTaskDelay(pdMS_TO_TICKS(1000)); 
        xSemaphoreTake(mutex_2, portMAX_DELAY); 
        Serial.println("Hello from Task1"); 
        xSemaphoreGive(mutex_2); 
        vTaskDelay(pdMS_TO_TICKS(200)); 
    } 
} 
 
void Task2(void *pvParameters) { 
    while(1) { 
       xSemaphoreTake(mutex_2, portMAX_DELAY); 
        Serial.println("Hello from Task2"); 
        xSemaphoreGive(mutex_2); 
        vTaskDelay(pdMS_TO_TICKS(1000)); 
        xSemaphoreTake(mutex_1, portMAX_DELAY); 
        Serial.println("Hi from Task2"); 
        xSemaphoreGive(mutex_1); 
        vTaskDelay(pdMS_TO_TICKS(500)); 
          
    } 
} 
 
void loop() { 
}
