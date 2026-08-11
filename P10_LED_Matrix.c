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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
uint8_t a = 0;
uint8_t b = 0;
uint8_t OE = 1;
uint8_t bitmap[16][4];
uint8_t data00[16] =
{
		0xff,//first1
				0xff,//first5
				0xff,//first9
				0xfe,//first13

				0xff,//2nd1
				0xff,//2nd5
				0xff,//2nd9
				0x8b,//2nd13

				0xff,//3rd1
				0xff,//3rd5
				0xff,//3rd9
				0x6e,//3rd13

				0xff,//last1
				0xff,//last5
				0xff,//last9
				0xbf,//last13
};
uint8_t data01[16] =
{
		0xff,//first2
				0xff,//first6
				0xfe,//first10
				0xff,//first14

				0xff,//2nd2
				0xff,//2nd6
				0xaf,//2nd10
				0xbb,//2nd14

				0xff,//3rd2
				0xff,//3rd6
				0xa2,//3rd10
				0x6e,//3rd14

				0xff,//last2
				0xff,//last6
				0x3f,//last10
				0x3f,//last14
};
uint8_t data10[16] =
{
		0xff,//first3
		0xff,//first7
		0xfe,//first11
		0xfe,//first15

		0xff,//2nd3
		0xff,//2nd7
		0xa8,//2nd11
		0xf8,//2nd15

		0xff,//3rd3
		0xff,//3rd7
		0x6a,//3rd11
		0x6f,//3rd15

		0xff,//last3
		0xff,//last7
		0xff,//last11
		0xff,//last15
};
uint8_t data11[16] =
{
		0xff,//first4
		0xff,//first8
		0xfe,//first12
		0xff,//first16

		0xff,//2nd4
		0xff,//2nd8
		0xaa,//2nd12
		0xff,//2nd16

		0xff,//3rd4
		0xff,//3rd8
		0x62,//3rd12
		0xff,//3rd16

		0xff,//last4
		0xff,//last8
		0x3f,//last12
		0xff,//last16

};
uint32_t rout,full,i;
uint8_t bitmap[16][4] = {
   {0x00, 0x00, 0x00, 0x00},
   {0x00, 0x00, 0x00, 0x00},
   {0x00, 0x00, 0x00, 0x00},
   {0x00, 0x00, 0x00, 0x00},

   {0x00, 0x07, 0x10, 0x00},
   {0x00, 0x08, 0x90, 0x00},
   {0x05, 0x08, 0x90, 0x00},
   {0x01, 0xC8, 0x9C, 0x60},

   {0x05, 0x28, 0x92, 0x90},
   {0x05, 0x2A, 0x92, 0xE0},
   {0x05, 0x29, 0x12, 0x80},
   {0x05, 0x26, 0x9C, 0x70},

   {0x00, 0x00, 0x40, 0x00},
   {0x00, 0x00, 0x00, 0x00},
   {0x00, 0x00, 0x00, 0x00},
   {0x00, 0x00, 0x00, 0x00}
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
uint32_t concat(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);
uint32_t rotate_right(uint32_t data);
uint32_t rotate_left(uint32_t data);

void split(uint32_t data,
           uint8_t *msb,
           uint8_t *msb1,
           uint8_t *lsb1,
           uint8_t *lsb);
//void OE(void);
//void OD(void);
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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2*/
  for(int s=0;s<16;s++)
	  for(int x=0;x<4;x++)
		  bitmap[s][x]^=0x01;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {for(int m=0;m<250;m++){
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0); //a
	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0); //b
	   	   	map(14);
	  		HAL_SPI_Transmit(&hspi1, data00, 16, HAL_MAX_DELAY);// for 01

	  		OD_();

	  		Latch();
	  		OE_();

	  	  	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1); //a
	  	  	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0); //b
	  	  	map(13);
	  		HAL_SPI_Transmit(&hspi1, data00, 16, HAL_MAX_DELAY);// for 10
	  		OD_();

	  		Latch();
	  		OE_();

	  	  	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0); //a
	  	  	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1); //b

	  	  	map(15);
	  		HAL_SPI_Transmit(&hspi1, data00, 16, HAL_MAX_DELAY);// for 00
	  		OD_();
	  		Latch();
	  		OE_();

	  	  	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1); //a
	  	  	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1); //b

	  	  	map(12);
	  		HAL_SPI_Transmit(&hspi1, data11, 16, HAL_MAX_DELAY); //for 11
	  		OD_();

	  		Latch();
	  		OE_();

  }


  ShiftGroupRight(data00);
  ShiftGroupRight(data01);
  ShiftGroupRight(data10);
  ShiftGroupRight(data11);	  		//HAL_Delay(75);
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
uint32_t concat(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3)
{
    return ((uint32_t)b0 << 24) |
           ((uint32_t)b1 << 16) |
           ((uint32_t)b2 << 8)  |
           ((uint32_t)b3);
}
uint32_t rotate_right(uint32_t data)
{
    return (data >> 1) | (data << 31);
}
void split(uint32_t data,
                     uint8_t *msb,
                     uint8_t *msb1,
                     uint8_t *lsb1,
                     uint8_t *lsb)
{
    *msb  = (data >> 24) & 0xFF;
    *msb1 = (data >> 16) & 0xFF;
    *lsb1 = (data >> 8)  & 0xFF;
    *lsb  = data & 0xFF;
}

uint32_t rotate_left(uint32_t data)
{
    return (data << 1) | (data >> 31);
}
void OE_(void){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //latch on


}
void OD_(void){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); //latch off
}
void map(int r){
	int index=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			data00[index]=bitmap[r][j];
			index++;
		}
		r-=4;
	}

}
void Latch(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

}
void ShiftGroupRight(uint8_t *data)
{
    for(int row=0; row<4; row++)
    {
        uint32_t pixels =
            ((uint32_t)data[row]    << 24) |
            ((uint32_t)data[row+4]  << 16) |
            ((uint32_t)data[row+8]  << 8 ) |
            ((uint32_t)data[row+12]);

        pixels = (pixels >> 1) | (pixels << 31);

        data[row]    = (pixels >> 24) & 0xFF;
        data[row+4]  = (pixels >> 16) & 0xFF;
        data[row+8]  = (pixels >> 8 ) & 0xFF;
        data[row+12] = pixels & 0xFF;
    }
}
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
