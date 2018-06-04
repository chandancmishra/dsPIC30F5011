#include <p30f5011.h>



//==================================== LCD =========================//


 //LCD Control pins

#define rs PORTEbits.RE2
#define rw PORTEbits.RE1
#define en PORTEbits.RE0

//LCD Data pins
#define lcdport PORTB



//================================== LED ===================================

#define led PORTDbits.RD2