#!/bin/bash

cd "$(dirname "$0")"

echo "Répertoire courant : $(pwd)"

# Testing caesar cypher
cp tests/test.txt tests/caesar_test.txt
./fileEncryptor -c -k 13 -f tests/caesar_test.txt
DIFF=$(diff --brief tests/test.txt tests/caesar_test.txt)

if [ "$DIFF" != "" ]; then
    echo -e "\e[32m✓ Caesar cypher works\e[0m"
else
    echo -e "\e[31m× Caesar cypher does not work\e[0m"
fi

# Testing caesar decypher
./fileEncryptor -c -k 13 -f tests/caesar_test.txt -d
DIFF=$(diff --brief tests/test.txt tests/caesar_test.txt)

if [ "$DIFF" = '' ]; then
    echo -e "\e[32m✓ Caesar decypher works\e[0m"
else
    echo -e "\e[31m× Caesar decypher does not work\e[0m"
fi

rm tests/caesar_test.txt

# Testing vigenere cypher
cp tests/test.txt tests/vigenere_test.txt

./fileEncryptor -v -k gauffre -f tests/vigenere_test.txt
DIFF=$(diff --brief tests/test.txt tests/vigenere_test.txt)

if [ "$DIFF" != '' ]; then
    echo -e "\e[32m✓ Vigenere cypher works\e[0m"
else
    echo -e "\e[31m× Vigenere cypher does not work\e[0m"
fi

# Testing vigenere decypher
./fileEncryptor -v -k gauffre -f tests/vigenere_test.txt -d
DIFF=$(diff --brief tests/test.txt tests/vigenere_test.txt)

if [ "$DIFF" = '' ]; then
    echo -e "\e[32m✓ Vigenere decypher works\e[0m"
else
    echo -e "\e[31m× Vigenere decypher does not work\e[0m"
fi

rm tests/vigenere_test.txt