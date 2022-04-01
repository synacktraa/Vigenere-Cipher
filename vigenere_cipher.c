#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define NLET 26
#define UTL 32


char slash = '/', ch = 0;

char *basename(char const *path) {

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

    cred_len = strlen(cred);
    key_len = strlen(key);

    char *gen_key = (char*)malloc(sizeof(char) * cred_len);

    if(gen_key == NULL)
        exit(1);

    for(i = 0; i < key_len; ++i){

        if(isdigit(i[key])){
            fprintf(stderr, "CharError: character %c not in list, expected: [a-zA-Z]", i[key]);
            putc(ch, stdout);
            exit(1);
        }

        while(isalpha(i[key]) == 0)
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


void eval(char* cred, char* key, char mode){

    int cred_len = strlen(cred), i;
    char *outcome = (char*)malloc(sizeof(char) * cred_len);

    if(outcome == NULL)
        exit(0);

    if(mode == 'e'){
        for(i = 0; i < strlen(cred); ++i){
            if((toupper(i[cred]) >=65 && toupper(i[cred]) <=90)){
                i[outcome] = toupper(i[cred]) - (65 - toupper(i[key]));
                if(i[outcome] > 90)
                    i[outcome] = i[outcome]-NLET;
            } else
                i[outcome] = i[cred];

            if(islower(i[cred])){
                i[outcome] = i[outcome]+UTL;
            }
        }
        i[outcome] = '\0';

    } else if(mode == 'd'){

        for(i = 0; i < strlen(cred); ++i){
            if((toupper(i[cred]) >=65 && toupper(i[cred]) <=90)){
                i[outcome] = toupper(i[cred]) - (toupper(i[key]) - 65);
                if(i[outcome] < 65)
                    i[outcome] = i[outcome]+NLET;
            }else
                i[outcome] = i[cred];

            if(islower(i[cred])){
                i[outcome] = i[outcome]+UTL;
            }
        }
        i[outcome] = '\0';
    }
    puts(outcome);

    free(outcome); free(key);
}


void usage(char* exe){
        fprintf(stderr, "\nUsage: %s -k <key> (-e|-d)  (-s|-f) (string|file)\n", exe);
        fprintf(stderr, "\nFor more, check help section:\
        \n    %s -h\n", exe);
        putc(ch, stdout);
}
int validate_args(char* next_arg, char* exe, char* type){
    if(next_arg == NULL ||
        !strcmp(next_arg, "-e") ||
        !strcmp(next_arg, "-d") ||
        !strcmp(next_arg, "-k")){
            fprintf(stderr, "InputError: %s not detected!", type);
            putchar(ch);
            usage(basename(exe));
            return 1;
    }
    return 0;
}
void help(){
    fprintf(stdout, "\n|CLI options|:-\
        \n   -k = takes next argument as key\
        \n   -s = takes next argument as string\
        \n   -f = takes next argument as filename\
        \n   -e = encrypts the data string\
        \n   -d = decrypts the data string");
        putc(ch, stdout);
}

int main(int argc, char*argv[]){
    


    #ifdef _WIN32
        ch = 0;
        slash = '\\';
    #elif __unix__
        ch = 10;
        slash = '/';
    #endif

    int enc_stat = 0, dec_stat = 0, i, file_stat = 0, str_stat =0;
    char *keygen, *key, *cred, mode = 'e', *file = NULL;


    

    if (argc == 1 || argc > 6){
        usage(basename(argv[0]));
        return 1;

    } else if(argc == 2 && (!strcmp(argv[1], "-h"))){
        fprintf(stdout, "\nUsage: %s -k <key> (-e|-d)  (-s|-f) (string|file)", basename(argv[0]));
        help();
        return 0;

    } else if(argc == 6) {

        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-k")){
                if(validate_args(argv[i+1], argv[0], "key"))
                    return 1;
                key = argv[i+1];
            } else 
                continue;
        }
        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-s")){
                if(validate_args(argv[i+1], argv[0], "data"))
                    return 1;
                cred = argv[i+1];
                str_stat = 1;
            } else 
                continue;
        }
        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-f")){
                if(validate_args(argv[i+1], argv[0], "file"))
                    return 1;
                file = argv[i+1];
                file_stat = 1;

            } else 
                continue;
        }
        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-e")){
                enc_stat = 1;
            } else 
                continue;
        }

        for(i = 0; i < argc; ++i){
            if(!strcmp(argv[i], "-d")){
                dec_stat = 1;
            } else 
                continue;
        }

    }

    if(file_stat && str_stat)
    {
        fprintf(stderr, "InputError: can't take data from two streams.");
        putc(ch, stdout);
        return 1;
    }
    
    if(file_stat == 0 && str_stat == 0)
    {
        fprintf(stderr, "InputError: data not detected");
        putc(ch, stdout);
        return 1;
    }  
    
    if(enc_stat && dec_stat)
    {
        fprintf(stderr, "OperationError: can't perform both operation at the same time.");
        putc(ch, stdout);
        return 1;
    }
    
    if(enc_stat == 0 && dec_stat == 0)
    {
        fprintf(stderr, "OperationError: no operation specified.");
        putc(ch, stdout);
        return 1;
    }   



    if(enc_stat) 
    {
        mode = 'e';
    } else if(dec_stat) 
        mode = 'd';
    
    if(file_stat)
        cred = get_file_data(file);

    keygen = key_generator(key, cred);

    eval(cred, keygen, mode);
    return 0;
}