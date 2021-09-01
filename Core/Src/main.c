/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "dma.h"
#include "iwdg.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "stdlib.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"
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

/* USER CODE BEGIN PV */

size_t 	process_stack_point_p32_1;
size_t 	process_stack_point_p32_2;

uint32_t 	process_stack_point__use_func_p32_1;
uint32_t 	process_stack_point__use_func_p32_2;

uint32_t 	*main_stack_point_p32_1;
uint32_t 	*main_stack_point_p32_2;

uint32_t 	main_stack_point_use_func_p32_1;
uint32_t 	main_stack_point_use_func_p32_2;

extern DMA_HandleTypeDef hdma_usart2_tx;
extern volatile uint8_t flag_dma_uart2;

char str[100] = {0};
sData sLog;
size_t heap_size_free;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
//uint8_t my_function1(void)
//{
//
//	process_stack_point_p32_1 = xPortGetFreeHeapSize();
////	main_stack_point_use_func_p32_1 = __get_MSP();
//
//	//process_stack_point__use_func_p32_1 = __get_PSP();
//
//	uint8_t 	var_test_u8[200]= {0};
////	uint8_t var1_u8[50] = {0};
////	uint8_t var2_u8[50] = {0};
////	uint8_t var3_u8[50] = {0};
////	uint8_t i = 0;
////	uint8_t *heap_test = (uint8_t *) malloc(sizeof(uint8_t*));
////	uint8_t *heap_thread = (uint8_t *) pvPortMalloc(sizeof(uint8_t));
//
//	process_stack_point_p32_2 = xPortGetFreeHeapSize();
//	main_stack_point_use_func_p32_2 = __get_MSP();
////	process_stack_point__use_func_p32_1 = heap_thread;
////	process_stack_point__use_func_p32_2 = __get_PSP();
//	process_stack_point__use_func_p32_1 = __get_PSP();
//	main_stack_point_p32_1 = &var_test_u8[0];
////	main_stack_point_p32_2 = &var1_u8[0];
//
////	var1_u8[0] = var_test_u8;
////	var2_u8[0] = var_test_u8;
////	var3_u8[0] = var_test_u8;
////	var_test_u8 = var1_u8[0];
////	var_test_u8 = var2_u8[0];
////	var_test_u8 = var3_u8[0];
//
////	HAL_Delay(500);
//
//	//for (i = 0; i < 100; i++) {
////		var3_u8[i] = var1_u8[i] + var2_u8[i] + 1;
//	//}
////		*heap_test  = i;
////		*heap_thread = i;
//
////	free(heap_test);
////	vPortFree(heap_thread);
//
//}
//void my_function2(void)
//{
//	uint8_t 	var_test_u8 = 10;
//
//	uint8_t var1_u8[50] = {0};
//	uint8_t var2_u8[50] = {0};
//	uint8_t var3_u8[50] = {0};
//	uint8_t i = 0;
//	uint8_t *heap_test = (uint8_t *) malloc(sizeof(uint8_t*));
//	uint8_t *heap_thread = (uint8_t *) pvPortMalloc(sizeof(uint8_t));
//	//uint8_t *heap_task = (uint8_t *) pvPortMalloc(sizeof(uint8_t));
//
//	var1_u8[0] = var_test_u8;
//	var2_u8[0] = var_test_u8;
//	var3_u8[0] = var_test_u8;
////	var_test_u8 = var1_u8[0];
////	var_test_u8 = var2_u8[0];
////	var_test_u8 = var3_u8[0];
//
////	HAL_Delay(500);
//
//	//for (i = 0; i < 100; i++) {
//		var3_u8[i] = var1_u8[i] + var2_u8[i] + 1;
//	//}
//	*heap_test  = i;
//	*heap_thread = i;
//	//*heap_task = i;
//
//	//process_stack_point_p32 = xPortGetFreeHeapSize();
//	my_function1();
//
//	free(heap_test);
//	vPortFree(heap_thread);
//	//vPortFree(heap_task);
//
//}
//void my_function3(void)
//{
//	uint8_t 	var_test_u8 = 10;
//
//	uint8_t var1_u8[50] = {0};
//	uint8_t var2_u8[50] = {0};
//	uint8_t var3_u8[50] = {0};
//	uint8_t i = 0;
//
//	var1_u8[0] = var_test_u8;
//	var2_u8[0] = var_test_u8;
//	var3_u8[0] = var_test_u8;
//	var_test_u8 = var1_u8[0];
//	var_test_u8 = var2_u8[0];
//	var_test_u8 = var3_u8[0];
//
////	HAL_Delay(500);
//
//	//for (i = 0; i < 100; i++) {
//		var3_u8[i] = var1_u8[i] + var2_u8[i] + 1;
//	//}
//
//	my_function2();
//	//my_function3();
//}
//
//void my_submain_function(void)
//{
//	uint8_t 	var_test_u8 = 10;
//	uint32_t 	var_global_u32 = 0;
//	uint8_t 	array_u8[100] = {0};
//
//	uint32_t var_test1_su8 = 0;
//	uint32_t var_test1_su32 = 0;
//	uint32_t var_test2_su32 = 0;
//	uint32_t var_test3_su32 = 0;
//	//uint32_t var_test4_su32 = 0;
//
//	  var_test_u8++;
//	  var_global_u32++;
//	  array_u8[0]++;
//	  var_test1_su8++;
//	  var_test1_su32++;
//	  var_test2_su32++;
//	  var_test3_su32++;
//	//	  var_test4_su32++;
//	  if (var_global_u32 == var_test_u8)
//	  {
//		  var_test_u8++;
//		  var_global_u32++;
//	  }
//	  var_test_u8 = var_test1_su8;
//	  var_test_u8 = var_test1_su32;
//	  var_test_u8 = var_test2_su32;
//	  var_test_u8 = var_test3_su32;
//	//	  var_test_u8 = var_test4_su32;
//	  var_test_u8 = array_u8[0];
//}
//
//void led_control(void)
//{
////	HAL_Delay(200);
////	HAL_GPIO_TogglePin(LED_USER_GPIO_Port, LED_USER_Pin);
////	HAL_Delay(200);
//}
//
////void (* pCallback)( DMA_HandleTypeDef * _hdma)
//void my_callback_dma(DMA_HandleTypeDef * _hdma)
//{
//	//flag_dma_uart2 = 1;
//}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  /* Implement your write code here, this is used by puts and printf for example */
//  heap_size_free = xPortGetMinimumEverFreeHeapSize();
  HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, 2000);

//  int i=0;
//  for(i=0 ; i<len ; i++)
//    ITM_SendChar((*ptr++));
  return len;
}

int _read(int fd, char* ptr, int len)
{
	HAL_StatusTypeDef hstatus;

	if (fd == 0) {
		hstatus = HAL_UART_Receive(&huart2, (uint8_t *) sLog.data, 1, HAL_MAX_DELAY);
		if (hstatus == HAL_OK) {
			sLog.length++;
			return 1;
		} else {
			return 5;
		}
	}

	return -1;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
  __HAL_IWDG_START(&hiwdg);
  sLog.data = str;
  HAL_UART_Transmit(&huart2, (uint8_t *)"hello world\r\n", 13, 1000);
  HAL_UART_Transmit(&huart2, (uint8_t *)"hello abcde\r\n", 13, 1000); // wrong, never being send
  HAL_Delay(1000);
  printf("123\n");
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  NVIC_SystemReset();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
