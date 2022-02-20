# Vigenere Cipher

>Vigenere Ciphers' encryption and decryption algorithm written in C. 

Compile:

```powershell
gcc vigcipher.c -o vc
```
---
Ask For Help:
```bash
vc -h 'or' vc --help
```
Output:
```

Usage: vc.exe <key> <mode> <data>
|CLI options|:-
        <data> = A plaintext or ciphertext.
        <key> = A key string to scramble and unscramble the data.
        <mode>:
                --encrypt = Encrypts the data string
                --decrypt = Decrypts the data string
```
---
## Encryption:
```powershell
vc key --encrypt "Hack Teh World"
```
Output:
```
Reau Xcr Ambpb
```
---
## Decryption:
```powershell
vc key --decrypt "Reau Xcr Ambpb"
```
Output:
```
Hack Teh World
```
___
