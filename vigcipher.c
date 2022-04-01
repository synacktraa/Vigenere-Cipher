#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX 100
#define NLET 26
#define UTL 32


char ch = 0, slash = '/';

char *basename(char const *path, char slash) {

    char *s = strrchr(path, slash);
    if(!s) 
        return strdup(path);
    else 
        return strdup(s + 1);
}


int delete(char*data, int index, int len){

    int i;
    for (i = index; i < (len)-1; i++)
        *(data+i) = *(data+i+1);

    *(data+i) = '\0';
    len--;
    return len;

}


int get_filesize(char file_name[]){

    FILE* fp = fopen(file_name, "r");
    if (fp == NULL) {
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    int res = ftell(fp);
    fclose(fp);
  
    return res;
}


int checkIfFileExists(const char * filename) {

    FILE *file;
    if((file = fopen(filename, "r")) != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}


char* get_file_data(char*file) {

/*
    Checks if file exists on the system, if yes
    stores the file size in buffer_len var
    by evaulating get_filesize function which 
    retrieves the file size and then reads the
    file line by line and stores it in buffer 
    and then concatenate it to data_storage
    and finally frees the buffer and return data_storage
*/
    if(!checkIfFileExists(file)) {
        fprintf(stderr, "FileError: can't open %s file.", file);
        putc(ch, stdout);
        exit(1);
    }

    int buffer_len = get_filesize(file)+2;
    
    FILE * file_in = fopen(file, "r");
    char* data_storage = (char*)malloc(sizeof(char) * buffer_len);
    char* buffer = (char*)malloc(sizeof(char) * buffer_len);

    memset(data_storage, 0, strlen(data_storage));
    while (fgets(buffer, buffer_len, file_in))
        strcat(data_storage, buffer);

    free(buffer);
    return data_storage;
}


char* key_generator(char*key, char*cred){

    int cred_len, key_len, j = 0, i;

    cred_len = strlen(cred)+1;
    key_len = strlen(key)+1;

    char *gen_key = (char*)malloc(sizeof(char) * cred_len);

    if(gen_key == NULL)
        exit(1);

    for(i = 0; i < key_len; ++i){

        if(isdigit(i[key])){
            fprintf(stderr, "CharError: character %c not in list, expected -> [a-zA-Z]", i[key]);
            putchar(ch);
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


void eval(char* cred, char* key, char operstatus){

    int cred_len = strlen(cred)+1, i;
    char *product = (char*)malloc(sizeof(char) * cred_len);


    if(product == NULL)
        exit(0);
        
    for(i = 0; i < strlen(cred)+1; ++i){
        if(operstatus == 'e'){
            if((toupper(i[cred]) >=65 && toupper(i[cred]) <=90)){
                i[product] = toupper(i[cred]) - (65 - toupper(i[key]));
                if(i[product] > 90)
                    i[product] = i[product]-NLET;
            } else i[product] = i[cred];

        } else{ 
            if((toupper(i[cred]) >=65 && toupper(i[cred]) <=90)){
                i[product] = toupper(i[cred]) - (toupper(i[key]) - 65);
                if(i[product] < 65)
                    i[product] = i[product]+NLET;
            } else i[product] = i[cred];
        }
        if(islower(i[cred])){
            i[product] = i[product]+UTL;
        }
    }
    i[product] = '\0';

    free(key);
    puts(product);
    free(product); 
}


void help(){
    fprintf(stdout, "\n|CLI options|:-\
        \n   -k = takes next argument as key to manipulate data\
        \n   -e = takes next argument as data to encrypt it\
        \n   -d = takes next argument as data to decrypt it");
        putchar(ch);

}

void usage(char* exe){
    fprintf(stderr, "\nUsage: %s -k <key> -e/-d data", exe);
    fprintf(stderr, "\nFor more, check help section:\
    \n    %s -h", exe);
    putchar(ch);

}

int validate_args(char* next_arg, char* exe, char* type){
    if(next_arg == NULL ||
        !strcmp(next_arg, "-e") ||
        !strcmp(next_arg, "-d") ||
        !strcmp(next_arg, "-k")){
            fprintf(stderr, "InputError: %s not detected!", type);
            putchar(ch);
            usage(basename(exe, slash));
            return 1;
    }
    return 0;
}

int main(int argc, char*argv[]){
    

    int enc_stat = 0, dec_stat = 0, i;
    char *keygen, *key, *src, *cred, op = 0;

    #ifdef _WIN32
        ch = 0;
        slash = '\\';
    #elif __unix__
        ch = 10;
        slash = '/';
    #endif

    if (argc == 1){
        usage(basename(argv[0], slash));
        return 1;

    } else if(argc == 2 && (!strcmp(argv[1], "-h"))){
        fprintf(stdout, "\nUsage: %s -k <key> -e/-d data\n", basename(argv[0], slash));
        fprintf(stdout, "Note: to take input from file, put 'file:' before filename");
        putchar(ch);
        help();
        return 0;

    } else {

        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-k")){
                if(validate_args(argv[i+1], argv[0], "key"))
                    return 1;
                key = argv[i+1];
            } else 
                continue;
        }

        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-e")){
                if(validate_args(argv[i+1], argv[0], "data"))
                    return 1;
                src = argv[i+1];
                enc_stat = 1;
            } else 
                continue;
        }

        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-d")){
                if(validate_args(argv[i+1], argv[0], "data"))
                    return 1;
                src = argv[i+1];
                dec_stat = 1;
            } else 
                continue;
        }

    }

    if(enc_stat && dec_stat)
    {
        fprintf(stderr, "OperationError: can't perform both operation at the same time.");
        putchar(ch);
        return 1;
    }
    
    if(enc_stat == 0 && dec_stat == 0)
    {
        fprintf(stderr, "OperationError: no operation or data specified.");
        putchar(ch);
        return 1;
    }   

    if(!strncmp(src, "file:", 5)){
        for(i = 0; i < 5; ++i)
            delete(src, 0, strlen(src));
        cred = get_file_data(src);
    } else {
        cred = src;
    }
    keygen = key_generator(key, cred);

    if(enc_stat) 
        op = 'e';
    else if(dec_stat) 
        op = 'd';

    eval(cred,keygen, op);

    return 0;
}