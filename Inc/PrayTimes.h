//--------------------- Copyright Block ----------------------
/* 

PrayTime.cs: Prayer Times Calculator (ver 1.2)
Copyright (C) 2007-2010 PrayTimes.org

C# Code By: Jandost Khoso
Original JS Code By: Hamid Zarrabi-Zadeh

License: GNU LGPL v3.0

TERMS OF USE:
	Permission is granted to use this code, with or 
	without modification, in any website or application 
	provided that credit is given to the original work 
	with a link back to PrayTimes.org.

This program is distributed in the hope that it will 
be useful, but WITHOUT ANY WARRANTY. 

PLEASE DO NOT REMOVE THIS COPYRIGHT BLOCK.



developer Mohsen Faryabi 09131484530
*/

//#include "Math.h"
#define PI 3.14159265358979

// Calculation Methods
typedef enum
{
	Jafari     = 0,    // Ithna Ashari
	Karachi    = 1,    // University of Islamic Sciences, Karachi
	ISNA       = 2,    // Islamic Society of North America (ISNA)
	MWL        = 3,    // Muslim World League (MWL)
	Makkah     = 4,    // Umm al-Qura, Makkah
	Egypt      = 5,    // Egyptian General Authority of Survey
	Tehran     = 6,    // Institute of Geophysics, University of Tehran
	Custom     = 7,    // Custom Setting
}Cal_methods;


// Juristic Methods
enum
{
	  Shafii     = 0,    // Shafii (standard)
	  Hanafi     = 1    // Hanafi
}juristic_methods;

	// Adjusting Methods for Higher Latitudes
enum
{
	  None       = 0,    // No adjustment
	  MidNight   = 1,    // middle of night
	  OneSeventh = 2,    // 1/7th of night
	  AngleBased = 3    // angle/60th of night
}adjusting_methods;

	// Time Formats
enum
{
	  Time24     = 0,    // 24-hour format
	  Time12     = 1,    // 12-hour format
	  Time12NS   = 2,    // 12-hour format with no suffix
	  Floating   = 3    // floating point number
}time_formats;


double methodParams [][5]={
		                        {16, 0, 4, 0, 14},    //Jafari   0
		                        {18, 1, 0, 0, 18},    //Karachi  1 
		                        {15, 1, 0, 0, 15},    //ISNA     2 
		                        {18, 1, 0, 0, 17},    //MWL      3
		                        {18.5, 1, 0, 1, 90},  //Makkah   4 
		                        {19.5, 1, 0, 0, 17.5},//Egypt    5
		                        {17.7, 0, 4.5, 0, 14},//Tehran   6 
		                        {18, 1, 0, 0, 17}     //Custom   7
	                         };

													 
													 
													 
double t[] = {0.2083333333333333, 0.25, 0.5, 0.5416666666666667, 0.75, 0.75, 0.75}; //default times






class PrayTime{

//------------------------ Constants --------------------------
	public:
	
 PrayTime();
 void getDatePrayerTimes(int year, int month, int day, double latitude, double longitude, double timeZone);
 double JulianDate ( int year , int month , int day );
 void computeDayTimes(void);
 void computeTimes ( void );
	 double computeTime (double G, double t);
	 double sunDeclination (double jd);
	 double sunPosition ( double jd ,char);
	 double FixAngle ( double angel );
	 double FixHour ( double hour );
	 double computeMidDay ( double t);
	 double equationOfTime (double jd);
	 void  adjustTimes(void);
	 void adjustHighLatTimes (void);
	 double nightPortion ( double angle);
	 void adjustTimesFormat (void);
	 void floatToTime24(double time ,char *hor ,char *min);
	 double computeAsr (int step, double t);

	 
	 
	 
	 
	 
	 double dsin (double d){return sin(DegreeToRadian(d));}
   double dcos (double d){return cos(DegreeToRadian(d));}
   double dtan (double d){return tan(DegreeToRadian(d));}
   double darcsin (double x){return RadianToDegree(asin(x));}
   double darccos (double x){return RadianToDegree(acos(x));}
   double darctan (double x){return RadianToDegree(atan(x));}
   double darctan2 (double y, double x){return RadianToDegree(atan2(y, x));}
   double darccot (double x){return RadianToDegree(atan(1/x));}
   double RadianToDegree ( double radian){return (radian * 180.0) / PI;}
	 double DegreeToRadian (double degree){return (degree * PI) / 180.0;}
	 
	 double GetTimeDifference (double c1,double c2){ return FixHour(c2 - c1);}
	 void   setCalcMethod (Cal_methods methodID);


	// Time Names
	//public  static String [] timeNames ={	"Fajr", "Sunrise", "Dhuhr", "Asr", "Sunset", "Maghrib","Isha"};
	//static String InvalidTime = "----";	 // The string used for inv


//struct TEMP{
//	double temp1;
//	double temp2;
//	double temp3;
//	double temp4;
//	double temp5;
//	double temp6;
//	double temp7;
//	double temp8;
//	double temp9;
//	double temp10;
//	
//}temp;

//---------------------- Global Variables --------------------


	int calcMethod ;		// caculation method
	int asrJuristic ;		  // Juristic method for Asr
	int dhuhrMinutes ;		// minutes after mid-day for Dhuhr
	int adjustHighLats ;	// adjusting method for higher latitudes

	int timeFormat   ;		// time format

	double lat;        // latitude
	double lng;        // longitude
  double timeZone;   // time-zone
	double JDate;      // Julian date
	
	double times[10];

	//int [] times ;


//--------------------- Technical Settings --------------------


	int numIterations;		// number of iterations needed to compute times



//------------------- Calc Method Parameters --------------------

//	 
//	public PrayTime ()
//	{
//		times = new int [7];
//	}

typedef struct { //"Fajr", "Sunrise", "Dhuhr", "Asr", "Sunset", "Maghrib","Isha"}
	char fajr_hor;
	char fajr_min;
	
	char sunrise_hor;
	char sunrise_min;
	
	char dhihr_hor;
	char dhuhr_min;
	
	char asr_hor;
	char asr_min;
	
	char sunset_hor;
	char sunset_min;
	
	char maghrib_hor;
	char maghrib_min;
	 
	char isha_hor;
	char isha_min;
	
	
	
	
}TIM;

TIM tim;

}pt;
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
PrayTime::PrayTime()
{
	calcMethod = 6;		// caculation method
	dhuhrMinutes = 0;		// minutes after mid-day for Dhuhr
	adjustHighLats = 1;	// adjusting method for higher latitudes
	timeFormat   = 0;		// time format

	numIterations = 1;
	
	asrJuristic=0;
}





//// return prayer times for a given date
//public String [] getPrayerTimes (int year, int month , int day , double latitude, double  longitude, int timeZone)
//{
//	return this.getDatePrayerTimes(year, month+ 1, day, latitude, longitude, timeZone);
//}

// set the calculation method
void PrayTime::setCalcMethod (Cal_methods methodID)
{
	calcMethod = methodID;
};

//// set the juristic method for Asr
//public void setAsrMethod (int methodID)
//{
//	if (methodID < 0 || methodID > 1)
//		return;
//	this.asrJuristic = methodID;
//}

//// set the angle for calculating Fajr
//public void setFajrAngle (double angle)
//{
//	this.setCustomParams(new int [] {(int)angle, -1, -1, -1, -1});
//}

//// set the angle for calculating Maghrib
//public void setMaghribAngle (double angle)
//{
//	this.setCustomParams(new int [] {-1, 0, (int)angle, -1, -1});
//}

//// set the angle for calculating Isha
//public void setIshaAngle (double angle)
//{
//	this.setCustomParams(new int [] {-1, -1, -1, 0, (int)angle});
//}

//// set the minutes after mid-day for calculating Dhuhr
//public void setDhuhrMinutes (int  minutes)
//{
//	this.dhuhrMinutes = minutes;
//}

//// set the minutes after Sunset for calculating Maghrib
//public void setMaghribMinutes (int minutes)
//{
//	this.setCustomParams(new int []{-1, 1, minutes, -1, -1});
//}

//// set the minutes after Maghrib for calculating Isha
//public void setIshaMinutes (int minutes)
//{
//	this.setCustomParams(new int [] {-1, -1, -1, 1, minutes});
//}

//// set custom values for calculation parameters
//public void setCustomParams( int [] param)
//{
//	for (int i=0; i<5; i++)
//	{
//		if (param[i] == -1)
//			this.methodParams[Custom][i] = this.methodParams[this.calcMethod][i];
//		else
//			this.methodParams[Custom][i] = param[i];
//	}
//	this.calcMethod = Custom;
//}

//// set adjusting method for higher latitudes
//public void setHighLatsMethod (int methodID)
//{
//	this.adjustHighLats = methodID;
//}

//// set the time format
//public void setTimeFormat (int timeFormat)
//{
//	this.timeFormat = timeFormat;
//}
//-----------------------------------------------------------------
//-------------------------------------------------------------------
//---------------------------------------------------------------
// convert float hours to 24h format
void PrayTime::floatToTime24(double time ,char *hor ,char *min)  //String floatToTime24 (double time)
{
	//if (time < 0)	return 255;//InvalidTime;
	
	time = FixHour(time+ 0.5/ 60);  // add 0.5 minutes to round
	*hor = (char) floor(time);
	*min = floor((time- *hor)* 60);
	
//	temp.temp1=time;
//	temp.temp2=*hor;
//	temp.temp3=*min;
//	while(1);
	
	//return this.twoDigitsFormat((int)hours)+":"+ this.twoDigitsFormat((int)minutes);
}
//-----------------------------------------------------------------
//-------------------------------------------------------------------
//---------------------------------------------------------------

//// convert float hours to 12h format
//public String floatToTime12 (double time, bool noSuffix)
//{
//	if (time < 0)
//		return InvalidTime;
//	time = this.FixHour(time+ 0.5/ 60);  // add 0.5 minutes to round
//	double hours = Math.Floor(time);
//	double minutes = Math.Floor((time- hours)* 60);
//	String suffix = hours >= 12 ? " pm" : " am";
//	hours = (hours+ 12 -1)% 12+ 1;
//	return ((int)hours)+":"+ this.twoDigitsFormat((int)minutes)+ (noSuffix ? "" : suffix);
//}

//// convert float hours to 12h format with no suffix
//public String floatToTime12NS (double time)
//{
//	return this.floatToTime12(time, true);
//}



//-------------------------------------------------------------------
//-------------------------------------------------------------------
//---------------------- Compute Prayer Times -----------------------
// return prayer times for a given date
void PrayTime::getDatePrayerTimes(int year, int month, int day, double latitude, double longitude, double timeZonee=3.5)
{
	lat = latitude;
	lng = longitude;
	timeZone = timeZonee;
  JDate = JulianDate ( year , month , day ) - longitude / ( 15 * 24 );
 
  computeDayTimes();	//return this.computeDayTimes();
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
// compute declination angle of sun and equation of time   
double PrayTime::sunPosition ( double jd , char ret )
{
    
  double D = jd - 2451545.0;  
	double g = FixAngle(357.529 + 0.98560028* D);      
	double q = FixAngle(280.459 + 0.98564736* D);
	double L = FixAngle(q + 1.915* dsin(g) + 0.020* dsin(2*g));
	double R = 1.00014 - 0.01671* dcos(g) - 0.00014* dcos(2*g);
  double e = 23.439 - 0.00000036* D;
	double RA = darctan2(dcos(e)* dsin(L), dcos(L))/ 15;
   
    
  RA = FixHour(RA);
	double d = darcsin(dsin(e)* dsin(L));
  double  EqT = q/15 - RA;

//  temp.temp1=jd;
//	temp.temp2=D;
//	
//	temp.temp3=g;
//	temp.temp4=q;
//	temp.temp5=L;
//	
//	temp.temp6=R;
//	temp.temp7=e;
//	temp.temp8=RA;
//	temp.temp9=d;
//	temp.temp10=EqT;
//	

//	while(1);
	 
	
  return ret? EqT:d; //	return new double [] {d, EqT};

}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// compute equation of time
double PrayTime::equationOfTime (double jd)
{
	return sunPosition(jd,1);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// compute declination angle of sun
double PrayTime::sunDeclination (double jd)
{
	return sunPosition(jd ,0);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// compute mid-day (Dhuhr, Zawal) time
double PrayTime::computeMidDay ( double t)
{
    double T = equationOfTime(JDate + t);// Console.WriteLine("T=" + t);
    double Z = FixHour(12 - T);               // Console.WriteLine("Z=" + Z);
	return Z;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// compute time for a given angle G
double PrayTime::computeTime (double G, double t)
{
////System.out.println("G: "+G);
  

	
	 
    double D = sunDeclination(JDate + t);    
    double Z = computeMidDay(t);                 
  	double V = ((double)1/15)* darccos((-dsin(G)- dsin(D)* dsin(lat)) /(dcos(D)* dcos(lat)));

//	temp.temp1=D;
//	temp.temp2=Z;
//	temp.temp3=V;
//	temp.temp4=G;
//	while(1);
//    //Console.WriteLine("Vvvv=" + V);
  	return Z+ (G>90 ? -V : V);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------

// compute the time of Asr
double PrayTime::computeAsr (int step, double t)  // Shafii: step=1, Hanafi: step=2
{
	double D = sunDeclination(JDate+ t);
	double G = -darccot(step+ dtan(abs(lat-D)));
	return computeTime(G, t);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------- Compute Prayer Times -----------------------
// compute prayer times at given julian date
void PrayTime::computeTimes ( void )
{

 
	

  double Fajr    = computeTime(180- methodParams[calcMethod][0], t[0]);
  double Sunrise = computeTime(180 - 0.833, t[1]);
	double Dhuhr   = computeMidDay(t[2]);
	
	
  double Asr     = computeAsr(1+ asrJuristic, t[3]);

	double Sunset  = computeTime(0.833, t[4]);;


	double Maghrib = computeTime(methodParams[calcMethod][2], t[5]);
	double Isha    = computeTime(methodParams[calcMethod][4], t[6]);

//	return new double [] {Fajr, Sunrise, Dhuhr, Asr, Sunset, Maghrib, Isha};
	times[0] = Fajr;
	times[1] = Sunrise;
	times[2] = Dhuhr;
	times[3] = Asr;
	times[4] = Sunset;
	times[5] = Maghrib;
	times[6] = Isha;
	 
	 
	
	
	
	
}
//------------------------------------------------------------------------------
//----------------------------------------------------------------------------
//------------------------------------------------------------------------------
// adjust Fajr, Isha and Maghrib for locations in higher latitudes
void PrayTime::adjustHighLatTimes (void)
{
	double nightTime =  GetTimeDifference(times[4], times[1]); // sunset to sunrise

	// Adjust Fajr
	double FajrDiff =  nightPortion(methodParams[calcMethod][0])* nightTime;
	if (GetTimeDifference(times[0], times[1]) > FajrDiff)
		times[0] = times[1]- FajrDiff;

	// Adjust Isha
	double IshaAngle = (methodParams[calcMethod][3] == 0) ? methodParams[calcMethod][4] : 18;
	
	double IshaDiff =  nightPortion(IshaAngle)* nightTime;
	if (GetTimeDifference(times[4], times[6]) > IshaDiff)times[6] = times[4]+ IshaDiff;

	// Adjust Maghrib
	double MaghribAngle = (methodParams[calcMethod][1] == 0) ? methodParams[calcMethod][2] : 4;
	double MaghribDiff =  nightPortion(MaghribAngle)* nightTime;
	if (GetTimeDifference(times[4], times[5]) > MaghribDiff)times[5] = times[4]+ MaghribDiff;

//	return times;
}
//------------------------------------------------------------------------------
//----------------------------------------------------------------------------
//------------------------------------------------------------------------------
// the night portion used for adjusting times in higher latitudes
double PrayTime::nightPortion ( double angle)
{
	double val = 0;
	if (adjustHighLats == AngleBased)
		val = 1.0/60.0* angle;
	if (adjustHighLats == MidNight)
		val = 1.0/2.0;
	if (adjustHighLats == OneSeventh)
		val =1.0/7.0;

	return val;
}
//------------------------------------------------------------------------------
//----------------------------------------------------------------------------
//------------------------------------------------------------------------------
//public double [] dayPortion ( double [] times)
//{
//    for ( int i = 0 ; i < times . Length ; i++ )
//    {
//        times [ i ] /= 24;
//    }
//	return times;
//}



//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// compute prayer times at given julian date
void PrayTime::computeDayTimes (void)
{
	

    //for ( int i = 0 ; i < this . numIterations ; i++ )
    //{
         computeTimes ();//times = computeTimes ();
   // }

	adjustTimes();              //times = adjustTimes(times);           
	
//		temp.temp1=times[0];
//		temp.temp2=times[1];
//    temp.temp3=times[2];
//		while(1);
	adjustTimesFormat();        //return adjustTimesFormat(times);                  
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// adjust times in a prayer time array
void  PrayTime::adjustTimes  ( void)
{
 
	
    for ( int i = 0 ; i < 7 ; i++ )
    {
        times [ i ] += timeZone - lng / 15;
         
    }
		
//		temp.temp1=times[0];
//		temp.temp2=times[1];
//    temp.temp3=times[2];
//		while(1);

  	times[2] += dhuhrMinutes/ 60; //Dhuhr
  	if (methodParams[calcMethod][1] == 1) // Maghrib
		times[5] = times[4]+ methodParams[calcMethod][2]/ 60.0;
		
	if (methodParams[calcMethod][3] == 1) // Isha
		times[6] = times[5]+ methodParams[calcMethod][4]/ 60.0;

    if ( adjustHighLats != None )
    {
        adjustHighLatTimes();//times = adjustHighLatTimes ();
    }

//	return times;
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void PrayTime::adjustTimesFormat (void)
{
//	String [] formatted = new String [times.Length];

//	if (this.timeFormat == Floating)
//		{
//			for	( int i = 0 ; i < times.Length ; ++i )
//			{
//				formatted [i] = times[i]+"";
//			}
//			return formatted;
//		}
//        for ( int i = 0 ; i < 7 ; i++ )
//        {
//            if ( this . timeFormat == Time12 )
//                formatted [ i ] = this . floatToTime12 ( times [ i ] , true );
//            else if ( this . timeFormat == Time12NS )
//                formatted [ i ] = this . floatToTime12NS ( times [ i ] );
//            else
              //formatted [ i ] = floatToTime24 ( times [ i ] );
//        }
//	return formatted;
	char hor,min;
	
	floatToTime24(times[0] , &hor , &min);
  tim.fajr_hor=hor;
  tim.fajr_min=min;

	floatToTime24(times[1] , &hor , &min);
  tim.sunrise_hor=hor;
  tim.sunrise_min=min;
	
	floatToTime24(times[2] , &hor , &min);
  tim.dhihr_hor=hor;
  tim.dhuhr_min=min;
	
	floatToTime24(times[3] , &hor , &min);
  tim.asr_hor=hor;
  tim.asr_min=min;
	
	floatToTime24(times[4] , &hor , &min);
  tim.sunset_hor=hor;
  tim.sunset_min=min;
	
	floatToTime24(times[5] , &hor , &min);
  tim.maghrib_hor=hor;
  tim.maghrib_min=min;
	
	floatToTime24(times[6] , &hor , &min);
  tim.isha_hor=hor;
  tim.isha_min=min;
	 
//	floatToTime24(times[0] , &hor , &min);
//  tim.sunset_hor=hor;
//  tim.sunset_min=min;
//	
// 
	
	
	
}
////--------------------------------------------------------------------------
////--------------------------------------------------------------------------
////--------------------------------------------------------------------------
////---------------------- Misc Functions -----------------------

//////////////////////	// compute the difference between two times
//////////////////////	public double GetTimeDifference (double c1 , double c2)
//////////////////////	{
//////////////////////		double diff = this.FixHour(c2 - c1);;
//////////////////////		return diff;
//////////////////////	}

//	// add a leading 0 if necessary
//	public String twoDigitsFormat ( int num)
//	{

//		return (num <10) ? "0"+ num : num+"";
//	}




//--------------------------------------------------------------------
//--------------------------------------------------------------------
//---------------------- Julian Date Functions -----------------------
// calculate julian date from a calendar date
double PrayTime::JulianDate ( int year , int month , int day )
    {
        if ( month <= 2 )
        {
            year -= 1;
            month += 12;
        }
        double A = ( double ) floor ( year / 100.0 );
        double B = 2 - A + floor ( A / 4 );

        double JD = floor ( 365.25 * ( year + 4716 ) ) + floor ( 30.6001 * ( month + 1 ) ) + day + B - 1524.5;
        return JD;
    }
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//---------------------- Time-Zone Functions -----------------------

//	
//	// detect daylight saving in a given date
//	public bool UseDayLightaving ( int year, int month , int day )
//	{
//        return TimeZone . CurrentTimeZone . IsDaylightSavingTime ( new DateTime ( year , month , day ) ); 
//	}

//--------------------------------------------------------------
//--------------------------------------------------------------
//-------------------------------------------------------------
double PrayTime::FixAngle ( double angel )
	{
		angel = angel - 360.0 * (floor(angel / 360.0));
		angel = angel < 0 ? angel + 360.0 : angel;
		return angel;
	}
//--------------------------------------------------------------
//--------------------------------------------------------------
//-------------------------------------------------------------
	// range reduce hours to 0..23
	double PrayTime::FixHour ( double hour )
	{
		hour = hour - 24.0 * (floor(hour / 24.0));
		hour = hour < 0 ? hour + 24.0 : hour;
		return hour;
	}
//--------------------------------------------------------------
//--------------------------------------------------------------
//-------------------------------------------------------------
	
	