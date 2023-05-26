#include <Arduino_FreeRTOS.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
//TaskHandle_t TaskHandle_3;
int counter =0;
void setup()
{
  
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  /* Create three tasks with priorities 1,2 and 3. Capture the Task details to respective handlers */
  xTaskCreate(MyTask1, "Task1", 100, NULL, 1, &TaskHandle_1);
  xTaskCreate(MyTask2, "Task2", 100, NULL, 2, &TaskHandle_2);
//  xTaskCreate(MyTask3, "Task3", 100, NULL, 3, &TaskHandle_3);
}


void loop()
{
//  // Hooked to IDle task, it will run whenever CPU is idle
//  Serial.println(F("Loop function"));
//  delay(50);
}


/* Task1 with priority 1 */
static void MyTask1(void* pvParameters)
{
  while(1)
  {
  counter ++;
    Serial.println(F("Task1 Running"));
if (counter == 10)
    {
     vTaskResume(TaskHandle_2);     //Delete own task by passing NULL(TaskHandle_2 can also be used)
    }
//   Serial.println(F("Back in Task1 and About to delete itself"));
 //   vTaskDelete(TaskHandle_1);    // Delete the task using the TaskHandle_1  
 vTaskDelay(100/portTICK_PERIOD_MS);
 
  }
}


/* Task2 with priority 2 */
static void MyTask2(void* pvParameters)
{
  while(1)
  {    
     
    Serial.println(F("Task2 Running"));
    
     vTaskSuspend(TaskHandle_2);     //Delete own task by passing NULL(TaskHandle_2 can also be used)
    
    vTaskDelay(100/portTICK_PERIOD_MS);

//    Serial.println(F("Back in Task2 and About to delete itself"));
   
  }
}


///* Task3 with priority 3 */
//static void MyTask3(void* pvParameters)
//{
//  while(1)
//  {    
//    Serial.println(F("Task3 Running"));
//    vTaskDelay(150/portTICK_PERIOD_MS);
//
////    Serial.println(F("Back in Task3 and About to delete itself"));
//    vTaskDelete(TaskHandle_3); 
//  }
//}
