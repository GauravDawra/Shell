#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

short INTERMEDIATE_DIRECTORIES = 0;
short BE_VERBOSE = 0;

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0){
       return 0;
    }
   return S_ISDIR(statbuf.st_mode);
}

void output_directory_created(char* s){
    if(BE_VERBOSE) printf("mkdir: created directory '%s'\n", s);
}

int mkdir_recursive(char* dir, int mode){
    int len = strlen(dir);
    int res = mkdir(dir, mode);
    if(res==0) {output_directory_created(dir); return 0;}
    for(int i=len-1;i>=0;i--){
        if(dir[i] == '/'){
            dir[i] = '\0';
            res = mkdir_recursive(dir, mode);
            if(res == 0) {
                dir[i] = '/';
                res = mkdir(dir, mode);
                output_directory_created(dir);
                return res;
            }
            return -1;
        }
    }
    return -1;
}

int main(int argc, char* argv[]){

    for(int i=0;i<argc;i++){
        if(strcmp(argv[i], "-p") == 0) INTERMEDIATE_DIRECTORIES = 1;
        if(strcmp(argv[i], "-v") == 0) BE_VERBOSE = 1;
    }
    int res = 0;
    char* dir = argv[argc-1];
    if(INTERMEDIATE_DIRECTORIES){
        res = mkdir_recursive(dir, 0777);
    }
    else {
        res = mkdir(dir, 0777);
        if(res == 0) output_directory_created(dir);
    }
    if(res != 0) printf("mkdir: directory cannot be created\n");
    return 0;
}