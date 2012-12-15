// This file has been prepared for Doxygen automatic documentation generation.
/*! \file ********************************************************************
*
* Atmel Corporation
*
* - File              : AVR_api.c
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
#include <RTL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
//Used for SPLINT
#ifdef S_SPLINT_S
  #include"splint.h"
#endif


//Includes

#include "phone_com.h"
#include "phone_zip.h"
#include "phone_header.h"
#include "phone_tools.h"
#include "phone_api.h"

//#include "STM32F4xx.h"
#include "uart.h"
#include "phone_sms_sending.h"


//! Extern flag from AVRSMS_com.c
extern int rx_ack;

//! Message buffer for coded and decoded messages
char msgbuff[161];

//! AT-Command set used
const unsigned char  ATE0[]                    = "ATE0\r\n";                         //!< Echo off
const unsigned char  AT_CNMI[]                 = "AT+CNMI=1,1,,,1\r\n";              //!< Identification of new sms
const unsigned char  AT_CPMS[]                 = "AT+CPMS=\"ME\",\"ME\",\"ME\"\r\n"; //!< Preferred storage
const unsigned char  AT_CMGD[]                 = "AT+CMGD=";                         //!< Delete message at index
const unsigned char  AT_CMGR[]                 = "AT+CMGR=";                         //!< Read from index
const unsigned char  AT_CMGS[]                 = "AT+CMGS=";                         //!< Send mmessage
const unsigned char  CRLF[]                    = "\r\n";                             //!< Carrige return Line feed


//! Function prototype
int API_check_acknowledge( void );  //Checks acknowledge from phone

static void itoa(int i, unsigned char *ptr);


/*! \brief Delete a message from a given index
 *
 *  This function will use the "AT+CMGD" command to delete
 *  the message @ index
 *
 *  \param    index index to delete from
 *
 *  \retval   1 Success
 *  \retval   0 Error
 */
int API_deletemsg( int index )
{
	//-------------------------------------------------------------------------
	send_to_modem("AT+CMGD=");               
	USART1->DR = (index & (uint16_t)0x01FF);
	send_to_modem("\r\n");
	//-------------------------------------------------------------------------
	return 1;
	//-------------------------------------------------------------------------
}


/*! \brief Send message
 *
 *  This function will take your user defined message, encode this
 *  text, add the header information found in AVRSMS_header.h.
 *  If successful, the message will be forwarded to the connected GSM modem
 *
 *  \param    *msg unsigned char pointer user defined message
 *
 *  \retval   1 Success, message sent
 *  \retval   0 Error doing compression
 *  \retval  -1 No "> " from phone
 *  \retval  -2 No message sent acknowledge
 */
int API_sendmsg( unsigned char *msg )
{
  //-------------------------------------------------------------------------
  int payload_len, len, ilgis_int;
  unsigned char payload_len_c[3], jump;
	unsigned char ilgis_char[3];
	//char EOFSMS[] = {0x1A};
	//-------------------------------------------------------------------------
  payload_len = len = 0;
  payload_len_c[0] = jump = '\0';
	//-------------------------------------------------------------------------
  if( ( payload_len = ZIP_compress( msg, &jump, 
		(unsigned char*)msgbuff) ) == 0 ) {  //Convert user text to pdu format
		//-------------------------------------------------------------------------
    return 0;                                                        //Something wrong happend during compression
		//-------------------------------------------------------------------------
  }else{	
		//-------------------------------------------------------------------------
    ZIP_itoh(payload_len, &payload_len_c[0]);                         //Convert Integer payload to hex in string format
		//-------------------------------------------------------------------------
		ilgis_int = HEADER_LEN+payload_len-(payload_len)/8;
		//-------------------------------------------------------------------------
		itoa(ilgis_int,ilgis_char);
		//-------------------------------------------------------------------------
		snprintf((char*)logmsg,MAXLOG,"Lenght Int: %d; HEX: %s \r\n",ilgis_int,ilgis_char);
		put_log(logmsg);
		//-------------------------------------------------------------------------		
		snprintf((char*)logmsg,MAXLOG,"Payload Lenght: %d; HEX: %s; Overall message lenght: %d\r\n",payload_len,payload_len_c,len);
		put_log(logmsg);
		//-------------------------------------------------------------------------
		snprintf((char*)logmsg,MAXLOG,"SMS PDU Format:\r\nAT+CMGS=%d\r\n%s,%s,%s\r\n",ilgis_int,PDU_HEADER,payload_len_c,msgbuff);
		put_log(logmsg);
		//-------------------------------------------------------------------------	
    send_to_modem((const char*)AT_CMGS);                                         //Send message
		send_to_modem((const char*)ilgis_char);
		send_to_modem("\r");
		os_dly_wait(80);
		//----------------------------------------------------------------
    //Append payload
		//----------------------------------------------------------------
		send_to_modem((const char*)PDU_HEADER);
		send_to_modem((const char*)payload_len_c);
		send_to_modem(msgbuff);
		//send_to_modem((unsigned char*)0x1A);
		//send_to_modem((unsigned char*)EOFSMS);
		USART1->DR = (26 & (uint16_t)0x01FF);
		//----------------------------------------------------------------
  }
	//-------------------------------------------------------------------------
	return 1;
	//-------------------------------------------------------------------------
}

int API_sendmsg_Unauth( unsigned char *msg )
{

  //! Local variables
  int payload_len, len, ilgis_int;                                           //Total length of message, and length of user text
  unsigned char payload_len_c[3], jump;
	unsigned char ilgis_char[3];
	//char EOFSMS[] = {0x1A};
	

  payload_len = len = 0;
  payload_len_c[0] = jump = '\0';

  //If necessary turn interrupts off
  if( ( payload_len = ZIP_compress( msg, &jump, (unsigned char*)msgbuff) ) == 0 ) //Convert user text to pdu format
  {
    return 0;                                                     //Something wrong happend during compression
  }

  //Compression ok
  else
  {
		//------------------------------------------------------------------
    ZIP_itoh(payload_len, &payload_len_c[0]);                     //Convert Integer payload to hex in string format
		//------------------------------------------------------------------
		ilgis_int = HEADER_LEN+payload_len-(payload_len)/8;
		//------------------------------------------------------------------
		itoa(ilgis_int,ilgis_char);
		//------------------------------------------------------------------
		snprintf((char*)logmsg,MAXLOG,"Lenght Int: %d; HEX: %s \r\n",ilgis_int,ilgis_char);
		put_log(logmsg);
		//------------------------------------------------------------------
		snprintf((char*)logmsg,MAXLOG,"Payload Lenght: %d; HEX: %s; Overall message lenght: %d\r\n",payload_len,payload_len_c,len);
		put_log(logmsg);
		//------------------------------------------------------------------
		snprintf((char*)logmsg,MAXLOG,"SMS PDU Format:\r\nAT+CMGS=%d\r\n%s|%s|%s|%s|%s|,%s,%s\r\n",ilgis_int,PDU_HEADER_UNAUTH_P1,PDU_HEADER_UNAUTH_P2,PDU_HEADER_UNAUTH_P3,PDU_HEADER_UNAUTH_P4,PDU_HEADER_UNAUTH_P5,payload_len_c,msgbuff);
		put_log(logmsg);
		//------------------------------------------------------------------	
    send_to_modem((const char*)AT_CMGS);                                         //Send message
		send_to_modem((const char*)ilgis_char);
		send_to_modem("\r");
		os_dly_wait(500);
		//----------------------------------------------------------------
    //Append payload
		//----------------------------------------------------------------
		send_to_modem((const char*)PDU_HEADER_UNAUTH_P1);
		send_to_modem((const char*)PDU_HEADER_UNAUTH_P2);
		send_to_modem((const char*)PDU_HEADER_UNAUTH_P3);
		send_to_modem((const char*)PDU_HEADER_UNAUTH_P4);
		send_to_modem((const char*)PDU_HEADER_UNAUTH_P5);
		send_to_modem((const char*)payload_len_c);
		send_to_modem((const char*)msgbuff);
		//------------------------------------------------------------------
		USART1->DR = (26 & (uint16_t)0x01FF);
		//------------------------------------------------------------------
  }
	return 1;
}


/*! \brief Read message from a given index
 *  \param    ind index to read message from
 *
 *  \retval   i Length of new message
 *  \retval   0 Error, No acknowledge from phone
 */
int API_readmsg( int ind )
{
	//------------------------------------------------------------------
	unsigned char *encodedmsg;                      //Pointer to encoded message
	int i;
	//------------------------------------------------------------------
	encodedmsg = '\0';
	i = 0;
	//------------------------------------------------------------------
	encodedmsg = TOOLS__decodeCMGR(ind);      //Get encoded message from the data returned from the phone
	i = ZIP_decompress(encodedmsg,(unsigned char*)msgbuff);  //Decompress this message
	//------------------------------------------------------------------
	return i;
	//------------------------------------------------------------------
}


static void itoa(int i, unsigned char *ptr)
 {
 	int dig = 0;
 	int tempi;
 
 	tempi = i;
 	do {
 		dig++;
 		tempi /= 10;
 	} while (tempi);
 
 	ptr += dig;
 	*ptr = '\0';
 	while (--dig >= 0) {
 		*(--ptr) = i % 10 + '0';
 		i /= 10;
}
  }
