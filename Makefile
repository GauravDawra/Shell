all: ./bin/ls ./bin/cat ./bin/date ./bin/rm ./bin/mkdir source

./bin/ls: ./src/ls.c
	gcc ./src/ls.c -o ./bin/ls

./bin/cat: ./src/cat.c
	gcc ./src/cat.c -o ./bin/cat

./bin/date: ./src/date.c
	gcc ./src/date.c -o ./bin/date

./bin/rm: ./src/rm.c
	gcc ./src/rm.c -o ./bin/rm

./bin/mkdir: ./src/mkdir.c
	gcc ./src/mkdir.c -o ./bin/mkdir

source: source.c
	gcc source.c -o source