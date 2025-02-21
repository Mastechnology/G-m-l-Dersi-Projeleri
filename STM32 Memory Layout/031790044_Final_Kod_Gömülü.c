/******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
 
/* USER CODE BEGIN Includes */
 
/* USER CODE END Includes */
 
/* Private variables ---------------------------------------------------------*/
 
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint16_t data,flash_data=0;
/* USER CODE END PV */
 
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
 
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
/*######################## Adresten Veri Okuma Fonksiyonu ####################*/
uint16_t Read_Flash(uint32_t  adr)
{
  uint16_t * Pntr = (uint16_t *)adr;
  return(*Pntr); 
}
/*######################## Verilen adresteki veriyi silmek için yazilan fonksiyon ############*/
void Erase_Flash (uint32_t adr)
{
	FLASH->KEYR=0x45670123;  					// Silme veya yazma islemi yapilmadan önce Flash kilidi mutlaka açilmalidir.
  FLASH->KEYR=0xCDEF89AB;						// FLASH->KEYR registerine KEY1 ve KEY2 degerleri atandiginda Flash kilidi açilir.
  FLASH->CR|=0x00000002;            //PER enable
  FLASH->AR=adr;                    //FLASH->AR registerine silinmek istenen adres yazilir
  FLASH->CR|=0x00000040;            //STRT anable
  while((FLASH->SR&0x00000001));    //Islem bitene kadar bekle(BUSY kontrol ediliyor)
  FLASH->CR &= ~0x00000042;         //FLASH->CR ilk durumuna aliniyor (kilit hala açik!)
	FLASH->CR=0x00000080;  						//FLASH_CR registeri resetlendiginde FLASH kiltlenmis olur
}
/*################ Verilen adrese veri yazma fonksiyonu ##############################*/
void Write_Flash (uint32_t adr, uint16_t data)
{
  FLASH->KEYR=0x45670123;  					// Silme veya yazma islemi yapilmadan önce Flash kilidi mutlaka açilmalidir.
  FLASH->KEYR=0xCDEF89AB;						// FLASH->KEYR registerine KEY1 ve KEY2 degerleri atandiginda Flash kilidi açilir.
  FLASH->CR|=0x00000001;            //PG enable
  *(__IO uint16_t*)adr = data;      //istenen adrese istenen data yaziliyor
  while((FLASH->SR&0x00000001));    //Islem bitene kadar bekle(BUSY kontrol ediliyor)
	FLASH->CR=0x00000080;  					  //FLASH_CR registeri resetlendiginde FLASH kiltlenmis olur
}
/* USER CODE END PFP */
 
/* USER CODE BEGIN 0 */
 
/* USER CODE END 0 */
 
int main(void)
{
 
  /* USER CODE BEGIN 1 */
 
  /* USER CODE END 1 */
 
  /* MCU Configuration----------------------------------------------------------*/
 
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
 
  /* USER CODE BEGIN 2 */
	data = 10;
	Erase_Flash(0x0801FC00);                        // adresteki değer silindi.
	Write_Flash(0x0801FC00,data);                   // 16 bitlik veri adrese yazıldı.
	HAL_Delay(2000);								// flash_data degiskeninin baslangiçta sifir oldugunu görebilmek için gecikme eklendi.
	flash_data = Read_Flash(0x0801FC00);		    // addresten 16 bitlik veri okundu.
  /* USER CODE END 2 */
 
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
 
  /* USER CODE BEGIN 3 */
 
  }
  /* USER CODE END 3 */
 
}
 
/** System Clock Configuration
*/
void SystemClock_Config(void)
{
 
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
 
    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
 
    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
 
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
 
    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
 
    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
 
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
 
/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{
 
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
 
}
 
/* USER CODE BEGIN 4 */
 
/* USER CODE END 4 */
 
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}
 
#ifdef USE_FULL_ASSERT
 
/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
 
}
 
#endif
 
/**
  * @}
  */ 
 
/**
  * @}
*/ 
 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/