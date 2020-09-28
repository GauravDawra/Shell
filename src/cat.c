#include <stdio.h>
#include <string.h>
const int MAX_LINE_LENGTH = 1024;

short NUMBER_LINES = 0;
short NUMBER_NON_BLANK = 0;
int main(int argc, char* argv[]){
    // cout<<'h';
    // printf("hello");

    for(int i=0;i<argc;i++){
        if(strcmp(argv[i], "-b") == 0) NUMBER_NON_BLANK = 1;
        if(strcmp(argv[i], "-n") == 0) {
            NUMBER_LINES = 1;
            NUMBER_NON_BLANK = 0;
        }
    }

    FILE* fp = fopen(argv[argc-1], "r");
    char str[MAX_LINE_LENGTH];
    int cnt = 1;
    int cnt_non_blank = 1;
    while(fgets(str, MAX_LINE_LENGTH, fp)){
        int len = strlen(str);
        if(len && str[len-1] == '\n'){
            str[len-1] = '\0';
            len--;
        }
        if(NUMBER_LINES) printf("%d  ", cnt++);
        if(NUMBER_NON_BLANK) 
            if(len) printf("%d  ", cnt_non_blank++);
        printf("%s\n", str);
    }
    return 0;
}