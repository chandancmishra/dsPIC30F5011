#include <p30f5011.h>


//take dutycycle in percentage
//frequency in kHz
//pin values:5,6,7,8
void PWM_init(float period)
{

	TRISD = 0b1100001111000000; //output on all available pins

//	period = 30e6 / frequency;
	
		// Configure Timers 2 & 3
	PR2 = period - 1;      // Set Timer 2 period for 50kHz
	PR3 = period - 1;      // Set Timer 3 period for 50kHz
	T2CONbits.TCKPS = 0;   // 1:1 prescale
	T3CONbits.TCKPS = 0;   // 1:1 prescale
	TMR2 = period / 4;     // Timer 2 leads Timer 3 by 25% of period.
	TMR3 = period / 2;     // Timer 3 lags Timer 2 by 25% of period. Give it a "head start" of 1 because Timer3 is enabled just after Timer2

	T2CONbits.TON = 1;
	T3CONbits.TON = 1;
	// Select timer for each channel
	OC3CONbits.OCTSEL = 0; // OC1 driven by Timer 2
	OC4CONbits.OCTSEL = 1; // OC2 driven by Timer 3
	OC5CONbits.OCTSEL = 0; // OC3 driven by Timer 2
	OC6CONbits.OCTSEL = 1; // OC4 driven by Timer 3


}
void PWM_start(float dutycycle,float period,int pin)
{

//int pulse, space;//, period;   // pulse width, space width, period
//period = 30e6 / frequency;               // f_m = 30e6 / 600 = 50 kHz
//pulse = dutycycle * period; // width of PWM pulses
//space = period - pulse;     // gap between PWM pulses

	if(pin==5)
	{
		OC3CONbits.OCM = 0b101;
		OC3R = 0;     // pulse start time
		OC3RS = dutycycle*period/100;   // pulse end time
	}
	else if(pin==6)
	{
		OC4CONbits.OCM = 0b101;
		OC4R = 0;       // pulse start time
   		OC4RS = dutycycle*period/100;   // pulse end time
	}
	else if(pin==7)
	{
		OC5CONbits.OCM = 0b101;
		OC5R = 0;       // pulse start time (start of gap in PWM3)
  	  	OC5RS = dutycycle*period/100;   // pulse end time (end of gap in PWM3)
	}
	else if(pin==8)
	{
		OC6CONbits.OCM = 0b101;
		OC6R = 0;       // pulse start time (start of gap in PWM4)
    		OC6RS = dutycycle*period/100;   // pulse end time (end of gap in PWM4)
	}
}
