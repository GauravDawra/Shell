#include<stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]){
    // for(int i=0;i<argc;i++)
    //     printf("%s", argv[i]);
    char *binaryPath = "./bin/date";
    char *arg1 = "-a";
    char *arg2 = "/Users/gaurav/C++Projects/OS_Assignment1/Excercies2/src/cat.c";
    // char *args[] = {"-A", arg2};
    // printf("%02d", 2);
    execl(binaryPath, binaryPath, arg2, NULL);
    return 0;
}