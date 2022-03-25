#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX 100
#define NLET 26
#define UTL 32

char *basename(char const *);
int delete(char*, int, int);
char* key_generator(char*, char*);
void encrypt(char*, char*);
void decrypt(char*, char*);


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


int delete(char*data, int index, int len){

    int i;
    for (i = index; i < (len)-1; i++)
        *(data+i) = *(data+i+1);

    *(data+i) = '\0';
    len--;
    return len;

}


char* key_generator(char*key, char*cred){

    int cred_len, key_len, j = 0, i;

    cred_len = strlen(cred);
    key_len = strlen(key);

    char *gen_key = (char*)malloc(sizeof(char) * cred_len);

    if(gen_key == NULL)
        exit(1);

    for(i = 0; i < key_len; ++i){

        if(isdigit(i[key])){
            fprintf(stderr, "character %c not in list, expected: [a-zA-Z]", i[key]);
            exit(1);
        }

        if(isalpha(i[key]) == 0)
            key_len = delete(key, i, key_len);
    }

    for(i = 0; i < cred_len; ++i){

        if(j >= key_len)
            j = 0;

        if(isalpha(i[cred]) == 0){
                i[gen_key] = i[cred];
        } else {i[gen_key] = j[key]; ++j;}
        
    }
    i[gen_key] = '\0';   

    return gen_key;
}


void encrypt(char* cred, char* key){

    int cred_len = strlen(cred), i;
    char *cipher = (char*)malloc(sizeof(char) * cred_len);

    if(cipher == NULL)
        exit(0);

    for(i = 0; i < strlen(cred); ++i){
        if((toupper(i[cred]) >=65 && toupper(i[cred]) <=90)){
            i[cipher] = toupper(i[cred]) - (65 - toupper(i[key]));
            if(i[cipher] > 90)
                i[cipher] = i[cipher]-NLET;
        } else
            i[cipher] = i[cred];

        if(islower(i[cred])){
            i[cipher] = i[cipher]+UTL;
        }
    }
    i[cipher] = '\0';
    puts(cipher);

    free(cipher); free(key);
}


void decrypt(char* cred, char* key){

    int cred_len = strlen(cred), i;
    char *cipher = (char*)malloc(sizeof(char) * cred_len);

    if(cipher == NULL)
        exit(1);

    for(i = 0; i < strlen(cred); ++i){
        if((toupper(i[cred]) >=65 && toupper(i[cred]) <=90)){
            i[cipher] = toupper(i[cred]) - (toupper(i[key]) - 65);
            if(i[cipher] < 65)
                i[cipher] = i[cipher]+NLET;
        }else
            i[cipher] = i[cred];

        if(islower(i[cred])){
            i[cipher] = i[cipher]+UTL;
        }
    }
    i[cipher] = '\0';
    puts(cipher);

    free(cipher); free(key);
}


int main(int argc, char*argv[]){
    
    auto void help();
    auto void usage(char*);

    int enc_stat = 0, dec_stat = 0, i;
    char *keygen, *key, *cred;

    void help(){
        fprintf(stdout, "\n|CLI options|:-\
            \n\t<data> = A plaintext or ciphertext.\
            \n\t<key> = A key string to scramble and unscramble the data.\
            \n\t<mode>:\n\t\t--encrypt = Encrypts the data string\
            \n\t\t--decrypt = Decrypts the data string\n\n");
    }

    void usage(char* exe){
        fprintf(stderr, "\nUsage: %s -k <key> -e/-d data\n", exe);
        fprintf(stderr, "\nFor more, check help section:\
        \n    %s -h\n\n", exe);
    }

    if (argc == 1){
        usage(basename(argv[0]));
        return 1;

    } else if(argc == 2 && (!strcmp(argv[1], "-h"))){
        fprintf(stdout, "\nUsage: %s -k <key> -e/-d data", basename(argv[0]));
        help();
        return 0;

    } else {

        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-k")){
                if(argv[i+1] == NULL ||
                   !strcmp(argv[i+1], "-e") ||
                   !strcmp(argv[i+1], "-d") ||
                   !strcmp(argv[i+1], "-k")){
                        fprintf(stderr, "InputError: key not detected!\n");
                        usage(basename(argv[0]));
                        return 1;
                } 
                key = argv[i+1];
            } else 
                continue;
        }

        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-e")){
                if(argv[i+1] == NULL ||
                   !strcmp(argv[i+1], "-e") ||
                   !strcmp(argv[i+1], "-d") ||
                   !strcmp(argv[i+1], "-k")){
                        fprintf(stderr, "InputError: data not detected!\n");
                        usage(basename(argv[0]));
                        return 1;
                }
                cred = argv[i+1];
                enc_stat = 1;
            } else 
                continue;
        }

        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-d")){
                if(argv[i+1] == NULL ||
                   !strcmp(argv[i+1], "-e") ||
                   !strcmp(argv[i+1], "-d") ||
                   !strcmp(argv[i+1], "-k")){
                    fprintf(stderr, "InputError: data not detected!\n");
                    usage(basename(argv[0]));
                    return 1;
                }
                cred = argv[i+1];
                dec_stat = 1;
            } else 
                continue;
        }

    }

    if(enc_stat && dec_stat)
    {
        fprintf(stderr, "OperationError: can't perform both operation at the same time.");
        return 1;
    }
    
    if(enc_stat == 0 && dec_stat == 0)
    {
        fprintf(stderr, "OperationError: no operation or data specified.");
        return 1;
    }   

    if(enc_stat) 
    {
        keygen = key_generator(key, cred);
        encrypt(cred, keygen);
    } else if(dec_stat) 
    {
        keygen = key_generator(key, cred);
        decrypt(cred, keygen);
    }

    return 0;
}