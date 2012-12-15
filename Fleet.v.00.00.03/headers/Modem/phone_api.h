
  int API_phoneinit( void );
  int API_deletemsg( int index );
  int API_sendmsg(unsigned char *msg );
	int API_sendmsg_Unauth( unsigned char *msg );
  int API_readmsg( int ind );
	extern char msgbuff[161];
	
	struct time_struct {
	
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t days;
	
	uint8_t work_start_hours;
	uint8_t work_start_minutes;
	uint8_t work_start_seconds;
	uint8_t work_start_days;
	
	uint8_t work_stop_hours;
	uint8_t work_stop_minutes;
	uint8_t work_stop_seconds;
	uint8_t work_stop_days;

};


extern struct time_struct time_data;


