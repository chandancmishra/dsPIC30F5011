#include <p30f5011.h>
#include "Hardware.h"
#include "LCD.h"
#include "Can.h"
#include "Pwm.h"
#include "External_intreup.h"
#include "input_capture.h"
#include "Timer_int.h"
#include "ADC.h"
 
 //defines
 #define FCY            10000000*4/4 //FCY=ext_clk_freq*XT_PLLx/4


 
 _FOSC(CSW_FSCM_OFF & XT_PLL4); 
 _FWDT(WDT_OFF);                 /* Turn off the Watch-Dog Timer.  */
 _FBORPOR(PBOR_OFF & MCLR_EN);
 _FGS(CODE_PROT_OFF);            /* Disable Code Protection */
 

 //    Initialization




//=============================== variable =====================//


 
 // Buffer Register for CAN data to be send out in the transmit mode.





 unsigned int OutData0[4] = {0x5555,0x5555,0x5555,0x5555};
 unsigned int OutData1[4] = {0xCCCC,0x7777,0x4444,0x4444};  

//int *a;              
//int x_y;
//
////int x2 __attribute__((at(0x12000))) = 10;
//
//a = &x_y;
////*a = 100;

//int var __attribute__((at(0x40001000)));

var = 4;   // changes the memory location at 0x40001000

//=============================================    K-fram   ========================================//

typedef struct 
{

char data;
struct node *next;

}K_fram ;


K_fram i;
//=============================================    CAN ON UDS =======================================//



//=====================================================================================================//

 void __attribute__((interrupt, no_auto_psv)) _C1Interrupt(void)
 {
  
     IFS1bits.C1IF = 0;         //Clear interrupt flag
 
     //Transmit Flags
     if(C1INTFbits.TX0IF)
       { 
         C1INTFbits.TX0IF = 0;  //If the Interrupt is due to Transmit0 of CAN1 Clear the Interrupt
       }
     else if(C1INTFbits.TX1IF)
       {
         C1INTFbits.TX1IF = 0;   //If the Interrupt is due to Transmit1 of CAN1 Clear the Interrupt 
       }  
    
     
     //Receive Flags

     if(C1INTFbits.RX0IF)
      {
         
                               //Move the recieve data from Buffers to InData
         InData0[0] = C1RX1B1; InData0[1] = C1RX1B2; InData0[2] = C1RX1B3;    InData0[3] = C1RX1B4;
      
         
         PORTDbits.RD2=0;                       //if data received is same as sent turn on all leds
        
	        
         C1INTFbits.RX0IF = 0; 
         if ((InData0[0]==0x4D)&& (InData0[1]==0x4D) && (InData0[2]==0x4D) && (InData0[3]==0x4D)) 
          {    //  PORTEbits.RE2=1; }
                     //If the Interrupt is due to Receive0 of CAN1 Clear the Interrupt
          }
     else if(C1INTFbits.RX1IF)
     {       PORTDbits.RD2=0;
        C1INTFbits.RX1IF = 0;      //If the Interrupt is due to Receive1 of CAN1 Clear the Interrupt
    

         InData1[1] = C1RX1B2 & 0b1111111100000000;
         InData1[2] = C1RX1B3 & 0b0000000011111111;
         
         InData1[1] = C1RX1B2>>8;
         InData1[2] = C1RX1B3<<8;
          
         temp = InData1[1]|InData1[2];
         temp = temp/8;

         cmd(0x80);

         Convert(temp);
         data(D);
         delay_ms(5);
         data(C);
         delay_ms(5);
         data(B);
         delay_ms(5);
         data(A);
         delay_ms(5);
          
         
     C1INTF = 0;
     //    if ((InData1[0]==0x4D) && (InData1[1]==0x4D) && (InData1[2]==0x4D) && (InData1[3]==0x4D))
                // PORTEbits.RE2=1;
     }
 
 //    if(C1INTF!=0){}                //set breakpoint here

 }
 }

 void __attribute__((interrupt, no_auto_psv)) _C2Interrupt(void)
{


     IFS2bits.C2IF = 0;         //Clear interrupt flag
 
}

 void main(void)
 
{
     TRISF=0xFD; //set F1 (C1TX) to output and F0 (C1RX) to input
  //   TRISE=0x0000;             // modified 
     TRISC=0;				// Set Port B as output port
	 LATC=0;
	 TRISB=0;
	 LATB=0;
     TRISD=0;
     LATD=0;

 TRISBbits.TRISB13 = 1;       // ANALOG PIN

     TRISGbits.TRISG0 = 1;
TRISGbits.TRISG1 = 0;


    init_can1(); //init the can registers
      
  init_can2();

PWM_Init( );
     
     lcd_ini();

	 
     __delay32(1000000);
    

// a = (int*)calloc(10, sizeof(int));

    cmd(0x01);
    delay_ms(50);
    LCD_Disp(0x80,name);
    LCD_Disp(0xC0,name1); 	/* Display Company Name 			*/

    __delay32(10000000);
    cmd(0x01);

    LCD_Disp(0x80,name2);
    LCD_Disp(0xC0,name3); 	/* Display Company Name 			*/

    PORTDbits.RD0=0; 
   PORTCbits.RC13=1; 
   PORTCbits.RC14=1;
 //  PORTEbits.RE2=1;         modified
PORTDbits.RD2=1; 
   _LATC13 = 0;
   _LATC14 = 0;
 
    _LATD0 = 0;
    _LATD2 = 0;
     cmd(0x01);

     C1CTRLbits.REQOP = 0; //set to normal operating mode
     while(C1CTRLbits.OPMODE != 0);
 

     C2CTRLbits.REQOP = 0; //set to normal operating mode
     while(C2CTRLbits.OPMODE != 0);

  while(1)
{  
    
       
         C1TX0CONbits.TXREQ = 1; //Enable transmission
    //     while(C1TX0CONbits.TXREQ != 0);
         C1TX1CONbits.TXREQ = 1; //Enable transmission
    //     while(C1TX1CONbits.TXREQ != 0);
         __delay32(100000);
       C1RX1CON=0b0000000000000011;


       C2TX0CONbits.TXREQ = 1; //Enable transmission
    //     while(C1TX0CONbits.TXREQ != 0);
         C2TX1CONbits.TXREQ = 1; //Enable transmission
    //     while(C1TX1CONbits.TXREQ != 0);
         __delay32(100000);
       C2RX1CON=0b0000000000000011;



 ADC_AN13() ;
OC3RS = (unsigned int)ADC_float13;

 /*
     while(1);
     return 0;
*/
}
}
 
 
 


/******************** DELAY *****************************/



void delay_ms(unsigned int delay)	                        
{
  unsigned int i,j;
  for(i=0;i<delay;i++)
  {
  for(j=0;j<1275;j++);
  }
}

//******************************** temp value *********************//

void Convert(unsigned int temp)
{
	 unsigned int X,Y,Z; 			/* Intermidiate Variables */

	 A=0,B=0,C=0,D=0;

	 X = temp/10;

	 A = temp%10;
	 A = 0x30|A;		/* First Byte(LSB) */

	 Y = X/10;
	 B = X % 10;
	 B = 0x30|B;	/* Second Byte */

	 Z = Y/10;
	 C = Y % 10;
	 C = 0x30|C; 		/* Third Byte */

	 D = Z;					/* Last Byte(MSB) */
	 D=0x30|D;		    		/* Third Byte      */
}
//