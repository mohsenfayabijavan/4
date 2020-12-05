

#include <rtc_calc.h>

#include <stdio.h> 
//#include <main.h>

//##################################################################################
//                                    function                                 
//##################################################################################

//##################################################################################
//                                    function                                 
//##################################################################################
void DATE_CALC::milady_to_shamsy(int m_year,int m_month,int m_day)
{
//   //==past day of year
 int pdayofyear , m_year_;
//                           //==shamsy past day of year
 
	bool isleapyear;
 char mmonth[]={31,28,31,30,31,30,31,31,30,31,30,31};
 int temp1 , temp2 , temp3 , temp4 , j;
 m_year+=2000;
 pdayofyear=0;
 temp1=m_year % 4;
 temp2=m_year % 100;
 temp3=m_year % 400 ;
 temp4=temp1 & temp2;
 if (temp4 !=0 || temp3==0)
  {
   mmonth[1]=28 ;
  }
  else
  {
   mmonth[1]=29  ;
  };
  //putchar(13);putchar(13);putchar(13);
  m_year_=m_year-1;
  temp1=m_year_ % 4;
  temp2=m_year_ % 100;
  temp3=m_year_ % 400 ;
  temp4=temp1 & temp2;
  if (temp4 != 0 || temp3==0)  isleapyear=0;
  else isleapyear=1;
  temp1=m_month-1;
  for(j=1 ; j<=temp1 ; j++) 
  {
   pdayofyear+=mmonth[ j-1 ];
  };
  pdayofyear+=m_day;  
   if(pdayofyear > 79)
  {
     temp1=pdayofyear-79; 
     sh.year=m_year-621;
     if(temp1<=186)
     {
       temp2=temp1%31;
       temp3=temp1/31;
       if (temp2==0)
       {
         sh.month=temp3;
         sh.day_of_mont=31;
       } 
       else
       {
       sh.month=temp3+1;
       sh.day_of_mont=temp2;
      }  ;
    }

   else 
    { 
      temp2=temp1-186;
      temp3=temp2%30;
      temp4=temp2/30;
      if (temp3==0)
      {
        sh.month=temp4+6;
        sh.day_of_mont=30;
      }
      else
      {
        sh.month=temp4+7;
        sh.day_of_mont=temp3;
      };
    } ;
  }
 else 
  {
    sh.year=m_year-622;
    if (isleapyear==1) 
    {
      pdayofyear+=11;
    }
    else
    {    
      pdayofyear+=10;
    } ;
    temp2=pdayofyear%30;
    temp3=pdayofyear/30;
    if (temp2==0)
    {
      sh.month=temp3+9;
      sh.day_of_mont=30;
    }
    else 
    {
      sh.month=temp3+10;
      sh.day_of_mont=temp2;
    }    
    HAL_Delay(1);
  }  
  //shyear
  //shmonth
  //shday  
  sh.day_of_week=sh.day_of_mont%2;
	
	//---calc day_of_year
	if( sh.month < 7)
	{
		sh.day_of_year=(sh.month*31) + sh.day_of_mont;
		
	}else
	{
		sh.day_of_year=(6*31) + ((sh.month-6)*30) + sh.day_of_mont;
	}
	//-------------------
}


//---------------------------------------------------------------------------------
void DATE_CALC::shamsy_to_milady(int hshyear,int hshmonth,int hshday)                                      
{   
 int hshleap , grgleap , hshelapsed,  grgelapsed ,i;
 int grgsumofdays[2][13]={{0,31,59,90,120,151,181,212,243,273,304,334,365},{0,31,60,91,121,152,182,213,244,274,305,335,366}};
 int hshsumofdays[2][13]={{0,31,62,93,124,155,186,216,246,276,306,336,365},{0,31,62,93,124,155,186,216,246,276,306,336,366}};
 mi.year=hshyear+621;    
 hshleap = hshisleap (hshyear);
 grgleap=grgisleap(mi.year);  
 hshelapsed=  hshsumofdays [hshleap ? 1:0] [hshmonth-1]+hshday;  
 if (hshmonth>10||(hshmonth==10&& hshelapsed>286+(grgleap?1:0))) 
  {
    grgelapsed= hshelapsed-(286+(  grgleap?1:0));
   grgleap=grgisleap (++mi.year);
  }
  else
  {  
   hshleap=  hshisleap (hshyear-1);
   grgelapsed=   hshelapsed+79+(hshleap?1:0)-(  grgisleap(mi.year-1)?1:0);
  };   
  for (i=1;i<=12;i++) 
  {
    if(grgsumofdays[grgleap?1:0][i]>=grgelapsed) 
    {
     mi.month=i;
     mi.day_of_mont=  grgelapsed-  grgsumofdays[grgleap?1:0][i-1];
     break;
    }
  };
}; 
//----------------------------------------------------------------------------------
int DATE_CALC::grgisleap(int  year)  
{
 return((year%4)==0&&((year%100)!=0||(year%400)==0));
} ;
//----------------------------------------------------------------------------------
int DATE_CALC::hshisleap(int year)
{
 year=(year-474)%128;
 year=((year>=30)?29:0)+year;
 year=year-floor((float)(year/33))-1;
 return((year%4)==0);
};
//----------------------------------------------------------------------------------
//void DATE_CALC::cal_sunset_sunrise(float Longitude,float Latitude)
//{
// float riset, settm;
// float tzone=3.5;
// float j_d,landa,obliq,alpha,delta,LL,equation,ha;
// float L0;
// j_d=FNday(); 
// 
//	//----------------------------------
//	float L = FNrange(280.461 * rads + .9856474 * rads * j_d);
//  float g = FNrange(357.528 * rads + .9856003 * rads * j_d);
//  L0=L;
//  landa= FNrange(L + 1.915 * rads * sin(g) + .02 * rads * sin(2 * g)); 
//	//---------------------------------
//	
//	
//	obliq = 23.439 * rads - .0000004 * rads * j_d;
// alpha = atan2(cos(obliq) * sin(landa), cos(landa));
// delta = asin(sin(obliq) * sin(landa));
// LL = L0 - alpha;
// if (L0 < PI) LL += 2.0*PI;
// equation = 1440.0 * (1.0 - LL / PI/2.0);
// ha = f0(Latitude,delta);
// riset = 12.0 - 12.0 * ha/PI + tzone - Longitude/15.0 + equation/60.0;
// settm = 12.0 + 12.0 * ha/PI + tzone - Longitude/15.0 + equation/60.0;  
// ss.sun_rise_hor=(int)riset;
// ss.sun_rise_min=(int)((riset-ss.sun_rise_hor)*60);
// ss.sun_set_hor=(int)settm;
// ss.sun_set_min=(int)((settm-ss.sun_set_hor)*60); 
//  if (1<=sh.month)
//   if(sh.month<7)
//   {
//    ss.sun_rise_hor++;  
//    ss.sun_set_hor++;
//   } 
// }
//----------------------------------------------------------------------------------
//float DATE_CALC::FNday (void)
//{
//float luku = - 7 * ((mi.year+2000) + (mi.month + 9)/12)/4 + 275*mi.month/9 + mi.day_of_mont;
//luku+=(mi.year+2000)*3.67*100;
//return luku - 730531.5 + ti.hour/24.0;
//};
//----------------------------------------------------------------------------------
//float DATE_CALC::FNsun (float d)
// { 
// 
//  float L = FNrange(280.461 * rads + .9856474 * rads * d);
//  float g = FNrange(357.528 * rads + .9856003 * rads * d);
//  L0=L;
//  return FNrange(L + 1.915 * rads * sin(g) + .02 * rads * sin(2 * g));
// };
//----------------------------------------------------------------------------------
//float DATE_CALC::FNrange (float x)
// {
//   float b = 0.5*x / PI;
//   float a = 2.0*PI * (b - (int)(b));
//   if (a < 0) a = 2.0*PI + a;
//   return a;
// };
//----------------------------------------------------------------------------------
//float DATE_CALC::f0(float lat, float declin)
// {
//  float fo,dfo,SunDia = 0.53, AirRefr =34.0/60.0 ;
//  dfo = rads*(0.5*SunDia + AirRefr);
//  if (lat < 0.0) dfo = -dfo;
//  fo = tan(declin + dfo) * tan(lat*rads);
//  if (fo>0.99999) fo=1.0; // to avoid overflow //
//  fo = asin(fo) + PI/2.0;
//  return fo;
//	 
// }; 
// 
//##################################################################################
//                                    function                                 
//##################################################################################
 char DATE_CALC::check_day_shamsi(int year,char mont )
 {
   //1391   
	 if(mont <= 6 )  //sumer
	 {
		 return 31;			 
	 }
	 else if(mont > 6 &&  mont < 13) //winter
	 {
		 if( (year == 1391 || year == 1395 || year == 1399 || year == 1403) && mont==12)
		 {
       return 29; 
		 }			
		 else return 30;
	 }
	 else return 0;
	 
	// return 0;
	 
 }
//##################################################################################
//                                    function                                 
//##################################################################################


//##################################################################################
//                                    function                                 
//##################################################################################
 char DATE_CALC::cal_on_off_out(TIME_ now,TIME_ on,TIME_ off)
 {
	 
	 
   unsigned long	 t_now= (now.hour*60) + now.min;
	 unsigned long	 t_on=   (on.hour*60)+ on.min;
	 unsigned long	 t_off=   (off.hour*60  )+ off.min;
	 

	 if(t_off > t_on)
	 {
            if(t_now < t_on)  return 0;		  
		   else if(t_now < t_off) return 1;
		   else                   return 0;
	 }
	 else if(t_off < t_on)
	 {
		      if(t_now >= t_on )return 1; 
		 else if(t_now < t_off )return 1; 
		 else                  return 0;
		 
	 };
return 0;
}
//##################################################################################
//                                    function                                 
//##################################################################################




//##################################################################################
//                                    function                                 
//##################################################################################




//##################################################################################
//                                    function                                 
//##################################################################################




//##################################################################################
//                                    function                                 
//##################################################################################





//##################################################################################
//                                    function                                 
//##################################################################################





//##################################################################################
//                                    function                                 
//##################################################################################

