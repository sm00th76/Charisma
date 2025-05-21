#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 200
#define INSTRUCTION_SIZE 5

char memory[MEMORY_SIZE][INSTRUCTION_SIZE];
char IR[INSTRUCTION_SIZE];
char R[INSTRUCTION_SIZE];
int IC = 0;

// Helper to convert string to int, and back
void set_register_from_int(int value) {
    sprintf(R, "%04d", value);  // store in 4-byte format
}

int get_register_value() {
    return atoi(R);
}

void load_program_with_arithmetic() {
    strcpy(memory[0], "LR05"); 
    strcpy(memory[1], "AD06"); 
    strcpy(memory[2], "SR07"); 
    strcpy(memory[3], "H  ");   
    strcpy(memory[5], "0010");  
    strcpy(memory[6], "0020"); 
}

void execute_program_with_add() {
    while (1) {
        strcpy(IR, memory[IC]);
        printf("IC: %d, IR: %s\n", IC, IR);
        IC++;

        char opcode[3], operand[3];
        strncpy(opcode, IR, 2); opcode[2] = '\0';
        strncpy(operand, IR + 2, 2); operand[2] = '\0';

        int addr = atoi(operand);

        if (strcmp(opcode, "LR") == 0) {
            strcpy(R, memory[addr]);
        } else if (strcmp(opcode, "SR") == 0) {
            strcpy(memory[addr], R);
        } else if (strcmp(opcode, "AD") == 0) {
            int value = atoi(memory[addr]);
            int sum = get_register_value() + value;
            set_register_from_int(sum);
        } else if (strcmp(opcode, "H") == 0) {
            printf("Program halted successfully.\n");
            printf("Final Register Value: %s\n", R);
            break;
        } else {
            printf("Unknown instruction: %s\n", IR);
            break;
        }
    }
}

int main() {
    printf("===[ Phase 3: Arithmetic Instruction - AD ]===\n");
    load_program_with_arithmetic();
    execute_program_with_add();
    return 0;
}
