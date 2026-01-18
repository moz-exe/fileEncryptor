#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <stdlib.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

void caesarCypher(char* filePath, char* key, bool decypher) {

    // Determine operation based on decipher flag
    int (*operation)(int, int); // Function pointer
    operation = decypher ? subtract : add; // Works as an operator overload

    if (filePath != NULL) {
        FILE* file = fopen(filePath, "rb+");

        if (!file) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        fseek(file, 0, SEEK_END); // Aller à la fin du fichier
        long taille = ftell(file);
        fseek(file, 0, SEEK_SET); // Retourner au début

        // Read and print each character from the file
        int c;
        char *tab1 = malloc((size_t)taille);
        char *tab2 = malloc((size_t)taille);
        if (tab1 == NULL || tab2 == NULL) {
            perror("malloc");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        size_t idx = 0;
        while ((c = fgetc(file)) != EOF && idx < (size_t)taille) {
            // putchar(c);
            tab1[idx] = (char)c;
            // increment character for tab2
            tab2[idx] = (char)(operation(c, (int) key));
            idx++;
        }

        printf("Before : ");
        for (int j = 0; j < idx; j++) {
            printf("0x%02x ", (unsigned char)tab1[j]);
        }
        printf("\r\n");
        for (int j = 0; j < idx; j++) {
            putchar(tab1[j]);
        }

        printf("\n\rAfter : ");
        for (int j = 0; j < idx; j++) {
            printf("0x%02x ", (unsigned char)tab2[j]);
        }
        printf("\r\n");
        for (int j = 0; j < idx; j++) {
            putchar(tab2[j]);
        }
        printf("\r\n");

        // Write modified content back to the file
        fseek(file, 0, SEEK_SET); // Retourner au début
        fwrite(tab2, sizeof(char), (size_t)taille, file);
        
        // Close the file after reading & free memory
        free(tab1);
        free(tab2);
        fclose(file);
    }
}