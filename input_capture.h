

#include <p30f5011.h>
/*
#include "stdio.h"
#include "float.h"
#include "math.h" 
 //defines
// #define FCY            10000000*4/4 //FCY=ext_clk_freq*XT_PLLx/4

#define FOSC = 10000000 Hz

 _FOSC(HS); 

// _FOSC(CSW_FSCM_OFF & XT_PLL4); 
 _FWDT(WDT_OFF);                 // Turn off the Watch-Dog Timer.  
 _FBORPOR(PBOR_OFF & MCLR_EN);
 _FGS(CODE_PROT_OFF);            // Disable Code Protection 
 

*/









//********************** FUNCTION **********************************//

void IC1_SETUP(void);
void IC2_SETUP (void);





//==================================================================//





//==========================SETUP_IC=======================//
void IC1_SETUP (void)
{

IC1CONbits.ICM=1;		//Capture every rising edge

IC1CONbits.ICBNE=0;		//Input capture buffer is empty
IC1CONbits.ICOV=0;		//No input capture overflow occured
IC1CONbits.ICI=0;		//Interrupt on every capture event
IC1CONbits.ICTMR=1;		//TMR2 contents are captured on captured event
IPC0bits.IC1IP=0x02;
IC1CONbits.ICSIDL=0;    //Input capture module will continue to operate in CPU Idle mode
IFS0bits.IC1IF = 0;       //Interrupt bit is cleared
IEC0bits.IC1IE = 1;     //Set the IC1 interrupt enable bit
//IEC1bits.INT1IE =1;
//INTCON2bits.INT1EP = 0;
//IC1BUF=0x00;
}











