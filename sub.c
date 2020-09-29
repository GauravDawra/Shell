#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdlib.h>
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
#include <string.h>
int main(int argc, char* argv[]){
    // for(int i=0;i<argc;i++)
    //     printf("%s", argv[i]);
    // char *binaryPath = "./bin/mkdir";
    // char *arg1 = "-a";
    // char *arg2 = "/Users/gaurav/C++Projects/OS_Assignment1/Excercies2/test";
    // char *args[] = {"-A", arg2};
    // printf("%02d", 2);
    // printf("%d", is_regular_file(arg2));

    // struct stat buffer;
    // char base_dir[100]; getcwd(base_dir, 100);
    // char dir_name[100] ; getcwd(dir_name, 100);
    // char path[100];
    // printf("%s", base_dir);
    // strcpy(path, base_dir);
    // strcat(path, "/bin/ls");
    
    // char* input_buffer[10];
    // input_buffer[0] = "ls";
    // input_buffer[1] = dir_name;
    // input_buffer[2] = NULL;
    // char* args[] = {"/Users/gaurav/C++Projects/OS_Assignment1/Excercies2", NULL};
    // execv("./bin/ls", args);
    // char buf[1024];
    // char* res = realpath("./src2/source.c", buf);
    // printf("%s", buf);
    // char* sl = "/Users/gaurav/C++Projects/OS_Assignment1/Excercies2/src2/dateC";
    char original[100];
    // if(readlink(sl,original, sizeof(original)) < 0)
    //     printf("Error\n");
    // else printf("%s", original);
    // printf("%c %d\n", 'f', (int)'f');
    // printf("%c %d\n", 'n', (int)'n');
    // printf("%c %d\n", 'r', (int)'r');
    // printf("%c %d\n", 't', (int)'t');
    // printf("%c %d\n", 'v', (int)'v');
    // printf("%c %d\n", '\\', (int)'\\');
    // int res=mkdir("/Users/gaurav/C++Projects/OS_Assignment1/Excercies2", 0777);
    // printf("%d", res);
    // printf("%s", getenv("PWD"));
    
    realpath(".", original);
    printf("%s\n", original);
    return 0;
}