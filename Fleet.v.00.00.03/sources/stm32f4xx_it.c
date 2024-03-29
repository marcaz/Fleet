/**
  ******************************************************************************
  * @file    LIS302DL/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"


#include "main.h"
// #include "usb_core.h"
// #include "usbd_core.h"
// #include "stm32f4_discovery.h"
// #include "usbd_hid_core.h"

// #define CURSOR_STEP     7
// uint8_t Buffer[6];

// extern USB_OTG_CORE_HANDLE  USB_OTG_dev;
// uint8_t *USBD_HID_GetPos (void);
// extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);



// void OTG_FS_WKUP_IRQHandler(void)
// {
//   if(USB_OTG_dev.cfg.low_power)
//   {
// 	/* Reset SLEEPDEEP and SLEEPONEXIT bits */
// 	SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));

// 	/* After wake-up from sleep mode, reconfigure the system clock */
// 	SystemInit();
//     USB_OTG_UngateClock(&USB_OTG_dev);
//   }
//   EXTI_ClearITPendingBit(EXTI_Line18);
// }

// void OTG_FS_IRQHandler(void)
// {
//   USBD_OTG_ISR_Handler (&USB_OTG_dev);
// }

// uint8_t *USBD_HID_GetPos (void)
// {
//   static uint8_t HID_Buffer[4] = {0};
//   
//   HID_Buffer[1] = 0;
//   HID_Buffer[2] = 0;
//   /* LEFT Direction */
//   if(((int8_t)Buffer[2]) < -2)
//   {
//     HID_Buffer[1] += CURSOR_STEP;
//   }
//   /* RIGHT Direction */ 
//   if(((int8_t)Buffer[2]) > 2)
//   {
//    HID_Buffer[1] -= CURSOR_STEP;
//   } 
//   /* UP Direction */
//   if(((int8_t)Buffer[0]) < -2)
//   {
//     HID_Buffer[2] += CURSOR_STEP;
//   }
//   /* DOWN Direction */ 
//   if(((int8_t)Buffer[0]) > 2)
//   {
//     HID_Buffer[2] -= CURSOR_STEP;
//   } 
//   
//   return HID_Buffer;
// }
/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//
//}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
