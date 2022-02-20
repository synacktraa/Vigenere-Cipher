# Vigenere Cipher

>Vigenere Ciphers' encryption and decryption algorithm written in C. 

Compile:

```powershell
gcc vigcipher.c -o vc
```

Ask For Help:
```bash
vc -h 'or' vc --help
```

Encrypt:
```powershell
vc "Hack Teh World" "key" --encrypt
Output: Reau Xcr Ambpb
```

Decrypt:
```powershell
vc "Reau Xcr Ambpb" "key" --decrypt
Output: Hack Teh World
```
