#include <dirent.h>
#include <stdio.h>
#include <string.h>

short SHOW_HIDDEN = 0;
short HIDE_PARENT_CURRENT = 0;

int main(int argc, char* argv[]){
    DIR* d;
    struct dirent *dir;
    d = opendir(argv[argc - 1]);
    // for(int i=0;i<argc;i++)
    //     printf("%s ", argv[i]);
    for(int i=0;i<argc-1;i++){
        if(strcmp(argv[i], "-a") == 0) SHOW_HIDDEN = 1;
        if(strcmp(argv[i], "-A") == 0) HIDE_PARENT_CURRENT = 1;
    }
    if(d){
        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_name[0] == '.'){
                if(SHOW_HIDDEN) { 
                    printf("%s\n", dir->d_name); 
                    continue; 
                }
                
                if(HIDE_PARENT_CURRENT){
                    if(strcmp(dir->d_name, ".") == 0 || 
                        strcmp(dir->d_name, "..") == 0);
                    else printf("%s\n", dir->d_name);
                }
                
            }
            else 
                printf("%s\n", dir->d_name);
        }
        closedir(d);
    } 
    else perror("ls");
    return 0;
}
