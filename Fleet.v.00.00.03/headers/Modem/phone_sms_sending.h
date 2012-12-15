//----------------------------------------------
#define SMSCNUM		32
#define TIMESTAMP	14
#define USERDATA	140
#define NUMBER_LEN 17

#define SMSLENGHT 161
//----------------------------------------------
extern struct pdu_read_struct {

	char smsc_length;
  char smsc_type;
	char smsc_number[SMSCNUM];
	char smsc_deliver;
	char sender_length;
	char sender_type;
	char sender_number[SMSCNUM];
	char TP_PID;
	char TP_DCS;
	char TP_SCTS[TIMESTAMP];
	char TP_UDL;

} pdu_read;

char octet_to_byte(unsigned char*);
//----------------------------------------------
#define GSMBUFFSIZE 512u
extern unsigned char message_gsm[GSMBUFFSIZE];

extern char num_buf[NUMBER_LEN];
extern unsigned char SMSsendBuffer[SMSLENGHT];
//----------------------------------------------
extern unsigned char ModemBuffer[GSMBUFFSIZE];
extern unsigned char SMSBuffer[GSMBUFFSIZE];
extern volatile uint16_t RXHeadModem;
extern volatile uint16_t SMSRXHeadModem;
extern uint16_t RXTailModem;
//----------------------------------------------
extern uint8_t rx_ok;
volatile extern uint8_t sms_enabled;
volatile extern uint8_t modem_online;

extern volatile unsigned char send_pending_sms;
extern volatile unsigned char authorized_sender;
//----------------------------------------------
void create_SMS_Processor_task(void);
void create_SMS_Sending_task(void);
void create_SMS_Reading_task(void);
//----------------------------------------------
extern char driver_number_1[NUMBER_LEN];
extern char driver_number_2[NUMBER_LEN];
extern unsigned char car_number_1[];
extern unsigned char car_number_2[];

extern const unsigned char PDU_HEADER_UNAUTH_P1[];
extern const unsigned char PDU_HEADER_UNAUTH_P2[];
extern const unsigned char PDU_HEADER_UNAUTH_P3[];
extern unsigned char PDU_HEADER_UNAUTH_P4[13];
extern const unsigned char PDU_HEADER_UNAUTH_P5[];

uint8_t read_DIN1(void);

