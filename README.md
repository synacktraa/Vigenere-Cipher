# Vigenere Cipher   | <img src="https://app.codacy.com/project/badge/Grade/67e0b6137ded418eb654b73b177b7293"/> |

>Vigenere Ciphers' encryption and decryption algorithm implemented in C. 

## Help
```bash
vigit -h 
```
Output:
```bash

Usage: vigit -k <key> -e/-d data
Note: to take input from file, put 'file:' before filename

|CLI options|:-
   -k = takes next argument as key to manipulate data
   -e = takes next argument as data to encrypt it
   -d = takes next argument as data to decrypt it
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