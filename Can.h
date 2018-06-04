#include <p30f5011.h>
#include "Hardware.h"

 void init_can1();
 void init_can2();


extern unsigned int OutData0[4];

extern unsigned int OutData1[4];

 // Intilializing the receive register to be 0

 unsigned int InData0[4] = {0, 0, 0, 0};
 unsigned int InData1[4] = {0, 0,0, 0};
 unsigned int temp;

 
// **********************CAN Initialize***************************//

 void init_can1()

{
 
                
     C1CFG1=0x0000;//BRP=0
     C1CFG2=0x07FA;
     
     ///Interrupt Section of CAN Peripheral
     C1INTF = 0;                    //Reset all The CAN Interrupts 
     IFS1bits.C1IF = 0;             //Reset the Interrupt Flag status register
     C1INTE = 0x00FF;               //Enable all CAN interrupt sources
     IEC1bits.C1IE = 1;             //Enable the CAN1 Interrupt 
 
   
     C1CTRLbits.CANCKS = 1; 
 
  
      
    //Set Receive Registers
     C1RX0CON =  0x0000;



     //set masks for SID:
     C1RXM0SID  =  0b1111111111111100;
     C1RXM0SIDbits.MIDE=1;
  
 
     //Initializing of Acceptance Filter n Standard Identifier for CAN1
     C1RXF0SID     = 0b0001111011101000;    //CAN1 Receive Acceptance Filter2 SID         
     C1RXF0SIDbits.EXIDE=0;                 //   Enable filter for standard identifier

     //set masks for EID:
    
   //  C1RX1CONbits.FILHIT=2;
  
     C1RX1CON=0b0000000000000011;


    C1RXM1SID =  0b1111111111111111;
    C1RXM1EIDH = 0b1111111111111111;
    C1RXM1EIDL = 0b1111110000000000;

    C1RXF2SID =  0b0000110011110011;
    C1RXF2EIDH = 0b0000000000010000;
    C1RXF2EIDL = 0b0000000000000000;

    C1RXF3SID =  0b0000110011110011;
    C1RXF3EIDH = 0b0000000000001100;
    C1RXF3EIDL = 0b0000000000000000;

    C1RXF4SID =  0b0001100011111111;
    C1RXF4EIDH = 0b0000101111000100;
    C1RXF4EIDL = 0b0000000000000000;
  


/*
     C1RXM1SID  =  0b1111111111111100;
     C1RXM1SIDbits.MIDE=1;
     C1RXM1EIDH =  0b0000111111111111;
     C1RXM1EIDL =  0b1111110000000000;

     //Initializing of Acceptance Filter n Standard Identifier for CAN1
    
     
     C1RXF2SID     = 0b0000110001000001;   //CAN1 Receive Acceptance Filter2 SID
     C1RXF2SIDbits.EXIDE=1;                // Enable filter for extended identifier
     C1RXF2EIDH    = 0b0000000000001100;   //CAN1 Receive Acceptace  Filter2 Extended Identifier high byte
     C1RXF2EIDL    = 0b0000000000000000;   //CAN1 Receive Acceptance Filter2 Extended identifier low byte
     
*/
                
     //Set Transmit Registers
         //TX0
     C1TX0CON = 0x0002;     
     
     C1TX0SID = 0b1111000010100000;     // SID 
     C1TX0SIDbits.TXIDE=1;
     C1TX0EID = 0b0011000011011101;     // EID 
     C1TX0DLC = 0b0010010001000000;     //Select the Data word Length for CAN1 Transmit Buffer0 which is 8 byte  
     
     // Data Field 1,Data Field 2, Data Field 3, Data Field 4 // 8 bytes selected by DLC 
     C1TX0B1 = OutData0[0];
     C1TX0B2 = OutData0[1];
     C1TX0B3 = OutData0[2];
     C1TX0B4 = OutData0[3];
 
      

     //TX1
     C1TX1CON = 0x0003;            
     C1TX1SID = 0b1111000010100000;             // SID 
     C1TX1SIDbits.TXIDE=1; 
     C1TX1EID = 0b0001100011011011;             // EID                   
     C1TX1DLC = 0b1010100001000000;             //Select the Data word Length for CAN1 Transmit Buffer1 which
                                                // is 4 byte
    
     //Data Field 1, Data Field 2 // 4 bytes selected by DLC
     C1TX1B1 = OutData1[0];
     C1TX1B2 = OutData1[1];
     C1TX1B3 = OutData1[2];
     C1TX1B4 = OutData1[3];

     
    
 }



void init_can2()
{/*
         C2CFG1 = 0x0000;
         C2CFG2 = 0x0086;

        ///Interrupt Section of CAN Peripheral
     C2INTF = 0;                    //Reset all The CAN Interrupts 
     IFS2bits.C2IF = 0;             //Reset the Interrupt Flag status register
     C2INTE = 0x00FF;               //Enable all CAN interrupt sources
     IEC2bits.C2IE = 1;             //Enable the CAN1 Interrupt 
 
   
     C2CTRLbits.CANCKS = 1; 

    //Set Receive Registers
     C2RX0CON =  0x0000;


            */
     C2CFG1=0x0000;//BRP=0
     C2CFG2=0x07FA;
     
     ///Interrupt Section of CAN Peripheral
     C2INTF = 0;                    //Reset all The CAN Interrupts 
     IFS2bits.C2IF = 0;             //Reset the Interrupt Flag status register
     C2INTE = 0x00FF;               //Enable all CAN interrupt sources
     IEC2bits.C2IE = 1;             //Enable the CAN1 Interrupt 
 
   
     C2CTRLbits.CANCKS = 1; 
 
  
      
    //Set Receive Registers
     C2RX0CON =  0x0000;



     //set masks for SID:
     C2RXM0SID  =  0b1111111111111100;
     C2RXM0SIDbits.MIDE=1;
  
 
     //Initializing of Acceptance Filter n Standard Identifier for CAN1
     C2RXF0SID     = 0b0001111011101000;    //CAN1 Receive Acceptance Filter2 SID         
     C2RXF0SIDbits.EXIDE=0;                 //   Enable filter for standard identifier

     //set masks for EID:
    
   //  C1RX1CONbits.FILHIT=2;
  
     C2RX1CON=0b0000000000000011;


    C2RXM1SID =  0b1111111111111111;
    C2RXM1EIDH = 0b1111111111111111;
    C2RXM1EIDL = 0b1111110000000000;

    C2RXF2SID =  0b0000110011110011;
    C2RXF2EIDH = 0b0000000000010000;
    C2RXF2EIDL = 0b0000000000000000;

    C2RXF3SID =  0b0000110011110011;
    C2RXF3EIDH = 0b0000000000001100;
    C2RXF3EIDL = 0b0000000000000000;

    C2RXF4SID =  0b0001100011111111;
    C2RXF4EIDH = 0b0000101111000100;
    C2RXF4EIDL = 0b0000000000000000;
  


/*
     C1RXM1SID  =  0b1111111111111100;
     C1RXM1SIDbits.MIDE=1;
     C1RXM1EIDH =  0b0000111111111111;
     C1RXM1EIDL =  0b1111110000000000;

     //Initializing of Acceptance Filter n Standard Identifier for CAN1
    
     
     C1RXF2SID     = 0b0000110001000001;   //CAN1 Receive Acceptance Filter2 SID
     C1RXF2SIDbits.EXIDE=1;                // Enable filter for extended identifier
     C1RXF2EIDH    = 0b0000000000001100;   //CAN1 Receive Acceptace  Filter2 Extended Identifier high byte
     C1RXF2EIDL    = 0b0000000000000000;   //CAN1 Receive Acceptance Filter2 Extended identifier low byte
     
*/
                
     //Set Transmit Registers
         //TX0
     C2TX0CON = 0x0002;     
     
     C2TX0SID = 0b1111000010100000;     // SID 
     C2TX0SIDbits.TXIDE=1;
     C2TX0EID = 0b0011000011011101;     // EID 
     C2TX0DLC = 0b0010010001000000;     //Select the Data word Length for CAN1 Transmit Buffer0 which is 8 byte  
     
     // Data Field 1,Data Field 2, Data Field 3, Data Field 4 // 8 bytes selected by DLC 
     C2TX0B1 = OutData0[0];
     C2TX0B2 = OutData0[1];
     C2TX0B3 = OutData0[2];
     C2TX0B4 = OutData0[3];
 
      

     //TX1
     C2TX1CON = 0x0003;            
     C2TX1SID = 0b1111000010100000;             // SID 
     C2TX1SIDbits.TXIDE=1; 
     C2TX1EID = 0b0001100011011011;             // EID                   
     C2TX1DLC = 0b1010100001000000;             //Select the Data word Length for CAN1 Transmit Buffer1 which
                                                // is 4 byte
    
     //Data Field 1, Data Field 2 // 4 bytes selected by DLC
     C2TX1B1 = OutData1[0];
     C2TX1B2 = OutData1[1];
     C2TX1B3 = OutData1[2];
     C2TX1B4 = OutData1[3];

     
    

}