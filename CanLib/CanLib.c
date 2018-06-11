/*--------------------------------------------------------------------

  Title     : Can routines for dsPIC30f. 
  Filename  : CanLib.c 
  Author    : RW
  
----------------------------------------------------------------------

  CHANGE HISTORY

  Issue   Modifier  Date      Change Description
  1.0     RW        02/09/05  First Issue
  
----------------------------------------------------------------------

  Module Description: 
  Can utility library.
  Configure can module. 
  Send and receive can messages with standard identifiers. 
  
--------------------------------------------------------------------*/

#include "canlib.h"

/*--- Function prototypes ---*/

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

void CanSetFilter(uint8_t filter_no, uint16_t sid)
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

void CanSetMask(uint8_t mask_no, uint16_t mask)
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
  uint16_t ix = ((message->sid & 0x07C0) << 5) | ((message->sid & 0x003F) << 2); 

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
  uint8_t ix, buffer = 0xff;

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
      case 0: message->sid = (C1RX0SID >> 2) & 0x07ff;
              message->length = C1RX0DLCbits.DLC;
              break;
      case 1: message->sid = (C1RX1SID >> 2) & 0x07ff;
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

/*--- End of file.---*/
