/*********************************************************************
* File Name     : CanLib.h 
* Description   : Header file for CanLib.c                      

* Revision      : 1.0 
* Date          : 02/09/05 
*********************************************************************/

#ifndef CANLIB_H
#define CANLIB_H

#include <p30f4011.h>
#include <types.h>

/*--- Can message structure. ---*/

typedef struct
  {
  uint16_t sid;    
  uint8_t length;
  uint8_t data[8];
  }CANMSG;
     
/*--- CanLib function prototypes. ---*/

void CanInit(void);                                 /* Call this function first */
void CanSetMask(uint8_t mask_no, uint16_t mask);    /* Then set up masks */ 
void CanSetFilter(uint8_t filter_no, uint16_t sid); /* and filters */
void CanConfig(void);                               /* Then call this function last, to enable can. */

void CanSetPriority(uint8_t buffer, uint8_t priority);
void CanSendMessage(const CANMSG *message);
Bool CanReceiveMessage(CANMSG *message);    /* Returns True if message received. */ 

/*--- End of file. ---*/

#endif

