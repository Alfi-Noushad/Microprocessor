#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct SYMTAB {
    char symbol[30];
    char address[30];
} s[100];

int scount = 0;

// Convert hexadecimal string to decimal
int hexToDecimal(char acHex[]) {
    int len = strlen(acHex), dec = 0, i, temp;

    for(i = 0; i < len; i++) {
        switch(acHex[i]) {
            case '0': temp = 0; break;
            case '1': temp = 1; break;
            case '2': temp = 2; break;
            case '3': temp = 3; break;
            case '4': temp = 4; break;
            case '5': temp = 5; break;
            case '6': temp = 6; break;
            case '7': temp = 7; break;
            case '8': temp = 8; break;
            case '9': temp = 9; break;
            case 'A': case 'a': temp = 10; break;
            case 'B': case 'b': temp = 11; break;
            case 'C': case 'c': temp = 12; break;
            case 'D': case 'd': temp = 13; break;
            case 'E': case 'e': temp = 14; break;
            case 'F': case 'f': temp = 15; break;
            default: temp = 0; break;
        }
        dec += temp * pow(16, len - i - 1);
    }
    return dec;
}

void onePass() {
    char label[30], opcode[30], operand[30], address[30], loc[30];
    int startAddress = 0, locctr = 0;
    FILE *fp, *f1;

    fp = fopen("source.txt", "r");
    if(!fp) {
        printf("Error: Cannot open source.txt\n");
        return;
    }

    f1 = fopen("intermediate.txt", "w");
    if(!f1) {
        printf("Error: Cannot create intermediate.txt\n");
        fclose(fp);
        return;
    }

    // Read first line
    if(fscanf(fp, "%s %s %s", label, opcode, operand) != 3) {
        printf("Empty or invalid source file.\n");
        fclose(fp);
        fclose(f1);
        return;
    }

    // If START directive
    if(strcmp(opcode, "START") == 0) {
        startAddress = hexToDecimal(operand);
        locctr = startAddress;
        fprintf(f1, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        fscanf(fp, "%s %s %s", label, opcode, operand);
    }

    // Process each line
    while(!feof(fp)) {
        // Add label to symbol table if present
        if(strcmp(label, "**") != 0) {
            strcpy(s[scount].symbol, label);
            sprintf(address, "%X", locctr);
            strcpy(s[scount++].address, address);
        }

        // Print intermediate line
        char displayLabel[30];
        if(strcmp(label, "**") == 0)
            strcpy(displayLabel, "*");
        else
            strcpy(displayLabel, label);

        fprintf(f1, "%X\t%s\t%s\t%s\n", locctr, displayLabel, opcode, operand);

        // Update locctr based on opcode
        if(strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if(strcmp(opcode, "RESW") == 0) {
            locctr += atoi(operand) * 3;
        } else if(strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        } else if(strcmp(opcode, "BYTE") == 0) {
            locctr += strlen(operand); // assume literal like EOF
        } else {
            locctr += 3; // default instruction size
        }

        if(fscanf(fp, "%s %s %s", label, opcode, operand) != 3)
            break;
    }

    fclose(fp);
    fclose(f1);

    // Print Symbol Table
    printf("Symbol Table:\n");
    for(int i = 0; i < scount; i++) {
        printf("%s\t%s\n", s[i].symbol, s[i].address);
    }

    // Print Intermediate Code
    printf("\nIntermediate Code of Assembler:\n");
    f1 = fopen("intermediate.txt", "r");
    while(fscanf(f1, "%s %s %s %s", loc, label, opcode, operand) == 4) {
        printf("%s\t%s\t%s\t%s\n", loc, label, opcode, operand);
    }
    fclose(f1);
}

int main() {
    onePass();
    return 0;
}
