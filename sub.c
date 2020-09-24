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

int cfileexists(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else // -1
        return 0;
}

int main(int argc, char* argv[]){
    // for(int i=0;i<argc;i++)
    //     printf("%s", argv[i]);
    char *binaryPath = "./bin/mkdir";
    // char *arg1 = "-a";
    char *arg2 = "/Users/gaurav/C++Projects/OS_Assignment1/Excercies2/test";
    // char *args[] = {"-A", arg2};
    // printf("%02d", 2);
    // printf("%d", is_regular_file(arg2));

    struct stat buffer;
    int exist = stat("src",&buffer);

    printf("%d", exist);
    // execl(binaryPath, binaryPath,"hi", NULL);
    return 0;
}