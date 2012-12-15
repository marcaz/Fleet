/**
  ******************************************************************************
  * @file    selftest.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   This file provides the hardware tests
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "selftest.h"
#include "stm32f4_discovery.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define MEMS_PASSCONDITION              15
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Init Structure definition */
//RCC_ClocksTypeDef      RCC_Clocks;
//ADC_InitTypeDef        ADC_InitStructure;
//ADC_CommonInitTypeDef  ADC_CommonInitStructure;

//__IO uint16_t ConvData1, ConvData2;
//__IO uint16_t counter0 = 0, counter1 = 0, Idx = 0;
//uint8_t ADC_Channel[2] = {ADC_Channel_2, ADC_Channel_3};
//uint8_t DACTest = 0;
uint8_t GPIO_Pin [2] = {GPIO_Pin_2, GPIO_Pin_3};

//uint16_t count = 0, count1 = 24, Left_Right = 0;
//const int16_t sinebuf[48] = {0, 4276, 8480, 12539, 16383, 19947, 23169, 25995,
//                             28377, 30272, 31650, 32486, 32767, 32486, 31650, 30272,
//                             28377, 25995, 23169, 19947, 16383, 12539, 8480, 4276,
//                             0, -4276, -8480, -12539, -16383, -19947, -23169, -25995,
//                             -28377, -30272, -31650, -32486, -32767, -32486, -31650, -30272,
//                             -28377, -25995, -23169, -19947, -16383, -12539, -8480, -4276
//                             };


/**
  * @brief Test USB Hardware.
  *   The main objectif of this test is to check the hardware connection of the 
  *   Audio and USB peripheral.
  * @param None
  * @retval None
  */
void USB_Test(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /******************************** USB Test **********************************/
  
  /*----------------- Part1: without cables connected ------------------------*/ 
  
  /* GPIOA, GPIOC and GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC | \
                         RCC_AHB1Periph_GPIOD, ENABLE);
  
  /* GPIOD Configuration: Pins 5 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  /* Turn LED8 ON using PD5 */
  GPIO_ResetBits(GPIOD, GPIO_Pin_5);
  
  /* GPIOC Configuration: Pin 0 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 9 in input pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Turn LED7 ON using PC0 (5v) */
  GPIO_ResetBits(GPIOC, GPIO_Pin_0); 
  
  /* Waiting delay 10ms */
  //Delay(1);
  
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_RESET)
  {
    //Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 10 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Waiting delay 10ms */
//  Delay(1);
  
  /* Check the ID level without cable connected */
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_RESET)
  {
//    Fail_Handler();
  }
  
  /* Turn LED7 OFF using PC0 */
  GPIO_SetBits(GPIOC, GPIO_Pin_0);  
  
  /* GPIOA Configuration: Pins 11, 12 in input pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 9 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_9);
  
  /* Waiting delay 10ms */
//  Delay(1);
  
  /* Check PA11 and PA12 level without cable connected */
  if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET) || \
      (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == Bit_RESET))
  {
//    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 12 in input pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 11 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_11);
  
  /* Waiting delay 10ms */
 // Delay(1);
  
  /* Check PA12 level without cable connected */
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == Bit_RESET)
  {
//    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 11 in input pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 12 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_12);
  
  /* Waiting delay 10ms */
//  Delay(1);
  
  /* Check PA12 level without cable connected */
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET)
  {
//    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 9 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Turn LED7 ON using PA9 */
  GPIO_SetBits(GPIOA, GPIO_Pin_9);
  
  /* Turn Green LED ON: signaling Audio USB Test part1 PASS */
  STM_EVAL_LEDOn(LED4);
  
  /* Waiting User Button is pressed */
  while (STM_EVAL_PBGetState(BUTTON_USER) == Bit_RESET)
  {}
  
  /* Waiting User Button is Released */
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {}
  
  /* Turn Green LED OFF: signaling the end of Audio USB Test part1 and switching to 
  the part2 */
  STM_EVAL_LEDOff(LED4);
  
  /* Turn LED7 OFF using PA9 */
  GPIO_ResetBits(GPIOA, GPIO_Pin_9);
  
  /* Turn LED8 OFF using PD5 */
  GPIO_SetBits(GPIOD, GPIO_Pin_5);
  
  /*--------------- Part2: with Audio USB cables connected  ------------------*/ 
  
  /*********************************** USB Test *******************************/
  /* Check the ID level with cable connected */
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) != Bit_RESET)
  {
//    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 11, 12 in input pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 9 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_9);
  
  /* Waiting delay 10ms */
//  Delay(1);
  
  /* Check PA11 and PA12 level with cable connected */
  if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET) || \
      (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == Bit_RESET))
  {
//    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 9, 12 in input pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 11 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_11);
  
  /* Waiting delay 10ms */
//  Delay(1);
  
  /* Check PA9 and PA12 level with cable connected */
  if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_RESET)|| \
      (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == Bit_RESET))
  {
//    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 9, 11 in input pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 12 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_12);
  
  /* Waiting delay 10ms */
//  Delay(1);
  
  /* Check PA9 and PA12 level with cable connected */
  if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_RESET)|| \
      (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET))
  {
//    Fail_Handler();
  }

  /* GPIOA Configuration: Pins 11, 12 in input pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 9 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Turn LED7 OFF using PA9 */
  GPIO_ResetBits(GPIOA, GPIO_Pin_9);
}
