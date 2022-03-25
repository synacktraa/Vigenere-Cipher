# Vigenere Cipher

>Vigenere Ciphers' encryption and decryption algorithm implemented in C. 

#
## Help:
```bash
vigit -h 
```
Output:
```bash

Usage: vigit.exe -k <key> -e/-d data
|CLI options|:-
        <data> = A plaintext or ciphertext.
        <key> = A key string to scramble and unscramble the data.
        <mode>:
                --encrypt = Encrypts the data string
                --decrypt = Decrypts the data string
```
#
## Encryption:
```bash
vigit -k key -e "Star this project :)"
```
Output:
```
Cxyb xfsw nbshogr :)
```
#
## Decryption:
```bash
vigit -k key -d "Reto e lsgc new (;"
```
Output:
```
Have a nice day (;
```