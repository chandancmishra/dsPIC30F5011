//#include "ADC.h"
#include <p30f5011.h>

//=========================================== ADC ==============//




unsigned long ADCValue13=0;
unsigned int *ADC16Ptr13;
float ADC_float13 = 0;
float ADC_average13[]={0};
float average13[10]={0};

float test_float13 = 0;

unsigned char ADC_buffer13 [3] = {0};





unsigned int ii , jj , kk ; 

unsigned int ii = 0, jj = 0, kk = 0; 
unsigned int kk1 = 0, kk2 = 0, kk3 = 0, kk5 = 0, kk6 =0, kk7 =0;




void ADC_AN13()    // I_BATTERY
{


float maxima_average13 = 0;

 ADPCFG = 0b1101111111111111; // all PORTB = Digital; RB2 = analog
 ADCON1 = 0x00E0; // SSRC bit = 111 implies internal
// counter ends sampling and starts
// converting.
 ADCHS = 0x000D; // Connect RB2/AN2 as CH0 input ..
// in this example RB2/AN2 is the input
 ADCSSL = 0;
 ADCON3 = 0x0F00; // Sample time = 15Tad, Tad = internal Tcy/2
 ADCON2 = 0x0004; // Interrupt after every 2 samples
 ADCON2bits.SMPI = 15;



//for(jj=0;jj<400;jj++)
{

ADCON1bits.ADON = 1; // turn ADC ON

ADCValue13 = 0; // clear value     ////////////////////AVERAGING
ADC16Ptr13 = &ADCBUF0; // initialize ADCBUF pointer
IFS0bits.ADIF = 0; // clear ADC interrupt flag
 ADCON1bits.ASAM = 1; // auto start sampling
// for 31Tad then go to conversion
while (!IFS0bits.ADIF); // conversion done?
ADCON1bits.ASAM = 0; // yes then stop sample/convert
for (ii = 0; ii < 15; ii++) // average the 2 ADC value
ADCValue13 = ADCValue13 + *ADC16Ptr13++;
ADCValue13 = ADCValue13 >> 4;

maxima_average13 = maxima_average13  + ADCValue13;
}

//ADC_float0 = (float)(maxima_average0/400);
ADC_float13 = (float)(ADCValue13)*((5.03/1023)*10);
//ADC_float0 = (float)(ADCValue0)*((5.03/1023)*120*1.114*0.833);
sprintf(ADC_buffer13,"%f",ADC_float13);
//average3[0] = ADC_float3;
}

