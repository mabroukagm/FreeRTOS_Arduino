#include <Arduino_FreeRTOS.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_4;

void setup()
{  
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  /* Create three tasks with priorities 1,2 and 3. Capture the Task details to respective handlers */
  xTaskCreate(MyTask1, "Task1", 120, NULL, 1, &TaskHandle_1); 
}


void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println(F("Loop function"));
  delay(50);
}


/* Task1 with priority 1 */
static void MyTask1(void* pvParameters)
{
  while(1)
  {
    Serial.print(F("Task1 with Priority:"));
    Serial.print(uxTaskPriorityGet(TaskHandle_1));
    Serial.println(F(" Creating Task2"));
    
    xTaskCreate(MyTask2, "Task2", 100, NULL, 3, &TaskHandle_2);
    
    Serial.print(F("Task1 with Priority:"));
    Serial.print(uxTaskPriorityGet(TaskHandle_1));
    Serial.println(F(" Deleting All"));
    vTaskDelete(TaskHandle_2);   // Delete task2 and task4 using their handles
    vTaskDelete(TaskHandle_4); 
    vTaskDelete(TaskHandle_1);    // Delete the task using the TaskHandle_1
  }
}


/* Task2 with priority 2 */
static void MyTask2(void* pvParameters)
{
  while(1)
  {    
    Serial.println(F("Task2 Running, Creating Task4"));
    xTaskCreate(MyTask4, "Task4", 100, NULL, 4, &TaskHandle_4);
    
    Serial.println(F("Back in Task2, Deleting itself"));
    vTaskDelete(NULL);     //Delete own task by passing NULL(TaskHandle_2 can also be used)
  }
}



/* Task4 with priority 4 */
static void MyTask4(void* pvParameters)
{
    Serial.println(F("Task4 Running, Changing Priority of Task1 from 1-3"));
    vTaskPrioritySet(TaskHandle_1,3); //Change the priority of task1 to 3 which is greater than task2

    while(1)
    {
      Serial.println(F("Back in Task4 "));
      vTaskDelay(100/portTICK_PERIOD_MS);   
    }
}
