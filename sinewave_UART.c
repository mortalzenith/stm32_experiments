/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

// 250-point custom Sine Look-Up Table pre-formatted for Arduino Serial Plotter
// Stored in FLASH memory to save RAM
const char* const SINE_LUT[256] = {
    "499\r\n", "511\r\n", "524\r\n", "536\r\n", "548\r\n", "560\r\n", "572\r\n", "584\r\n", "597\r\n", "609\r\n",
    "620\r\n", "632\r\n", "644\r\n", "656\r\n", "667\r\n", "679\r\n", "690\r\n", "702\r\n", "713\r\n", "724\r\n",
    "735\r\n", "745\r\n", "756\r\n", "766\r\n", "777\r\n", "787\r\n", "797\r\n", "807\r\n", "816\r\n", "826\r\n",
    "835\r\n", "844\r\n", "853\r\n", "861\r\n", "869\r\n", "878\r\n", "886\r\n", "893\r\n", "901\r\n", "908\r\n",
    "915\r\n", "921\r\n", "928\r\n", "934\r\n", "940\r\n", "946\r\n", "951\r\n", "956\r\n", "961\r\n", "965\r\n",
    "970\r\n", "974\r\n", "977\r\n", "981\r\n", "984\r\n", "987\r\n", "989\r\n", "992\r\n", "994\r\n", "995\r\n",
    "997\r\n", "998\r\n", "998\r\n", "999\r\n", "999\r\n", "999\r\n", "998\r\n", "998\r\n", "997\r\n", "995\r\n",
    "994\r\n", "992\r\n", "989\r\n", "987\r\n", "984\r\n", "981\r\n", "977\r\n", "974\r\n", "970\r\n", "965\r\n",
    "961\r\n", "956\r\n", "951\r\n", "946\r\n", "940\r\n", "934\r\n", "928\r\n", "921\r\n", "915\r\n", "908\r\n",
    "901\r\n", "893\r\n", "886\r\n", "878\r\n", "869\r\n", "861\r\n", "853\r\n", "844\r\n", "835\r\n", "826\r\n",
    "816\r\n", "807\r\n", "797\r\n", "787\r\n", "777\r\n", "766\r\n", "756\r\n", "745\r\n", "735\r\n", "724\r\n",
    "713\r\n", "702\r\n", "690\r\n", "679\r\n", "667\r\n", "656\r\n", "644\r\n", "632\r\n", "620\r\n", "609\r\n",
    "597\r\n", "584\r\n", "572\r\n", "560\r\n", "548\r\n", "536\r\n", "524\r\n", "511\r\n", "499\r\n", "487\r\n",
    "475\r\n", "462\r\n", "450\r\n", "438\r\n", "426\r\n", "414\r\n", "402\r\n", "390\r\n", "378\r\n", "366\r\n",
    "354\r\n", "342\r\n", "331\r\n", "319\r\n", "308\r\n", "297\r\n", "286\r\n", "275\r\n", "264\r\n", "253\r\n",
    "242\r\n", "232\r\n", "222\r\n", "212\r\n", "202\r\n", "192\r\n", "182\r\n", "173\r\n", "164\r\n", "155\r\n",
    "146\r\n", "138\r\n", "129\r\n", "121\r\n", "113\r\n", "106\r\n", "98\r\n",  "91\r\n",  "84\r\n",  "77\r\n",
    "71\r\n",  "65\r\n",  "59\r\n",  "53\r\n",  "48\r\n",  "43\r\n",  "38\r\n",  "33\r\n",  "29\r\n",  "25\r\n",
    "21\r\n",  "18\r\n",  "15\r\n",  "12\r\n",  "10\r\n",  "7\r\n",   "5\r\n",   "4\r\n",   "2\r\n",   "1\r\n",
    "1\r\n",   "0\r\n",   "0\r\n",   "0\r\n",   "1\r\n",   "1\r\n",   "2\r\n",   "4\r\n",   "5\r\n",   "7\r\n",
    "10\r\n",  "12\r\n",  "15\r\n",  "18\r\n",  "21\r\n",  "25\r\n",  "29\r\n",  "33\r\n",  "38\r\n",  "43\r\n",
    "48\r\n",  "53\r\n",  "59\r\n",  "65\r\n",  "71\r\n",  "77\r\n",  "84\r\n",  "91\r\n",  "98\r\n",  "106\r\n",
    "113\r\n", "121\r\n", "129\r\n", "138\r\n", "146\r\n", "155\r\n", "164\r\n", "173\r\n", "182\r\n", "192\r\n",
    "202\r\n", "212\r\n", "222\r\n", "232\r\n", "242\r\n", "253\r\n", "264\r\n", "275\r\n", "286\r\n", "297\r\n",
    "308\r\n", "319\r\n", "331\r\n", "342\r\n", "354\r\n", "366\r\n", "378\r\n", "390\r\n", "402\r\n", "414\r\n",
    "426\r\n", "438\r\n", "450\r\n", "462\r\n", "475\r\n", "487\r\n", "499\r\n"
};
uint8_t index = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  char* sine_string = (char*)SINE_LUT[index];

	      HAL_UART_Transmit(&huart1, (uint8_t*)sine_string, strlen(sine_string), 10);

	      index++;
	      if(index >= 256) // Reset boundary updated for the 250-point array
	      {
	          index = 0;
	      }

	      HAL_Delay(2); // Control your plotting speed here

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
#ifdef USE_FULL_ASSERT
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
