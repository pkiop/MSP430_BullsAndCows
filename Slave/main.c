#include <msp430.h>
#include "USER_TOP_HEADER.h"

#define MLED1 0x62
#define MLED2 0x83
#define SLED1 0x77
#define SLED2 0x23
#define ON  0x11
#define OFF 0x07
#define STURN 223
#define MTURN 233

unsigned int NB[3]={0};//Numberboard
unsigned int ENB[3]={0};//적의 numberboard
unsigned int NST=0; //numberselecstate;
unsigned char USENUM='0';
unsigned int usenum=0;
unsigned int i;
unsigned int j;
unsigned int y;
unsigned int cal;
unsigned int turnchk=0;
int strike;
int breakchk=0;

unsigned int temp_ENB=0;
unsigned int temp_cal=0;
unsigned int transin;

void Init_system(void);
void Init_SPIMaster(void);


void firstselection(void);




void main(void)
{
	   Init_system();

	   int yyy=10,xxx=10,iii=8;
	   Print_Character('N',xxx,10,2,0);
	   Print_Character('u',xxx+20,yyy+10,1,0);
	   Print_Character('m',xxx+20+i,yyy+10,1,0);
	   Print_Character('b',xxx+20+2*i,yyy+10,1,0);
	   Print_Character('e',xxx+20+3*i,yyy+10,1,0);
	   Print_Character('r',xxx+20+4*i,yyy+10,1,0);
	 	 	 __delay_cycles(20000000);
	   Print_Character('B',xxx+10,yyy+40,2,0);
	   Print_Character('a',xxx+28,yyy+50,1,0);
	   Print_Character('s',xxx+20*i,yyy+50,1,0);
	   Print_Character('e',xxx+20+2*i,yyy+50,1,0);
	   Print_Character('b',xxx+20+3*i,yyy+50,1,0);
	   Print_Character('a',xxx+20+4*i,yyy+50,1,0);
	   Print_Character('l',xxx+20+5*i,yyy+50,1,0);
	   Print_Character('l',xxx+20+6*i,yyy+50,1,0);
	   __delay_cycles(15000000);
	   LcdClear();

	   	 Print_Character('N',xxx,10,2,0);
	     Print_Character('u',xxx+20,yyy+10,1,0);
	     Print_Character('m',xxx+20+i,yyy+10,1,0);
	     Print_Character('b',xxx+20+2*i,yyy+10,1,0);
	     Print_Character('e',xxx+20+3*i,yyy+10,1,0);
	     Print_Character('r',xxx+20+4*i,yyy+10,1,0);
	     Print_Character('B',xxx+10,yyy+40,2,0);
	     Print_Character('a',xxx+28,yyy+50,1,0);
	     Print_Character('s',xxx+20*i,yyy+50,1,0);
	     Print_Character('e',xxx+20+2*i,yyy+50,1,0);
	     Print_Character('b',xxx+20+3*i,yyy+50,1,0);
	     Print_Character('a',xxx+20+4*i,yyy+50,1,0);
	     Print_Character('l',xxx+20+5*i,yyy+50,1,0);
	     Print_Character('l',xxx+20+6*i,yyy+50,1,0);
	     __delay_cycles(15000000);
	     LcdClear();


		 	  Print_Character('N',xxx,10,2,0);
	          Print_Character('u',xxx+20,yyy+10,1,0);
	          Print_Character('m',xxx+20+i,yyy+10,1,0);
	          Print_Character('b',xxx+20+2*i,yyy+10,1,0);
	          Print_Character('e',xxx+20+3*i,yyy+10,1,0);
	          Print_Character('r',xxx+20+4*i,yyy+10,1,0);
	          Print_Character('B',xxx+10,yyy+40,2,0);
	          Print_Character('a',xxx+28,yyy+50,1,0);
	          Print_Character('s',xxx+20*i,yyy+50,1,0);
	          Print_Character('e',xxx+20+2*i,yyy+50,1,0);
	          Print_Character('b',xxx+20+3*i,yyy+50,1,0);
	          Print_Character('a',xxx+20+4*i,yyy+50,1,0);
	          Print_Character('l',xxx+20+5*i,yyy+50,1,0);
	          Print_Character('l',xxx+20+6*i,yyy+50,1,0);
	 	 	 __delay_cycles(15000000);
	          LcdClear();

   j=14;
   i=10;
   Print_Char('M',j,0);
   Print_Char('U',j+i,0);
   Print_Char('M',j+2*i,0);
   Print_Char('B',j+3*i,0);
   Print_Char('E',j+4*i,0);
   Print_Char('R',j+5*i,0);

   DrawLine(10,10,10,76,3);
   DrawLine(10,76,45,76,3);
   DrawLine(45,76,45,10,3);
   DrawLine(45,10,10,10,3);

   DrawLine(10,32,45,32,3);
   DrawLine(10,54,45,54,3);

   DrawCircle(16,63,9,1);

   firstselection();

}



void Init_system(void)
{
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer

	Init_DIO();

	Init_UCS();
	Init_UCA1_UART();

	Init_LCD();
	LcdClear();

	Init_SPIMaster();
	//Create_Circle_template(10);
	//DRAW_TAMLATE(CIRCLE_TEMPLATE,50,50,10*2+1,10*2+1);

//	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
	__bis_SR_register(GIE);       // enable interrupts

}

void Init_SPIMaster(void)
  {

                                            // Set P1.1 for slave reset
  P3SEL |= 0x31;                            // P3.5,4,0,3 option select

  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    // 3-pin, 8-bit SPI master
                                            // Clock polarity high, MSB
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0x02;                           // /2
  UCA0BR1 = 0;                              //
  UCA0MCTL = 0;                             // No modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

  P3SEL |= 0x0e;                            // P3.1,2,3 option select 0000 1110

  UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCB0CTL0 |= UCSYNC+UCCKPL+UCMSB;          // 3-pin, 8-bit SPI slave,
                                          // Clock polarity high, MSB
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCB0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

  P1OUT &= ~0x02;                           // Now with SPI signals initialized,
  P1OUT |= 0x02;                            // reset slave

  __delay_cycles(100);                      // Wait for slave to initialize

 // MST_Data = 0x01;                          // Initialize data values
 // SLV_Data = 0x00;                          //

// while (!(UCA0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
//  UCA0TXBUF = MST_Data;                     // Transmit first character
 }

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{

   static int tmp_a=10;//,init_flag=0;
   static int tmp_c=50,tmp_r=50;

  switch(__even_in_range(P2IV,0x10))
  {
  	  breakchk=breakchk+1;
      if(breakchk<5)
      	  { break;}
      	  breakchk=0;
  case 0x0:break;                             // Vector 0 - no interrupt
  case 0x2:

   break;
  case 0x4://LEFT
	  breakchk=breakchk+1;
	      	  if(breakchk<2)
	      	  { break;}
	      	  breakchk=0;
	 	 __delay_cycles(100);
	  	  if(USENUM>'0')
	  	 {
	  		 USENUM=USENUM-1;
	  		 usenum=usenum-1;
	  		Print_Character(USENUM,14,57,1,0);
	  	 }

	  	  break;
  case 0x6://RIGHT
	  breakchk=breakchk+1;
	      	  if(breakchk<2)
	      	  { break;}
	      	  breakchk=0;
	 	 __delay_cycles(100);
	  	 if(USENUM<'9')
	  	 {
	  		 USENUM=USENUM+1;
	  		 usenum=usenum+1;
		    Print_Character(USENUM,14,57,1,0);

	  	 }

	  	  break;
  case 0x8://select

	  break;

  case 0xa://up

     break;
  case 0xc://down

     break;
  case 0xe://a
	  breakchk=breakchk+1;
	      	  if(breakchk<3)
	      	  { break;}
	      	  breakchk=0;
	  __delay_cycles(100);

 	   NST++;
 	   switch(NST)
 	   {
 	   	   case 1:
 	   		 NB[0]=USENUM-48;
 	   		 Print_Character(USENUM,15,17,2,0);
 	   		 break;
 	   	   case 2:
 	   		 NB[1]=USENUM-48;
 	   		 Print_Character(USENUM,37,17,2,0);
 	   		break;
 	   	   case 3:
 	   		NB[2]=USENUM-48;
 	   		Print_Character(USENUM,59,17,2,0);
 	   		j=10;
 	   		i=8;
 	   		y=79;
 	   		if(NB[0]==NB[1] || NB[1]==NB[2] || NB[2]==NB[0])
 	   		{
 	 	   		Print_Char('R',j,y);
 	 	   		Print_Char('E',j+i,y);
 	 	   		Print_Char(' ',j+2*i,y);
 	 	   		Print_Char('P',j+3*i,y);
 	 	   		Print_Char('U',j+4*i,y);
 	 	   		Print_Char('T',j+5*i,y);
 	 	    	DEL_LAYER(11,11,21,33);
 	 	    	DEL_LAYER(33,11,21,33);
 	 	    	DEL_LAYER(55,11,21,33);
 	 	   		NST=0;
 	 	   		break;
 	   		}
 	   		Print_Char('S',j,y);
 	   		Print_Char('U',j+i,y);
 	   		Print_Char('R',j+2*i,y);
 	   		Print_Char('E',j+3*i,y);
 	   		Print_Char(':',j+4*i,y);
 	   		Print_Char('A',j+5*i,y);
 	   		break;
 	   	   case 4:
 	   		cal = NB[0]*100+NB[1]*10+NB[2];
 	   		if (cal<=200)
 	   			{
 	  	 	 __delay_cycles(100000);

 	   				while (!(UCA0IFG&UCTXIFG));
 	   				UCA0TXBUF=cal;
 	   		 	 __delay_cycles(100000);
 	   				while (!(UCA0IFG&UCTXIFG));
 	   				UCA0TXBUF=253;

 	   			}
 	   		else if (cal<=400)
 	   			{
 	   			__delay_cycles(100000);
 	   				while (!(UCA0IFG&UCTXIFG));
 	   		 	   	UCA0TXBUF=200;
 	   		 	 __delay_cycles(100000);
 	   		 	   	while (!(UCA0IFG&UCTXIFG));
 	   		 	 	UCA0TXBUF=cal-200;
 	   		 	 __delay_cycles(100000);
 	   		 	   	while (!(UCA0IFG&UCTXIFG));
 	   		 	   	UCA0TXBUF=253;

 	   			}
 	   		else if (cal<=600)
 	   	 	   			{
 	   				__delay_cycles(100);
 	   	 	   				while (!(UCA0IFG&UCTXIFG));
 	   	 	   		 	   	UCA0TXBUF=200;
 	   	 	  	 	 __delay_cycles(100000);
 	   	 	   		 	   	while (!(UCA0IFG&UCTXIFG));
 	   	 	   		 	    UCA0TXBUF=200;
 	   	 	  	 	 __delay_cycles(100000);
 	   	 	   		 	   	while (!(UCA0IFG&UCTXIFG));
 	   	 	   		 	 	UCA0TXBUF=cal-400;
 	   	 	  	 	 __delay_cycles(100000);
 	   	 	   		 	   	while (!(UCA0IFG&UCTXIFG));
 	   	 	   		 	   	UCA0TXBUF=253;
 	   	 	   			}
 	   		else if (cal<=800)
 	    	   			{
 	  	 	 __delay_cycles(100000);
 	    	   				while (!(UCA0IFG&UCTXIFG));
 	    	   		 	   	UCA0TXBUF=200;
 	    	   		 	 __delay_cycles(100000);
 	    	   		 	   	while (!(UCA0IFG&UCTXIFG));
 	    	   		 	 	UCA0TXBUF=200;
 	    	   		 	 __delay_cycles(100000);
 	    	   		 	 	while (!(UCA0IFG&UCTXIFG));
 	    	   		 	 	UCA0TXBUF=200;

 	    	   		 	 __delay_cycles(100000);
 	    	   		 	   	while (!(UCA0IFG&UCTXIFG));
 	    	   		 	 	UCA0TXBUF=cal-600;
 	    	   		 	 __delay_cycles(100000);
 	    	   		 	   	while (!(UCA0IFG&UCTXIFG));
 	    	   		 	   	UCA0TXBUF=253;
 	    	   			}
 	   else if (cal<=999)
 	   	   			{
 		 	 __delay_cycles(100000);
 		   	   	   	   	   	while (!(UCA0IFG&UCTXIFG));
 		   	    	   		UCA0TXBUF=200;
 		   	   	 	 __delay_cycles(100000);
 		   	    	   		while (!(UCA0IFG&UCTXIFG));
 		   	    	   		UCA0TXBUF=200;
 		   	   	 	 __delay_cycles(100000);
 		   	    	   		 	 	while (!(UCA0IFG&UCTXIFG));
 		   	    	   		 	 	UCA0TXBUF=200;
 		   	    	   	 	 __delay_cycles(100000);
 		   	    	   		 	 	while (!(UCA0IFG&UCTXIFG));
 		   	    	   		 	 	UCA0TXBUF=200;
 		   	    	   	 	 __delay_cycles(100000);
 		   	    	   		 	   	while (!(UCA0IFG&UCTXIFG));
 		   	    	   		 	 	UCA0TXBUF=cal-800;
 		   	    	   	 	 __delay_cycles(100000);
 		   	    	   		 	 	while (!(UCA0IFG&UCTXIFG));
 		   	    	   		  	    UCA0TXBUF=253;
 	   	   			}
 	   		DEL_LAYER(10,80,50,30);
 	   		j=10;
 	   		i=9;
 	   		y=83;
 	   		Print_Char('T',j,y);
 	   		Print_Char('R',j+i,y);
 	   		Print_Char('A',j+2*i,y);
 	   		Print_Char('N',j+3*i,y);
 	   		Print_Char('S',j+4*i,y);
 	   		__delay_cycles(50000000);
 	   		while (!(UCA0IFG&UCTXIFG));
 	   	 		UCA0TXBUF=MTURN;
 	   	 	j=10;
 	   	 	i=9;
 	   		y=83;
 	   		Print_Char('E',j,y);
 	   		Print_Char(' ',j+i,y);
 	   		Print_Char('N',j+2*i,y);
 	   		Print_Char(' ',j+3*i,y);
 	   		Print_Char('D',j+4*i,y);
 	    	DEL_LAYER(11,11,21,33);
 	    	DEL_LAYER(33,11,21,33);
 	    	DEL_LAYER(55,11,21,33);
 	   		NST=49;
 	   		break;
 	   	   case 50:
 	   		DEL_LAYER(10,80,70,30);
 	   		NB[0]=USENUM-48;
 	   	 	Print_Character(USENUM,15,17,2,0);
 	   	 	break;
 	   	 	case 51:
 	   	 	 NB[1]=USENUM-48;
 	   	 	 Print_Character(USENUM,37,17,2,0);
 	   	 	break;
 	   	 	case 52:
 	   	 	 NB[2]=USENUM-48;
 	   	 	 Print_Character(USENUM,59,17,2,0);
 	   	 	 j=10;
 	   	 	 i=8;
 	   	 	 y=79;
 	   	 	 if(NB[0]==NB[1] || NB[1]==NB[2] || NB[2]==NB[0])
			{
				Print_Char('R',j,y);
				Print_Char('E',j+i,y);
				Print_Char(' ',j+2*i,y);
				Print_Char('P',j+3*i,y);
				Print_Char('U',j+4*i,y);
				Print_Char('T',j+5*i,y);
		    	DEL_LAYER(11,11,21,33);
		    	DEL_LAYER(33,11,21,33);
		    	DEL_LAYER(55,11,21,33);
				NST=49;
				break;
			}
 	   	 	 Print_Char('S',j,y);
 	   	 	 Print_Char('U',j+i,y);
 	   	 	 Print_Char('R',j+2*i,y);
 	   	 	 Print_Char('E',j+3*i,y);
 	   	 	 Print_Char(':',j+4*i,y);
 	   	 	 Print_Char('A',j+5*i,y);
 	   	 	 break;
 	   	 	 case 53:
 	   	 	 strike=compare(NB,ENB);
 	   	 	 if (strike==3)
 	   	 		 {
 	   	 		 while (!(UCA0IFG&UCTXIFG));
 	   	 	 	   	 UCA0TXBUF=217;

 	   	 		 j=25;
 	   	 	 	   	 		 i=30;
 	   	 	 	 	   	 	 y=30;
 	   	 	 	 	   	 	 LcdClear();
 	   	 	 	 	   	 	 Print_Character('W',j,y,4,0);
 	   	 	 	 	   	 	 Print_Character('I',j+i,y,4,0);
 	   	 	 	 	   	 	 Print_Character('N',j+2*i,y,4,0);
 	   	 	 	 	   	 	 __delay_cycles(10000000);
 	   	 	 	 	   	 	 LcdClear();
 	   	 	 	 	   	 	 __delay_cycles(10000000);
 	   	 	 	 	   	 	 Print_Character('W',j,y,4,0);
 	   	 					 Print_Character('I',j+i,y,4,0);
 	   	 					 Print_Character('N',j+2*i,y,4,0);
 	   	 	 	 	 	   __delay_cycles(10000000);
 	   	 	 	 	 	   main();}
 	   	 	 	 	 	 DEL_LAYER(11,11,21,33);
 	   	  	   	 	 	 DEL_LAYER(33,11,21,33);
 	   	  	   	 	 	 DEL_LAYER(55,11,21,33);
 	   	  	   	 	 	 {
 	   	  	   	    		   j=8;
 	   	  	   				   i=8;
 	   	  	   				   y=90;
 	   	  	   				   DEL_LAYER(10,80,50,30);
 	   	  	   				   Print_Char('N',j,y);
 	   	  	   				   Print_Char('O',j+i,y);
 	   	  	   				   Print_Char(' ',j+2*i,y);
 	   	  	   				   Print_Char('T',j+3*i,y);
 	   	  	   				   Print_Char('O',j+4*i,y);
 	   	  	   				   Print_Char('U',j+5*i,y);
 	   	  	   				   Print_Char('C',j+6*i,y);
 	   	  	   				   Print_Char('H',j+7*i,y);
 	   	  	   	 	 	 }

			 NST = 49;
			 while (!(UCA0IFG&UCTXIFG));
			  	   UCA0TXBUF=STURN;
 	   	 		 break;
 	   	   default :
 	   		   NST=0;

 	   }

 	  break;
    case 0x10://b
    	//while (!(UCB0IFG&UCTXIFG));
    	//       UCB0TXBUF = MLED2;
    	__delay_cycles(100000);
    	if (NST>=1 && NST<=3)
    	{
    	DEL_LAYER(11,11,21,33);
    	DEL_LAYER(33,11,21,33);
    	DEL_LAYER(55,11,21,33);
    	DEL_LAYER(10,80,50,30);
    	firstselection();
    	NST=0;
    	}
    	if (NST>=50 && NST<=53)
    	{
    		DEL_LAYER(11,11,21,33);
    		DEL_LAYER(33,11,21,33);
    		DEL_LAYER(55,11,21,33);
    		DEL_LAYER(10,80,50,30);
    		firstselection();
    		NST=49;
    	}

       break;
    default: break;
    }
  }

#pragma vector=USCI_B0_VECTOR//RX가 다 차면 들어옴
__interrupt void USCI_B0_ISR(void)

{
  switch(__even_in_range(UCB0IV,4))
  {
    case 0: break;                          // Vector 0 - no interrupt
    case 2:                                 // Vector 2 - RXIFG

    	if (UCB0RXBUF==MTURN)
	   {
		j=8;
		i=8;
		y=90;
			   Print_Char(' ',j,y);
			   Print_Char(' ',j+i,y);
			   Print_Char(' ',j+2*i,y);
			   Print_Char(' ',j+3*i,y);
			   Print_Char(' ',j+4*i,y);
			   Print_Char(' ',j+5*i,y);
			   Print_Char(' ',j+6*i,y);
			   Print_Char(' ',j+7*i,y);
		}
    	if (UCB0RXBUF==217)
    	{
    		j=10;
    		 	   	 		 i=30;
    		 	 	   	 	 y=30;
    		 	 	   	 	 LcdClear();
    		 	 	   	 	 Print_Character('L',j,y,4,0);
    		 	 	   	 	 Print_Character('O',j+i,y,4,0);
    		 	 	   	 	 Print_Character('S',j+2*i,y,4,0);
    		 	 	   	 	 Print_Character('E',j+3*i,y,4,0);
    		 	 	   	 	 __delay_cycles(10000000);
    		 	 	   	 	 LcdClear();
    		 	 	   	 	 __delay_cycles(10000000);
    		 	 	   	 Print_Character('L',j,y,4,0);
						 Print_Character('O',j+i,y,4,0);
						 Print_Character('S',j+2*i,y,4,0);
						 Print_Character('E',j+3*i,y,4,0);
		 	 	   	 	 __delay_cycles(10000000);
		 	 	   	 	 main();



    	}

    	if (UCB0RXBUF<=203)
    		temp_cal=temp_cal+UCB0RXBUF;
    	if (UCB0RXBUF==253)
    	{
    		ENB[0] = temp_cal/100;
    		ENB[1] = temp_cal/10-ENB[0]*10;
    		ENB[2] = temp_cal-(ENB[0]*100+ENB[1]*10);
    		DrawLine(5,85,25,85,3);
    	    DrawLine(5,85,5,115,3);
    	    DrawLine(25,115,25,85,3);
    	    DrawLine(5,115,25,115,3);
    		Print_Char('?', 90,10);
    		Print_Char('?', 98,10);
    		Print_Char('?', 106,10);
    		temp_cal=0;
    	}

      __delay_cycles(40);                   // Add time between transmissions to
                                            // make sure slave can process information
      break;
    case 4: break;                          // Vector 4 - TXIFG
    default: break;
  }
}

#pragma vector=USCI_A0_VECTOR//RX가 다 차면 들어옴
__interrupt void USCI_A0_ISR(void)

{
  switch(__even_in_range(UCA0IV,4))
  {
    case 0: break;                          // Vector 0 - no interrupt
    case 2:                                 // Vector 2 - RXIFG

               // Add time between transmissions to
                                            // make sure slave can process information
      break;
    case 4: break;                          // Vector 4 - TXIFG
    default: break;
  }
}


void firstselection(void)
{
	 j=10;
	   i=8;
	   y=79;
	   Print_Char('N',j,y);
	   Print_Char('E',j+i,y);
	   Print_Char('X',j+2*i,y);
	   Print_Char('T',j+3*i,y);
	   Print_Char(':',j+4*i,y);
	   Print_Char('A',j+5*i,y);
	   		   j=10;
	   		   i=8;
	   		   y=91;
	   		   Print_Char('D',j,y);
	   		   Print_Char('E',j+i,y);
	   		   Print_Char('L',j+2*i,y);
	   		   Print_Char(' ',j+3*i,y);
	   		   Print_Char(':',j+4*i,y);
	   		   Print_Char('B',j+5*i,y);

}

int compare(int* input, int* num)
{
 int k, l;
 int strike=0, ball=0;


 // input과 num 값을 비교하여 strike, ball을 구함
 for(k=0, l=0; k<3; k++) {
  for(l=0; l<3; l++) {
   if(input[k] == num[k]) {
    strike++;
    break;
   }
   else if(input[k] == num[l])
    ball++;
  }
 }
 j=60, i=8, y=65;
 Print_Char('S',j+0*i,y);
 Print_Char(':',j+1*i,y);
 Print_Char(strike+48,j+2*i,y);
 Print_Char(' ',j+3*i,y);
 Print_Char('B',j+4*i,y);
 Print_Char(':',j+5*i,y);
 Print_Char(ball+48,j+6*i,y);
 return strike;
}



