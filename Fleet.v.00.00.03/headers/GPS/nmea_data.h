//---------------------------------------------------------------------------
// MAIN DEFINES
//---------------------------------------------------------------------------
#define HDOP_TIME_VAL	60		// 60 seconds to collect best HDOP record with active GPS(!)
#define HDOP_LIMIT		4.0		// all records will be considered as bad above this value
#define HDOP_MAX_VAL	50.0	// maximum allowed hdop value
//------------------------------------------------------------------------------
#define TS_LIMIT_MIN	1199145600 // minimum allowed timestamp value - Tue, 01 Jan 2008 00:00:00 GMT
#define TS_LIMIT_MAX	1514764800 // maximum allowed timestamp value - Mon, 01 Jan 2018 00:00:00 GMT
//---------------------------------------------------------------------------
#define DELTATIME	3000 // Time differnce for time sync to change time [milliseconds]
//---------------------------------------------------------------------------
#define NMEA_INIT_COUNTS	3 // Amount of NMEA Base Packets to ignore after GPS Restart
//---------------------------------------------------------------------------
#define MINSAT 4	//	minimum amount of sattelites to receive good data
//---------------------------------------------------------------------------
#define MAX_SPEED_FILER 1
//---------------------------------------------------------------------------]
extern unsigned char gps_jump_counter;
//---------------------------------------------------------------------------
// GLOBAL GPS FIX FLAG
//---------------------------------------------------------------------------
extern unsigned char gps_fix;
//---------------------------------------------------------------------------
// GLOBAL NMEA INIT COUNTER
//---------------------------------------------------------------------------
extern unsigned char nmea_init_flg;
//---------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------
void nmea_filter	(void);
void nmea_stat_calc (void);
//---------------------------------------------------------------------------
// NMEA DATA STRUCTURE
//---------------------------------------------------------------------------
struct gps_data_struct {
	//-----------------------------------------------------------------------
	unsigned char	sRMCDataValid;
	unsigned char	sGGAGPSQuality;
	float			sRMCLatitude;
	float			sRMCLongitude;
	short			sGGAAltitude;
	unsigned short	sRMCGroundSpeed;
	unsigned short	sRMCCourse;
	char			sGGANumOfSatInUse;
	unsigned int	sRMCYear;
	unsigned char	sRMCMonth;
	unsigned char	sRMCDay;
	unsigned char	sRMCHour;
	unsigned char	sRMCMinute;
	unsigned char	sRMCSecond;
	//-----------------------------------------------------------------------
};
//---------------------------------------------------------------------------
// GLOBAL STRUCTURES
//---------------------------------------------------------------------------
extern struct gps_data_struct gps_data_moment;
extern struct gps_data_struct gps_data_good;
//---------------------------------------------------------------------------
// NMEA STATISTICAL DATA
//---------------------------------------------------------------------------
extern struct nmea_stat_struct {
	
	unsigned int total;			// total amount of processed nmea packets


} nmea_stat;
//---------------------------------------------------------------------------
