// This file has been prepared for Doxygen automatic documentation generation.
/*! \file ********************************************************************
*
* Atmel Corporation
*
* - File              : AVR_header.h
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

#ifndef AVRSMS_HEADER_H_INCLUDED
#define AVRSMS_HEADER_H_INCLUDED

    /*! \brief This flash string holds the message header
     *
     *  This string should be modified with the desired\n
     *  receiver number etc. Please see the GSM modem data sheet.
     */

    const unsigned char PDU_HEADER[]    =
    {
				'0' , '7',
				'9' , '1',
				'7' , '3', '6', '0', '4', '8', '9', '9', '9', '1','F', '9',
        '1' , '1',                                          					//<! SUBMIT SMS
        '0' , '0',
        '0' , 'B',                                         						//<! Phone nmbr length: 10 (0x0A) 11 (0x0B)
        '9' , '1',                                         						//<! Adr type
        '7' , '3', '6', '0', '8', '7', '5', '5', '7', '5','F', '0',  	//<! Receivers phone nmbr
        '0' , '0',                                          			    //<! TP_PID
        '0' , '0',                                          		    	//<! TP_DCS
				'A' , 'A',																								  	//SMS validity time
        '\0'
    };

#define HEADER_LEN 14                                       //<! Number of octets in header

#endif
