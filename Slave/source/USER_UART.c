/*
 * USER_UART.c
 *
 *  Created on: 2013. 2. 23.
 *      Author: mcssol
 */

#include "MSP430_UART.h"

#define WAIT_STATE			0x0
#define START_STATE			0x1
#define c1_state			0x2
#define c2_state			0x3
#define c3_state			0x4
#define r1_state			0x5
#define r2_state			0x6
#define r3_state			0x7
#define ERROR_STATE			0x8
#define END_STATE			0x9


int c_value[3]={50,2,80};
int r_value[3]={2,80,80};


void UART_A1_xmit(unsigned char a)
{
    while (!(UCA1IFG&UCTXIFG));             // USCI_A1 TX buffer ready?

    UCA1TXBUF = a;

}

void UART_A1_msg(unsigned char * msg)
{
    unsigned int i;
    i = 0;
    while(msg[i] != '\0')
    {
    	UART_A1_xmit(msg[i]);
        i++;
    }
}


void MENU_UART(void)
{
	static int LINE_DRAW_STATE=START_STATE, next_state=c1_state;
	static unsigned char c1_ASCii[3],c2_ASCii[3],c3_ASCii[3],r1_ASCii[3],r2_ASCii[3],r3_ASCii[3];
	static unsigned char c1,c2,c3,r1,r2,r3;
	static unsigned int receive_data_num=0;
	unsigned char receive_data;


		switch(LINE_DRAW_STATE)
		{
		case START_STATE :
			UART_A1_msg("\n\r Enter the two points \n\r\0");
			UART_A1_msg(" c1 : \0");
			receive_data_num=0;
			LINE_DRAW_STATE=WAIT_STATE;
			next_state=c1_state;
			break;

		case WAIT_STATE:
			if(head_point != tail_point)
			{
				LINE_DRAW_STATE=next_state;
			}

			break;

		case c1_state:
			receive_data=queue_data_out();
			if((receive_data>='0')&&(receive_data<='9'))
			{
				c1_ASCii[receive_data_num++]=receive_data;
				LINE_DRAW_STATE=WAIT_STATE;

			}
			else if((receive_data=='\r')&&(receive_data_num<=3))
			{
				c1=conv_ASCii_to_dec(c1_ASCii,receive_data_num);
				receive_data_num=0;
				LINE_DRAW_STATE=WAIT_STATE;
				next_state=r1_state;
				UART_A1_msg("\n\r r1 : \0");
			}
			else
			{
				LINE_DRAW_STATE=ERROR_STATE;
			}
			break;

		case r1_state:
			receive_data=queue_data_out();
			if((receive_data>='0')&&(receive_data<='9'))
			{
				r1_ASCii[receive_data_num++]=receive_data;
				LINE_DRAW_STATE=WAIT_STATE;
			}
			else if((receive_data=='\r')&&(receive_data_num<=3))
			{
				r1=conv_ASCii_to_dec(r1_ASCii,receive_data_num);
				receive_data_num=0;
				LINE_DRAW_STATE=WAIT_STATE;
				next_state=c2_state;
				UART_A1_msg("\n\r c2 : \0");
			}
			else
			{
				LINE_DRAW_STATE=ERROR_STATE;
			}
			break;
		case c2_state:
			receive_data=queue_data_out();
			if((receive_data>='0')&&(receive_data<='9'))
			{
				c2_ASCii[receive_data_num++]=receive_data;
				LINE_DRAW_STATE=WAIT_STATE;
			}
			else if((receive_data=='\r')&&(receive_data_num<=3))
			{
				c2=conv_ASCii_to_dec(c2_ASCii,receive_data_num);
				receive_data_num=0;
				LINE_DRAW_STATE=WAIT_STATE;
				next_state=r2_state;
				UART_A1_msg("\n\r r2 : \0");
			}
			else
			{
				LINE_DRAW_STATE=ERROR_STATE;
			}
			break;
		case r2_state:
			receive_data=queue_data_out();
			if((receive_data>='0')&&(receive_data<='9'))
			{
				r2_ASCii[receive_data_num++]=receive_data;
				LINE_DRAW_STATE=WAIT_STATE;
			}
			else if((receive_data=='\r')&&(receive_data_num<=3))
			{
				r2=conv_ASCii_to_dec(r2_ASCii,receive_data_num);
				receive_data_num=0;
				LINE_DRAW_STATE=END_STATE;
			}
			else
			{
				LINE_DRAW_STATE=ERROR_STATE;
			}
			break;

		case ERROR_STATE :
			receive_data_num=0;
			LINE_DRAW_STATE=START_STATE;
			UART_A1_msg("\n\r ERROR \n\r  \0");
			break;

		case END_STATE :
			c_value[0]=c1;
			c_value[1]=c2;
			r_value[0]=r1;
			r_value[1]=r2;
			LcdClear();
			DrawLine(r_value[0],c_value[0],r_value[1],c_value[1],3);

			UART_A1_msg("\n\r END  \0");
			LINE_DRAW_STATE=START_STATE;

			break;

		}

}

unsigned char queue_data_out(void)
{
	unsigned char receive_data;
	if(head_point != tail_point)
	{
		receive_data=UART_DATA[head_point];
		head_point++;
		if(head_point>=Queue_size)
		{
			head_point=0;
		}
	}
	return receive_data;
}
unsigned char conv_ASCii_to_dec(unsigned char* ASCii_data,int data_num)//This function convert ASCii to DECIMAL(max : 999)//ASCii_data[0] : high byte....ASCii_data[2] :Low byte
{
	unsigned int tmp_i,scale_term=100;
	unsigned char result=0;
	/*if(data_num==2) scale_term =10;
	else if(data_num==1) scale_term=1;*/



	for(tmp_i=3;tmp_i>data_num;tmp_i--)
	{
		scale_term/=10;
	}


	for(tmp_i=0;tmp_i<data_num;tmp_i++)
	{
		result+=(ASCii_data[tmp_i]-'0')*scale_term;
		scale_term/=10;
	}
	return result;
}
