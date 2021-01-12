#include <stdio.h>
#include <stdlib.h>

#define LDA 0
#define STA 1
#define ADD 2
#define BRA 3
#define BEQ 4
#define STOP 7
void main(void)
{

    unsigned short int PC =0;       /*program counter*/
    unsigned short int D0 =0;       /*Data register*/
    unsigned short int MAR;         /*memory address register*/
    unsigned short int MBR;         /*memory buffer register*/
    unsigned short int IR;          /*instruction register*/
    unsigned short int operand;     /*the 8-bit operand from the IR*/
    unsigned short int source;      /*source operand*/
    unsigned short int opcode;      /*the 3-bit op-code from the IR*/
    unsigned short int amode;       /*the 1-bit addressing mode*/
    unsigned short int memory[16];  /*the memory*/
    unsigned short int run = 1;     /*execute program while run is 1*/


    int n= sizeof(memory)/sizeof(memory[0]);
    for(int i=0;i<n;i++){
       memory[i]=0;
    }

    memory[0] = 0b00001010;
    memory[1] = 0b01010001;
    memory[2] = 0b00101010;
    memory[3] = 0b11110000;
    memory[10] = 0b000000010;

    while(run){
        MAR = PC;
        PC = PC+1;
        MBR =memory[MAR];
        IR = MBR;

        opcode = IR>>5;
        amode = (IR & 0x10)>>4;
        operand = IR & 0x0F;

        if(amode == 0){
            source = memory[operand];
        }else{
            source = operand;
        }

        switch(opcode){
          case LDA: { D0 =source;               break;}
          case STA: { memory[operand]=D0;       break;}
          case ADD: { D0 = D0 + source ;        break;}
          case BRA: { PC =operand;              break;}
          case BEQ: { if(D0 ==0) PC = operand;  break;}
          case STOP:{ run=0;                    break;}
        }
       printf("The value of D0 = %i \n\n",D0);
    }
    printf("Final result of D0 = %i \n",D0);
}
