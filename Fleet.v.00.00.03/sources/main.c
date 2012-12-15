#include <rtl.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
//----------------------------------------------------------------
#include "leds.h"
#include "acc.h"
#include "acc_api.h"
#include "uart.h"

//----------------------------------------------------------------
__task void Init_System(void);
//----------------------------------------------------------------
//
//----------------------------------------------------------------


__task void Init_System(void){
	//----------------------------------------------------------------
	// Peripgherals INIT Section
	//----------------------------------------------------------------
	os_dly_wait(1);
	//----------------------------------------------------------------
	put_log("[MAIN]: Starting System PERIPHERALS Initialisation...\r\n");
	//----------------------------------------------------------------
	LED_Init();
	//----------------------------------------------------------------
	// System Tasks INIT Section
	//----------------------------------------------------------------
	put_log("[MAIN]: Starting System TASKS...\r\n");
	//----------------------------------------------------------------
	create_LED_Control_Task();
	create_Acc_Update_task();	
	//----------------------------------------------------------------
	put_log("[MAIN]: TASKS and PERIPHERALS Init Complete.\r\n");
	//----------------------------------------------------------------
	os_tsk_delete_self();
	//----------------------------------------------------------------
}

int main(void){
	//----------------------------------------------------------------
	// Low Level Peripheral INIT [must be done before RTOS Init]
	//----------------------------------------------------------------
	Init_USARTS();
	os_dly_wait(1);
	Acc_Init();
	os_dly_wait(1);
	//----------------------------------------------------------------
	//
	//----------------------------------------------------------------
	os_sys_init(Init_System);
	//----------------------------------------------------------------
}







