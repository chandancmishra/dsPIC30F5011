//#include<can.h>
#include<p30f5011.h>
#include "types.h"
/*#if defined(__dsPIC30F4013__) || defined(__dsPIC30F5011__) || defined(__dsPIC30F6011__)  || defined(__dsPIC30F6012__) \
    || defined(__dsPIC30F5013__) || defined(__dsPIC30F6013__) || defined(__dsPIC30F6014__) || defined(__dsPIC30F4012__) \
    || defined(__dsPIC30F4011__) || defined(__dsPIC30F6010__) || defined(__dsPIC30F5015__) || defined(__dsPIC30F6010A__) \
    || defined(__dsPIC30F6011A__) || defined(__dsPIC30F6012A__) || defined(__dsPIC30F6013A__) || defined(__dsPIC30F6014A__)
*/
/************************************************************************
* Function Name     : ConfigIntCAN1
* Description       : This function configures the interrupts for CAN1
*
* Parameters        : unsigned int: config1 individual interrupt enable
*                     unsigned int: config2 interrupt priority and enable/disable
*                                   information
* Return Value      : None
*************************************************************************/
/*void ConfigIntCAN1(unsigned int,unsigned int);
void CAN1SetOperationMode(unsigned int);
void CAN1SetMask(char, unsigned int, unsigned long);
void CAN1SetFilter(char, unsigned int, unsigned long)
void CAN1SendMessage(unsigned int, unsigned long , unsigned char*, unsigned char,char);
void CAN1ReceiveMessage(unsigned char * , unsigned char,char);
*/
typedef struct
  {
  uint32_t eid;
  uint8_t length;
  uint8_t data[8];
  }CANMSG;

void delay_ms(unsigned int delay)
{
  unsigned int i,j;
  for(i=0;i<delay;i++)
  {
  for(j=0;j<1275;j++);
  }
}
void ConfigIntCAN1(unsigned int config1, unsigned int config2)
{
    C1INTF = 0;                          /* the individual flag register cleared */

    IFS1bits.C1IF = 0;                   /* Clear combined IRQ C2IF */
    C1INTE = config1;

    IPC6bits.C1IP = config2 & 0x07;      /* set interrupt priority */
    IEC1bits.C1IE = (config2 & 0x08) >>3;/* enable or disable interrupt */

}


/***************************************************************************
* Function Name     : CAN1SetOperationMode
* Description       : This function configures the following bits of CxCTRL:
*                     CSIDL, REQOP<2:0> and CANCKS
* Parameters        : unsigned int config
* Return Value      : None
****************************************************************************/

void CAN1SetOperationMode(unsigned int config)
{
   C1CTRL = config;
}



/*************************************************************************
* Function Name     : CAN1SetMask
* Description       : This function sets the values for the acceptance
*                     filter mask registers (SID and EID)
* Parameters        : char: mask_no
*                     unsigned int: sid register value
*                     unsigned long: eid registers value
* Return Value      : None
**************************************************************************/

void CAN1SetMask(char mask_no, unsigned int sid, unsigned long eid)
{
    unsigned int uppereid = eid >>16;
    switch(mask_no)
    {
    case 0:
      C1RXM0SID = sid;
      C1RXM0EIDH = uppereid;     /*upper 16 to the EIDH reg */
      C1RXM0EIDL = eid;          /*lower 16 to EIDL */
      break;
    case 1:
      C1RXM1SID = sid;
      C1RXM1EIDH = uppereid;     /*upper 16 to the EIDH reg */
      C1RXM1EIDL = eid;          /*lower 16 to EIDL */
      break;
    default:
      C1RXM0SID = sid;
      C1RXM0EIDH = uppereid;     /*upper 16 to the EIDH reg */
      C1RXM0EIDL = eid;          /*lower 16 to EIDL */
      break;
    }
}




/*********************************************************************
* Function Name     : CAN1SetFilter
* Description       : This function sets the acceptance filter values
*                     (SID and EID) for the specified filter
* Parameters        : char: filter_no
*                     unsigned int: sid register value
*                     unsigned long: eid registers value
* Return Value      : None
*********************************************************************/

void CAN1SetFilter(char filter_no, unsigned int sid, unsigned long eid)
{
    unsigned int uppereid = eid >>16;
    switch(filter_no)
    {
    case 0:
      C1RXF0SID = sid;
      C1RXF0EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF0EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 1:
      C1RXF1SID = sid;
      C1RXF1EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF1EIDL = eid;        /*lower 16 to EIDH */
      break;
    case 2:
      C1RXF2SID = sid;
      C1RXF2EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF2EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 3:
      C1RXF3SID = sid;
      C1RXF3EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF3EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 4:
      C1RXF4SID = sid;
      C1RXF4EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF4EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 5:
      C1RXF5SID = sid;
      C1RXF5EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF5EIDL = eid;        /*lower 16 to EIDL */
      break;
    default:
      C1RXF0SID = sid;
      C1RXF0EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF0EIDL = eid;        /*lower 16 to EIDL */
      break;
    }
}



/******************************************************************************
* Function Name     : CAN1SendMessage
* Description       : This function writes the message identifiers (SID, EID),
                      writes the data to be transmitted into the Transmit buffer
*                     and sets the corresponding Transmit request bit.
* Parameters        : unsigned long: id
*                     unsigned char: * data
*                     unsigned char: datalen
*                     char: MsgFlag
* Return Value      : None
*******************************************************************************/

void CAN1SendMessage(unsigned int sid, unsigned long eid, unsigned char * data, unsigned char  datalen,char MsgFlag)
{
    int i;
    unsigned int uppereid = eid >> 16;
    switch(MsgFlag)
    {
    case 0:
        C1TX0SID = sid;
        C1TX0EID = uppereid;
        C1TX0DLC = eid;
        break;
    case 1:
        C1TX1SID = sid;
        C1TX1EID = uppereid;
        C1TX1DLC = eid;
        break;
    case 2:
        C1TX2SID = sid;
        C1TX2EID = uppereid;
        C1TX2DLC = eid;
	break;
    default:
        C1TX0SID = sid;
        C1TX0EID = uppereid;
        C1TX0DLC = eid;
        break;
    }
    for(i = 0;i < datalen;i++)
    {
        switch(MsgFlag)
        {
        case 0: *((unsigned char *)&C1TX0B1+i)= data[i];
            break;
        case 1: *((unsigned char *)&C1TX1B1+i)= data[i];
            break;
        case 2: *((unsigned char *)&C1TX2B1+i)= data[i];
            break;
        default:*((unsigned char *)&C1TX0B1+i)= data[i];
            break;
        }
    }

    /* Msg send request */
    switch(MsgFlag)
    {
    case 0:
        C1TX0DLCbits.DLC = datalen;
        C1TX0CONbits.TXREQ = 1;
        break;
    case 1:
        C1TX1DLCbits.DLC = datalen;
        C1TX1CONbits.TXREQ = 1;
        break;
    case 2:
        C1TX2DLCbits.DLC = datalen;
        C1TX2CONbits.TXREQ = 1;
        break;
    default:
        C1TX0DLCbits.DLC = datalen;
        C1TX0CONbits.TXREQ = 1;
        break;
    }
}


/*************************************************************************
* Function Name     : CAN1ReceiveMessage
* Description       : This function reads the data from the receive buffer
*                     into an array.
* Parameters        : unsigned char*: data pointer
*                     unsigned char:  datalen
*                     char:           MsgFlag
* Return Value      : void
**************************************************************************/

void CAN1ReceiveMessage(CANMSG *message, unsigned char  datalen,char MsgFlag)
{
    uint32_t SID,EID,DLC;
    uint32_t var = 0;

    int i;
/*    for(i = 0;i<datalen;i++)
    {
        switch(MsgFlag)
        {
        case 0:
            message->data[i]  = *((unsigned char *)&C1RX0B1 + i);
            break;
        case 1:
            message->data[i]  = *((unsigned char *)&C1RX1B1 + i);
            break;
        default:
            message->data[i]  = *((unsigned char *)&C1RX0B1 + i);
            break;

          }
        }*/
        switch(MsgFlag)
        {
        case 0:
            SID = C1RX0SID;
            EID = C1RX0EID;
            DLC = C1RX0DLC;
          //  SID = ((SID >> 2)<<18);
            SID = (SID >> 2);
            SID = (SID <<18);
            var = SID;
            EID = (EID << 6);
            var = var | EID;
            DLC = DLC >> 11;
            var = var | DLC;
            message->eid = var;
            message->length = C1RX0DLCbits.DLC;
            for (i = 0; i < datalen; i++) {
            message->data[i]  = *((unsigned char *)&C1RX0B1 + i);
            }
            break;
        case 1:
            SID = C1RX1SID;
            EID = C1RX1EID;
            DLC = C1RX1DLC;
            //SID = ((SID >> 2)<<18);
            SID = (SID >> 2);
            SID = (SID <<18);
            var = SID;
            EID = (EID << 6);
            var = var | EID;
            DLC = DLC >> 11;
            var = var | DLC;
            message->eid = var;
            message->length = C1RX1DLCbits.DLC;
            for (i = 0; i < datalen; i++) {
            message->data[i]  = *((unsigned char *)&C1RX1B1 + i);
            }
            break;
        default:
          break;
        }

}







/****************************************************************************
* Function Name     : CAN1IsTXReady
* Description       : This function returns TXREQ bit status which indicates
*                     whether the transmitter is ready for next transmission.
* Parameters        : char: buffno
* Return Value      : char: compliment of TXREQ bit status
*****************************************************************************/

char CAN1IsTXReady(char buffno)
{
    switch(buffno)
    {
    case 0:
        return !(C1TX0CONbits.TXREQ);
        break;
    case 1:
        return !(C1TX1CONbits.TXREQ);
        break;
    case 2:
        return !(C1TX2CONbits.TXREQ);
        break;
    }
    return 0;
}


/*************************************************************************
* Function Name     : CAN1Initialize
* Description       : This function configures Sync jump width, Baud Rate
*                     Pre-scaler, Phase Buffer Segment 1 and 2, and
*                     Propogation time segment.
* Parameters        : unsigned int: config1, unsigned int: config2
* Return Value      : None
**************************************************************************/

void CAN1Initialize(unsigned int config1, unsigned int config2)
{
    C1CFG1 = config1; /* configure SJW and BRP */
    C1CFG2 = config2; /* configure PHSEG2 and PHSEG1 and PROPSEG */
}

//unsigned char *data;
//unsigned char data1[]={1,2,2,2,2,2,2,2};
CANMSG msg1,msg2,msg3,msg4;
int main(){

TRISF=0xFD;
C1CTRLbits.REQOP=4;
while(C1CTRLbits.OPMODE != 4){
    ;
    }

//CAN1SetFilter('3',0b11000111111,0b101110111000000000);
CAN1SetFilter('3',0b11000111111,0b101110111000000000);

CAN1SetMask('0',0,0);
C1CFG1=0x0000;
C1CFG2=0x0086;
 // C1CFG1bits.BRP = 1;       /* 10 Meg clock */
  //C1CFG1bits.SJW = 3;       /* Synchronized jump width time is 4Tq. */
  //C1CFG2bits.PRSEG = 7;     /* Propagation time segment = 8Tq. */
  //C1CFG2bits.SEG1PH = 5;    /* Phase buffer Segment 1 = 6Tq. */
  //C1CFG2bits.SAM = 0;       /* Bus is sampled once. */
  //C1CFG2bits.SEG2PHTS = 1;  /* PhaseSeg2 is freely programmable. */
  //C1CFG2bits.SEG2PH = 4;    /* Phase buffer Segment 2 = 5Tq. */
  C1CTRL = 0x8800;          /* Can clock is Fcy = 10MHz. Request normal operation mode. */


ConfigIntCAN1(0x00FF,0);
C1CTRLbits.REQOP=0;

while(C1CTRLbits.OPMODE != 0){
    ;
    }


while(1){



      CAN1ReceiveMessage(&msg,8,0);
      delay_ms(100);
      /*if(C1RX0CONbits.RXFUL)
      {C1RX0CONbits.DBEN=1;}
      */
      // C1RX0B1 = 0;
      // C1RX0B2 = 0;
      // C1RX0B3 = 0;
      // C1RX0B4 = 0;
      // C1RX1B1 = 0;
      // C1RX1B2 = 0;
      // C1RX1B3 = 0;
      // C1RX1B4 = 0;

      delay_ms(100);
      //CAN1SendMessage(0b101110111000000000,0b11000111111,&data, 8,1);
      delay_ms(100);
        }

return 0;
}
