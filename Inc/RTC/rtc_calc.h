
//#ifndef __STM32F0xx_IT_H
//#define __STM32F0xx_IT_H

//#ifdef __cplusplus
// extern "C" {
//#endif 



	 
	 #ifndef __RTC_CALC_H
#define    __RTC_CALC_H

#ifdef __cplusplus
 extern "C" {
#endif 


//#define PI 3.14159265358979
//#define rads PI/180
//#define ZENITH -.83
	 
	 
	 
	 	struct TIME_{
		unsigned char hour;
		unsigned char min;  //not used
		unsigned char sec;  //not used
	};
		
	

class DATE_CALC{
	public:
	  void milady_to_shamsy(int,int,int);
    void shamsy_to_milady(int,int,int);
   // void cal_sunset_sunrise(float,float);
	//void set_shamsi(int year,int mont,int day){sh.year=year;sh.month=mont;sh.day_of_mont=day;}
	//void set_miladi(int year,int mont,int day){mi.year=year;mi.month=mont;mi.day_of_mont=day;}
	//float calculateSunriseSunset(int , int ,int, float , float , int , int , bool );
   char check_day_shamsi(int,char); // if summer 31day winter 30day kabise 29day
	
	char cal_on_off_out(TIME_,TIME_,TIME_);
  
	struct SUN_SET_SUN_RISE{
		int sun_rise_hor;
		int sun_rise_min;
		int sun_set_hor;
		int sun_set_min;
	}ss;//sunset sunrise
	
	struct SHAMSI{
		int year;
		int month;
    int	day_of_mont;//day;
		int day_of_week;//sh_day; 
		int day_of_year;
	}sh;
	struct MILADI{
		int year;
		int month;
    int	day_of_mont;//day;
		int day_of_week;//sh_day; 
	}mi;
  
	struct TIME{
		unsigned char hour;
		unsigned char min;  //not used
		unsigned char sec;  //not used
	}ti;
   
		


		private:	
		int grgisleap (int year);
    int hshisleap(int year);
//    float FNday (void);
//    float FNrange (float x); 
//	  float f0(float lat, float declin); 

    //float L0;
}cal;


#ifdef __cplusplus
}
#endif

#endif 

