#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <stdlib.h>

void vigenereCypher(char* filePath, char* key, bool decypher) {

    if (filePath == NULL) {
        perror("No file specified");
        exit(EXIT_FAILURE);
    }

    int keyLength = strlen(key);

    for (int i = 0; i < keyLength; i++) {
        printf("key[%i] : %c → 0x%x \r\n", i, key[i], key[i]);
    }


    printf("\n\n\r");

// -------------------- Opening and mapping Vigenere table --------------------
    FILE *vigenereTableCSV = fopen("vigenere_hex_table.csv", "r");
    if (!vigenereTableCSV) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    printf("Opened CSV file of vigenere table\n");

    // Allocation statique du buffer contenant une ligne enitère du CSV
    // Chaque ligne contient 256 colonnes de 4 caractères, séparées par des virgules, terminées par un caractère de fin de ligne et un caractère nul
    const int columns = 256;
    const int rows = 256;

    const int numberOfColumns = 256;
    const int sizeOfCell = 4;
    const int sizeOfComa = 2;
    const int bufferSize = numberOfColumns * sizeOfCell + (numberOfColumns - 1) * sizeOfComa + 2; // =1536
    
    char buffer[bufferSize];
    
    // Allocation de la table Vigenere à partir des données du CSV
    int sizeOfRow = numberOfColumns * sizeOfCell;
    unsigned char vigenereTable[rows][columns];

    printf("Created 2D table for vigenere table\n");

    // Remplissage du tableau vigenereTable
    int row = 0;
    int column = 0;

    fseek(vigenereTableCSV, 0, SEEK_SET); // Retourner au début du fichier
    while (fgets(buffer, bufferSize, vigenereTableCSV)) {
            column = 0;

            // Splitting the data
            char* value = strtok(buffer, ","); // Tokenized string

            while(value) {
                vigenereTable[row][column] = (unsigned char) strtol(value, NULL, 16);

                // printf("%s", value);
                value = strtok(NULL, ",");
                column++;
            }

            row++;
    }

    printf("Allocated CSV values to 2D table\n\r");

    fclose(vigenereTableCSV);

// -------------------- Opening & cyphering file to cypher --------------------
    FILE* file = fopen(filePath, "rb+");

    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END); // Aller à la fin du fichier
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET); // Retourner au début


    // Remplissage du tableau de sortie chiffré caractère par caractère
    char *output = malloc(fileSize); // tableau de sortie
    char *input = malloc(fileSize); // Sert uniquement pour vérifier le bon fonctionnement du programme
    char *keyRowNumber_table = malloc(fileSize); // Sert uniquement pour vérifier le bon fonctionnement du programme

    int keyIndex = 0;
    size_t idx = 0;
    int c;
    
    printf("strlen(key) = %lu",strlen(key));
    while ((c = fgetc(file)) != EOF && idx < fileSize) {
        // On calcule les coordonées du caractère chiffré dans la tablede Vigenere et on l'ajoute au tableau de sortie
        printf("\nkey[keyIndex] = %c", key[keyIndex]);
        int clearColumnNumber = c;
        int keyRowNumber = (int) key[keyIndex];
        keyRowNumber_table[idx] = keyRowNumber;
        output[idx] = vigenereTable[keyRowNumber][clearColumnNumber];   //[(sizeOfRow * keyRowNumber + clearColumnNumber) * sizeOfCell];
        printf("\noutput[idx] = %c, should be %i", output[idx], sizeOfRow * keyRowNumber + clearColumnNumber);
        input[idx] = (char) c;

        if (keyIndex + 1 >= strlen(key)) {
            keyIndex = 0;
        }

        else {
            keyIndex++;
        }
        
        idx++;
    }

    // Vérification du bon fonctionnement
    for (int i = 0; i < idx; i++) {
        printf("Encrypting : %c became %c --> Searched column %02x, row %02x and found %02x\n\r", input[i], output[i], input[i], keyRowNumber_table[i], output[i]);
    } 

    // Réécriture du fichier
    fseek(file, 0, SEEK_SET); // Retourner au début du fichier
    fwrite(output, sizeof(char), fileSize, file);

    free(output);
    free(input);
    fclose(file);
}