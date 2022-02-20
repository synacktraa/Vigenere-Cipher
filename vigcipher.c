#include<stdio.h>
#define MAX 100
#define LET 26
#define UTL 32

int Strlen(const char* string){
    
    int len = 0;
    while (*string != '\0'){
        len++;
        string++;
    }
    return len;    
}

int Strcmp(const char* string1, const char* string2){

   int len_string1 = Strlen(string1);
   int len_string2 = Strlen(string2);

   if((len_string1 - len_string2) == 0){
      for(int i = 0; i < len_string1; i++){
         if(*(string1+i) == *(string2+i))
            len_string2--;         
      }
      if(len_string2 == 0)
         return 0;
      else
         return 1;
   } else{
      return 1;
      }
}

int toUpper(int ch){

   int upper;
   if(ch >= 97 && ch <= 122){
      upper = ch-32;
   } else {
      upper = ch;
   }
   return upper;
}

int isLower(int ch){
   if(ch >= 97 && ch <= 122)
      return 1;
   return 0 ;
}

void vignere_cipher(char*key, char*mode, char*cred){

    auto void encrypt();
    auto void decrypt();

    char outcome[MAX];
    int cred_len, key_len;

    cred_len = Strlen(cred);
    key_len = Strlen(key);

    int j = 0, i;
    if(key_len < cred_len){
        for(i = key_len; i < cred_len; ++i){
            if(j >= key_len)
                j = 0;
            if(*(cred+i) == 32)
                *(key+i) = 32;
            else {*(key+i) = *(key+j);++j;}
            
        }
        *(key+i) = '\0';   
    }
    if(Strcmp(mode, "--encrypt") == 0) encrypt();
    else if(Strcmp(mode, "--decrypt") == 0) decrypt();

    void encrypt(){
        int i;
        for(i = 0; i < Strlen(cred); ++i){
            if((*(cred+i) >=32 && *(cred+i) <=64) || (*(cred+i) >=91 && *(cred+i) <=96) || (*(cred+i) >=123 && *(cred+i) <=126)){
                *(outcome+i) = *(cred+i);
            } else if((toUpper(*(cred+i)) >=65 && toUpper(*(cred+i)) <=90)){
                *(outcome+i) = toUpper(*(cred+i)) - (65 - toUpper(*(key+i)));
                if(*(outcome+i) > 90){
                    *(outcome+i) = *(outcome+i)-LET;
                }
            }
            if(isLower(*(cred+i))){
                *(outcome+i) = *(outcome+i)+UTL;
            }
        }
        *(outcome+i) = '\0';
    }

    void decrypt(){
        int i;
        for(i = 0; i < Strlen(cred); ++i){
            if((*(cred+i) >=32 && *(cred+i) <=64) || (*(cred+i) >=91 && *(cred+i) <=96) || (*(cred+i) >=123 && *(cred+i) <=126)){
                *(outcome+i) = *(cred+i);
            } else if((toUpper(*(cred+i)) >=65 && toUpper(*(cred+i)) <=90)){
                *(outcome+i) = toUpper(*(cred+i)) - (toUpper(*(key+i)) - 65);
                if(*(outcome+i) < 65){
                    *(outcome+i) = *(outcome+i)+LET;
                }
            }
            if(isLower(*(cred+i))){
                *(outcome+i) = *(outcome+i)+UTL;
            }
        }
        *(outcome+i) = '\0';
    }
    printf("%s", outcome);
}

int main(int argc, char*argv[]){
    
    if(argc == 2 && (Strcmp(argv[1], "--help")||Strcmp(argv[1], "-h"))){
        fprintf(stdout, "\nUsage: %s <key> <mode> <data>\n|CLI options|:-\
        \n\t<data> = A plaintext or ciphertext.\
        \n\t<key> = A key string to scramble and unscramble the data.\
        \n\t<mode>:\n\t\t--encrypt = Encrypts the data string\
        \n\t\t--decrypt = Decrypts the data string", argv[0]);
    }else if(argc == 4){
        vignere_cipher(argv[1], argv[2], argv[3]);
    } else{
        fprintf(stderr, "\nUsage: %s <key> <mode> <data>\
        \nFor more, check help section:\
        \n    %s --help 'or' -h", argv[0], argv[0]);
        return 1;
    }

    return 0;
}