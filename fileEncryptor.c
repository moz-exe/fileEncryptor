#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <stdlib.h>

#include "caesar.c"
#include "vigenere.c"
#include "chacha20.c"

typedef enum algo {
    caesar,
    vigenere,
    chacha20
}Algo;


int main(int argc, char **argv) {
    char* filePath;
    char* key;
    bool decypher = false;
    Algo algo = caesar; // Default
    


    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            // Open file in read mode
            FILE *fptr = fopen("help.txt", "r");  
  
            // Check if the file was opened successfully
            if (fptr == NULL) {  
                return 1;  
            }

            // Read and print each character from the file
            char ch;
            while ((ch = fgetc(fptr)) != EOF) {
                putchar(ch);
            }

            // Close the file after reading
            fclose(fptr);  
            return 0;

        } else if ((strcmp(argv[i], "-f") == 0 | strcmp(argv[i], "--file") == 0) && i + 1 < argc) {
            i++;
            filePath = (char*)malloc(strlen(argv[i]));
            strcpy(filePath, argv[i]);

        } else if ((strcmp(argv[i], "-k") == 0 | strcmp(argv[i], "--key") == 0) && i + 1 < argc) {
            i++;
            key = (char*)malloc(strlen(argv[i]));
            strcpy(key, argv[i]);

        } else if (strcmp(argv[i], "-d") == 0 | strcmp(argv[i], "--decipher") == 0) {
            decypher = true;

        } else if (strcmp(argv[i], "-c") == 0 | strcmp(argv[i], "--caesar") == 0) {
            algo = caesar;

        } else if (strcmp(argv[i], "-v") == 0 | strcmp(argv[i], "--vigenere") == 0) {
            algo = vigenere;

        } else if (strcmp(argv[i], "-ch") == 0 | strcmp(argv[i], "--chacha20") == 0) {
            algo = chacha20;

        }
    }

    printf("Algo : %d \r\n", algo);
    printf("Decypher : %d \r\n", decypher);
    printf("FilePath : %s \r\n", filePath);

    if (!filePath) {
        perror("File does not exist");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(filePath, "rb+");

    switch (algo) {
        case caesar :
            caesarCypher(file, key, decypher);
            break;

        case vigenere :
            unsigned char vigenereTable[rows][columns];
            createVigenereTable(vigenereTable);

            if (decypher == true) {
                vigenereDecypher(file, key, vigenereTable);
            } else {
                vigenereCypher(file, key, vigenereTable);
            }
                    break;

        case chacha20 :

            
    }

}