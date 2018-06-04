#include <p30f5011.h>

/*
  // Define time values
    int Tpwm = 1500; // PWM period = 1500 * Tcy = 50us (i.e. 20kHz)
    int dead_time = 60; // 2us deadtime is in the right ballpark for IGBTs
    int Ton = Tpwm - 2*dead_time ; // total on time during each cycle
    double duty_cycle = 0.5;
*/
void Motor_PWM_Init(void)
{

    TRISD = 0x00; // make sure PWM pins are set to be outputs
    PORTD = 0x00; // clear the outputs 
 
    PTCONbits.PTOPS = 0; // PWM timer post-scale
    PTCONbits.PTCKPS = 0; // PWM timer pre-scale
    PTCONbits.PTMOD = 2; // PWM operates in Up-down Mode continuously
 
    PTMR = 0; // PWM counter value, start at 0
 
    PTPER = 50; // PWM Timebase period  18KHz
 
    PWMCON1bits.PMOD3 = 0; // PWM in complimentary mode
    PWMCON1bits.PMOD2 = 0; // PWM in complimentary mode
    PWMCON1bits.PMOD1 = 0; // PWM in complimentary mode
    PWMCON1bits.PEN3H = 1; // PWM High pin is enabled
    PWMCON1bits.PEN2H = 1; // PWM High pin is enabled
    PWMCON1bits.PEN1H = 1; // PWM High pin is enabled
    PWMCON1bits.PEN3L = 1; // PWM Low pin enabled (direction control later?)
    PWMCON1bits.PEN2L = 1; // PWM Low pin enabled (direction control later?)
    PWMCON1bits.PEN1L = 1; // PWM Low pin enabled (direction control later?)
 
    //PWMCON2 = 0x0000; // PWM update info
 
    DTCON1bits.DTAPS = 0;  //DeadTime pre-scaler
    DTCON1bits.DTA = 15;   //DeadTime value for 4 us/59. 
 
    //FLTACON = 0x0000; // Fault A Control
 
    //OVDCON = 0x0000; // Override control info
 
    // Duty Cycle has a max value of 2xPeriod since output  
    // can change on rising or falling edge of Tcy
    PDC1 = 1; // PWM#1 Duty Cycle register (11-bit)
  //  PDC2 = 19999; // PWM#2 Duty Cycle register (11-bit)
 //   PDC3 = 19999; // PWM#3 Duty Cycle register (11-bit)
 
    PTCONbits.PTEN = 1; // Enable PWM Timerbase!
}

/*
void PWM_Init(void)
{
// Initialise OC channel 1 & 2 start and stop times
    OC1R = 0;
    OC1RS = (int)(duty_cycle * Ton);
    OC2R = OC1RS + dead_time;
    OC2RS = PR2 - dead_time;
     
    // Set output compare mode for continuous pulses
    OC1CONbits.OCM = 0b101;
    OC2CONbits.OCM = 0b101;

}
*/
