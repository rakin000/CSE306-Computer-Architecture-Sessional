#include <avr/io.h>
​
​
​
int main(void)
{
	DDRB = 0b00000000; //PB0-PB3
	DDRC = 0b11111111; //PC0-PC3
	DDRA = 0b11111111; // full
	​
	unsigned char input;
	unsigned char opcode;
	/* Replace with your application code */
	​
	​
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);
	​
	​
	while(1)
	{
		input = PINB;
		opcode = input & 15;
		if(opcode == 0)
		{
			PORTA = 0x0C;
			PORTC = 0x00;
		}
		else if(opcode == 1)
		{
			PORTA = 0x04;
			PORTC = 0x12;
		}
		else if(opcode == 2)
		{
			PORTA = 0x00;
			PORTC = 0x24;
		}
		else if(opcode == 3)
		{
			PORTA = 0x04;
			PORTC = 0x16;
		}
		else if(opcode == 4)
		{
			PORTA = 0x02;
			PORTC = 0x10;
		}
		else if(opcode == 5)
		{
			PORTA = 0x0C;
			PORTC = 0x06;
		}
		else if(opcode == 6)
		{
			PORTA = 0x00;
			PORTC = 0x80;
		}
		else if(opcode == 7)
		{
			PORTA = 0x0C;
			PORTC = 0x04;
		}
		else if(opcode == 8)
		{
			PORTA = 0x04;
			PORTC = 0x18;
		}
		else if(opcode == 9)
		{
			PORTA = 0x0C;
			PORTC = 0x08;
		}
		else if(opcode == 10)
		{
			PORTA = 0x05;
			PORTC = 0x11;
		}
		else if(opcode == 11)
		{
			PORTA = 0x04;
			PORTC = 0x14;
		}
		else if(opcode == 12)
		{
			PORTA = 0x04;
			PORTC = 0x10;
		}
		else if(opcode == 13)
		{
			PORTA = 0x00;
			PORTC = 0x44;
		}
		else if(opcode == 14)
		{
			PORTA = 0x04;
			PORTC = 0x1A;
		}
		else if(opcode == 15)
		{
			PORTA = 0x0C;
			PORTC = 0x0C;
		}
		​
	}
	​
}