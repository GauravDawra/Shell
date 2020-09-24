#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
// int is_regular_file(const char *path)
// {
//     struct stat path_stat;
//     stat(path, &path_stat);
//     return S_ISREG(path_stat.st_mode);
// }

int main(int argc, char* argv[]){
    // for(int i=0;i<argc;i++)
    //     printf("%s", argv[i]);
    char *binaryPath = "./bin/mkdir";
    // char *arg1 = "-a";
    char *arg2 = "/Users/gaurav/C++Projects/OS_Assignment1/Excercies2/test";
    // char *args[] = {"-A", arg2};
    // printf("%02d", 2);
    // printf("%d", is_regular_file(arg2));
    execl(binaryPath, binaryPath,"hi", NULL);
    return 0;
}