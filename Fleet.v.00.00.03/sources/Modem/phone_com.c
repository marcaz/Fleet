// This file has been prepared for Doxygen automatic documentation generation.
/*! \file ********************************************************************
*
* Atmel Corporation
*
* - File              : AVR_com.c
* - Compiler          : IAR EWAAVR 4.11a
*
* - Support mail      : avr@atmel.com
*
* - Supported devices : All devices with a UART/USART can be used.
*                       The example is written for ATmega128
*
* - AppNote           : AVR323 - Interfacing GSM modems
*
* - Description       : Example of how to use AT-Commands to control a GSM modem
*
* $Revision: 1.1 $
* $Date: Tuesday, November 08, 2005 12:26:20 UTC $
*****************************************************************************/

//Used for SPLINT
#ifdef S_SPLINT_S
  #include"splint.h"
#endif


//Includes
#include "phone_com.h"
#include "STM32F4xx.h"
#include "phone_sms_sending.h"
#include "uart.h"

//-------------------------------------------------------------------------
int rx_overflow, rx_ack;
//-------------------------------------------------------------------------
//! Possible strings pointed to by searchStr
const unsigned char  OK[]                      = "OK\r\n";                   //!< "OK"
const unsigned char  CMTI[]                    = "+CMTI: ";                  //!< New Message arrived
const unsigned char  READY[]                   = "> ";                       //!< Phone ready to receive text message
const unsigned char  CR_LF[]                   = "\r\n";                     //!< Carrige Return Line Feed
const unsigned char  *searchFor;                                             //!< Flash pointer
const unsigned char  *searchStrings[4]         = {OK, CMTI, READY, CR_LF};   //!< Initialize pointer

/*! \brief This method will print an integer in the range +-(10^5 - 1 )
 *
*  \param    i  integer to be printed
 *
 *  \retval   void
 */
void COM_put_integer( int i )
{
    //---------------------------------------------------------------
    int ii;
    unsigned char int_buf[5];
		//---------------------------------------------------------------
    if (i < 0)                                              //Integer is negative
    {
        i = -i;                                             //Convert to positive Integer
        USART1->DR = ('-' & (uint16_t)0x01FF);//('-');                                   //Print - sign
    }
		//---------------------------------------------------------------
    for (ii=0; ii < 5; )                                    //Convert Integer to char array
    {
        int_buf[ii++] = '0'+ i % 10;                        //Find carry using modulo operation
        i = i / 10;                                         //Move towards MSB
    }
    do{ ii--; }while( (int_buf[ii] == '0') && (ii != 0) );  //Remove leading 0's
    do{ 
			USART1->DR = (int_buf[ii--] & (uint16_t)0x01FF);
			}while (ii >= 0);     //Print int->char array convertion
		//---------------------------------------------------------------
}



/*! \brief Remove trailing O, K, \r and \n
 *
 *  If the receive buffer have trailing "OK\r\n"
 *  These characters will be deleted.
 *
 *  \param  void
 *
 *  \retval i   Length of trimmed buffer
 */
int COM_trim( void )
{
	//---------------------------------------------------------------
	int i;
	unsigned char temp;
	//---------------------------------------------------------------
	for( i = SMSRXHeadModem - 1; i >= 0; i--)                                                      //Run through COM_in[] backwards
	{
			temp = SMSBuffer[i];                                                                //rx_buff[i] into temp
			if( ( temp != '\r' ) && ( temp != '\n' ) && ( temp != 'O' ) && ( temp != 'K' ) )    //If not equal to 'O', 'K', '\r' or '\n', break
			{
					break;                                                                          //Do break
			}
	}
	//---------------------------------------------------------------
	SMSBuffer[ i+1 ] = '\0';                                                                //Terminate trimmed string
	//---------------------------------------------------------------
	return i;                                                                               //Return new length
	//---------------------------------------------------------------
}


unsigned char* COM_gets( void )
{
  return SMSBuffer;
}
