#include <p30f5011.h>


void EXT_INT(void);

/************************ External intreup ********************/
void EXT_INT(void)
{
INTCON1=0x00;
INTCON2=0x00;
INTCON2bits.INT1EP=0;
IPC4bits.INT1IP=1;
IFS1bits.INT1IF=0;
IEC1bits.INT1IE=1;

}