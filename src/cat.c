#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
const int MAX_LINE_LENGTH = 1024;

short NUMBER_LINES = 0;
short NUMBER_NON_BLANK = 0;

int is_regular_file(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(int argc, char* argv[]){

    for(int i=0;i<argc;i++){
        if(strcmp(argv[i], "-b") == 0) NUMBER_NON_BLANK = 1;
        if(strcmp(argv[i], "-n") == 0) {
            NUMBER_LINES = 1;
            NUMBER_NON_BLANK = 0;
        }
    }

    if(!is_regular_file(argv[argc-1])){
        printf("cat: %s: No such file\n", argv[argc-1]);
        return 0;
    }

    FILE* fp = fopen(argv[argc-1], "r");
    if(fp == NULL){
        printf("cat: File could not be opened\n");
        return 0;
    }
    char str[MAX_LINE_LENGTH];
    int cnt = 1;
    int cnt_non_blank = 1;
    while(fgets(str, MAX_LINE_LENGTH, fp)){
        int len = strlen(str);
        int has_endline = 0;
        if(len && str[len-1] == '\n'){
            str[len-1] = '\0';
            len--;
            has_endline = 1;
        }
        if(NUMBER_LINES) printf("%d  ", cnt++);
        if(NUMBER_NON_BLANK) 
            if(len) printf("%d  ", cnt_non_blank++);
        printf("%s", str);
        if(has_endline) printf("\n");
    }
    return 0;
}