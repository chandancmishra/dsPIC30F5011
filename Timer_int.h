#include <p30f5011.h>


void TIMER2_SETUP (void);
void TIMER1_SETUP (void);



void TIMER1_SETUP (void)
{
TMR1 = 0x00; //Clear contents of the timer register
T1CON = 0x00; //Stops the Timer2 and reset control reg.
T1CONbits.TCS=0; 			/*Using Internal Clock (Fosc/4)*/
//T1CONbits.T32=0;			/*TMRx and TMRy form a 16-bit timer*/
T1CONbits.TCKPS=1;  		/*Using 1:256 prescale value*/
T1CONbits.TGATE=1;			/*Timer Gate Accumulation Disabled*/
T1CONbits.TSIDL=0;			/*Continue in Idle Mode*/
//T2CON = 0x00; //Stops the Timer2 and reset control reg.
PR1 = 0x038F; //Load the Period register with the value 0xFFFF
//IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
// (This example assigns level 1 priority)
IFS0bits.T1IF = 0; //Clear the Timer1 interrupt status flag
IEC0bits.T1IE = 1; //Enable Timer1 interrupts
T1CONbits.TON = 1; // Start Timer

//clock source set to the internal instruction cycle
//TMR2=0xFFFF;
}


//=======================TIMER_SETUP*============//
void TIMER2_SETUP (void)
{

TMR2 = 0x00; //Clear contents of the timer register
T2CON = 0x00; //Stops the Timer2 and reset control reg.
T2CONbits.TCS=0; 			/*Using Internal Clock (Fosc/4)*/
T2CONbits.T32=0;			/*TMRx and TMRy form a 16-bit timer*/
T2CONbits.TCKPS=3;  		/*Using 1:256 prescale value*/
T2CONbits.TGATE=0;			/*Timer Gate Accumulation Disabled*/
T2CONbits.TSIDL=0;			/*Continue in Idle Mode*/
//T2CON = 0x00; //Stops the Timer2 and reset control reg.
PR2 = 0xFFFF; //Load the Period register with the value 0xFFFF
//IPC1bits.T2IP = 0x04; //Setup Timer2 interrupt for desired priority leve
// (This example assigns level 1 priority)
IFS0bits.T2IF = 0; //Clear the Timer1 interrupt status flag
IEC0bits.T2IE = 1; //Enable Timer1 interrupts
T2CONbits.TON = 1; //Start Timer1 with prescaler settings at 1:1 and 
//clock source set to the internal instruction cycle
//TMR2=0xFFFF;

/*
TMR2 = 0x00; //Clear contents of the timer register
T2CON = 0x00; //Stops the Timer2 and reset control reg.
T2CONbits.TCS=0; 			//Using Internal Clock (Fosc/4)
T2CONbits.T32=0;			//TMRx and TMRy form a 16-bit timer
T2CONbits.TCKPS=2;  		//Using 1:256 prescale value
T2CONbits.TGATE=0;			//Timer Gate Accumulation Disabled
T2CONbits.TSIDL=0;			//Continue in Idle Mode
//T2CON = 0x00; //Stops the Timer2 and reset control reg.
PR2 = 0xFFFF; //Load the Period register with the value 0xFFFF
IPC1bits.T2IP = 0x04; //Setup Timer2 interrupt for desired priority leve
// (This example assigns level 1 priority)
IFS0bits.T2IF = 0; //Clear the Timer1 interrupt status flag
IEC0bits.T2IE = 1; //Enable Timer1 interrupts
T2CONbits.TON = 1; //Start Timer1 with prescaler settings at 1:1 and 
//clock source set to the internal instruction cycle
//TMR2=0xFFFF;
*/

}
