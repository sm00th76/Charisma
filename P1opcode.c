#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 200
#define INSTRUCTION_SIZE 5

char memory[MEMORY_SIZE][INSTRUCTION_SIZE];
char IR[INSTRUCTION_SIZE];
char R[INSTRUCTION_SIZE];
int IC = 0;
int toggle = 0;

void load_program_with_errors() {
    strcpy(memory[0], "GD10");  // Valid
    strcpy(memory[1], "AB12");  // Invalid opcode
    strcpy(memory[2], "LRXX");  // Invalid operand
    strcpy(memory[3], "H  ");   // Valid
}

void execute_program_with_error_check() {
    while (1) {
        strcpy(IR, memory[IC]);
        printf("IC: %d, IR: %s\n", IC, IR);
        IC++;

        char opcode[3], operand[3];
        strncpy(opcode, IR, 2); opcode[2] = '\0';
        strncpy(operand, IR + 2, 2); operand[2] = '\0';

        if (strcmp(opcode, "GD") == 0 || strcmp(opcode, "PD") == 0 ||
            strcmp(opcode, "LR") == 0 || strcmp(opcode, "SR") == 0 ||
            strcmp(opcode, "CR") == 0 || strcmp(opcode, "BT") == 0 ||
            strcmp(opcode, "H") == 0) {

            if (strcmp(opcode, "H") != 0) {
                int is_digit = 1;
                for (int i = 0; i < 2; i++) {
                    if (operand[i] < '0' || operand[i] > '9') {
                        is_digit = 0;
                        break;
                    }
                }

                if (!is_digit) {
                    printf("Operand Error at IC=%d: '%s' — operand '%s' not numeric.\n", IC - 1, IR, operand);
                    break;
                }

                int address = atoi(operand);
                if (address < 0 || address >= MEMORY_SIZE) {
                    printf("Operand Error at IC=%d: '%s' — address out of bounds.\n", IC - 1, IR, operand);
                    break;
                }
            }

            if (strcmp(opcode, "H") == 0) {
                printf("Program halted successfully.\n");
                break;
            }

        } else {
            printf("Opcode Error at IC=%d: '%s' — opcode '%s' not valid.\n", IC - 1, IR, opcode);
            break;
        }
    }
}

int main() {
    printf("===[ Phase 1: Opcode/Operand Error Check ]===\n");
    load_program_with_errors();
    execute_program_with_error_check();
    return 0;
}
