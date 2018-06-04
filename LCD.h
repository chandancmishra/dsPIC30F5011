#include <p30f5011.h>
#include "Hardware.h"




 unsigned int A,B,C,D;
 char name[]="AARSH EM";
 char name1[]="BE SYS ";
 char name2[]="GEAR ADV";
 char name3[]="ISER SYS ";
//********************************** LCD function ********************//




void lcd_ini(void);

void cmd(unsigned char cmdout);
void data(unsigned char dataout);
void delay_ms(unsigned int delay);
void LCD_Disp(unsigned char Loc,unsigned char *String);
void Convert(unsigned int temp);




/************************ LCD initializion********************/

void lcd_ini(void)	                    
{
	cmd(0x38);		
	cmd(0x0f);	
	cmd(0x06);
    cmd(0x01);
	cmd(0x80);
    cmd(0x0C);	
}


void cmd(unsigned char cmdout)
{
	lcdport=cmdout;		//Send command to lcdport=PORTB
//	rs=0;						
//	rw=0;
//	en=1;
  __delay32(100000);
//	en=0;
}

void data(unsigned char dataout)
{
	lcdport=dataout;	//Send data to lcdport=PORTB
//	rs=1;
//	rw=0;
//	en=1;
    __delay32(100000);
//	en=0;
}

/*************** Write String to LCD *****************/

void LCD_Disp(unsigned char Loc,unsigned char *String)
{
	cmd(Loc);
	while(*String)
	{
		data(*String);	  	/* write data to LCD */
        String++;
      delay_ms(1);
	}
}


