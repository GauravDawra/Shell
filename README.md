# IMPLEMENTING A SHELL WITH 10 COMMANDS 

# Commands:
- # `ls`: an external command
    Prints all the directories in the current working directory or any specific directory. If you call the `ls` command without any command line options, it will just display the files in the directory that are not hidden.

    Has the following command line options:
    1. `-a`: This flag is used to view the hidden files in the      directory specified.
    2. `-A`: This flag is used to view all the files in the directory specified(including the hidden files), except '.' and '..'.

- # `cat [filename]`: an external command
    Outputs the contents of a file to the console. [filename] is the name of the file whose contents are to be viewed. Note that [filename] should either be a valid file in the present working directory, or it must be a valid absolute path. If none of these satisfied, the error message `no such file` is displayed. If the file cannot be opened due to some other reasons, the error `File could not be opened` is displayed.

    Has the following command line options:
    1. `-n [filename]`: This modifies the output so that the number of the respective line is also printed along with the lines of the file. The numbering starts from 1. Note that this flag numbers the blank lines as well(see `-e` option below).
    2. `-e [filename]`: This modifies the output so the non-blank lines in the file are numbered in the output. To number the blank lines as well, see `-n` option above.

- # `date`: an external command
    Prints the date and time to the console. By default, the command outputs the date and time according to the Indian Standard Time (IST). To change the date and time to UTC, see options below. The format of the output is `[day] [month] [date] [hours]:[minutes]:[seconds] [time_type] [year]`.
    - `[hours]` are printed in 24 hour clock. 
    - `[time_type]` denotes the which standard time is followed, IST or UTC.
    - `[month]` is the first three letters of the current month.

    Has the following command line options:
    1. `-r [filename]`: This flag is used to determine the last modified date and time of the specified file. Note that that time type in this case will be IST by default.
    2. `-u`: This flag is used to view the date in Universal Time Coordinated (UTC). This can be used with the above `-r [filename]` flag.

- # `rm [filename]`: an external command
    Removes the file if present in the current working directory. Note that the removal takes place only if the parameter passed is a file. To delete directories, see options below. You cannot delete `.` and `..` files. Trying to delete them will throw an error. If the file is not found in the directory, it will show "rm: the inputted parameter is a directory". 
    If it could not be deleted due to some other reasons, the console will prompt: "rm: The file/directory is not deleted". Note that this command can take only one argument at a time.

    Has the following options:
    1. `-d [file/directory name]`: This flag is used to allow removal of directories as well. You can pass either a directory or a file if you use this flag.
    2. `-i [filename]`: This flag asks for permission before deleting the specified file. Write `yes` if you want to proceed with deletion or `no` if you don't want to delete it.

- # `mkdir [directoryname]`: an external command
    Makes a new directory in the directory specified. The [directoryname] is the name of the directory to be created.
