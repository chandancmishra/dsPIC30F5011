#include <p30f5011.h>
#include <math.h>

//void ADCinit(void);

 void ADC_AN13(void);    // Battery voltage
 void ADC_AN2(void);
 void ADC_AN1(void);
 void ADC_AN5(void);
 void ADC_AN6(void);
 void ADC_AN7(void);





extern unsigned int SHUNT1 ;
extern unsigned int SHUNT2 ;
extern unsigned int SHUNT3 ;

extern unsigned int test_max;
extern unsigned long ADCValue13;
extern unsigned int *ADC16Ptr13;
extern float ADC_float13 ;
extern float ADC_average13[];
extern float average13[10];

extern float test_float13 ;

extern unsigned char ADC_buffer13 [3] ;

// int ii ,jj , kk ;
extern unsigned int ii , jj , kk ; 



