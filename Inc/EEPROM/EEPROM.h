/**
programer  Mohsen Faryabi
date       1396/6/26
Co         Javan electronic jiroft
instagram  Javan_electronic_jiroft
tel        09134484899

1396/11/12 add aryy to code

1398/08/29 size   tekrari not write

 */
 #define EEPROM_SIZE_KBIT 32 //24c32



//-----------------------------------------------------
//------------------String test-------------------------
//-----------------------------------------------------
//char* name="mohsen";
//char=respons=ee.write_string(name,ee._buf);

//char buf[25];
//ee.read_string(buf,ee._buf);
//show buf
//-----------------------------------------------------
//---------------Long test----------------------------
//-----------------------------------------------------
//test
//long test_long=131484530;
//int respons=ee.write(test_long,ee._z);
//HAL_Delay(100);

//long test;
// ee.read(&test,ee._z);
// sprintf(buf,"##%u##",test);
// glcd.print(buf,3,10);

//------------------------------------------------------------
//-------------------copy to main------------------------------
//I2C_HandleTypeDef read_i2c_in_main (void) {return hi2c1;}
//#include "EEPROM.h"

//5 setep to add varibel!!!!!!!!!!!!!!!!!!!

#define _bool     1
#define _char     1    // 255
#define _int      2    // 65 535
#define _long     4    //  4 294 967 295
//#define _longlong 8    //  9 223 372 036 854 775 807


#if (EEPROM_SIZE_KBIT < 32)
#define EE_SIZE I2C_MEMADD_SIZE_8BIT
#else
#define EE_SIZE I2C_MEMADD_SIZE_16BIT
#endif
	
#include <string.h>  



enum {
	EE_ERR=100,
	EE_OK,
	EE_yeki
	
	
};
 


  class EEPROM_24Cxx{
	
	public:
//	char buf[200];	
	
	EEPROM_24Cxx();
	char read(I2C_HandleTypeDef *i2c ,int address ,char *buf ,int number_of_byte);
	char write(I2C_HandleTypeDef *i2c ,int address ,char *buf ,int number_of_byte);

	char read_char(char* ,char,int);// varabel to read  , vrabel in eeprom , arry number
	char read_int(int*  ,char,int);
	char read_long(long* ,char,int);
	char read_string(char* ,char);
	
	char write_char(char ,char ,int ); // 
	char write_int(int  ,char ,int );
	char write_long(long ,char ,int );
	char write_string(char* ,char);
		
	//--------------------------------------
	private:
		char data[4];
		char write_one_byte(int address ,char data );

	
	int  find_sector(int varabel , int arry);
 
	//--------------------------------------
	public:
		//varabel name step[1-4]		exampel:_x
	enum 
	{
		_on_tim_hor = 0     ,  // char 
		_on_tim_min         ,  // char   
		_off_tim_hor        ,  // char  
 		_off_tim_min        ,  //char   
		_longitude          ,  //long   
		_latitudes               ,  //long 
		_ontime_mode        ,  //char
		_offtime_mode       ,  //char
		_OnTimePosNeg       ,  //char
		_OffTimePosNeg      ,  //char
		_LiteLong                ,  //char
		_max_lite                , //long
		_min_lite                ,//long
		_max_lite_persent    ,//char
		_min_lite_persent    ,//char
		
		number_of_variables
	}variables;
	
	//buf size  step[2-4]       exampel:x_
		enum 
	{
		on_tim_hor_         =1, //char [1]
		on_tim_min_        =1 , //char [1] 
		off_tim_hor_         =1, //char [1]
		off_tim_min_        =1, //char [1]
		longitude_           =1, //char [1]
		latitudes_             =1, //long [1]
		ontime_mode_      =1, //char [1]
		offtime_mode_      =1, //char [1]
		OnTimePosNeg_    =1, //char [1]
		OffTimePosNeg_    =1, //char [1]
		LiteLong_              =1 ,//char [1]
		max_lite_               =1 , //long
		min_lite_                =1,//long
		max_lite_persent_    =1 ,//char
		min_lite_persent_     =1 ,//char
		 
	}ARRY;
	              //this number equl to sum of arry varyabel
	              //    \/ 
int  address_valu   [                        //[number_of_variables];  // address in eeprom  *************************************************
	                 on_tim_hor_          +
	                 on_tim_min_          +
                     off_tim_hor_         +
                     off_tim_min_         + 
                     longitude_           +
                     latitudes_           +
                     ontime_mode_         +
                     offtime_mode_        +
                     OnTimePosNeg_        +
                     OffTimePosNeg_       +
                     LiteLong_            +
	                 max_lite_            +
	                 min_lite_            +
	                 max_lite_persent_ +
	                 min_lite_persent_ +
                    1];


	
char byte_of_valu   [number_of_variables];  // byte use on eeprom for exampel 2byte <==> int
unsigned int number_of_varabel;

//char buf[100];
	// int sum_of_use_sector;  // varabel + arry      var+arry[6] ==> 7
	  
	 int arry[number_of_variables];
	
	
	}ee;
//------------------------------------------------------
//------------------------------------------------------
 EEPROM_24Cxx::EEPROM_24Cxx()
{
	
 char cont=0;
	
    arry[cont++]=on_tim_hor_;
    arry[cont++]=on_tim_min_;
    arry[cont++]=off_tim_hor_;
    arry[cont++]=off_tim_min_;
	arry[cont++]=longitude_;
	arry[cont++]=latitudes_;
	arry[cont++]=ontime_mode_;
	arry[cont++]=offtime_mode_;
	arry[cont++]=OnTimePosNeg_;
	arry[cont++]=OffTimePosNeg_;
	arry[cont++]=LiteLong_;
	arry[cont++]=max_lite_;
	arry[cont++]=min_lite_;
	arry[cont++]=max_lite_persent_;
	arry[cont++]=min_lite_persent_;
	
 
	
//	
	
	//var type  step[3-4]  exampel:_x
	byte_of_valu  [_on_tim_hor]         = _char; //1    
	byte_of_valu  [_on_tim_min]         = _char ;//1 
	byte_of_valu  [_off_tim_hor]          = _char; //1   
	byte_of_valu  [_off_tim_min]         = _char; //1  
	byte_of_valu  [_longitude]            = _long; //1    
	byte_of_valu  [_latitudes]              = _long; //1    
	byte_of_valu  [_ontime_mode]       = _char; //1    
	byte_of_valu  [_offtime_mode]       = _char; //1 
	byte_of_valu  [_OnTimePosNeg]    = _char; //1    
	byte_of_valu  [_OffTimePosNeg]    = _char; //1  
	byte_of_valu  [_LiteLong]              = _int ; //1  
	byte_of_valu  [_max_lite]               = _long ; //1  
	byte_of_valu  [_min_lite]                = _long ; //1  
	byte_of_valu  [_max_lite_persent]    = _char ; //1  
	byte_of_valu  [_min_lite_persent]     = _char ; //1  
 

 
 
 //--------------------------------------------- 
// 	for(int x = 0 ; x<number_of_variables ;x++)
//	{
//			for(int y = 0 ;y < arry[x] ;y++)
//	    {
//		   sum_of_use_sector+= byte_of_valu[x];
//	    }
//	}
 //--------------------------------------------- 
// 	for(int x = 0 ; x<number_of_variables ;x++)
//	{
//			for(unsigned int y = 0 ;y < arry[x] ;y++)
//	    {
//		   number_of_varabel++;  
//	    }
//	}
//---------------------------------------------
	static long address=0;
	int x = 0 ,y=0,xx=0;
	
	for( x = 0 , xx=0; x < number_of_variables; x++,xx++ )
  { 
     for( y=0; y < (arry[x]); y++ )
		 {
		     if(y) xx++;
  			 address_valu[xx] = address;
		     address+=byte_of_valu[x];
		 }
	}
	
//	while(1);
	
};
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::read(I2C_HandleTypeDef *i2c ,int address ,char *buf ,int number_of_byte)
{
	
	char x=255;
	x=HAL_I2C_Mem_Read(i2c,0xA0 , 0x00 , EE_SIZE,(uint8_t *) buf,number_of_byte,1000);

return x;
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::write(I2C_HandleTypeDef *i2c ,int address ,char *buf ,int number_of_byte)
{
	
	char x=255;
	x=HAL_I2C_Mem_Write(i2c,0xA0 ,address , EE_SIZE,(uint8_t *) buf,number_of_byte,1000);

return x;
}

//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::write_one_byte(int address ,char data )
{
	I2C_HandleTypeDef i2c =read_i2c_in_main();
	char x=255;
	char buf[1];
	buf[0] = data;
	
	x=HAL_I2C_Mem_Write(&i2c,0xA0 ,address , EE_SIZE,(uint8_t *) buf,1,1000);
	
	
  HAL_Delay(3);
	if(x==HAL_OK)return EE_OK; 
	
	return x;
  
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::read_char(char *x ,char name,int arryy=0)
{
  //if(byte_of_valu[name] != _char) return 0;
	int find  = find_sector(name,arryy);;
	I2C_HandleTypeDef i2c =read_i2c_in_main();
	char respons=HAL_I2C_Mem_Read(&i2c,0xA0 , address_valu[find] , EE_SIZE,(uint8_t *) data,byte_of_valu[name],1000);
	*x=data[0];
return respons;
}
//------------------------------------------------------
//----------------------int--------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::read_int(int *x , char name,int arryy=0)
{
	//if(byte_of_valu[name] != _int) return 0;
	int find  = find_sector(name,arryy);
	I2C_HandleTypeDef i2c =read_i2c_in_main();
	char respons=HAL_I2C_Mem_Read(&i2c,0xA0 , address_valu[find] , EE_SIZE,(uint8_t *) data,byte_of_valu[name],1000);
 	*x=data[0]<<8 | data[1];
return respons;
}
//------------------------------------------------------
//---------------------long---------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::read_long(long *x , char name,int arryy=0)
{
	//if(byte_of_valu[name] != _long) return 0;
	int find  = find_sector(name,arryy);
	I2C_HandleTypeDef i2c =read_i2c_in_main();
	char respons=HAL_I2C_Mem_Read(&i2c,0xA0 , address_valu[find] , EE_SIZE,(uint8_t *) data,byte_of_valu[name],1000);
	*x=data[0]<<24 | data[1]<<16 | data[2]<<8 | data[3]<<0 ;
return respons;
}

//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::read_string(char *valu ,char name)
{
	int find  = find_sector(name,0);;
	I2C_HandleTypeDef i2c =read_i2c_in_main();
	
	
	char len;
	read_char(&len,name);
	
//	glcd.print_number(len,4,0);
//	glcd.print_number(arry[name],5,0);
	if(len > arry[name] ) return 0;
	
	for(char x=1;x<=len;x++)
	{
		ee.read_char(&valu[x-1],name,x);
	}
  return 0;
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::write_char(char valu ,char name,int arryy=0)
{
	if(byte_of_valu[name] != _char) return 0;
	
	char x;
	read_char(&x,name,arryy);
	if(valu == x) return EE_yeki; // if varabel equal to mem not write
			
	
	int find  = find_sector(name,arryy);
	int address = address_valu[find];
	char responsI=write_one_byte(address   ,valu );
	
return responsI;
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::write_int(int valu ,char name,int arryy=0)
{
	if(byte_of_valu[name] != _int) return 0;
	
	int x;
	read_int(&x,name,arryy);
	if(valu == x) return EE_yeki; // if varabel equal to mem not write
	
	
	int find  = find_sector(name,arryy);
	int address = address_valu[find];
	
	char responsI =write_one_byte(address+0 ,((valu & 0xFF00)>>8));
	char responsII=write_one_byte(address+1 ,((valu & 0x00FF)>>0));

return responsI | responsII;
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::write_long(long valu ,char name,int arryy=0)
{
	if(byte_of_valu[name] != _long) return 0;
	
	long x;
	read_long(&x,name,arryy);
	if(valu == x) return EE_yeki; // if varabel equal to mem not write
	
	int find  = find_sector(name,arryy);
	int address = address_valu[find];
	

	char responsI   =write_one_byte(address+0  ,((valu & 0xFF000000)>>24));
	char responsII  =write_one_byte(address+1  ,((valu & 0x00FF0000)>>16));
	char responsIII =write_one_byte(address+2  ,((valu & 0x0000FF00)>>8 ));
	char responsIIII=write_one_byte(address+3  ,((valu & 0x000000FF)>>0 ));
	
//	 glcd.print_number(responsI,1,0);
//	glcd.print_number(responsII,2,0);
//	glcd.print_number(responsIII,3,0);
//	glcd.print_number(responsIIII,4,0);
	 
	
return responsI | responsII | responsIII | responsIIII;
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
char EEPROM_24Cxx::write_string(char* valu ,char name)
{
	//if(byte_of_valu[name] != _long) return 0;
	char len=strlen(valu);
	
	
	char y=0;
	
	char x[100];
	read_string(x,name);
	for(int loop=0;loop<len ; loop++)
	{
		if(valu[loop] == x[loop]) y++; 
		else break;
	}
	if(y == len) return EE_yeki;
	
	
	int find  = find_sector(name,0);
	int address = address_valu[find];
	
  
	
	 write_one_byte(address ,len);
	
	for(char x=1;x<=len ;x++)
 {
   write_one_byte(address+x,valu[x-1] );
 }	
	
	
return EE_OK ;
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
int  EEPROM_24Cxx::find_sector(int varabel , int arry_)
{	
	int conter=0;
 	for(int x = 0 ; x<number_of_variables ;x++)
	{
			for(int y = 0 ;y < arry[x] ;y++)
	    {
       if(x == 	varabel && y==arry_) return conter;			
				conter++;
	    }
	}
return 65530;
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------


//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------


//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------




//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------




//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------



//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------


//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------




//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------




//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------



//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------


//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------




//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------




//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------



//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------



