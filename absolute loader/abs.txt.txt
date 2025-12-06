#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char record[100], type;
    unsigned int startAddr, currAddr, execAddr;
    int i;

    fp = fopen("TXT.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open TXT.txt file\n");
        exit(0);
    }

    printf("The loaded program is as follows:\n\n");

    while (fgets(record, sizeof(record), fp)) {
        sscanf(record, "%c", &type); // read first character

        if (type == 'H') {
            continue; // skip header
        } 
        else if (type == 'T') {
            char objcode[80];
            sscanf(record, "%c %x %s", &type, &startAddr, objcode);
            currAddr = startAddr;

            // Print object code in pairs of two characters
            for (i = 0; objcode[i] != '\0'; i += 2) {
                if (objcode[i+1] == '\0') break;
                printf("%04X %c%c\n", currAddr, objcode[i], objcode[i+1]);
                currAddr++;
            }
        } 
        else if (type == 'E') {
            sscanf(record, "%c %x", &type, &execAddr);
        }
    }

    printf("\nProgram execution starts at address: %04X\n", execAddr);

    fclose(fp);
    return 0;
}
