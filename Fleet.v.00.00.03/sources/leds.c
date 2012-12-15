#include <rtl.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "leds.h"
#include "acc.h"
#include "uart.h"
//----------------------------------------------------------------
OS_TID t_LED_TOGGLE;
OS_ID  tmr1;
//----------------------------------------------------------------
__task void LED_TOGGLE(void);
//----------------------------------------------------------------



void create_LED_Control_Task(void){
	//----------------------------------------------------------------
	t_LED_TOGGLE  = os_tsk_create (LED_TOGGLE, 0);
	//----------------------------------------------------------------
}

__task void LED_TOGGLE (void) {
	//----------------------------------------------------------------
	uint8_t led_timer = 0;
   //----------------------------------------------------------------
	put_log("[LED]: LED Task Started...\r\n");
	//----------------------------------------------------------------
	for (;;) {
		//----------------------------------------------------------------
		os_dly_wait(20);
		//----------------------------------------------------------------
		led_timer++;
		//----------------------------------------------------------------
		if(led_timer==3 || led_timer==4){
			//----------------------------------------------------------------
			tmr1 = os_tmr_create (5, MAIN_LED_OFF_TMO);
			if (tmr1 != NULL) {
				GPIOD->BSRRL = GPIO_Pin_12;
			}
			//----------------------------------------------------------------
			if(led_timer==4){
				led_timer = 0;
			}
			//----------------------------------------------------------------
		}
		//----------------------------------------------------------------
	}
	//----------------------------------------------------------------
}

void LED_Init(void){
  //----------------------------------------------------------------
  GPIO_InitTypeDef  GPIO_InitStructure;
  //----------------------------------------------------------------
  /* Enable the GPIO_LED Clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  //----------------------------------------------------------------
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  //----------------------------------------------------------------
}
