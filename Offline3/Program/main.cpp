#include <avr/io.h>

int main(void)
{
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD) ;
	DDRB = 0x00; // B4-7 = address
	// B0-3 = write_data
	DDRD = 0x00 ; // D0 = MEM_READ
	// D1 = MEM_WRITE
	// D2 = MEM_TO_REG
	DDRA = 0xFF ;
	DDRC = 0xFF ;
	PORTA=0x01;
	const int N = 1<<8;
	uint8_t data[N] ;
	data[8] = 0xF;
	//data[0] = 0b0000000000000000;
	//data[1] = 0b1100101101001010;
	//data[2] = 0b1111111100000000;
	//data[3] = 0b0000000011111111;
	//data[4] = 0b0000111100001111;
	
	unsigned char location,write_data,mem_to_reg,memread,memwrite,read_data,memory_data=0,in;
	while (1)
	{
		in = PINB;
		write_data = (unsigned char)(in & 0x0F) ;
		location = (unsigned char)( (in >> 4 ) & 0x0F );
		memread=PIND & 0x01;
		memwrite=PIND & 0x02;
		mem_to_reg=PIND & 0x04;
		
		if(memwrite==1)
		{
			data[location]=write_data;
		}
		
		memory_data=data[location];
		
		if(mem_to_reg==1)
		{
			read_data=memory_data;
		}
		else
		{
			read_data=location;
		}
		PORTA=0x01;
	}
}

