#include <stdio.h>
#include <stdlib.h>

#define MOVE 0
#define ADD 1
#define SUB 2
#define BRA 3
#define CMP 4
#define BEQ 5
#define BNE 6
#define EXG 7
#define OR 8
#define XOR 9
#define AND 10
#define STOP 15
void main()
{
    unsigned short int PC = 0;
    unsigned short int D0 = 0;
    unsigned short int A0 = 0;
    unsigned short int CCR = 0;
    unsigned short int MAR;
    unsigned short int MBR;
    unsigned short int IR;
    unsigned short int operand;
    unsigned short int source;
    unsigned short int destination;
    unsigned short int opcode;
    unsigned short int amode;
    unsigned short int direction;
    unsigned short int memory[256];
    unsigned short int run = 1;

    int n= sizeof(memory)/sizeof(memory[0]);
    for(int i=0;i<n;i++){
       memory[i]=0;
    }

    memory[0] = 0b00000101;
    memory[1] = 0b00001010;
    memory[2] = 0b00010101;
    memory[3] = 0b00000001;
    memory[4] = 0b00000000;
    memory[5] = 0b00011001;
    memory[6] = 0b10100100;
    memory[7] = 0b00001111;
    memory[8] = 0b00100101;
    memory[9] = 0b00000001;
    memory[10]= 0b10000100;
    memory[11]= 0b00010000;
    memory[12]= 0b10010100;
    memory[13]= 0b00010001;
    memory[14]= 0b11110000;
    memory[15]= 0b00010111;
    memory[16]= 0b00001110;
    memory[17]= 0b00001000;

    while(run){
        MAR = PC;
        PC = PC +1;
        MBR = memory[MAR];
        IR = MBR;
        opcode = IR;
        MAR = PC;
        PC = PC + 1;
        MBR = memory[MAR];
        IR = MBR;
        operand = IR;
        amode = opcode & 0x03;
        direction = (opcode & 0x04) >> 2;
        opcode = opcode >> 4;
        switch(amode){
            case 0:{ source = memory[operand];break;}
            case 1:{ source = operand;break;}
            case 2:{ source = memory[A0 + operand];break;}
            case 3:{ source = memory[PC + operand];break;}
        }
        switch(opcode){
            case MOVE:{ if(direction == 0) destination = D0;
                        else    D0= source;
                        if(D0 == 0) CCR = 1; else CCR = 0;
                        break;
            }
            case ADD: {if(direction == 0){
                destination = D0 + source;
                if(destination == 0) CCR = 1; else CCR = 0;
                }
                else
                {
                    D0 = D0 + source;
                    if(D0 == 0) CCR = 1; else CCR = 0;
                }
                break;
                }
            case SUB:{ if(direction == 0)
                            {destination = D0 - source;
                             if(destination == 0) CCR = 1;else CCR = 0;
                            }
                        else
                            { D0 = D0 - source;
                            if(D0 == 0) CCR = 1; else CCR = 0;
                            }
                        break;
                        }
            case BRA: { if(amode == 0) PC = operand;
                        if(amode == 1) PC = PC +operand;break;
                        }
            case CMP: {MBR = D0 - source;
                       if(MBR == 0) CCR = 1;
                       else CCR =0; break;
                       }
            case BEQ: {if(CCR == 1)
                        {if (amode == 0) PC = operand;
                         if (amode == 1) PC = PC + operand;
                        } break;
                    }
            case BNE: {if(CCR != 1)
                        {if(amode == 0) PC = operand;
                        if(amode == 1) PC =PC +operand;
                        } break;
                    }
            case EXG: {MBR = D0;D0=A0;A0=MBR;break;
                        }
            case STOP: {run = 0;break;}
            case AND:{if(direction == 0){
                destination = D0 & source;
                if(destination == 0) CCR = 1; else CCR = 0;
                }
                else
                {
                    D0 = D0 & source;
                    if(D0 == 0) CCR = 1; else CCR = 0;
                }
                break;
                }
            case OR:{if(direction == 0){
                destination = D0 | source;
                if(destination == 0) CCR = 1; else CCR = 0;
                }
                else
                {
                    D0 = D0 | source;
                    if(D0 == 0) CCR = 1; else CCR = 0;
                }
                break;
                }
            case XOR: {if(direction == 0){
                destination = D0 ^ source;
                if(destination == 0) CCR = 1; else CCR = 0;
                }
                else
                {
                    D0 = D0 ^ source;
                    if(D0 == 0) CCR = 1; else CCR = 0;
                }
                break;
                }
        }
        if(direction == 0)
            switch(amode)
            { case 0: { memory[operand] = destination; break;
                        }
              case 1:{ break; }
              case 2:{memory[A0 + operand] = destination;break;}
              case 3:{memory[PC+operand] = destination;break;}
            }
            printf("The value of D0 = %i \n\n",D0);
        }
        printf("Final result of D0 = %i \n",D0);
      }


