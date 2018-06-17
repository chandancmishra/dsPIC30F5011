/*********************************************************************
* File Name     : CanLib.h
* Description   : Header file for CanLib.c
* Date          : 11/06/2018
*********************************************************************/

#ifndef CANLIB_H
#define CANLIB_H

#include <p30f5011.h>
#include "types.h"

/*--- Can message structure. ---*/
  uint32_t SID1 ,EID1,DLC1,var1;
typedef struct
  {
  uint32_t eid;
  uint8_t length;
  uint8_t data[8];
  }CANMSG;

/*--- CanLib function prototypes. ---*/

void CanInit(void);                                 /* Call this function first */
void CanSetMask(uint8_t mask_no, uint32_t mask);    /* Then set up masks */
void CanSetFilter(uint8_t filter_no, uint32_t sid); /* and filters */
void CanConfig(void);                               /* Then call this function last, to enable can. */

void CanSetPriority(uint8_t buffer, uint8_t priority);
void CanSendMessage(const CANMSG *message);
Bool CanReceiveMessage(CANMSG *message);    /* Returns True if message received. */


/*********************************************************************
* Function Name : delay_ms
* Description   : Generates delay

*********************************************************************/
void delay_ms(unsigned int delay)
{
  unsigned int i,j;
  for(i=0;i<delay;i++)
  {
  for(j=0;j<1275;j++);
  }
}


static uint8_t getTxbuffer(void);

/*********************************************************************
* Function Name : CanInit
* Description   : Put can into configuration mode.

*********************************************************************/

void CanInit(void)
  {
  C1CTRLbits.REQOP = 4;           /* Request configuration mode */
  while(C1CTRLbits.OPMODE != 4){  /* Wait until configuration mode entered */
    ;
    }
  }

/*********************************************************************
* Function Name : CanConfig
* Description   : Sets baud rate to 500Kbps with 20Tq for a clock of 10MHz

*********************************************************************/

void CanConfig(void)
  {
//	C1CFG1=0x0000;
//	C1CFG2=0x07FA;
  C1CFG1bits.BRP = 1;       /* 10 Meg clock */
  C1CFG1bits.SJW = 3;       /* Synchronized jump width time is 4Tq. */
  C1CFG2bits.PRSEG = 7;     /* Propagation time segment = 8Tq. */
  C1CFG2bits.SEG1PH = 5;    /* Phase buffer Segment 1 = 6Tq. */
  C1CFG2bits.SAM = 0;       /* Bus is sampled once. */
  C1CFG2bits.SEG2PHTS = 1;  /* PhaseSeg2 is freely programmable. */
  C1CFG2bits.SEG2PH = 4;    /* Phase buffer Segment 2 = 5Tq. */

  C1CTRL = 0x8000;          /* Can clock is Fcy = 10MHz. Request normal operation mode. */

  while(C1CTRLbits.OPMODE != 0){
    ;
    }
  }

/*********************************************************************
* Function Name : CanSetFilter
* Description   : This function sets the acceptance filter, SID for
                  standard length identifiers.

* Parameters    : uint16_t: filter_no:  (Filter number 0-5)
*                 uint16_t: sid:        (SID value)
*********************************************************************/

void CanSetFilter(uint8_t filter_no, uint32_t sid)
  {
  switch(filter_no)
    {
    case 0: C1RXF0SID = 0;
            C1RXF0SIDbits.SID = sid;
            break;
    case 1: C1RXF1SID = 0;
            C1RXF1SIDbits.SID = sid;
            break;
    case 2: C1RXF2SID = 0;
            C1RXF2SIDbits.SID = sid;
            break;
    case 3: C1RXF3SID = 0;
            C1RXF3SIDbits.SID = sid;
            break;
    case 4: C1RXF4SID = 0;
            C1RXF4SIDbits.SID = sid;
            break;
    case 5: C1RXF5SID = 0;
            C1RXF5SIDbits.SID = sid;
            break;

    default:C1RXF0SID = 0;
            C1RXF0SIDbits.SID = sid;
            break;
    }
  }

/*************************************************************************
* Function Name : CanSetMask
* Description   : This function sets the values for the acceptance
*                 filter masks for standard length identifiers.

* Parameters    : uint16_t: mask_no:  (Mask number 0-1)
*                 uint16_t: mask:     (Mask value)
**************************************************************************/

void CanSetMask(uint8_t mask_no, uint32_t mask)
  {
  switch(mask_no)
    {
    case 0: C1RXM0SID = 0x0001;
            C1RXM0SIDbits.SID = mask;
            break;
    case 1: C1RXM1SID = 0x0001;
            C1RXM1SIDbits.SID = mask;
            break;

    default:C1RXM0SID = 0x0001;
            C1RXM0SIDbits.SID = mask;
            break;
  }
}

/*************************************************************************
* Function Name : CanSetPriority
* Description   : This function sets the message transmission
*                 priority bits.

* Parameters    : uint16_t: buffer:   (Transmit buffer number 0-3)
                  uint16_t: priority: (Transmit priority 0-3)
**************************************************************************/

void CanSetPriority(uint8_t buffer, uint8_t priority)
  {
  priority = (priority > 3U) ? 3U : priority;

  switch(buffer)
    {
    case 0: C1TX0CONbits.TXPRI = priority;
            break;
    case 1: C1TX1CONbits.TXPRI = priority;
            break;
    case 2: C1TX2CONbits.TXPRI = priority;
            break;
    default:
            break;
    }
  }

/*********************************************************************
* Function Name : CanSendMessage
* Description   : This function writes the message identifier(SID),
                  writes the data to be transmitted into the Transmit buffer
*                 and sets the corresponding Transmit request bit.

* Parameters    : Pointer to structure CANMSG defined in can.h
*********************************************************************/

void CanSendMessage(const CANMSG *message)
  {
  uint8_t buffer;
  uint16_t ix = ((message->eid & 0x07C0) << 5) | ((message->eid & 0x003F) << 2);

  buffer = getTxbuffer();

  switch(buffer)
    {
    case 0: C1TX0SID = ix;
            break;
    case 1: C1TX1SID = ix;
            break;
    case 2: C1TX2SID = ix;
            break;

    default:C1TX0SID = ix;
            break;
    }

  for(ix = 0; ix < message->length; ix++)
    {
    switch(buffer)
      {
      case 0: *((uint8_t *)&C1TX0B1+ix)= message->data[ix];
              break;
      case 1: *((uint8_t *)&C1TX1B1+ix)= message->data[ix];
              break;
      case 2: *((uint8_t *)&C1TX2B1+ix)= message->data[ix];
              break;
      default:*((uint8_t *)&C1TX0B1+ix)= message->data[ix];
              break;
      }
    }

  switch(buffer)
    {
    case 0: C1TX0DLC = 0x0180;
            C1TX0DLCbits.DLC = message->length;
            C1TX0CONbits.TXREQ = 1;
            break;
    case 1: C1TX1DLC = 0x0180;
            C1TX1DLCbits.DLC = message->length;
            C1TX1CONbits.TXREQ = 1;
            break;
    case 2: C1TX2DLC = 0x0180;
            C1TX2DLCbits.DLC = message->length;
            C1TX2CONbits.TXREQ = 1;
            break;
    default:break;
    }
  }

/*************************************************************************
* Function Name : CanReceiveMessage
* Description   : If a message has been received, read the data from
                  the receive buffer into the structure CANMSG
                  and clear the RXFUL bit.

* Parameters    : Pointer to structure CANMSG defined in can.h
* Returns       : True if message received else False.
**************************************************************************/

Bool CanReceiveMessage(CANMSG *message)
  {
  uint8_t ix, buffer = 0;
  // uint16_t temp1,temp2;
  // temp1 = C1RX0SID;
  // temp2 = C2RX1SID;
  // temp1 = (temp1 >>2);
    uint32_t SID1 ,EID1,DLC1,var1;
SID1 = (C1RX0SID >> 2) *  0b1000000000000000000;
EID1 = (C1RX0EID) * 0b1000000;
DLC1 = (C1RX0DLC >> 10);
var1 = SID1 | EID1 | DLC1;
  if(C1RX0CONbits.RXFUL){
    buffer = 0;
    }
  else if(C1RX1CONbits.RXFUL){
    buffer = 1;
    }

  if(buffer != 0xff)
    {
    switch(buffer)
      {
      case 0: message->eid = var1;
      //message->eid = ((C1RX0SID >> 2) * 0b1000000000000000000) | ((C1RX0EID) * 0b1000000) | ((C1RX0DLC >> 10)) ;
              message->length = C1RX0DLCbits.DLC;
              break;
      case 1: message->eid = ((C1RX1SID >> 2) * 0b1000000000000000000) | ((C1RX1EID) * 0b1000000) | ((C1RX1DLC >> 10)) ;
              message->length = C1RX1DLCbits.DLC;
              break;
      default:
              break;
      }

    for(ix = 0; ix < message->length; ix++)
      {
      switch(buffer)
        {
        case 0: message->data[ix] = *((uint8_t *)&C1RX0B1 + ix);
                break;
        case 1: message->data[ix] = *((uint8_t *)&C1RX1B1 + ix);
                break;
        default:
              break;
        }
      }

    switch(buffer)
      {
      case 0: C1RX0CONbits.RXFUL = 0;
              break;
      case 1: C1RX1CONbits.RXFUL = 0;
              break;
      default:
              break;
      }
    }

  return (buffer != 0xff) ? True : False;
  }

/*************************************************************************
* Function Name : getTxbuffer
* Description   : Returns an available empty transmit buffer.

* Returns       : Transmit buffer number 0-2.
**************************************************************************/

static uint8_t getTxbuffer(void)
  {
  uint8_t buffer = 0;

  if(C1TX0CONbits.TXREQ == 0){
    buffer = 0;
    }
  else if(C1TX1CONbits.TXREQ == 0){
    buffer = 1;
    }
  else if(C1TX2CONbits.TXREQ == 0){
    buffer = 2;
    }

  return buffer;
  }



  /*************************************************************************
  * Function Name : PWM_init
  * Description   : Initializes the timers, sets PORTD as output
  * Parameters    : Pointer to structure CANMSG defined in can.h
  * Returns       : True if message received else False.
  **************************************************************************/

  void PWM_init(float period)
  {

  	TRISD = 0b1100001111000000;

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
  /*************************************************************************
  * Function Name : PWM_start
  * Description   : generates the PWM of given dutycycle and period at
                    desired pin

  * Parameters    : dytycycle in percetage,period,and pin number
  **************************************************************************/

  void PWM_generate(float dutycycle,float period,int pin)
  {

    //int pulse, space;//, period;   // pulse width, space width, period
    //period = 30e6 / frequency;               // f_m = 30e6 / 600 = 50 kHz
  //  pulse = dutycycle * period; // width of PWM pulses
  //  space = period - pulse;     // gap between PWM pulses

  	if(pin==5)
  	{
  		OC3CONbits.OCM = 0b101;
  		OC3R = 0;     // pulse start time
  		OC3RS = dutycycle * period / 100;   // pulse end time
  	}
  	else if(pin==6)
  	{
  		OC4CONbits.OCM = 0b101;
  		OC4R = 0;       // pulse start time
    	OC4RS = dutycycle * period / 100;   // pulse end time
  	}
  	else if(pin==7)
  	{
  		OC5CONbits.OCM = 0b101;
  		OC5R = 0;       // pulse start time (start of gap in PWM3)
    	OC5RS = dutycycle * period / 100;   // pulse end time (end of gap in PWM3)
  	}
  	else if(pin==8)
  	{
  		OC6CONbits.OCM = 0b101;
  		OC6R = 0;       // pulse start time (start of gap in PWM4)
    	OC6RS = dutycycle * period / 100;   // pulse end time (end of gap in PWM4)
  	}
  }


/*--- End of file. ---*/

#endif
