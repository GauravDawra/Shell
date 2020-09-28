#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

short MODIFIED_FILE = 0;
short UTC_TIME = 0;
int main(int argc, char* argv[])
{
    time_t t = time(NULL);
    struct tm TM;// = *localtime(&t);
//   printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    char* day[] = {
        "Sun", "Mon", "Tue", 
        "Wed", "Thu", "Fri", "Sat"
    };
    char* month[] = {
        "Jan", "Feb", "Mar", 
        "Apr", "May", "Jun", 
        "Jul", "Aug", "Sep",
        "Oct", "Nov", "Dec"
    };


    for(int i=0;i<argc;i++){
        if(strcmp(argv[i], "-r") == 0) MODIFIED_FILE = 1;
        if(strcmp(argv[i], "-u") == 0) UTC_TIME = 1;
    }

    char* TIME_TYPE = "IST";
    if(UTC_TIME) TIME_TYPE = "UTC";
    
    if(!MODIFIED_FILE){
        if(UTC_TIME) TM = *gmtime(&t);
        else TM = *localtime(&t);
        printf("%s %s %d %02d:%02d:%02d %s %d\n", day[TM.tm_wday], month[TM.tm_mon], TM.tm_mday, TM.tm_hour, TM.tm_min, TM.tm_sec, TIME_TYPE, 1900+TM.tm_year);
    }
    else{
        struct stat attrib;
        stat(argv[argc - 1], &attrib);
        if(UTC_TIME) TM = *gmtime(&(attrib.st_mtime));
        else TM = *localtime(&(attrib.st_mtime));
        printf("%s %s %d %02d:%02d:%02d %s %d\n", day[TM.tm_wday], month[TM.tm_mon], TM.tm_mday, TM.tm_hour, TM.tm_min, TM.tm_sec, TIME_TYPE, 1900+TM.tm_year);
    }

    return 0;
}