// --------------------------------------------------------------------------------------
#include "main.h"
// --------------------------------------------------------------------------------------
#define true 1
#define false 0

#define MAXFIELD 25

void process_MRC(char *buffer);
unsigned char check_for_data(char *gps_buff, char *data_to_return, int FieldNum, int nMaxFieldLen);
// --------------------------------------------------------------------------------------
unsigned int  GpsGetYear   (void);
unsigned char GpsGetMonth  (void);
unsigned char GpsGetDay    (void);
unsigned char GpsGetHour   (void);
unsigned char GpsGetMinute (void);
unsigned char GpsGetSecond (void);
// --------------------------------------------------------------------------------------
bool			GpsGetAvailable		(void);
float			GpsGetLatitude		(void);
float			GpsGetLongitude		(void);
short			GpsGetAltitude		(void);
unsigned short	GpsGetSpeed			(void);
unsigned short	GpsGetDirection		(void);
char			GpsGetSatellites	(void);
void			Gps_Param_Clear		(void);
double			distance			(double lat1, double lon1, double lat2, double lon2);
unsigned short  angle 				(unsigned short angle1, unsigned short angle2);
void			Nmea_Analise		(char *pcBuff, unsigned short dwLen);
// --------------------------------------------------------------------------------------
//	ADDONS
// --------------------------------------------------------------------------------------
unsigned char	GpsGetFixQuality	(void);
float 			GpsGetHDOP			(void);
float 			GpsGetPDOP			(void);
// --------------------------------------------------------------------------------------
unsigned char	ReadNmeaFlg		(void);
void			ClearNmeaFlg	(void);
// --------------------------------------------------------------------------------------

void nmea_parser(char*RXBUF,unsigned short packet_len);
void ProcessGPRMC (char *pData);
