#include <p30f5011.h>

void PWM_Init( void );

//=====================================================================

void PWM_Init( void )
{

 // Configure RD2, RD3, RD4, RD5 as digital outputs.
    // (Not sure if this is required when Output Compare is used)
    TRISD = 0b1100001111000000;
 
    // Set period and duty cycle
    int dutycycle = 20;      // 20% duty cycle for this example
    int pulse, space, period;   // pulse width, space width, period
    period = 600;               // f_m = 30e6 / 600 = 50 kHz
    pulse = dutycycle * period; // width of PWM pulses
    space = period - pulse;     // gap between PWM pulses
 
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
   // Select timer for each channel
    OC3CONbits.OCTSEL = 0; // OC1 driven by Timer 2
    OC4CONbits.OCTSEL = 1; // OC2 driven by Timer 3
    OC5CONbits.OCTSEL = 0; // OC3 driven by Timer 2
    OC6CONbits.OCTSEL = 1; // OC4 driven by Timer 3


  // Output continuous pulses on all OC channels
    OC3CONbits.OCM = 0b101;
    OC4CONbits.OCM = 0b101;
    OC5CONbits.OCM = 0b101;
    OC6CONbits.OCM = 0b101;


// Set OC1 to output continuous pulses of the desired width.
    // The pulses are positioned midway through the TMR2 up-count.
    OC3R = 20;    // pulse start time
    OC3RS = 20;   // pulse end time
 
    // Set OC2 to output continuous pulses of the desired width.
    // The pulses are positioned midway through the TMR3 up-count.
    OC4R = 20;    // pulse start time
    OC4RS = 20;   // pulse end time
 
    // Set OC3 to output continuous pulses. These will be inverted
    // to become the gaps between the pulses and vice versa. The
    // width of these pulses is therefore set to the width of the
    // gap between the final pulses in PWM3.
    OC5R = 20;    // pulse start time (start of gap in PWM3)
    OC5RS = 20;   // pulse end time (end of gap in PWM3)
 
    // Set OC4 to output continuous pulses. These will be inverted
    // to become the gaps between the pulses and vice versa. The
    // width of these pulses is therefore set to the width of the
    // gap between the final pulses in PWM4.
    OC6R = 20;    // pulse start time (start of gap in PWM4)
    OC6RS = 20;   // pulse end time (end of gap in PWM4)
 
    // Enable Timers 2 & 3
    //
    // It might be better to use some inline assembly language here
    // to ensure that the delay between the two timers being enabled
    // is very short and that we know exactly how many instruction
    // cycles "head start" Timer 3 should get to make the two timers
    // exactly 90 degrees out of phase.
    //

}




/*



void PWM_Init( void )
{

 // Configure RD0, RD1, RD2, RD3 as digital outputs.
    // (Not sure if this is required when Output Compare is used)
    TRISD = 0b1111111111000000;
 
    // Set period and duty cycle
    float dutycycle = 0.2;      // 20% duty cycle for this example
    int pulse, space, period;   // pulse width, space width, period
    period = 600;               // f_m = 30e6 / 600 = 50 kHz
    pulse = dutycycle * period; // width of PWM pulses
    space = period - pulse;     // gap between PWM pulses
 
    // Configure Timers 2 & 3
    PR2 = period - 1;      // Set Timer 2 period for 50kHz
    PR3 = period - 1;      // Set Timer 3 period for 50kHz
    T2CONbits.TCKPS = 0;   // 1:1 prescale
    T3CONbits.TCKPS = 0;   // 1:1 prescale
    TMR2 = period / 4;     // Timer 2 leads Timer 3 by 25% of period.
    TMR3 = 1;              // Timer 3 lags Timer 2 by 25% of period. Give it a "head start" of 1 because Timer3 is enabled just after Timer2
 


// Select timer for each channel
    OC1CONbits.OCTSEL = 0; // OC1 driven by Timer 2
    OC2CONbits.OCTSEL = 1; // OC2 driven by Timer 3
    OC3CONbits.OCTSEL = 0; // OC3 driven by Timer 2
    OC4CONbits.OCTSEL = 1; // OC4 driven by Timer 3
   // Select timer for each channel
    OC1CONbits.OCTSEL = 0; // OC1 driven by Timer 2
    OC2CONbits.OCTSEL = 1; // OC2 driven by Timer 3
    OC3CONbits.OCTSEL = 0; // OC3 driven by Timer 2
    OC4CONbits.OCTSEL = 1; // OC4 driven by Timer 3


  // Output continuous pulses on all OC channels
    OC1CONbits.OCM = 0b101;
    OC2CONbits.OCM = 0b101;
    OC3CONbits.OCM = 0b101;
    OC4CONbits.OCM = 0b101;


// Set OC1 to output continuous pulses of the desired width.
    // The pulses are positioned midway through the TMR2 up-count.
    OC1R = space / 2;       // pulse start time
    OC1RS = OC1R + pulse;   // pulse end time
 
    // Set OC2 to output continuous pulses of the desired width.
    // The pulses are positioned midway through the TMR3 up-count.
    OC2R = space / 2;       // pulse start time
    OC2RS = OC2R + pulse;   // pulse end time
 
    // Set OC3 to output continuous pulses. These will be inverted
    // to become the gaps between the pulses and vice versa. The
    // width of these pulses is therefore set to the width of the
    // gap between the final pulses in PWM3.
    OC3R = pulse / 2;       // pulse start time (start of gap in PWM3)
    OC3RS = OC3R + space;   // pulse end time (end of gap in PWM3)
 
    // Set OC4 to output continuous pulses. These will be inverted
    // to become the gaps between the pulses and vice versa. The
    // width of these pulses is therefore set to the width of the
    // gap between the final pulses in PWM4.
    OC4R = pulse / 2;       // pulse start time (start of gap in PWM4)
    OC4RS = OC4R + space;   // pulse end time (end of gap in PWM4)
 
    // Enable Timers 2 & 3
    //
    // It might be better to use some inline assembly language here
    // to ensure that the delay between the two timers being enabled
    // is very short and that we know exactly how many instruction
    // cycles "head start" Timer 3 should get to make the two timers
    // exactly 90 degrees out of phase.
    //
}

*/
