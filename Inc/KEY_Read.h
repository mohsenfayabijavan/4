#include "main.h"

#define read_key1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define read_key2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define read_key3 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)





class KEY_READ
{
	public:
		
	KEY_READ();
	char key,lastkey;
	bool newkey;
	int cont;
	
	
	char read(void);
	int get_delay(void);
	char check_key(void);
	bool debons(char,int);
	
	
	
	
	
	
	
	
	
	
	enum
	{
		up  = 1,
		down   ,
		set    ,
		
		none =255
	}KEY_VAR;
	
	
	
	
	
	private:
	void delay(int x);
	
	
}key;

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
KEY_READ::KEY_READ()
{
	key=0;
  newkey=0;
  cont=0;
}

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
char KEY_READ::read()
{
	key=none;
	if(read_key1 == 0)
	{  
		delay(4);
		if(read_key1 == 0)
		{
		   key = up;
		   newkey=1;
		}
	}
	else if(read_key2 == 0)
	{  
		delay(4);
		if(read_key2 == 0)
		{
		   key = set;
		   newkey=1;
		}
	}
	else if(read_key3 == 0)
	{  
		delay(4);
		if(read_key3 == 0)
		{
		   key = down;
		   newkey=1;
		}
	}
	
	if(key == lastkey && key != none ) cont++;else cont=0;
	if(key == none) cont=0;
	
	lastkey=key;
	return key;
}

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
int KEY_READ::get_delay(void)
{
	     if(cont < 20  ) return 300;
	else if(cont < 50 ) return 200;
	else if(cont < 100 ) return 100;
	else if(cont < 200 ) return 50;
	else if(cont < 500 ) return 10;
	else                return 0;
}
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
void KEY_READ::delay(int x)
{
	for( ; x>0 ; x--)
	   for(int z=0 ; z<1000 ; z++);
	
	
}
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
char KEY_READ::check_key(void)
{
// char buf[32];
	int cont_ref=100; // harche kamtar shavad delay kamtar
	
 while( !read_key1  || !read_key2  || !read_key3 )
 {
   read();
	 
        if(cont>cont_ref*3 && (read() == up))  {lcd.show("0",0,15); while(read() == up)  delay(10);delay(10); return up;  }
   else if(cont>cont_ref*3 && (read() == set)) {lcd.show("0",0,15); while(read() == set) delay(10);delay(10); return set; }
   else if(cont>cont_ref*3 && (read() == down)){lcd.show("0",0,15); while(read() == down)delay(10);delay(10); return down;}
 
  else if(cont <cont_ref)   lcd.show("3",0,15);
	else if(cont <cont_ref*2) lcd.show("2",0,15);	
  else if(cont <cont_ref*3) lcd.show("1",0,15);
 }
 
	lcd.show(" ",0,15);
 return none;

}
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
bool KEY_READ::debons(char key_pressed ,int tryy=0)
{
	
	
	delay(4);
	if(read() == key_pressed) return 1;
	return 0;
	
	
}
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------


//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------



//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------



//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------



//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------

