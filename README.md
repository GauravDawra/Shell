# Documentation for my shell: 

## Introduction
This project implements a linux shell, with 10 commands. The project creates an executable image of the our shell. The shell can perform all the basic commands that are listed below. The shell also supports some of the command line arguments as shown below in the *commands* section. The shell prompts the user for the command input. The prompt message looks like this:
    `[current_working_directory] [user_name]$ `
    For example: "Projects gaurav$ "

## Setup of the project
To set up the project, follow the following commands.
1. Clone the project from this repository
2. Choose a suitable location for cloning the project and place this project there
3. Move to the directory you have cloned this project in. By this, I mean, move to the folder of the project using your shell.
4. Run the `make` command in your shell to compile the respective files.

You are done!!! This will setup the project for you. To run the shell program, take a look at the *startup shell* section below.

### The following are the commands that can be given to the shell with appropriate arguments and command line options. Note that the commands are divided into two categories:

- ***internal commands***: These type of commands are directly handled by the program of the shell. No new process is created to handle these commands
-  ***external commands***: These types of commands are handled by sepereate processes, that are in turn called by the child process. The parent process forks a child process (using the fork() function - the fork system call). This child process, in turn loads a pre-made executable to take over itself. Thus, the child process is completely replaced with this binary. These binaries can be found in the `./bin` folder in the workspace folder.


## Commands:
- ### `ls`: an external command
    Prints all the directories in the current working directory or any specific directory. If you call the `ls` command without any command line options, it will just display the files in the directory that are not hidden.

    Has the following command line options:
    1. `-a`: This flag is used to view the hidden files in the      directory specified.
    2. `-A`: This flag is used to view all the files in the directory specified(including the hidden files), except '.' and '..'.

- ### `cat [filename]`: an external command
    Outputs the contents of a file to the console. [filename] is the name of the file whose contents are to be viewed. Note that [filename] should either be a valid file in the present working directory, or it must be a valid absolute path. If none of these satisfied, the error message `no such file` is displayed. If the file cannot be opened due to some other reasons, the error `File could not be opened` is displayed.

    Has the following command line options:
    1. `-n [filename]`: This modifies the output so that the number of the respective line is also printed along with the lines of the file. The numbering starts from 1. Note that this flag numbers the blank lines as well(see `-b` option below).
    2. `-b [filename]`: This modifies the output so the non-blank lines in the file are numbered in the output. To number the blank lines as well, see `-n` option above.

- ### `date`: an external command
    Prints the date and time to the console. By default, the command outputs the date and time according to the Indian Standard Time (IST). To change the date and time to UTC, see options below. The format of the output is `[day] [month] [date] [hours]:[minutes]:[seconds] [time_type] [year]`.
    - `[hours]` are printed in 24 hour clock. 
    - `[time_type]` denotes the which standard time is followed, IST or UTC.
    - `[month]` is the first three letters of the current month.

    Has the following command line options:
    1. `-r [filename]`: This flag is used to determine the last modified date and time of the specified file. Note that that time type in this case will be IST by default.
    2. `-u`: This flag is used to view the date in Universal Time Coordinated (UTC). This can be used with the above `-r [filename]` flag.

- ### `rm [filename]`: an external command
    Removes the file if present in the current working directory. Note that the removal takes place only if the parameter passed is a file. To delete directories, see options below. You cannot delete `.` and `..` files. Trying to delete them will throw an error. If the file is not found in the directory, it will show "rm: the inputted parameter is a directory". 
    If it could not be deleted due to some other reasons, the console will prompt: "rm: The file/directory is not deleted". Note that this command can take only one argument at a time.

    Has the following command line options:
    1. `-d [file/directory name]`: This flag is used to allow removal of directories as well. You can pass either a directory or a file if you use this flag.
    2. `-i [filename]`: This flag asks for permission before deleting the specified file. Write `yes` if you want to proceed with deletion or `no` if you don't want to delete it.
    Note that these two flags can be used simultaneously as well. In that case, permission will be asked before deleting the specified directory.

- ### `mkdir [directoryname]`: an external command
    Makes a new directory in the directory specified. The [directoryname] is the name/path of the directory to be created. By default, this command creates only the last directory(folder) in the path provide. For eg: if we try `mkdir a/b/c`, the folder `a/b` should already exist relative to the current working directory. See options below to create the intermediate directories as well.

    Has the following command line options:
    1. `-p [directory_path]`: This flag is used to create the intermediate directories as well in the path provided, if they are not already created. It recursively creates the folders.
    2. `-v [directory_path]`: This flag is the verbose flag and is used to report the creation of each directory that was successfully created.
    Note that these two flags can be used simultaneously with each other.

- ### `echo [message]`: an internal command
    Outputs the input message to the console. The message can be enclosed within single quotes(''), or double quotes(""), if the message contain spaces or otherwise. Note that the quotes are not necessary if there is only one string in message without any spaces. The enclosing quotes are not printed to the console.

    Has the following command line options:
    1. `-n [message]`: This flag is used to omit the endline character '\n' after the message. Thus, no endline printed after the message if this flag is used.
    2. `-e [message]`: This flag is used to allow the usage of escape characters in the string. This flag again works with or without quotes. It allows a limited number of escape characters to be used. The allowed escape characters are:
        - `\n`: endline character
        - `\a`: alarm (bell)
        - `\e`: escape character
        - `\E`: escape character
        - `\f`: form feed
        - `\r`: carriage return
        - `\t`: horizontal tab
        - `\v`: vertical tab
        - `\\`: backslash

- ### `pwd`: an internal command
    This outputs the present working directory on the console. This outputs the absolute path of the directory our shell is currently pointing to - starting from the root('/'). 

    Has the following command line options:
    1. `-P`: This is the only option available with this command. This resolves all the system links references in the path of the current working directory. Thus, the output contains no system link references.

- ### `cd [dirname]`: an internal command
    This changes the current working directory, pointed by the shell to [dirname]. Note that the [dirname] should be a valid directory name. We can provide the relative path of the directory from the current working directory, or an absolute path.

    Has the following command line options:
    1. `-P`: This is the only option available with this command. This resolves all the system links references in the path provided in the argument. Thus, the directory pointed to by our shell, after this command is executed, is the hard link of the directory we provided in the argument.

- ### `exit`: an internal command
    This command just exits the shell.


## Project structure:
The workspace folder consists of the following directory structure:

When you find this project in the repository, the project structure will be somwthing like this:
``` bash
.
├── Makefile
├── README.md
├── bin
├── source.c
└── src
    ├── cat.c
    ├── date.c
    ├── ls.c
    ├── mkdir.c
    └── rm.c
```

After you follow the setup instructions at the beginning of this README, your structure will look something like this:

``` bash
.
├── Makefile
├── README.md
├── bin
│   ├── cat
│   ├── date
│   ├── ls
│   ├── mkdir
│   └── rm
├── source
├── source.c
└── src
    ├── cat.c
    ├── date.c
    ├── ls.c
    ├── mkdir.c
    └── rm.c
```

The *source* is the executable which contains our shell. This binary when executed presents you with a console to give commands to. After this follow the *startup shell* instructions below to start your shell.

## Startup shell:
As discussed above, following the setup instructions will make a *source* executable in the workspace folder. You can run this with the command in the following two ways. But before that, make sure that you are in the workspace directory. The two ways are:
- `./source`: pretty straight forward. This just executes the *source* exeutable file.
- `make run`: I have also configured the execution of the shell in my Makefile. You can directly run this command from the workspace folder to run the command.

Make sure you have setup the project before running these commands.
