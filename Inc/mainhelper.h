
#include "string.h"

#define CancelNumber 254






class MAINHELPER{
	public:
	char buf[20];
	long temp1,temp2,temp3;
	
	
	char str_find(char*  , char*  , int  , int );
	char valu_number(long);
	void key_pressed_up(char,int,int);
//	void debons(char,int); 
	char menu (unsigned char);
	
	void change_on_time (void);
	void change_off_time(void);
	void change_time(void);
    void change_date(void);
	void change_lite_long(void);
	
	
	void change_Latitudes(void);
	void change_Longitude(void);
	
	long  change_number (char*,char*,long,int,long);
	
	unsigned long lite_calc(void);
	void cal_on_off_time(void);
	void sum_or_sub_time(TIME_*,char,char,char,char,char);
	
	
	void hide_menu (unsigned char);
	void max_lite_change (void);
	void min_lite_change (void);
	void max_lite_persent_change (void);
	void min_lite_persent_change (void);
	
	
}mh;
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
	void MAINHELPER::key_pressed_up(char keyy=1,int delayy=10,int tryy=2)
{
	while( tryy--)
	{
      while(key.read() == keyy) delay(delayy);
    }
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
char MAINHELPER::valu_number(long x)
{
	if (x<10) return 1;
	if (x<100) return 2;
	if (x<1000) return 3;
	if (x<10000) return 4;
	if (x<100000) return 5;
	if (x<1000000) return 6;
	
	return 0;
	
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
char MAINHELPER::str_find(char *buff , char *text , int start=0 , int stop=0)  
{
	int i; 
	
	int size_text  = strlen((char*)text);
	int size_buff  = strlen((char*)buff);
	int cnt=0;
	int   ii , z;
	
	
	if(stop == 0) stop=size_buff; 
	  
	
	
	 for(  i=start ; i<stop ; i++)
	 {
		 if(buff[i] == text[0])
		 {
			 for(  ii = i   ,z = 0 ,cnt=0 ;    z < size_text   ;     z++ , ii++)
			 {
				 if(buff[ii] == text[z] )
				 {
					 cnt++;
					 if(cnt == size_text)
					 {
						 //glcd.clear();
						 //sprintf(buf2 , " ii=%u z=%u ",ii,z);
						 
             //glcd.print(buf2);		
              return i;
						 
					 }
					 
				 }
			 }
			 
		 }
	 }
	 
	 return 255;
	
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
char MAINHELPER::menu (unsigned char locate=0)
{
	char buf[32];
  unsigned int cont=0;
  		
	//char *mem[]={"ON TIME","OFF TIME","TIME","DATE","Longitude","Latitudes"};
	do{

		        if(key.read() == key.up  ) {key_pressed_up(key.up);  if(locate)locate--;cont=0;}  
		   else if(key.read() == key.down) {key_pressed_up(key.down);if(locate<7)locate++;cont=0;}

			 //------------------ON TIME-------------------------------
			 if(locate == 0 && cont==1)
			 {
				 lcd.Clear();
         lcd.show("   ON TIME",0,0);			 
				 if(var.ontime_mode      == var.fix)     sprintf(buf,"%s= %u:%u","Fix"     ,var.OnTimeHour,var.OnTimeMin);
				 else if(var.ontime_mode == var.sun_set) sprintf(buf,"%s=%s%u:%u","SunSet" ,(var.OnTimePosNeg)?"+":"-",var.OnTimeHour,var.OnTimeMin);
				 else if(var.ontime_mode == var.sun_rise)sprintf(buf,"%s=%s%u:%u","SunRise",(var.OnTimePosNeg)?"+":"-",var.OnTimeHour,var.OnTimeMin);
				 lcd.show(buf,1,0);
			 }	
			 //---------------------OFF TIME---------------------
       else if(locate == 1 && cont==1)
			 {
				 lcd.Clear();
         lcd.show("   OFF TIME",0,0);
				 if(var.offtime_mode == var.fix          )sprintf(buf,"%s= %u:%u","Fix"     ,var.OffTimeHour,var.OffTimeMin);
				 else if(var.offtime_mode == var.sun_set )sprintf(buf,"%s=%s%u:%u","SunSet" ,(var.OnTimePosNeg)?"+":"-",var.OffTimeHour,var.OffTimeMin);
				 else if(var.offtime_mode == var.sun_rise)sprintf(buf,"%s=%s%u:%u","SunRise",(var.OnTimePosNeg)?"+":"-",var.OffTimeHour,var.OffTimeMin);
				 lcd.show(buf,1,0);
			 }			 
			 //----------------------TIME------------------------------
       else if(locate == 2 && cont==1)
			 {
				 lcd.Clear();
         lcd.show("   TIME",0,0);
         lcd.show(rtc.hour,1,0);lcd.show(":");lcd.show(rtc.min);
			 }	
			 //--------------------date--------------------------------
			 else if(locate == 3 && cont==1)
			 {
				 lcd.Clear();
         lcd.show("   DATE",0,0);
				 cal.milady_to_shamsy(rtc.year,rtc.mont,rtc.day_of_mont);
				 sprintf(buf,"%u/%u/%u",cal.sh.year,cal.sh.month,cal.sh.day_of_mont);lcd.show(buf,1,0);
			 }	
			 //--------------------------------------------------------
       else if(locate == 4 && cont==1)
			 {
				 lcd.Clear();
         lcd.show("   Longitude",0,0);
				 sprintf(buf,"%u.%u",((char)var.longitude),(var.longitude*100)-(((char)var.longitude)*100)   );
				 lcd.show(buf,1,0);
			 
			 }	
			 //--------------------------------------------------------
       else if(locate == 5 && cont==1)
			 {
				 lcd.Clear();
         lcd.show("   Latitudes",0,0);
				 sprintf(buf,"%u.%u",((char)var.latitudes),((var.latitudes*100)-(((char)var.latitudes)*100)));
				 lcd.show(buf,1,0);
			 }	
			 //--------------------------------------------------------
			 else if(locate == 6 && cont==1)
			 {
				 lcd.Clear();
         lcd.show("   LITE LONG TIME",0,0);
         lcd.show(var.LiteLong/60,1,0);lcd.show(":");lcd.show(var.LiteLong%60);
			 }	
			 //--------------------------------------------------------
			 else if(locate == 7 && cont==1)
			 {
				 lcd.Clear();
         lcd.show("   Exit",0,0);
			 }	
			 //--------------------------------------------------------
       else if(key.read() == key.set)
			 {
				 key_pressed_up(key.set);
				 if(locate == 0){change_on_time();cont=0;}
				 if(locate == 1){change_off_time();cont=0;}
				 if(locate == 2){change_time();cont=0;}
				 if(locate == 3){change_date();cont=0;}
				 if(locate == 4){change_Longitude();cont=0;}
				 if(locate == 5){change_Latitudes();cont=0;}
				 if(locate == 6){change_lite_long();cont=0;}
				 if(locate == 7) return 1;
			 }
  // cont++;
	delay(1);
	}while(cont++ < 10000);		
		
	
		
		
	return 0;
	}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::change_on_time(void)
{
	int  cont=0;
	char ontime_mode=var.ontime_mode;
	bool OnTimePosNeg=var.OnTimePosNeg;
  char OnTimeHour=var.OnTimeHour;
	char OnTimeMin =var.OnTimeMin;
	
	
	
	//ontime_mode=1;
	
	do{
		       if(key.read() == key.up  ) {key_pressed_up(key.up);  if(ontime_mode >= 2) ontime_mode=0;else ontime_mode++;cont=0;}  
		  else if(key.read() == key.down) {key_pressed_up(key.down);if(ontime_mode == 0) ontime_mode=2;else ontime_mode--;cont=0;}
		  
			if(cont == 0)
			{
				lcd.Clear();
        lcd.show("ON TIME",0,0);
				     if(ontime_mode == var.fix)     sprintf(buf,"%s= %u:%u","<Fix>"     ,OnTimeHour,OnTimeMin);
				else if(ontime_mode == var.sun_set) sprintf(buf,"%s=%s%u:%u","<SunSet>" ,(OnTimePosNeg)?"+":"-",OnTimeHour,OnTimeMin); 
				else if(ontime_mode == var.sun_rise)sprintf(buf,"%s=%s%u:%u","<SunRise>",(OnTimePosNeg)?"+":"-",OnTimeHour,OnTimeMin); 
				lcd.show(buf,1,0);
			}
			//11111111111111111111111111111
			if(key.read() == key.set)
			{
				key_pressed_up(key.set);
				cont=0;
				do{		
					
					       if(key.read() == key.up  ) {key_pressed_up(key.up);  if(OnTimePosNeg==0) OnTimePosNeg=1;else OnTimePosNeg=0;cont=0;}  
		        else if(key.read() == key.down) {key_pressed_up(key.down);if(OnTimePosNeg)    OnTimePosNeg=0;else OnTimePosNeg=1;cont=0;}
		  
			      if(cont == 0)
						{
				      lcd.Clear();
              lcd.show("ON TIME",0,0);
				      if(ontime_mode == var.fix)          sprintf(buf,"%s= %u:%u","Fix"       ,OnTimeHour,OnTimeMin); 
				      else if(ontime_mode == var.sun_set) sprintf(buf,"%s=<%s>%u:%u","SunSet" ,(OnTimePosNeg)?"+":"-",OnTimeHour,OnTimeMin); 
				      else if(ontime_mode == var.sun_rise)sprintf(buf,"%s=<%s>%u:%u","SunRise",(OnTimePosNeg)?"+":"-",OnTimeHour,OnTimeMin); 
				      lcd.show(buf,1,0);
						}
					  //22222222222222222222222222222
						if(key.read() == key.set || ontime_mode == var.fix)
						{
				      key_pressed_up(key.set);
				      cont=0;
				    do{
							      if(key.read() == key.up  ) {key_pressed_up(key.up);  if(OnTimeHour<23) OnTimeHour++;else OnTimeHour=0;cont=0;}  
		           else if(key.read() == key.down) {key_pressed_up(key.down);if(OnTimeHour==0)    OnTimeHour=23;else OnTimeHour--;cont=0;}
				
							 if(cont == 0)
			         {
				         lcd.Clear();
                 lcd.show("ON TIME",0,0);
	                    if(ontime_mode == var.fix     )sprintf(buf,"%s= <%u>:%u","Fix"     ,OnTimeHour,OnTimeMin);
				         else if(ontime_mode == var.sun_set )sprintf(buf,"%s=%s<%u>:%u","SunSet" ,(OnTimePosNeg)?"+":"-",OnTimeHour,OnTimeMin);
 				         else if(ontime_mode == var.sun_rise)sprintf(buf,"%s=%s<%u>:%u","SunRise",(OnTimePosNeg)?"+":"-",OnTimeHour,OnTimeMin);								 
				         lcd.show(buf,1,0);
							 }
					     //33333333333333333333333333
							 if(key.read() == key.set )
							 {
				        key_pressed_up(key.set);
				        cont=0;
				        do{
							            if(key.read() == key.up  ) {key_pressed_up(key.up);  if(OnTimeMin<59) OnTimeMin++;else OnTimeMin=0;cont=0;}  
		                else if(key.read() == key.down) {key_pressed_up(key.down);if(OnTimeMin==0)    OnTimeMin=59;else OnTimeMin--;cont=0;}
		  
		                if(cont == 0)
		                {
		                  lcd.Clear();
		                  lcd.show("ON TIME",0,0);
		                       if(ontime_mode == var.fix     )sprintf(buf,"%s= %u:<%u>" ,"Fix"    ,OnTimeHour,OnTimeMin); 
		                  else if(ontime_mode == var.sun_set )sprintf(buf,"%s=%s%u:<%u>","SunSet" ,(OnTimePosNeg)?"+":"-",OnTimeHour,OnTimeMin); 
		                  else if(ontime_mode == var.sun_rise)sprintf(buf,"%s=%s%u:<%u>","SunRise",(OnTimePosNeg)?"+":"-",OnTimeHour,OnTimeMin); 
		                  lcd.show(buf,1,0);
										}
					     //4444444444444444444444444444
							       if(key.read() == key.set )
										 {
											 key_pressed_up(key.set,10,3);
											 
											 
											 
											 var.ontime_mode=ontime_mode;
	                     var.OnTimePosNeg=OnTimePosNeg;
	                     var.OnTimeHour=OnTimeHour;
	                     var.OnTimeMin=OnTimeMin;
											 
											 var.update_eeprom();
											 
											 
											 
											 return;
										 }
							 //4444444444444444444444444444
                    cont++;delay(1);
									}while(cont<5000);
								}
							 //33333333333333333333333333
               cont++;delay(1);
						 }while(cont<5000);
					 }
						//22222222222222222222222222222222
         cont++;delay(1);
				}while(cont<5000);
			}
      //1111111111111111111111111111111			
		cont++;delay(1);
	}while(cont<5000);
	
	

}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::change_off_time(void)
{
	int  cont=0;
	char offtime_mode=var.offtime_mode;
	bool OffTimePosNeg=var.OffTimePosNeg;
    char OffTimeHour=var.OffTimeHour;
	char OffTimeMin =var.OffTimeMin;
	
	
	//offtime_mode=1;
	
	do{
		       if(key.read() == key.up  ) {key_pressed_up(key.up);  if(offtime_mode >= 2) offtime_mode=0;else offtime_mode++;cont=0;}  
		  else if(key.read() == key.down) {key_pressed_up(key.down);if(offtime_mode == 0) offtime_mode=2;else offtime_mode--;cont=0;}
		  
			if(cont == 0)
			{
				lcd.Clear();
        lcd.show("ON TIME",0,0);
				     if(offtime_mode == var.fix     )sprintf(buf,"%s= %u:%u","<Fix>"     ,OffTimeHour,OffTimeMin);
				else if(offtime_mode == var.sun_set )sprintf(buf,"%s=%s%u:%u","<SunSet>" ,(OffTimePosNeg)?"+":"-",OffTimeHour,OffTimeMin);
        else if(offtime_mode == var.sun_rise)sprintf(buf,"%s=%s%u:%u","<SunRise>",(OffTimePosNeg)?"+":"-",OffTimeHour,OffTimeMin);				
				lcd.show(buf,1,0);
			}
			//11111111111111111111111111111
			if(key.read() == key.set)
			{
				key_pressed_up(key.set);
				cont=0;
				do{
					
					       if(key.read() == key.up  ) {key_pressed_up(key.up);  if(OffTimePosNeg==0) OffTimePosNeg=1;else OffTimePosNeg=0;cont=0;}  
		        else if(key.read() == key.down) {key_pressed_up(key.down);if(OffTimePosNeg)    OffTimePosNeg=0;else OffTimePosNeg=1;cont=0;}
		  
			      if(cont == 0)
						{
				      lcd.Clear();
              lcd.show("ON TIME",0,0);
				           if(offtime_mode == var.fix)     sprintf(buf,"%s= %u:%u","Fix"       ,OffTimeHour,OffTimeMin);
				      else if(offtime_mode == var.sun_set) sprintf(buf,"%s=<%s>%u:%u","SunSet" ,(OffTimePosNeg)?"+":"-",OffTimeHour,OffTimeMin); 
							else if(offtime_mode == var.sun_rise)sprintf(buf,"%s=<%s>%u:%u","SunRise",(OffTimePosNeg)?"+":"-",OffTimeHour,OffTimeMin); 
							
				      lcd.show(buf,1,0);
						}
					  //22222222222222222222222222222
						if(key.read() == key.set || offtime_mode == var.fix)
						{
				      key_pressed_up(key.set);
				      cont=0;
				    do{
							      if(key.read() == key.up  ) {key_pressed_up(key.up);  if(OffTimeHour<23) OffTimeHour++;else OffTimeHour=0;cont=0;}  
		           else if(key.read() == key.down) {key_pressed_up(key.down);if(OffTimeHour==0)    OffTimeHour=23;else OffTimeHour--;cont=0;}
		  
							 if(cont == 0)
			         {
				         lcd.Clear();
                 lcd.show("ON TIME",0,0);
	                    if(offtime_mode == var.fix     )sprintf(buf,"%s= <%u>:%u","Fix"     ,OffTimeHour,OffTimeMin);
				         else if(offtime_mode == var.sun_set )sprintf(buf,"%s=%s<%u>:%u","SunSet" ,(OffTimePosNeg)?"+":"-",OffTimeHour,OffTimeMin); 
								 else if(offtime_mode == var.sun_rise)sprintf(buf,"%s=%s<%u>:%u","SunRise",(OffTimePosNeg)?"+":"-",OffTimeHour,OffTimeMin);
				         lcd.show(buf,1,0);
							 }
					     //33333333333333333333333333
							 if(key.read() == key.set )
							 {
				        key_pressed_up(key.set);
				        cont=0;
				        do{
							            if(key.read() == key.up  ) {key_pressed_up(key.up);  if(OffTimeMin<59) OffTimeMin++;else OffTimeMin=0;cont=0;}  
		                else if(key.read() == key.down) {key_pressed_up(key.down);if(OffTimeMin==0)    OffTimeMin=59;else OffTimeMin--;cont=0;}
		  
		                if(cont == 0)
		                {
		                  lcd.Clear();
		                  lcd.show("ON TIME",0,0);
		                  if(offtime_mode == var.fix          )sprintf(buf,"%s= %u:<%u>","Fix"     ,OffTimeHour,OffTimeMin);
		                  else if(offtime_mode == var.sun_set )sprintf(buf,"%s=%s%u:<%u>","SunSet" ,(OffTimePosNeg)?"+":"-",OffTimeHour,OffTimeMin); 
										  else if(offtime_mode == var.sun_rise)sprintf(buf,"%s=%s%u:<%u>","SunRise",(OffTimePosNeg)?"+":"-",OffTimeHour,OffTimeMin); 
		                  lcd.show(buf,1,0);
										}
					     //4444444444444444444444444444
							       if(key.read() == key.set )
										 {
											 key_pressed_up(key.set,10,3);
											 
											 
											 
											 var.offtime_mode=offtime_mode;
	                     var.OffTimePosNeg=OffTimePosNeg;
	                     var.OffTimeHour=OffTimeHour;
	                     var.OffTimeMin=OffTimeMin;
											 
											 var.update_eeprom();
											 
											 
											 
											 return;
										 }
							 //4444444444444444444444444444
                    cont++;delay(1);
									}while(cont<5000);
								}
							 //33333333333333333333333333
               cont++;delay(1);
						 }while(cont<5000);
					 }
						//22222222222222222222222222222222
         cont++;delay(1);
				}while(cont<5000);
			}
      //1111111111111111111111111111111			
		cont++;delay(1);
	}while(cont<5000);
	
	

	
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::change_time(void)
{
  char TimeHour=rtc.hour;
	char TimeMin =rtc.min;
	
	sprintf(buf,"%%u:%u",TimeMin);
	TimeHour=change_number("TIME",buf,TimeHour,0,23);
	if(TimeHour == CancelNumber) return;
	
	sprintf(buf,"%u:%%u",TimeHour);
	TimeMin=change_number("TIME",buf,TimeMin,0,59);
	if(TimeMin == CancelNumber) return;
	

  rtc.hour=TimeHour;
  rtc.min=TimeMin;
  rtc.set_time(rtc.year,rtc.mont,rtc.day_of_mont,TimeHour,TimeMin);
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::change_date(void)
{
	
	int  Year =cal.sh.year;
  char mont =cal.sh.month;
  char day  =cal.sh.day_of_mont;
	
	sprintf(buf,"%%u/%u/%u",mont,day);
	Year=change_number("DATE",buf,Year,1390,1450);
	if(Year == CancelNumber)return;
	
	sprintf(buf,"%u/%%u/%u",Year,day);
	mont=change_number("DATE",buf,mont,1,12);
	if(mont == CancelNumber)return;
	
	sprintf(buf,"%u/%u/%%u",Year,mont);
	day=change_number("DATE",buf,day,1,cal.check_day_shamsi(Year,mont));
	if(day==CancelNumber)return;
 
	
  cal.shamsy_to_milady(Year,mont,day);
  rtc.set_time( cal.mi.year,cal.mi.month,cal.mi.day_of_mont,rtc.hour,rtc.min,rtc.sec);
  rtc.year=cal.mi.year-2000;
  rtc.mont=cal.mi.month;
  rtc.day_of_mont=cal.mi.day_of_mont;								
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::change_lite_long(void)
{
	char sec = var.LiteLong%60;
	char min = var.LiteLong/60;
	

	sprintf(buf,"%%u:%u",sec);
	min=change_number("LITE LONG TIME",buf,min,0,59);
	if( sec == CancelNumber)return;
			
	sprintf(buf,"%u:%%u",min);
	sec=change_number("LITE LONG TIME",buf,sec,0,59);
	if(min == CancelNumber)return;
	
	if(((min*60)+sec) < 3600)var.LiteLong = (min*60)+sec;
	ee.write_int (var.LiteLong ,ee._LiteLong);
	
	
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::change_Longitude (void)
{
 // long xs   =
	                               // 28.69
	char x1  =(char)var.longitude; // 28       
  char x2  =((var.longitude*100)-(((char)var.longitude)*100));    


	
	sprintf(buf,"%%u.%u",x2);
	x1=change_number("Longitude",buf,x1,0,99);
	if( x1 == CancelNumber)return;
	
	sprintf(buf,"%u.%%u",x1);
	x2=change_number("Longitude",buf,x2,0,99);
	if( x2 == CancelNumber)return;
	
	

	var.longitude = x1 + (float)x2/100;
	
	
	var.update_eeprom();    
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::change_Latitudes(void)
{
	
  long xs   =((var.latitudes*100)-(((char)var.latitudes)*100));
	                               // 28.691217
	char x1  =(char)var.latitudes; // 28       
  char x2  =xs  ;         // 6
//  char x3  =xs/10000%10;         // 9
//	char x4  =xs/1000 %10;         // 1
//	char x5  =xs/100  %10;         // 2
//	char x6  =xs/10   %10;         // 1
//	char x7  =xs      %10;         // 7
	


	sprintf(buf,"%%u.%u",x2);//,x3,x4,x5,x6,x7);
	x1=change_number("latitudes",buf,x1,0,99);
	if( x1 == CancelNumber)return;
	
	sprintf(buf,"%u.%%u",x1);//,x3,x4,x5,x6,x7);
	x2=change_number("latitudes",buf,x2,0,99);
	if( x2 == CancelNumber)return;
	
//	sprintf(buf,"%u.%u%%u%u%u%u%u",x1,x2,x4,x5,x6,x7);
//	x3=change_number("latitudes",buf,x3,0,9);
//	if( x3 == CancelNumber)return;
//	
//	sprintf(buf,"%u.%u%u%%u%u%u%u",x1,x2,x3,x5,x6,x7);
//	x4=change_number("latitudes",buf,x4,0,9);
//	if( x4 == CancelNumber)return;
//	
//	sprintf(buf,"%u.%u%u%u%%u%u%u",x1,x2,x3,x4,x6,x7);
//	x5=change_number("latitudes",buf,x5,0,9); 
//	if( x5 == CancelNumber)return;
//	
//	sprintf(buf,"%u.%u%u%u%u%%u%u",x1,x2,x3,x4,x5,x7);
//	x6=change_number("latitudes",buf,x6,0,9);
//	if( x6 == CancelNumber)return;
//	
//	sprintf(buf,"%u.%u%u%u%u%u%%u",x1,x2,x3,x4,x5,x6);
//	x7=change_number("latitudes",buf,x7,0,9);
//	if( x7 == CancelNumber)return;

	
	var.latitudes = x1 + 
		       (float)x2/100;

	var.update_eeprom();  
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------

 
//-----------------------------------------------------
//
//text is should be have %u 
//-----------------------------------------------------
 long MAINHELPER::change_number (char* titr,char* text , long number , int min ,long max)
{
	key_pressed_up(key.set,10,5);
	 int cont=0;
	 char dis=0;
	 char arc=200;
	

	char buf[32];
	//--------------change %u to %s ------------------
	char text_[20];
	for(int x = 0; x<20 ; x++) text_[x]=0;
  for (char x=0 ; x < strlen(text); x++)text_[x]=text[x];
	char x=str_find(text,"%u");
  text_[x+1]='s';
	//-------------------------------------------------
//	lcd.Clear();
//	lcd.show(text_,0,0);
//	delay(5000);
	
	
		  do{
			      if(key.read() == key.up  ) {  if(key.debons(key.up)){  if(number<max)  number++;else   number=min; cont=0; delay(key.get_delay());}}
			else if(key.read() == key.down) { if(key.debons(key.down)){  if(number==min) number=max;else number--;   cont=0; delay(key.get_delay());}}
				 if((cont == 0 ) || (dis == 0 )|| (dis == arc))
				 {
					 lcd.Clear();
					 lcd.show(titr,0,0);
					 sprintf(buf,text,number);
					 
					 if(dis < arc)lcd.show(buf,1,0);
					 else
					 {
						 int z=valu_number(number);

						      if(z == 1) sprintf(buf,text_," ");
						 else if(z == 2) sprintf(buf,text_,"  ");
						 else if(z == 3) sprintf(buf,text_,"   ");
						 else if(z == 4) sprintf(buf,text_,"    ");
						 lcd.Clear();
					   lcd.show(titr,0,0);
						 lcd.show(buf,1,0);
					 }
					 
					 
				 }
				 if(key.read() == key.set )
				 {
					 key_pressed_up(key.set,10,5);
					 return number;
				 }
			 
				 
		   delay(1);
			 cont++;
			 dis++;
			 }while(cont < 10000);
			
			 return CancelNumber;
}

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
unsigned long MAINHELPER::lite_calc(void)
{
	char on_off=cal.cal_on_off_out(now_time,on_time,off_time);
	int LiteLong=var.LiteLong;//min*sec ==>  unit is seccond
	long scale=80000/LiteLong;
	long MaxTime=(23*60*60)+(59*60)+59;//one day
	
	long NowTime=now_time.hour*60*60+now_time.min*60+now_time.sec;
	long OnTime  = on_time.hour*60*60 + on_time.min*60;
	long OffTime = off_time.hour*60*60 + off_time.min*60;

	
	if(on_off == 1)
	{
		if( NowTime < OnTime)	NowTime+=MaxTime;				
		  
		long sub =NowTime - OnTime;
		if(sub<LiteLong) return ( (((LiteLong-sub)*scale)))+10000; 
		else           	 return 10000;
  }
	// off lite
	else
	{
		if( NowTime < OffTime)	NowTime+=MaxTime;				
		  
		long sub =NowTime - OffTime;
		if(sub<LiteLong) return (80000 - (((LiteLong-sub)*scale)))+10000; 
		else           	 return 90000;
		
		
		
	}
	
	
//	return 90000;
}

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::cal_on_off_time(void)
{
	char SunSet_hour =pt.tim.sunset_hor;
	char SunSet_min  =pt.tim.sunset_min;	
	char SunRise_hour=pt.tim.sunrise_hor;
  char SunRise_min =pt.tim.sunrise_min;
	
	
	now_time.hour=rtc.hour;
	now_time.min=rtc.min;
	now_time.sec=rtc.sec;
	
	
	
//--------on time
	if(var.ontime_mode == var.fix) 
	{
		on_time.hour=var.OnTimeHour;
		on_time.min =var.OnTimeMin;
	}
	else if(var.ontime_mode == var.sun_set)
		sum_or_sub_time(&on_time,SunSet_hour,SunSet_min,var.OnTimeHour,var.OnTimeMin,var.OnTimePosNeg);
	
	
	else if(var.ontime_mode == var.sun_rise)
		sum_or_sub_time(&on_time,SunRise_hour,SunRise_min,var.OnTimeHour,var.OnTimeMin,var.OnTimePosNeg);	
//--------off time
		if(var.offtime_mode == var.fix) 
	{
		off_time.hour=var.OffTimeHour;
		off_time.min =var.OffTimeMin;
	}
	else if(var.offtime_mode == var.sun_set)
		sum_or_sub_time(&off_time,SunSet_hour,SunSet_min,var.OffTimeHour,var.OffTimeMin,var.OffTimePosNeg);
	
	
	else if(var.offtime_mode == var.sun_rise)
		sum_or_sub_time(&off_time,SunRise_hour,SunRise_min,var.OffTimeHour,var.OffTimeMin,var.OffTimePosNeg);
//----------------
	
	
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::sum_or_sub_time(TIME_* ret,char time1_hour ,char time1_min ,char time2_hour ,char time2_min,char PosNeg)
 {
	  if(PosNeg)
		{
      ret->hour=time1_hour + time2_hour;
      ret->min =time1_min  + time2_min;
		}
		else
		{
      ret->hour=time1_hour - time2_hour;
      ret->min =time1_min  - time2_min;
		}	
		
 }

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void MAINHELPER::hide_menu (unsigned char locate=0)
{
//	char buf[32];
    unsigned int cont=0;
  		
	 
	do{

		        if(key.read() == key.up  ) {key_pressed_up(key.up);  if(locate)locate--;cont=0;}  
		   else if(key.read() == key.down) {key_pressed_up(key.down);if(locate<4)locate++;cont=0;}

			 //----------------------TIME------------------------------
            if(locate == 0 && cont==1)
			 {
				 lcd.Clear();
				 lcd.show("<<MAX LITE>>",0,0);
				 lcd.show(var.max_lite,1,0);
			 }	
			 //--------------------date--------------------------------
			 else if(locate == 1 && cont==1)
			 {
 				 lcd.Clear();
				 lcd.show("<<MIN LITE>>",0,0);
				 lcd.show(var.min_lite,1,0);
			 }	
			 //--------------------------------------------------------
       else if(locate == 2 && cont==1)
			 {
				  lcd.Clear();
				 lcd.show("<<MAX LITE PERSENT>>",0,0);
				 lcd.show(var.max_lite_persent,1,0);
			 }	
			 //--------------------------------------------------------
       else if(locate == 3 && cont==1)
			 {
		  	     lcd.Clear();
				 lcd.show("<<MIN LITE PERSENT>>",0,0);
				 lcd.show(var.min_lite_persent,1,0);
			 }	
            //--------------------------------------------------------
       else if(locate == 4 && cont==1)
			 {
				 lcd.Clear();
				 lcd.show("   Exit",0,0);
			 }	
			 //--------------------------------------------------------
       else if(key.read() == key.set)
			 {
				 key_pressed_up(key.set);
				 if(locate == 0){max_lite_change();cont=0;}
				 if(locate == 1){min_lite_change();cont=0;}
				 if(locate == 2){max_lite_persent_change();cont=0;}
				 if(locate == 3){min_lite_persent_change();cont=0;}
				 if(locate == 4) return ;
			 }
			 
   cont++;
			 delay(1);
	}while(cont < 10000);		
		
	return ;
	}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
 	void MAINHELPER::max_lite_change (void)
	{
		long max_lite = var.max_lite;
		max_lite=change_number("MAX LITE","%u",max_lite,0,90000);

		var.max_lite  = max_lite;
		ee.write_long (var.max_lite ,ee._max_lite);
	}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
 	void MAINHELPER::min_lite_change (void)
	{
        long min_lite = var.min_lite;
		min_lite=change_number("MIN LITE","%u",min_lite,0,90000);

		var.min_lite  = min_lite;
		ee.write_long (var.min_lite ,ee._min_lite);
 
	}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
	void MAINHELPER::max_lite_persent_change (void)
	{
		long max_lite_persent = var.max_lite_persent;
		max_lite_persent=change_number("MAX LITE PERSENT","%u",max_lite_persent,0,100);

		var.max_lite_persent  = max_lite_persent;
		ee.write_char (var.max_lite_persent ,ee._max_lite_persent);

	}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
	void MAINHELPER::min_lite_persent_change (void)
	{
		long min_lite_persent = var.min_lite_persent;
		min_lite_persent=change_number("MIN LITE PERSENT","%u",min_lite_persent,0,100);

		var.min_lite_persent  = min_lite_persent;
		ee.write_char (var.min_lite_persent ,ee._min_lite_persent);


	}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------



//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------



//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------



//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
 VARABEL::VARABEL()
 {
	 
	 
	 
	 
 }


//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void VARABEL::ee_set_Longitude(float longitude) // 0 to 180 degress
{                                               //28.691217
	long x=longitude*100;
	ee.write_long(x,ee._longitude);
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void VARABEL::ee_set_Latitudes(float latitudes)        //0 to 90 degress
{                                                      //57.753336 
  long x=latitudes*100;
	ee.write_long(x,ee._latitudes);	
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void VARABEL::ee_read_Longitude(void) // 0 to 180 degress
{             
 // char buf[32];	
  long x=0;        
	ee.read_long(&x,ee._longitude);
	longitude=(float)x/100;
	
	//sprintf(buf,"%u",x);lcd.show(buf,0,0);
	//sprintf(buf,"%f",longitude);lcd.show(buf,1,0);
	//while(1);
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void VARABEL::ee_read_Latitudes(void) //0 to 90 degress
{
	long x=0;        
	ee.read_long(&x,ee._latitudes);
	latitudes=(float)x/100;
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void VARABEL::update_eeprom(void)
 {
	 ee.write_char(ontime_mode,ee._ontime_mode);
	 ee.write_char(offtime_mode,ee._offtime_mode);
	 
	 ee.write_char(OnTimePosNeg ,ee._OnTimePosNeg);
	 ee.write_char(OffTimePosNeg,ee._OffTimePosNeg);
	 
	 ee.write_char(OnTimeHour ,ee._on_tim_hor);
	 ee.write_char(OnTimeMin  ,ee._on_tim_min);
	 ee.write_char(OffTimeHour,ee._off_tim_hor);
	 ee.write_char(OffTimeMin ,ee._off_tim_min);
	 
	 ee.write_int (LiteLong ,ee._LiteLong);
	 
	 ee_set_Longitude(longitude);
	 ee_set_Latitudes(latitudes);
	 
	 
	 ee.write_long(max_lite ,ee._max_lite);
	 ee.write_long(min_lite,ee._min_lite);
	 ee.write_char(max_lite_persent ,ee._max_lite_persent);
	 ee.write_char(min_lite_persent,ee._min_lite_persent);
	 
	 
	 
 }
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------




//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void ee_read_varabel(void)
{
	//char buf[32];
	
 ee.read_char(&var.OnTimeHour ,ee._on_tim_hor  );
 ee.read_char(&var.OnTimeMin  ,ee._on_tim_min   );
 ee.read_char(&var.OffTimeHour,ee._off_tim_hor);
 ee.read_char(&var.OffTimeMin ,ee._off_tim_min );
 var.ee_read_Longitude();
 var.ee_read_Latitudes();
	
	ee.read_int(&var.LiteLong , ee._LiteLong);
	
	char char_;
	ee.read_char(&char_,ee._ontime_mode);
	var.ontime_mode=char_;
	
	ee.read_char(&char_,ee._offtime_mode);
	var.offtime_mode=char_;
	
	ee.read_char(&char_,ee._OnTimePosNeg);
	var.OnTimePosNeg=char_;
	
	ee.read_char(&char_,ee._OffTimePosNeg);
	var.OffTimePosNeg=char_;
	
	ee.read_long(&var.max_lite,ee._max_lite);
	ee.read_long(&var.min_lite,ee._min_lite);
	ee.read_char(&var.max_lite_persent,ee._max_lite_persent);
	ee.read_char(&var.min_lite_persent,ee._min_lite_persent);
	
	 
	
    
	
	
}
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------



//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------




//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------




//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------



//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------



//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------



//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------



//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------



//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------

