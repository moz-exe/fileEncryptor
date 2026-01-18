#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <stdlib.h>
#include "caesar.c"

typedef enum algo {
    caesar,
    vigenaire
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

        } else if (strcmp(argv[i], "-v") == 0 | strcmp(argv[i], "--vigenaire") == 0) {
            algo = vigenaire;

        }
    }

    printf("Algo : %d \r\n", algo);
    printf("Decypher : %d \r\n", decypher);
    printf("FilePath : %s \r\n", filePath);

    switch (algo) {
        case caesar :
            caesarCypher(filePath, key, decypher);
            break;

        // case vigenaire :
        //     vigenaireCypher();
        //     break;
            
    }

}