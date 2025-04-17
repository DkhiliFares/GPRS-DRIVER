
#include "main.h"
#include "string.h"
#include <stdio.h>
#include "gprs_lib.h"




UART_HandleTypeDef huart1;
   // Assure-toi d'utiliser le bon périphérique UART
// Buffers pour les commandes et les réponses
char send_buffer[256];
char rx_buffer[512];
char response[1024];
volatile uint8_t uart_data = 0; 
uint8_t x;
uint8_t y;// Pour recevoir un octet à chaque interruption
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
int main(void)
{

  HAL_Init();

 
  SystemClock_Config();

    HAL_Init();
    SystemClock_Config();
		MX_GPIO_Init();

	
if (SIM808_Init(&huart1) != 0) {
        printf("Erreur lors de l'initialisation du module SIM808\n");
    } else {
        printf("Module SIM808 initialise avec succes\n");
    }

	 const char *url = "https://labs-iot.echaieb.com/multiusers/getvalue.php?user_id=84";  // Remplacer par l'URL réelle
    if (GPRS_HTTP_Get(&huart1, url, response) == 0) {
        printf("Reponse HTTP GET : %s\n", response);
    } else {
        printf("Erreur lors de la requete HTTP GET\n");
    }
		
		/*
		const char *post_data = "111";  // Remplacer par les données réelles à envoyer
    if (GPRS_HTTP_Post(&huart1, url, post_data, response) == 0) {
        printf("Reponse HTTP POST : %s\n", response);
    } else {
        printf("Erreur lors de la requete HTTP POST\n");
    }
		*/
  while (1)
  {
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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

 
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
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
 

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */





static void MX_GPIO_Init(void)
{


  __HAL_RCC_GPIOA_CLK_ENABLE();

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




/*// Envoi de la commande AT
    HAL_UART_Transmit(&huart3, (uint8_t*)cmd, strlen(cmd), 1000); 
    HAL_Delay(1000);  // Attente pour que le module réponde
    
    // Copier la réponse reçue dans rx_buffer
    strcpy((char*)rx_buffer, (char*)rx_buffer);
    
    // Vérifier la réponse dans rx_buffer
    if (strstr((char*)rx_buffer, "OK") != NULL)
    {
        // Si "OK" est trouvé, cela signifie que la commande a réussi
        printf("Réponse OK reçue\n");
    }
    else if (strstr((char*)rx_buffer, "ERROR") != NULL)
    {
        // Si "ERROR" est trouvé, cela signifie qu'il y a eu une erreur
        printf("Erreur reçue\n");
    }
    else
    {
        // Si aucune des deux chaînes n'est trouvée
        printf("Réponse inattendue : %s\n", rx_buffer);
    }*/