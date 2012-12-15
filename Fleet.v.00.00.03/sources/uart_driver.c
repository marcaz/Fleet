#include <rtl.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "leds.h"
#include "acc.h"
#include "uart.h"
//----------------------------------------------------------------
void Init_USARTS(void);
static void Usart_1_Init(void);
static void Usart_2_Init(void);
static void Usart_3_Init(void);
//----------------------------------------------------------------
//
//----------------------------------------------------------------

void Init_USARTS(void){
	//----------------------------------------------------------------
	// GPS uart
	Usart_1_Init();
	// LOG uart
	Usart_2_Init();
	// Phone uart
	Usart_3_Init();
	//----------------------------------------------------------------
}


static void Usart_1_Init(void){
	//----------------------------------------------------------------
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//----------------------------------------------------------------
	/* enable peripheral clock for USART2 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	
	//----------------------------------------------------------------
	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//---------------------------------------------------------------- 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//----------------------------------------------------------------
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	//----------------------------------------------------------------
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = (USART_Mode_Rx);
	USART_Init(USART2, &USART_InitStructure);
	//----------------------------------------------------------------
	USART_Cmd(USART2, ENABLE); // enable USART2
	//----------------------------------------------------------------

}

static void Usart_2_Init(void){
	//----------------------------------------------------------------
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//----------------------------------------------------------------
	/* enable peripheral clock for USART2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	
	//----------------------------------------------------------------
	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//---------------------------------------------------------------- 
   	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
	//----------------------------------------------------------------  
	/* GPIOA Configuration:  USART2 TX on PA2; RX on PA3 */
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_2 | GPIO_Pin_3);
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	//----------------------------------------------------------------
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	//----------------------------------------------------------------
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);
	USART_Init(USART2, &USART_InitStructure);
	//----------------------------------------------------------------
	USART_Cmd(USART2, ENABLE); // enable USART2
	//----------------------------------------------------------------

}

static void Usart_3_Init(void){
	//----------------------------------------------------------------
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//----------------------------------------------------------------
	/* enable peripheral clock for USART2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	
	//----------------------------------------------------------------
	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	//---------------------------------------------------------------- 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
	//----------------------------------------------------------------  
	/* GPIOA Configuration:  USART2 TX on PA2; RX on PA3 */
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_8 | GPIO_Pin_9);
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	//----------------------------------------------------------------
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
	//----------------------------------------------------------------
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);
	USART_Init(USART2, &USART_InitStructure);
	//----------------------------------------------------------------
	USART_Cmd(USART3, ENABLE); // enable USART2
	//----------------------------------------------------------------

}
