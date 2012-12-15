/**
  ******************************************************************************
  * @file    NMEA Api.c 
  * @author  
  * @version V1.0.0
  * @date    2012.05.23
  * @brief   NMEA APi Routines
  ******************************************************************************
**/
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
#include <RTL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "string.h"
#include "nmea_api.h"
#include "nmea_data.h"
#include "uart.h"


#define __FALSE 0
#define __TRUE 1

//------------------------------------------------------------------------
#define pi 3.14159265358979323846264
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// GPGGA Data
//------------------------------------------------------------------------
unsigned char GGAHour;					//
unsigned char GGAMinute;				//
unsigned char GGASecond;				//
unsigned char GGAGPSQuality;			// 0 = fix not available, 1 = GPS sps mode, 2 = Differential GPS, SPS mode, fix valid, 3 = GPS PPS mode, fix valid
unsigned char GGANumOfSatsInUse;		//
//------------------------------------------------------------------------
// GPGSA
//------------------------------------------------------------------------
unsigned char GSAFixMode;				// 1 = fix not available, 2 = 2D, 3 = 3D
//------------------------------------------------------------------------
// GPRMC
//------------------------------------------------------------------------
unsigned char	RMCHour;				//
unsigned char	RMCMinute;				//
unsigned char	RMCSecond;				//
unsigned char	RMCDataValid;			// A = Data valid, V = navigation rx warning
unsigned char	RMCDay;					//
unsigned char	RMCMonth;				//
unsigned int	RMCYear;				    //
double			RMCLatitude;				// current latitude
double			RMCLongitude;			// current longitude
double			RMCGroundSpeed;			// speed over ground, knots
double			RMCCourse;				// course over ground, degrees true

double      RMCMagVar;

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
void nmea_filter (void) {
	//--------------------------------------------------------------------
	gps_data_moment.sRMCDataValid		=	GpsGetAvailable();
	//--------------------------------------------------------------------
	gps_data_moment.sRMCLatitude		=	GpsGetLatitude();
	gps_data_moment.sRMCLongitude		=	GpsGetLongitude();
	gps_data_moment.sRMCGroundSpeed		=	GpsGetSpeed();
	gps_data_moment.sRMCCourse			=	GpsGetDirection();
	//--------------------------------------------------------------------
	gps_data_moment.sRMCYear			=	GpsGetYear();
	gps_data_moment.sRMCMonth			=	GpsGetMonth();
	gps_data_moment.sRMCDay				=	GpsGetDay();
	gps_data_moment.sRMCHour			=	GpsGetHour();
	gps_data_moment.sRMCMinute			=	GpsGetMinute();
	gps_data_moment.sRMCSecond			=	GpsGetSecond();
	//--------------------------------------------------------------------	
	memcpy((char*)&gps_data_good,(char*)&gps_data_moment,sizeof(struct gps_data_struct));
	//--------------------------------------------------------------------
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
void Gps_Param_Clear (void) {
	//--------------------------------------------------------------------
	GGAGPSQuality = 0;				// 0 = fix not available, 1 = GPS sps mode, 2 = Differential GPS, SPS mode, fix valid, 3 = GPS PPS mode, fix valid
	GGANumOfSatsInUse = 0;			//
	//--------------------------------------------------------------------
	GSAFixMode = 1;					// 1 = fix not available, 2 = 2D, 3 = 3D
	//--------------------------------------------------------------------
	RMCHour = 0;					//
	RMCMinute = 0;					//
	RMCSecond = 0;					//
	RMCDataValid = 'V';				// A = Data valid, V = navigation rx warning
	RMCLatitude = 0.0;				// current latitude
	RMCLongitude = 0.0;				// current longitude
	RMCGroundSpeed = 0.0;			// speed over ground, knots
	RMCCourse = 0.0;					// course over ground, degrees true
	RMCDay = 1;						//
	RMCMonth = 1;					//
	RMCYear = 2008;					//
	//--------------------------------------------------------------------
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
void process_MRC(char *buffer){
	//--------------------------------------------------------------
	char pcBuff[20];
	char pcField[MAXFIELD];
	static uint8_t nmea_log_cnt = 0;
	//--------------------------------------------------------------	
	//print_to_serial_3("Patikrinam\r\n");
	//--------------------------------------------------------------
	if(*buffer == ','){
				//print_to_serial_3("Sep Found, continue...\r\n");
	}
	//--------------------------------------------------------------
	// Hour, Minute, Second
	//--------------------------------------------------------------
	if(check_for_data(buffer, pcField, 1, MAXFIELD)){
		// HOURS
		pcBuff[0] = pcField[0];
		pcBuff[1] = pcField[1];
		pcBuff[2] = 0;
		RMCHour = atoi(pcBuff);
		// Minute
		pcBuff[0] = pcField[2];
		pcBuff[1] = pcField[3];
		pcBuff[2] = 0;
		RMCMinute = atoi(pcBuff);
		// Second
		pcBuff[0] = pcField[4];
		pcBuff[1] = pcField[5];
		pcBuff[2] = 0;
		RMCSecond = atoi(pcBuff);
	}
	//--------------------------------------------------------------
	//  Data valid
	//--------------------------------------------------------------	
	if (check_for_data(buffer, pcField, 2, MAXFIELD)) {
		RMCDataValid = pcField[0];
	} else {
		RMCDataValid = 'V';
	}
	//--------------------------------------------------------------
	// Latitude
	//--------------------------------------------------------------
	if (check_for_data(buffer, pcField, 3, MAXFIELD)) {
		
		RMCLatitude = atof(pcField + 2) / 60.0;
 		pcField[2] = 0;
 		RMCLatitude += atof(pcField);
		
		//snprintf((char*)message_3,MESSAGEBUFFSIZE,"---->Latitude: %f\r\n",RMCLatitude);
		//print_to_serial_3(message_3);

	}
	if (check_for_data(buffer, pcField, 4, MAXFIELD)) {
		if (pcField[0] == 'S') {
		  RMCLatitude = -RMCLatitude;
		}
	}
	//--------------------------------------------------------------
	//
	//--------------------------------------------------------------
	/// Longitude
	if (check_for_data(buffer, pcField, 5, MAXFIELD)) {
		RMCLongitude = atof(pcField + 3) / 60.0;
		pcField[3] = 0;
		RMCLongitude += atof(pcField);
		
		//snprintf((char*)message_3,MESSAGEBUFFSIZE,"---->Longitude: %f\r\n",RMCLongitude);
		//print_to_serial_3(message_3);
	}
	if (check_for_data(buffer, pcField, 6, MAXFIELD)) {
		if (pcField[0] == 'W') {
			RMCLongitude = -RMCLongitude;
		}
	}
	//--------------------------------------------------------------
	//
	//--------------------------------------------------------------
	/// Ground speed
	if (check_for_data(buffer, pcField, 7, MAXFIELD)) {
		RMCGroundSpeed = atof(pcField);
		
		//snprintf((char*)message_3,MESSAGEBUFFSIZE,"---->GSpeed: %f\r\n",RMCGroundSpeed);
		//print_to_serial_3(message_3);
		
	} else {
		RMCGroundSpeed = 0.0;
	}
	/// course over ground, degrees true
	if (check_for_data(buffer, pcField, 8, MAXFIELD)) {
		RMCCourse = atof(pcField);
		
		//snprintf((char*)message_3,MESSAGEBUFFSIZE,"---->Course: %f\r\n",RMCCourse);
		//print_to_serial_3(message_3);
		
	} else {
		RMCCourse = 0.0;
	}
	//--------------------------------------------------------------
	// Date
	//--------------------------------------------------------------
	if (check_for_data(buffer, pcField, 9, MAXFIELD)) {
		// Day
		pcBuff[0] = pcField[0];
		pcBuff[1] = pcField[1];
		pcBuff[2] = 0;
		RMCDay = atoi(pcBuff);
		/// Month
		pcBuff[0] = pcField[2];
		pcBuff[1] = pcField[3];
		pcBuff[2] = 0;
		RMCMonth = atoi(pcBuff);
		/// Year (Only two digits. I wonder why?)
		pcBuff[0] = pcField[4];
		pcBuff[1] = pcField[5];
		pcBuff[2] = 0;
		RMCYear = atoi(pcBuff);
		// make flexible 4 digit date
		if (RMCYear<=70) {
			RMCYear += 2000;
		} else {
			RMCYear += 1900;
		}
	}
	//--------------------------------------------------------------
	// Course over ground, Degrees true
	//--------------------------------------------------------------
	if (check_for_data(buffer, pcField, 10, MAXFIELD)) {
		RMCMagVar = atof(pcField);
	} else {
		RMCMagVar = 0.0;
	}
	if (check_for_data(buffer, pcField, 11, MAXFIELD)) {
		if (pcField[0] == 'W') {
			RMCMagVar = -RMCMagVar;
		}
	}
	//--------------------------------------------------------------
	nmea_filter();
	//--------------------------------------------------------------
	if(nmea_log_cnt++ >= 9){
		//--------------------------------------------------------------
		put_log("[NMEA.PARSER]-> NMEA Packet Check - OK!\r\n");
		nmea_log_cnt = 0;
		//--------------------------------------------------------------
	}
	//--------------------------------------------------------------	
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned char check_for_data(char *gps_buff, char *data_to_return, int FieldNum, int nMaxFieldLen){
	
	int i = 0;
	int i2 = 0;
	int field_nr = 0;
	
	if ((gps_buff == 0) || (data_to_return == 0)) {
		return false;
	}
	
	while((gps_buff[i])&&(FieldNum != field_nr)){
		
			if(gps_buff[i] == ','){
				
				field_nr++;
				
			}
			i++;
		
			if (!gps_buff[i]) {
				data_to_return[0] = 0;
				return false;
			}
		
	}
	
	if ((gps_buff[i] == ',') || (gps_buff[i] == '*')) {
		data_to_return[0] = 0;
		return false;
	}
	/// copy field from buffer to Field
	while((gps_buff[i] != ',') && (gps_buff[i] != '*') && (gps_buff[i])) {
		data_to_return[i2] = gps_buff[i];
		i2++; i++;
		// check if field is too big to fit on passed parameter. If it is,
		// crop returned field to its max length.
		if (i2 >= nMaxFieldLen) {
			i2 = nMaxFieldLen - 1;
			break;
		}
	}
	data_to_return[i2] = 0;
	return true;
	
	
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
bool GpsGetAvailable (void) {

	return (RMCDataValid == 'A' ? true : false);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned char GpsGetFixQuality (void) {

	return GGAGPSQuality;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
float GpsGetLatitude (void) {

	return RMCLatitude;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
float GpsGetLongitude (void) {

	return RMCLongitude;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned short GpsGetSpeed (void) {

	return (RMCGroundSpeed * 1.852);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned short GpsGetDirection (void) {

	return RMCCourse;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
char GpsGetSatellites (void) {

	return GGANumOfSatsInUse;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned int GpsGetYear (void) {

	return RMCYear;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned char GpsGetMonth (void) {

	return RMCMonth;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned char GpsGetDay (void) {

	return RMCDay;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned char GpsGetHour (void) {

	return RMCHour;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned char GpsGetMinute (void) {

	return RMCMinute;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
unsigned char GpsGetSecond (void) {

	return RMCSecond;
}
