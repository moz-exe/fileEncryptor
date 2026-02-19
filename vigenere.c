#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <stdlib.h>

void vigenereCypher(char* filePath, char* key, bool decypher) {

    if (filePath == NULL) {
        perror("No file specified");
        exit(EXIT_FAILURE);
    }

    // Converting key characters to their hexadecimal values
    int keyLength = strlen(key);
    char hexKey[keyLength];

    printf("key :");
    for (int i = 0; i <= keyLength; i++) {
        char hexValue[3];
        sprintf(hexValue, "%02x", key[i]);
        hexKey[i] = hexValue;
        printf("%s", hexKey);
    }

    printf("\n\n\r");

    // Opening and mapping Vigenere table 
    FILE *vigenereTableCSV = fopen("vigenere_hex_table.csv", "r");
    if (!vigenereTableCSV) {
            perror("fopen");
            exit(EXIT_FAILURE);
    }

    // Allocation statique du buffer
    // Chaque ligne contient 256 colonnes de 4 caractères, séparées par des virgules, terminées par un caractère de fin de ligne et un caractère nul 
    int numberOfColumns = 256;
    int sizeOfColumn = 4;
    int sizeOfComa = 2;
    int sizeOfEndlineChar = 1;
    int sizeOfNulChar = 1;
    int bufferSize = numberOfColumns * sizeOfColumn + (numberOfColumns - 1) * sizeOfComa + sizeOfEndlineChar + sizeOfNulChar; // =1536
    char buffer[bufferSize];

    // Allocation de la table Vigenere à partir des données du CSV
    int sizeOfRow = numberOfColumns * sizeOfColumn;
    char vigenereTable[numberOfColumns * sizeOfRow]; // Tableau 1D : vigenereTable[sizeOfRow * rowNumber + columnNumber]

    // Remplissage du tableau vigenereTable
    int row = 0;
    int column = 0;

    while (fgets(buffer, bufferSize, vigenereTableCSV)) {
            column = 0;
            row++;

            // Splitting the data
            char* value = strtok(buffer, ", ");

            while(value) {
                vigenereTable[sizeOfRow * row + column] = value;

                // printf("%s", value);
                value = strtok(NULL, ", ");
                column++;
            }

            // printf("\n");
    }

    fclose(vigenereTableCSV);

    // Ouverture du fichier à chiffrer
    FILE* file = fopen(filePath, "rb+");

    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END); // Aller à la fin du fichier
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET); // Retourner au début

    //Convert hexadecimal key values into decimal key values
    int decKey[keyLength];
    for (int i = 0; i <= keyLength; i++) {
        decKey[i] = (int)strtol(hexKey[i], NULL, 0);
        printf("decKey[%i] : %i", i, decKey[i]);
    }

    char input[fileSize];
    char output[fileSize];

    int keyIndex = 0;
    size_t idx = 0;
    int c;

    while ((c = fgetc(file)) != EOF && idx < (size_t)fileSize) {
        // Convertion des valeurs hexadécimales en numéros de ligne et de colonne
        int clearColumnNumber = (int)strtol(c, NULL, 0); // Numéro de colonne en décimal
        int keyRowNumber = 

        
        idx++;
    }

}