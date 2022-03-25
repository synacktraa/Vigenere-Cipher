#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX 100
#define NLET 26
#define UTL 32

char *basename(char const *path) {

    auto char *win_basename_parser(char const *);
    auto char *unix_basename_parser(char const *);
    
    char *win_basename_parser(char const *path) {
        char *s = strrchr(path, '\\');
        if(!s) 
            return strdup(path);
        else 
            return strdup(s + 1);
    }

    char *unix_basename_parser(char const *path) {
        char *s = strrchr(path, '/');
        if(!s) 
            return strdup(path);
        else 
            return strdup(s + 1);
    }

    if(strcmp(path, unix_basename_parser(path)))
        return strdup(unix_basename_parser(path));

    return strdup(win_basename_parser(path));
}

int vignere_cipher(char*key, char*mode, char*cred){

    auto void encrypt();
    auto void decrypt();

    int cred_len, key_len;

    cred_len = strlen(cred);
    key_len = strlen(key);

    char *cipher = (char*)malloc(sizeof(char) * cred_len);
    char *gen_key = (char*)malloc(sizeof(char) * cred_len);

    if(cipher == NULL || gen_key == NULL){
        return 1;
    }

    int j = 0, i;
    if(key_len < cred_len){
        for(i = 0; i < cred_len; ++i){
            if(j >= key_len)
                j = 0;
            if((i[cred] >=32 && i[cred] <=64) || (i[cred] >=91 && i[cred] <=96)
                || (i[cred] >=123 && i[cred] <=126)){
                    i[gen_key] = i[cred];
            } else {i[gen_key] = j[key]; ++j;}
            
        }
        i[gen_key] = '\0';   
    }

    if(strcmp(mode, "--encrypt") == 0) encrypt();
    else if(strcmp(mode, "--decrypt") == 0) decrypt();

    void encrypt(){

        for(i = 0; i < strlen(cred); ++i){
            if((toupper(i[cred]) >=65 && toupper(i[cred]) <=90)){
                i[cipher] = toupper(i[cred]) - (65 - toupper(i[gen_key]));
                if(i[cipher] > 90)
                    i[cipher] = i[cipher]-NLET;
            } else
                i[cipher] = i[cred];

            if(islower(i[cred])){
                i[cipher] = i[cipher]+UTL;
            }
        }
        i[cipher] = '\0';
    }

    void decrypt(){

        for(i = 0; i < strlen(cred); ++i){
            if((toupper(i[cred]) >=65 && toupper(i[cred]) <=90)){
                i[cipher] = toupper(i[cred]) - (toupper(i[gen_key]) - 65);
                if(i[cipher] < 65)
                    i[cipher] = i[cipher]+NLET;
            }else
                i[cipher] = i[cred];

            if(islower(i[cred])){
                i[cipher] = i[cipher]+UTL;
            }
        }
        i[cipher] = '\0';
    }
    puts(cipher);

    free(cipher);
    free(gen_key);
}

int main(int argc, char*argv[]){
    
    if(argc == 2 && (strcmp(argv[1], "--help")||strcmp(argv[1], "-h"))){
        fprintf(stdout, "\nUsage: %s <key> <mode> <data>\n|CLI options|:-\
        \n\t<data> = A plaintext or ciphertext.\
        \n\t<key> = A key string to scramble and unscramble the data.\
        \n\t<mode>:\n\t\t--encrypt = Encrypts the data string\
        \n\t\t--decrypt = Decrypts the data string\n\n", basename(argv[0]));
    }else if(argc == 4){
        vignere_cipher(argv[1], argv[2], argv[3]);
    } else{
        fprintf(stderr, "\nUsage: %s <key> <mode> <data>\
        \nFor more, check help section:\
        \n    %s --help 'or' -h\n", basename(argv[0]), basename(argv[0]));
        return 1;
    }

    return 0;
}