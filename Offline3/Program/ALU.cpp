/*
 * ALU.c
 *
 * Created: 8/25/2022 4:36:36 PM
 * Author : Sohaib
 */
 
#include <avr/io.h>
 
 
int main(void)
{
        DDRB = 0xFF;
        DDRD = 0xFF;
        DDRA = 0x00;
        DDRC = 0x00;
       
    while (1)
    {
                unsigned char op1 = (PINB >> 4);
                unsigned char op2 = (PINB & 0x0F);
                unsigned char immediate = (PIND >> 4);
                unsigned char alusrc = (PIND >> 3) & 1;
                unsigned char aluop = (PIND & 0x07);
               
                unsigned char result;
               
                if (alusrc) {
                        if (aluop == 0)
                                result = op1 + op2;
                        else if (aluop == 1)
                                result = (op1 << op2);
                        else if (aluop == 2)
                                result = op1 - op2;
                        else if (aluop == 3)
                                result = op1 | op2;
                        else if (aluop == 4)
                                result = op1 & op2;
                        else if (aluop == 5)
                                result = (op1 >> op2);
                        else if (aluop == 6)
                                result = ~(op1 | op2);
                }
                else {
                        if (aluop == 0)
                                result = op1 + immediate;
                        else if (aluop == 1)
                                result = (op1 << immediate);
                        else if (aluop == 2)
                                result = op1 - immediate;
                        else if (aluop == 3)
                                result = op1 | immediate;
                        else if (aluop == 4)
                                result = op1 & immediate;
                        else if (aluop == 5)
                                result = (op1 >> immediate);
                        else if (aluop == 6)
                                result = ~(op1 | immediate);
                }
               
                PORTA = ((result)<<4);
                if ((result & 0x0F) == 0) {
                        PORTA |= (1 << 3);
                }
    }
}