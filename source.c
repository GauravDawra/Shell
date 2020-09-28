#include <stdio.h>

#include <sys/types.h> 
#include <sys/stat.h>
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h>
#include <unistd.h> 
#include <dirent.h>

#include<string.h>

const int MAX_PATH_LENGTH = 1024;
DIR* dir_ptr;
char dir_name[MAX_PATH_LENGTH];
char base_dir[MAX_PATH_LENGTH];

const int MAX_HISTORY_LENGTH = 500;
char* history_buffer[MAX_HISTORY_LENGTH];
int history_ptr = 0;


/********** - INPUT HANDLING - **********/
const int MAX_TOKENS = 10;
const int MAX_TOKEN_SIZE = 128;
const int MAX_COMMAND_LENGTH = MAX_TOKENS * MAX_TOKEN_SIZE;
char *input_buffer[MAX_TOKENS];
char command[MAX_COMMAND_LENGTH];
int input_cnt = 0;
/*
    MAX_COMMAND_LENGTH = MAX_TOKENS * MAX_TOKEN_SIZE
    should always be maintained. This is an approximation but 
    still works.
*/


void init(){
    getcwd(base_dir, MAX_PATH_LENGTH);
    dir_ptr = opendir("/"); // open current directory;
    // dir_name="/";
    chdir("/");
    getcwd(dir_name, MAX_PATH_LENGTH);
    // strcpy(dir_name, "/");

    for(int i=0;i<MAX_HISTORY_LENGTH;i++){
        history_buffer[i] = "\0";
    }
    for(int i=0;i<MAX_HISTORY_LENGTH;i++){
        history_buffer[i] = (char*)malloc(MAX_COMMAND_LENGTH * sizeof(char));
    }
    // for(int i=0;i<MAX_TOKENS;i++){
    //     input_buffer[i] = (char*) malloc(MAX_TOKEN_SIZE * (sizeof(char)));
    // }

}

void _close(){
    for(int i=0;i<MAX_HISTORY_LENGTH;i++){
        free(history_buffer[i]);
    }
    // for(int i=0;i<MAX_TOKENS;i++)
    //     free(input_buffer[i]);
}

int is_regular_file(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0){
    //    printf("Doesn't exist");
       return 0;
    }
   return S_ISDIR(statbuf.st_mode);
}

void _cd(char* dir){
    char new_dir[MAX_PATH_LENGTH];
    int ptr = 0;
    for(int i=0;dir_name[i]!='\0';i++) new_dir[ptr++]=dir_name[i];
    if(new_dir[ptr-1]!='/') new_dir[ptr++] = '/';
    for(int i=0;dir[i]!='\0';i++) new_dir[ptr++] = dir[i];
    new_dir[ptr++] = '\0';
    // printf("%s", new_dir);
    if(isDirectory(new_dir)){
        strcpy(dir_name, new_dir);
        return;
    }
    else if(isDirectory(dir)){
        strcpy(dir_name, dir);
        return;
    }
    printf("Directory does not exist\n");
}

void _cd_2(char* dir){
    int result = chdir(dir);
    if(result != 0) printf("cd: no such directory\n");
    getcwd(dir_name, MAX_PATH_LENGTH);
}

void _pwd(){
    printf("%s\n", dir_name);
}

void _echo(char* str){
    printf("%s\n", str);
}

void _history(){
    int nxt = (history_ptr+1)%MAX_HISTORY_LENGTH;
    for(int i=0;i<MAX_HISTORY_LENGTH;i++){
        if(strcmp(history_buffer[nxt], "\0") == 0);
        else printf("%s\n", history_buffer[nxt]);
        nxt = (nxt+1)%MAX_HISTORY_LENGTH;
    }
}

void _exit_0(){
    _close();
    printf("closing....\n");
    exit(0);
}


int tokenize(char *str, char *buff[MAX_TOKENS]){
    // token
    int ptr = 0;
    int ind = 0;
    char token[MAX_TOKEN_SIZE];
    char sub[MAX_COMMAND_LENGTH];
    // strcpy(sub, str);
    char* it = str;
    
    for(int i=0;str[i]!='\0';i++){
    
        if(str[i] == ' '){
    
            buff[ptr++] = it;
            str[i] = '\0';
            it = str + i + 1;
        }
        
    }
    buff[ptr++] = it;
    return ptr;
}

int tokenize2(char str[MAX_COMMAND_LENGTH], char **buff){
    char delim[] = " ";
    char* ptr = strtok(str, delim);
    int cnt = 0;
    
    while(ptr!=NULL){
        strcpy(buff[cnt++], ptr);
        ptr = strtok(NULL, delim);
    }
    return cnt;
}

int input(){
    printf("%s$ ", dir_name);
    gets(command);
    int cnt = tokenize(command, input_buffer);
    for(int i=cnt;i<MAX_TOKENS;i++){
        input_buffer[i] = NULL;
    }
    return input_cnt = cnt;
}

void handle_internal_command(){
    if(strcmp(input_buffer[0], "cd") == 0){
        _cd_2(input_buffer[input_cnt - 1]);
    }
    else if(strcmp(input_buffer[0], "pwd") == 0){
        _pwd();
    }
    else if(strcmp(input_buffer[0], "echo") == 0){
        _echo(input_buffer[input_cnt - 1]);
    }
    else if(strcmp(input_buffer[0], "exit") == 0){
        _exit_0();
    }
    else if(strcmp(input_buffer[0], "history") == 0){
        _history();
    }
}

void handle_external_command(){

    pid_t pid = fork();
    if(pid < 0){
        printf("Fork failed\n");
        return;
    }
    
    if(pid == 0){
        if(strcmp(input_buffer[0], "date") == 0){
            char path[MAX_PATH_LENGTH];
            strcpy(path, base_dir);
            strcat(path, "/bin/date");
            execv(path, input_buffer);
            printf("date: Error occurred\n");
            exit(0);
        }
        if(strcmp(input_buffer[0], "ls") == 0){ // to be corrected
            char path[MAX_PATH_LENGTH];
            strcpy(path, base_dir);
            strcat(path, "/bin/ls");
            input_buffer[input_cnt] = dir_name;
            execv(path, input_buffer);
            printf("ls: Error occurred\n");
            exit(0);
        }
        if(strcmp(input_buffer[0], "mkdir") == 0){
            char path[MAX_PATH_LENGTH];
            strcpy(path, base_dir);
            strcat(path, "/bin/mkdir");
            execv(path, input_buffer);
            printf("mkdir: Error occurred\n");
            exit(0);
        }
        if(strcmp(input_buffer[0], "rm") == 0){
            char path[MAX_PATH_LENGTH];
            strcpy(path, base_dir);
            strcat(path, "/bin/rm");
            execv(path, input_buffer);
            printf("rm: Error occurred");
            exit(0);
        }
        if(strcmp(input_buffer[0], "cat") == 0){
            char path[MAX_PATH_LENGTH];
            strcpy(path, base_dir);
            strcat(path, "/bin/cat");
            execv(path, input_buffer);
            printf("cat: Error occurred");
            exit(0);
        }
        printf("Command not found\n");
        exit(0);
    }
    else if(pid > 0){
        waitpid(-1, NULL, 0);
    }
}
void process_command(){
    strcpy(history_buffer[history_ptr], command);
    history_ptr = (history_ptr+1)%MAX_HISTORY_LENGTH;
    
    if(strcmp(input_buffer[0], "cd") == 0 || 
       strcmp(input_buffer[0], "pwd") == 0 ||
       strcmp(input_buffer[0], "echo") == 0 ||
       strcmp(input_buffer[0], "exit") == 0 ||
       strcmp(input_buffer[0], "history") == 0)
        handle_internal_command();

    else{
        handle_external_command();
    }
}

int main(){

    init();
    while(1){
        int cnt = input();
        process_command();
    }
    
    _close();
    return 0;
}