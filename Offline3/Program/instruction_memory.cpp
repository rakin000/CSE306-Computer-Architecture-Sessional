/*
 * Program.cpp
 *
 * Created: 8/24/2022 5:39:56 PM
 * Author : Lenovo
 */ 

#include <avr/io.h>



int main(void)

{
	 MCUCSR = (1<<JTD);
     MCUCSR = (1<<JTD);
	/* Replace with your application code */
	DDRA = 0x00;
	DDRC = 0x00 ;
	DDRB = 0xFF ;
	DDRD = 0xFF ;
	
	const int N = 1<<8;
	uint16_t instructions[N] ;
	instructions[128] = 0xFFFF;
	instructions[0] = 0b0000000000000000;
	instructions[1] = 0b1100101101001010;
	instructions[2] = 0b1111111100000000;
	instructions[3] = 0b0000000011111111;
	instructions[4] = 0b0000111100001111;
	
	unsigned char in, temp , temp2 ; 
    while (1) 
    {
		in = PINC ;
		temp = (unsigned char)(instructions[in] & 0x00FF) ;
		temp2 = (unsigned char)((instructions[in] >> 8 ) & 0x00FF );
		PORTD = temp;
		PORTB = temp2;
	}
}

