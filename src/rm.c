#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

short DIRECTORY_REMOVE = 0;
short ASK_PERMISSION = 0;

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int cfileexists(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else // -1
        return 0;
}

int main(int argc, char* argv[]){
    // int del = remove("/Users/gaurav/C++Projects/OS_Assignment1/Excercies2/src/test.txt");
    
    for(int i=0;i<argc;i++){
        if(strcmp(argv[i], "-d") == 0) DIRECTORY_REMOVE = 1;
        if(strcmp(argv[i], "-i") == 0) ASK_PERMISSION = 1;
    }

    if(strcmp(argv[argc-1],".") == 0 || strcmp(argv[argc-1],"..") == 0){
        printf("You cannot remove %s", argv[argc-1]);
        return 0;
    }
    
    if(cfileexists(argv[argc-1]) == 0){
        printf("rm: file/directory does not exist\n");
        return 0;
    }

    if(!DIRECTORY_REMOVE && is_regular_file(argv[argc - 1]) == 0){
        printf("rm: the inputted parameter is a directory\n");
        return 0;
    }
    // if(!del) printf("The file is Deleted successfully");
    if(ASK_PERMISSION){
        printf("remove %s? ", argv[argc-1]);
        char ans[100]; scanf("%s", ans);
        if(ans[0] == 'n' || ans[0]=='N') return 0;
    }
    int del = remove(argv[argc-1]);
    if(del) {
        printf("The file/directory is not deleted\n");
    }

    return 0;
}