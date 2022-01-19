#include<stdio.h>
#define MAX 100
#define LET 26
#define UTL 32

int Strlen(char* string){
    
    int len = 0;
    while (*string != '\0'){
        len++;
        string++;
    }
    return len;    
}

int toLower(int ch){

   int lower;
   if(ch >= 65 && ch <= 90){
      lower = ch+32;
   } else {
      lower = ch;
   }
   return lower;
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
void vignere_cipher(char* cred){

    auto void encrypt();
    auto void decrypt();

    int mode;
    char outcome[MAX], key[MAX];
    int cred_len, key_len;

    printf("Enter the key: ");
    scanf("%s", key);

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
        *(key+i-1) = '\0';   
    }
    printf("%s\n", cred);
    printf("%s\n", key);

    printf("Enter 1 for encryption and 0 for decryption\n:");
    scanf("%d", &mode);

    if(mode == 1) encrypt();
    else decrypt();

    void encrypt(){
        int i;
        for(i = 0; i < Strlen(cred)-1; ++i){
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
        for(i = 0; i < Strlen(cred)-1; ++i){
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

int main(){
    
    char cred[MAX];

    printf("Enter the text: ");
    fgets(cred, MAX, stdin);

    vignere_cipher(cred);

    return 0;
}