#include <RTL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "STM32F4xx.h"
#include "main.h"
#include "leds.h"
#include "uart.h"
#include "nmea_api.h"
#include "nmea_data.h"
#include "acc_api.h"
#include "phone_api.h"
#include "phone_zip.h"
#include "phone_sms_sending.h"



struct pdu_read_struct pdu_read;

char num_buf[NUMBER_LEN];

char driver_number_1[NUMBER_LEN];
char driver_number_2[NUMBER_LEN];
unsigned char car_number_1[]="FJF999";
unsigned char car_number_2[]="FJF666";
unsigned char SMSsendBuffer[SMSLENGHT];
volatile unsigned char send_pending_sms = 0;
volatile unsigned char authorized_sender = 1;

const unsigned char PDU_HEADER_UNAUTH_P1[] = {'0' ,'7','9' ,'1','\0'};
const unsigned char PDU_HEADER_UNAUTH_P2[] = {'7' , '3', '6', '0', '4', '7', '5', '5', '8', '6','F','9','\0'};
const unsigned char PDU_HEADER_UNAUTH_P3[] = {'1','1','0','0','0','B','9','1','\0'};
unsigned char PDU_HEADER_UNAUTH_P4[13];
const unsigned char PDU_HEADER_UNAUTH_P5[] = {'0','0','0','0','A' ,'A','\0'};
	

unsigned char ModemBuffer[GSMBUFFSIZE];
unsigned char SMSBuffer[GSMBUFFSIZE];

volatile uint16_t RXHeadModem = 0;
volatile uint16_t SMSRXHeadModem = 0;
uint16_t RXTailModem = 0;

uint8_t rx_ok = 0;
volatile uint8_t sms_enabled = 1;
volatile uint8_t modem_online = 0;

volatile uint8_t new_sms_flag = 0;
volatile uint8_t pdu_in_buffer_flag = 0;


static void Update_PDU_Struct(void);
static void config_modem(void);

void SMS_commands_parser(void);

void sms_set_parameters (unsigned char *Data);

static void reset_working_time(void);
void create_response_number(void);



static void Update_PDU_Struct(void){
	//--------------------------------------------------------------------
	uint16_t pdu_cnt = 0;
	unsigned int i;
	char add_digit     = 0;
	char swap_buf      = 0;
	int smsc_lenght = 0;
	//--------------------------------------------------------------------
	// SMSC TYPE OF ADDRESS
	//--------------------------------------------------------------------
	pdu_cnt = 16;
	//------------------------------------------------------------------------
	// SMSC INFORMATION LENGTH (2 CHARS -> 1 BYTE)
	//------------------------------------------------------------------------
	pdu_read.smsc_length = octet_to_byte(&SMSBuffer[pdu_cnt]);
	pdu_cnt += 2;
	
	snprintf((char*)logmsg,MAXLOG,"[SMS_READER]-> Invalid SMSC Length (Bytes): %i\r\n",smsc_lenght);
	put_log(logmsg);
	//------------------------------------------------------------------------
	// OVERFLOW PROTECTION
	//------------------------------------------------------------------------
	if (pdu_read.smsc_length>SMSCNUM) {
		//--------------------------------------------------------------------
		snprintf((char*)logmsg,MAXLOG,"[SMS_READER]-> WARNING! Invalid SMSC Length (Bytes): %d\r\n",pdu_read.smsc_length);
		put_log(logmsg);
		//--------------------------------------------------------------------
		//return;
		//--------------------------------------------------------------------
	} else if (!pdu_read.smsc_length) {
		//--------------------------------------------------------------------
		put_log("[SMS_READER]-> No SMS Center Defined\r\n");
		//--------------------------------------------------------------------
	} else {
		put_log("[SMS_READER]-> SMS Center Lenght OK\r\n");
		//--------------------------------------------------------------------
		// SMSC TYPE OF ADDRESS
		//--------------------------------------------------------------------
		pdu_read.smsc_type = octet_to_byte(&SMSBuffer[pdu_cnt]);
		pdu_cnt += 2;
		//--------------------------------------------------------------------
		// STEP.1 WRITE INITIAL SMSC NUMBER
		// Minus one octet for SMSC LENGTH and multiply by 2 digits per octet
		//--------------------------------------------------------------------
		for (i=0;i<(pdu_read.smsc_length-1)*2;i++) {
			pdu_read.smsc_number[i] = SMSBuffer[pdu_cnt];
			pdu_cnt++;
		}
		//--------------------------------------------------------------------
		// STEP.2 SWAP TO NORMAL SMSC NUMBER
		//------------------------------------------------------------------------
		for (i=0;i<(pdu_read.smsc_length-1)*2;i++) {
			swap_buf = pdu_read.smsc_number[i];
			pdu_read.smsc_number[i] = pdu_read.smsc_number[i+1];
			pdu_read.smsc_number[i+1] = swap_buf;
			i++;
		}
		//--------------------------------------------------------------------
		// STEP.3 REMOVING TRAILING F SYMBOL IF EXISTS
		//------------------------------------------------------------------------
		if (pdu_read.smsc_number[(pdu_read.smsc_length-1)*2-1]==0x46) {
			pdu_read.smsc_number[(pdu_read.smsc_length-1)*2-1]=0x00;
		}
		//--------------------------------------------------------------------
	}
	//------------------------------------------------------------------------
	// FIRST OCTET OF SMS-DELIVER MESSAGE
	//------------------------------------------------------------------------
	pdu_read.smsc_deliver = octet_to_byte(&SMSBuffer[pdu_cnt]);
	pdu_cnt += 2;
	//------------------------------------------------------------------------
	// ADDRESS LENGTH (SENDER NUMBER)
	//------------------------------------------------------------------------
	pdu_read.sender_length = octet_to_byte(&SMSBuffer[pdu_cnt]);
	pdu_cnt += 2;
	//------------------------------------------------------------------------
	// OVERFLOW PROTECTION
	//------------------------------------------------------------------------
	if (pdu_read.sender_length>SMSCNUM) {
		//--------------------------------------------------------------------
		snprintf((char*)logmsg,MAXLOG,"[SMS.READER]->WARNING! Invalid SENDER NUM Length (Bytes): %d\r\n",pdu_read.sender_length);
		put_log(logmsg);
		//--------------------------------------------------------------------
		//return;
		//--------------------------------------------------------------------
	} else if (!pdu_read.sender_length) {
		//--------------------------------------------------------------------
		put_log("[SMS.READER]->No Sender Number Defined\r\n");
		//--------------------------------------------------------------------
	} else {
		put_log("[SMS_READER]-> SMS Sender Nr Lenght OK\r\n");
		//--------------------------------------------------------------------
		// CHECKING ADDRESS LENGTH FOR POSSIBLE F TRAIL
		//--------------------------------------------------------------------
		if (pdu_read.sender_length%2!=0) {
			add_digit = 1;
		} else {
			add_digit = 0;
		}
		//--------------------------------------------------------------------
		// TYPE OF ADDRESS OF SENDER NUMBER
		//--------------------------------------------------------------------
		pdu_read.sender_type = octet_to_byte(&SMSBuffer[pdu_cnt]);
		pdu_cnt += 2;
		//--------------------------------------------------------------------
		// STEP.1 WRITE INITIAL SENDER NUMBER
		//--------------------------------------------------------------------
		for (i=0;i<pdu_read.sender_length+add_digit;i++) {
			pdu_read.sender_number[i] = SMSBuffer[pdu_cnt];
			pdu_cnt++;
		}
		//--------------------------------------------------------------------
		// STEP.2 SWAP TO NORMAL SENDER NUMBER
		//--------------------------------------------------------------------
		for (i=0;i<pdu_read.sender_length+add_digit;i++) {
			swap_buf = pdu_read.sender_number[i];
			pdu_read.sender_number[i] = pdu_read.sender_number[i+1];
			pdu_read.sender_number[i+1] = swap_buf;
			i++;
		}
		//--------------------------------------------------------------------
		// STEP.3 REMOVING TRAILING F SYMBOL IF EXISTS
		//--------------------------------------------------------------------
		if (pdu_read.sender_number[pdu_read.sender_length]==0x46) {
			pdu_read.sender_number[pdu_read.sender_length]=0x00;
		}
		//--------------------------------------------------------------------
	}
	for(i=0;i<pdu_read.sender_length;i++) {
		//------------------------------------------------------------------
		num_buf[i] = pdu_read.sender_number[i];
		//------------------------------------------------------------------
	}
	//--------------------------------------------------------------------
	// OUTPUT SMS DATA (TEXT) TO UART 1
	//--------------------------------------------------------------------
	snprintf((char*)logmsg,MAXLOG,"[SMS.READER]->Sender Number:%s\r\n",num_buf);
	put_log(logmsg);
	//--------------------------------------------------------------------	
}

static void config_modem(void){
	//-----------------------------------------------------------------
	put_log("[MODEM.CFG]-> Configuring Modem..\r\n");
	//-----------------------------------------------------------------
	send_to_modem("ATE0\r\n");
	os_dly_wait(1500);
	//-----------------------------------------------------------------
	send_to_modem("AT+CPMS=\"ME\",\"ME\",\"ME\"\r\n");
	os_dly_wait(3000);
	//-----------------------------------------------------------------
	send_to_modem("AT+CNMI=1,1,0,0,1\r\n");
	os_dly_wait(3000);
	send_to_modem("ATE0\r\n");
	os_dly_wait(1500);
	//-----------------------------------------------------------------
	send_to_modem("AT+CPMS=\"ME\",\"ME\",\"ME\"\r\n");
	os_dly_wait(3000);
	//-----------------------------------------------------------------
	send_to_modem("AT+CNMI=1,1,0,0,1\r\n");
	os_dly_wait(3000);
	//-----------------------------------------------------------------
	put_log("[MODEM.CFG]-> Done.\r\n");
	//-----------------------------------------------------------------
}


char octet_to_byte (unsigned char*char_buf) {
	//------------------------------------------------------------------------
	char result = 0;
	//------------------------------------------------------------------------
	if (*char_buf==0x00) {
		result = 0x00;
		return result;
	} else if (*char_buf<=0x39) {
		result += *char_buf - 0x30;
	} else {
		result += *char_buf - 0x37;
	}
	//------------------------------------------------------------------
	snprintf((char*)logmsg,MAXLOG,"\r\n[SMS.OCT2B_1]-> Buffer: %X [%c] && %X [%c]\r\n",*char_buf,*char_buf,result,result);
	put_log(logmsg);
	//------------------------------------------------------------------------
	result <<= 4;
	//------------------------------------------------------------------------
	char_buf++;
	//------------------------------------------------------------------------
	if (*char_buf==0x00) {
		result = 0x00;
	}else if (*char_buf<=0x39) {
		result += *char_buf - 0x30;
	} else {
		result += *char_buf - 0x37;
	}
	snprintf((char*)logmsg,MAXLOG,"\r\n[SMS.OCT2B_2]->Buffer: %X [%c] && %X [%c]\r\n",*char_buf,*char_buf,result,result);
	put_log(logmsg);
	//------------------------------------------------------------------------
	return result;
	//------------------------------------------------------------------------
}


void create_response_number(void){
	//------------------------------------------------------------------
	unsigned char i = 0;
	unsigned char oct_cnt = 0;
	unsigned char head_cnt = 0;
	unsigned char src_cnt = 0;
	//------------------------------------------------------------------
	for(i=0;i<7;i++){
		//---------------------------------------------------
		if(oct_cnt != 5){
			//---------------------------------------------------
			PDU_HEADER_UNAUTH_P4[head_cnt]=num_buf[src_cnt+1];
			head_cnt++;
			PDU_HEADER_UNAUTH_P4[head_cnt]=num_buf[src_cnt];
			head_cnt++;
			src_cnt++;
			src_cnt++;
			//---------------------------------------------------
		}else{
			//---------------------------------------------------
			PDU_HEADER_UNAUTH_P4[head_cnt] = 'F';
			head_cnt++;
			PDU_HEADER_UNAUTH_P4[head_cnt] = num_buf[src_cnt];
			head_cnt++;
			snprintf((char*)logmsg,MAXLOG,"[SMS.NUMER.CREATOR] Inserting NULL on index:%d, Previous char is:%X\r\n",head_cnt,PDU_HEADER_UNAUTH_P4[head_cnt-1]);
			put_log(logmsg);
			PDU_HEADER_UNAUTH_P4[head_cnt] = '\0';
			break;
			//---------------------------------------------------
		}
		//---------------------------------------------------
		oct_cnt++;
 	//------------------------------------------------------------------
	}
	//------------------------------------------------------------------	
}


static void reset_working_time(void){
	//---------------------------------------------------------------------
	time_data.work_stop_hours   = 0;
	time_data.work_stop_minutes = 0;
	time_data.work_stop_seconds = 0;
	time_data.work_stop_days    = 0;
	//---------------------------------------------------------------------
	time_data.work_start_hours   = 0;
	time_data.work_start_minutes = 0;
	time_data.work_start_seconds = 0;
	time_data.work_start_days    = 0;
	//---------------------------------------------------------------------
}

void send_alarm_sms(void){
	//------------------------------------------------------------------
	snprintf((char*)SMSsendBuffer,SMSLENGHT,"Warning!Wehicle Moving!");
	authorized_sender = 1;
	send_pending_sms = 1;	
	//------------------------------------------------------------------
	os_dly_wait(1500);	
	//------------------------------------------------------------------

}
