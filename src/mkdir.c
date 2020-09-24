#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    mkdir(argv[argc-1], 0777);
    return 0;
}