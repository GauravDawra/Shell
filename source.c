#include <stdio.h>

#include <sys/types.h> 
#include <sys/stat.h>
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h>
#include <unistd.h> 
#include <dirent.h>
#include <limits.h>
#include <string.h>

const int MAX_HOST_SIZE = 128;
const int MAX_USER_SIZE = 128;
char host_name[MAX_HOST_SIZE];
char user_name[MAX_USER_SIZE];

const int MAX_PATH_LENGTH = 1024;
DIR* dir_ptr;
char dir_name[MAX_PATH_LENGTH];
char *dir_name_symlinks;
char base_dir[MAX_PATH_LENGTH];


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

const int MAX_HISTORY_LENGTH = 500;
char history_buffer[MAX_HISTORY_LENGTH][MAX_COMMAND_LENGTH];
int history_ptr = 0;


void init(){
    gethostname(host_name, MAX_HOST_SIZE);
    getlogin_r(user_name, MAX_USER_SIZE);
    getcwd(base_dir, MAX_PATH_LENGTH);
    dir_ptr = opendir("/"); // open current directory;
    chdir("/");
    getcwd(dir_name, MAX_PATH_LENGTH);
    // setenv("PWD", "/",1);
    // dir_name_symlinks = getenv("PWD");
    // strcpy(dir_name_symlinks, dir_name);
}

void _close(){
    // for(int i=0;i<MAX_HISTORY_LENGTH;i++){
        // free(history_buffer[i]);
    // }
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
    if(result != 0) {printf("cd: no such directory\n"); return;}
    getcwd(dir_name, MAX_PATH_LENGTH);
    // dir_name_symlinks = getenv("PWD");
    // int slen = strlen(dir_name_symlinks);
    // if(dir_name_symlinks[slen - 1] != '/') {
    //     dir_name_symlinks[slen] = '/';
    //     dir_name_symlinks[slen+1] = '\0';
    // }
    // strcat(dir_name_symlinks, dir);
}

void _pwd(){
    // short GET_PHYSICAL_ADDRESS = 0;
    // for(int i=0;i<input_cnt;i++){
    //     if(strcmp(input_buffer[i], "-P") == 0) 
    //         GET_PHYSICAL_ADDRESS = 1;
    // }
    // if(GET_PHYSICAL_ADDRESS) printf("%s\n", dir_name);
    // else printf("%s\n", dir_name_symlinks);
    printf("%s\n", dir_name);
}

void _echo(char* str){

    short NO_NEW_LINE = 0;
    short PARSE_ESCAPE_CHARACTERS = 0;
    for(int i=0;i<input_cnt;i++){
        if(strcmp(input_buffer[i], "-n") == 0) NO_NEW_LINE = 1;
        if(strcmp(input_buffer[i], "-e") == 0) PARSE_ESCAPE_CHARACTERS = 1;
    }

    int len = strlen(str);
    if(str[0] == '\"' && str[len-1] == '\"'){
        str[len-1] = '\0';
        str++;
        len-=2;
    }
    else if(str[0] == '\'' && str[len-1] == '\''){
        str[len-1] = '\0';
        str++;
        len-=2;
    }
    if(PARSE_ESCAPE_CHARACTERS){
    // char sub_str[MAX_COMMAND_LENGTH];
    // printf("hhoho");
    char* sub_str = (char*)malloc(len*sizeof(char));
    // sub_str
    int ptr = 0;

    char equi[128];
    for(int i=0;i<128;i++) equi[i] = 0;
    equi[110] = '\n';
    equi[97] = '\a';
    equi[101] = '\e';
    equi[69] = '\E';
    equi[102] = '\f';
    equi[114] = '\r';
    equi[116] = '\t';
    equi[118] = '\v';
    equi[92] = '\\';
    
    for(int i=0;i<=len;i++){
        if(str[i] == '\\' && i!=len-1){
            // if(i!=len-1){
            // printf("%d,HIHI\n", i);
            if(str[i+1] == 'c') {sub_str[ptr++] = '\0'; break;}
            if(equi[str[i+1]] != 0) {sub_str[ptr++] = equi[str[i+1]];}
            else sub_str[ptr++] = str[i+1]; 
            i++;
            // }
        }
        else sub_str[ptr++] = str[i];
    }
    printf("%s", sub_str);
    if(!NO_NEW_LINE) printf("\n");
    free(sub_str);
    return;
    }
    printf("%s", str);
    if(!NO_NEW_LINE) printf("\n");
}

void _clear_history(){
    for(int i=0;i<MAX_HISTORY_LENGTH;i++)
        strcpy(history_buffer[i], "\0");
}

void _history(){

    short DELETE_AT_OFFSET = 0;
    int offset = -1;
    for(int i=0;i<input_cnt;i++){
        if(strcmp(input_buffer[i], "-c") == 0){
            _clear_history();
            return;
        }
        if(strcmp(input_buffer[i], "-d") == 0){
            DELETE_AT_OFFSET = 1;
            offset = 0;
            for(int j=0;input_buffer[i+1][j]!='\0';j++){
                offset = 10*offset + (input_buffer[i+1][j]-'0');
            }
        }
    }

    int nxt = (history_ptr+1)%MAX_HISTORY_LENGTH;
    int cnt = 1;
    for(int i=0;i<MAX_HISTORY_LENGTH;i++){
        if(strcmp(history_buffer[nxt], "\0") == 0);
        else{
        if(!DELETE_AT_OFFSET) printf("%d  %s\n", cnt, history_buffer[nxt]);
        if(DELETE_AT_OFFSET && cnt == offset) strcpy(history_buffer[nxt], "\0");
        cnt++;
        }
        
        nxt = (nxt+1)%MAX_HISTORY_LENGTH;
    }
}

void _exit_0(){
    _close();
    printf("closing...\n");
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
    printf("%s %s$ ", dir_name,  getenv("USER"));
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
            if(!isDirectory(input_buffer[input_cnt-1]))
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
    
    strcpy(history_buffer[history_ptr], ""); // can be optimized
    for(int i=0;i<input_cnt;i++){
        strcat(history_buffer[history_ptr], input_buffer[i]);
        strcat(history_buffer[history_ptr], " ");
    }
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
    
    _close(); // will never execute
    return 0;
}