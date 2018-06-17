#include "CanLib.h"

#define FCY            10000000*4/4 //FCY=ext_clk_freq*XT_PLLx/4

CANMSG msg;
int x;
_FOSC(CSW_FSCM_OFF & XT_PLL4);
_FWDT(WDT_OFF);                 /* Turn off the Watch-Dog Timer.  */
_FBORPOR(PBOR_OFF & MCLR_EN);
_FGS(CODE_PROT_OFF);            /* Disable Code Protection */


int main()
  {

    CANMSG tx;
    CanInit();
    CanSetMask(0,0);//x1fffffff
    CanSetFilter(0, 0);
	CanConfig();
    tx.eid=01;
    tx.length = 8;
    tx.data[0]=1;
    tx.data[1]=1;
    tx.data[2]=1;
    tx.data[3]=1;
    tx.data[4]=1;
    tx.data[5]=1;
    tx.data[6]=1;
    tx.data[7]=1;
    while(1)
      {
        CanReceiveMessage(&msg);
		delay_ms(10);
		CanSendMessage(&msg);		

        delay_ms(10);
      }

    return 0;
}
