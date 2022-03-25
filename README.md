# Vigenere Cipher   | <img src="https://app.codacy.com/project/badge/Grade/67e0b6137ded418eb654b73b177b7293"/> |

>Vigenere Ciphers' encryption and decryption algorithm implemented in C. 

## Help
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

## Encryption
```bash
vigit -k key -e "Star this project :)"
```
Output:
```bash
Cxyb xfsw nbshogr :)
```

## Decryption
```bash
vigit -k key -d "Reto e lsgc new (;"
```
Output:
```bash
Have a nice day (;
```