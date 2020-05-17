/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
*/

#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void LightLEDs(uint16_t *Counter);
void IncreaseCounter(uint16_t *Counter);

const uint16_t MAX_VALUE = 0xFFF; // 4095
const uint64_t SECONDS = 199998; // More than 3

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
	
	uint16_t Counter = 4093, IncreasePressed = 0;
	//uint16_t Counter = 0, IncreasePressed = 0;
	uint64_t TicksIncreasePressed = 0;
	LightLEDs(&Counter);
	
  while (1)
  {
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 1)
		{
			Counter = 0;
			LightLEDs(&Counter);
		}
		else
		{
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 1)
			{
				TicksIncreasePressed++;
				IncreasePressed = 1;
				if (TicksIncreasePressed > SECONDS)
				{
					IncreaseCounter(&Counter);
					HAL_Delay(1000);
				}
			}
			else
			{
				if (IncreasePressed == 1)
				{
					if (TicksIncreasePressed <= SECONDS)
					{
						IncreaseCounter(&Counter);
					}
					IncreasePressed = 0;
					TicksIncreasePressed = 0;
				}
			}
		}
  }
}

void LightLEDs(uint16_t *Counter)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_All, GPIO_PIN_RESET);
	HAL_GPIO_TogglePin(GPIOA, *Counter);
}

void IncreaseCounter(uint16_t *Counter)
{
	if (*Counter == MAX_VALUE)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
		
		*Counter = 0;
	}
	else
	{
		*Counter = *Counter + 1;
	}
	
	LightLEDs(Counter);
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |overflow_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 PA5 PA6 PA7 
                           PA8 PA9 PA10 PA11 
                           overflow_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |overflow_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : increase_Pin reset_Pin */
  GPIO_InitStruct.Pin = increase_Pin|reset_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{ }

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif

