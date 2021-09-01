/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "string.h"
#include "usart.h"
#include "iwdg.h"
//#include "stdlib.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint32_t idle_ticks;
volatile uint32_t usart_tick;
volatile uint32_t usart_tx_period;
uint32_t queue_put;
uint32_t count_queue_get;
uint32_t sum_task01;
uint32_t sum_task02;
uint32_t sum_task03;
volatile uint8_t flag_dma_uart2;
uint32_t count_error = 0;
uint32_t sum_task;

const char Str1[] = "value = 01.............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................**************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************01\r\n";
const char Str2[] = "value = 02.........................................................................................................................................................................................................................................................\r\n";
const char Str3[] = "value = 03.........................................................................................................................................................................................................................................................\r\n";

extern sData sLog;

HeapStats_t my_Heap_Status;
uint8_t user_flag;

uint16_t highWaterMarkValue;

void myFunction1(void)
{
	char myArray[] = "myArray1...........................................................................................\r\n";

	printf(myArray);
//	HAL_UART_Transmit(&huart2, (uint8_t *)myArray, sizeof(myArray), 2000);
}

void myFunction2(void)
{
	char myArray[] = "myArray2.................................................................................................................................\r\n";

	printf(myArray);
//	HAL_UART_Transmit(&huart2, (uint8_t *)myArray, sizeof(myArray), 2000);
}

void myFunction3(void)
{
	char myArray[] = "myArray3.....................................................................................................................................................................................\r\n";

	printf(myArray);
//	HAL_UART_Transmit(&huart2, (uint8_t *)myArray, sizeof(myArray), 2000);
}

/* USER CODE END Variables */
osThreadId myTask01Handle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
osThreadId myTask05Handle;
osThreadId myTask06Handle;
osMessageQId myQueue01Handle;
osMutexId myMutex01Handle;
osSemaphoreId myBinarySem01Handle;
osSemaphoreId myBinarySem02Handle;
osSemaphoreId myCountingSem01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void StartTask01(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void StartTask04(void const * argument);
void StartTask05(void const * argument);
void StartTask06(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
	idle_ticks += 1;
}
/* USER CODE END 2 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of myMutex01 */
  osMutexDef(myMutex01);
  myMutex01Handle = osMutexCreate(osMutex(myMutex01));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

  /* definition and creation of myBinarySem02 */
  osSemaphoreDef(myBinarySem02);
  myBinarySem02Handle = osSemaphoreCreate(osSemaphore(myBinarySem02), 1);

  /* definition and creation of myCountingSem01 */
  osSemaphoreDef(myCountingSem01);
  myCountingSem01Handle = osSemaphoreCreate(osSemaphore(myCountingSem01), 3);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  osMessageQDef(myQueue01, 5, uint32_t);
  myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of myTask01 */
  osThreadDef(myTask01, StartTask01, osPriorityNormal, 0, 128);
  myTask01Handle = osThreadCreate(osThread(myTask01), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityNormal, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, StartTask04, osPriorityNormal, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* definition and creation of myTask05 */
  osThreadDef(myTask05, StartTask05, osPriorityNormal, 0, 128);
  myTask05Handle = osThreadCreate(osThread(myTask05), NULL);

  /* definition and creation of myTask06 */
  osThreadDef(myTask06, StartTask06, osPriorityAboveNormal, 0, 128);
  myTask06Handle = osThreadCreate(osThread(myTask06), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTask01 */
/**
  * @brief  Function implementing the myTask01 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask01 */
void StartTask01(void const * argument)
{
  /* USER CODE BEGIN StartTask01 */
//uint32_t queue_value = 1;
	uint32_t index = 0;
	uint32_t sum_temp = 0;
  /* Infinite loop */
  for(;;)
  {
	  //HAL_UART_Transmit(&huart2, (uint8_t *)"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\r\n", 244,200);
	  while (index < 10000000)
	  {
		  //osMutexWait(myMutex01Handle, osWaitForever);
		  sum_temp += 1;
		  //osMutexRelease(myMutex01Handle);
		  index++;
	  }
	  if (index == 10000000)
	  {
	  	  osMessagePut(myQueue01Handle, sum_temp, 0);
	  	  index++;
	  }
	  HAL_IWDG_Refresh(&hiwdg);
//	  taskYIELD();
//	  huart2.gState = HAL_UART_STATE_READY;
//	  if (osSemaphoreWait(myCountingSem01Handle, osWaitForever) == osOK)
//	  {
//		  if (osMessagePut(myQueue01Handle, queue_value, 0) != osOK)
//		  {
//			  //HAL_UART_Transmit_DMA(&huart2, (uint8_t *)"Task01 send queue error\r\n", strlen("Task01 send queue error\r\n"));
//		  }
//	  }
  }
  /* USER CODE END StartTask01 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
//	TickType_t last_tick;
//	last_tick = xTaskGetTickCount();
//	uint32_t queue_value = 2;
	uint32_t index = 0;
	uint32_t sum_temp = 0;
  /* Infinite loop */
  for(;;)
  {
//	  HAL_UART_Transmit(&huart2, (uint8_t *)"222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222\r\n", 244,200);
	  while (index < 10000000)
	  {
//		  osMutexWait(myMutex01Handle, osWaitForever);
		  sum_temp += 1;
//		  osMutexRelease(myMutex01Handle);
		  index++;
	  }
	  if (index == 10000000)
	  {
		  osMessagePut(myQueue01Handle, sum_temp, 0);
		  index++;
	  }
//	  taskYIELD();
//	  huart2.gState = HAL_UART_STATE_READY;
//	  if (osSemaphoreWait(myCountingSem01Handle, osWaitForever) == osOK)
//	  {
//		  if (osMessagePut(myQueue01Handle, queue_value, 0) != osOK)
//		  {
//			  //HAL_UART_Transmit_DMA(&huart2, (uint8_t *)"Task02 send queue error\r\n", strlen("Task02 send queue error\r\n"));
//		  }
//	  }
	  //vTaskDelayUntil(&last_tick, 100);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
//	uint32_t queue_value = 3;
	uint32_t index = 0;
	uint32_t sum_temp = 0;
  /* Infinite loop */
  for(;;)
  {
//	  HAL_UART_Transmit(&huart2, (uint8_t *)"333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333\r\n", 244,200);
	  while (index < 10000000)
	  {
//		  osMutexWait(myMutex01Handle, osWaitForever);
		  sum_temp += 1;
//		  osMutexRelease(myMutex01Handle);
		  index++;
	  }
	  if (index == 10000000)
	  {
		  osMessagePut(myQueue01Handle, sum_temp, 0);
		  index++;
	  }
//	  taskYIELD();
//	  huart2.gState = HAL_UART_STATE_READY;
//	  if (osSemaphoreWait(myCountingSem01Handle, osWaitForever) == osOK)
//	  {
//		  if (osMessagePut(myQueue01Handle, queue_value, 0) != osOK)
//		  {
//			  //HAL_UART_Transmit_DMA(&huart2, (uint8_t *)"Task03 send queue error\r\n", strlen("Task03 send queue error\r\n"));
//		  }
//	  }
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void const * argument)
{
  /* USER CODE BEGIN StartTask04 */
//	osEvent queue_get;
	uint32_t index = 0;
	uint32_t sum_temp = 0;
  /* Infinite loop */
  for(;;)
  {
//	  HAL_UART_Transmit(&huart2, (uint8_t *)"444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444\r\n", 244,200);
	  while (index < 10000000)
	  {
//		  osMutexWait(myMutex01Handle, osWaitForever);
		  sum_temp += 1;
//		  osMutexRelease(myMutex01Handle);
		  index++;
	  }
	  if (index == 10000000)
	  {
		  osMessagePut(myQueue01Handle, sum_temp, 0);
		  index++;
	  }
//	  taskYIELD();
//	  huart2.gState = HAL_UART_STATE_READY;
//	  queue_get = osMessageGet(myQueue01Handle, osWaitForever);
//	  if (queue_get.status == osEventMessage)
//	  {
//		  switch(queue_get.value.v)
//		  {
//		  case 1:
//			  HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Str1, strlen(Str1));
//			  sum_task01 += 1;
//			  break;
//		  case 2:
//			  HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Str2, strlen(Str2));
//			  sum_task02 += 1;
//			  break;
//		  case 3:
//			  HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Str3, strlen(Str3));
//			  sum_task03 += 1;
//			  break;
//		  default:
//			  break;
//		  }
//	  }
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void const * argument)
{
  /* USER CODE BEGIN StartTask05 */
//	TickType_t last_tick;
//	last_tick = xTaskGetTickCount();
//	osSemaphoreWait(myBinarySem01Handle, 0);
//	osSemaphoreWait(myCountingSem01Handle, 0);
//	char Str5[] = "$$$$$$$$$$$$ Task 05 $$$$$$$$$$$\r\n";
	uint32_t index = 0;
	uint32_t sum_temp = 0;
//	uint8_t *dy_var = NULL;
  /* Infinite loop */
  for(;;)
  {
//	  HAL_UART_Transmit(&huart2, (uint8_t *)"555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555\r\n", 244,200);
	  while (index < 10000000)
	  {
//		  osMutexWait(myMutex01Handle, osWaitForever);
		  sum_temp += 1;
//		  osMutexRelease(myMutex01Handle);
		  index++;
	  }
	  if (index == 10000000)
	  {
		  osMessagePut(myQueue01Handle, sum_temp, 0);
		  index++;
	  }

/*	  if (user_flag == 1)
	  {
		  dy_var = pvPortMalloc(100);
		  *dy_var = user_flag;
		  user_flag = 0;
		  vPortFree(dy_var);
	  }*/

//	  taskYIELD();
//	  huart2.gState = HAL_UART_STATE_READY;
//	  HAL_UART_Transmit(&huart2, (uint8_t *)Str5, strlen(Str5), 100);
//	  osSemaphoreRelease(myCountingSem01Handle);
//	  osSemaphoreRelease(myCountingSem01Handle);
//	  osSemaphoreRelease(myCountingSem01Handle);
//	  osSemaphoreWait(myBinarySem01Handle, osWaitForever);
//	  osSemaphoreWait(myBinarySem01Handle, osWaitForever);
//	  osSemaphoreWait(myBinarySem01Handle, osWaitForever);
	  //vTaskDelayUntil(&last_tick, 500);
  }
  /* USER CODE END StartTask05 */
}

/* USER CODE BEGIN Header_StartTask06 */
/**
* @brief Function implementing the myTask06 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask06 */
void StartTask06(void const * argument)
{
  /* USER CODE BEGIN StartTask06 */
	osEvent queue_get;
//	int value = 0;
//	uint8_t *dy_var = NULL;
//	char myStr[] = "0*1*2*3*4*5*6*7*8*9*0*1*2*3*4*5*6*7*8*9*0*1*2*3*4*5*6*7*8*9*0*1*2*3*4*5*6*7*8*9*0*1*2*3*4*5*6*7*8*9*\r\n";
  /* Infinite loop */
  for(;;)
  {
      queue_get = osMessageGet(myQueue01Handle, 0);
	  if (queue_get.status == osEventMessage)
	  {
		  sum_task += queue_get.value.v;
	  }
	  vPortGetHeapStats(&my_Heap_Status);
	  highWaterMarkValue = uxTaskGetStackHighWaterMark2(NULL);
	  osDelay(2000);
	  printf(Str1);

/*	  if (user_flag > 1)
	  {
		  dy_var = pvPortMalloc(user_flag*100);
		  *dy_var = user_flag;
		  user_flag = 0;
		  vPortFree(dy_var);
	  }*/

	  switch(user_flag)
	  {
	  case 1:
		  myFunction1();
//		  user_flag = 0;
		  break;
	  case 2:
		  myFunction2();
//		  user_flag = 0;
		  break;
	  case 3:
		  myFunction3();
//		  user_flag = 0;
		  break;
	  default:
		  break;
	  }
	  user_flag++;
	  if (user_flag > 3)
		  user_flag = 1;
//	  scanf("%s", sLog.data);
  }
  /* USER CODE END StartTask06 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//usart_tx_period = HAL_GetTick() - usart_tick;
	osSemaphoreRelease(myBinarySem01Handle);
	count_error += 1;
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
