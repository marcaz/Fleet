#define MAXLOG 300
#define MODEMBUFF 512

extern char logmsg[MAXLOG];
extern char modem_packet[MODEMBUFF];

void Init_USARTS(void);
void put_log (const char *data);
void send_to_modem(const char *data);

