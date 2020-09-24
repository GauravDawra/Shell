all: ./bin/ls ./bin/date ./bin/rm

./bin/ls: ./src/ls.c
	gcc ./src/ls.c -o ./bin/ls

./bin/date: ./src/date.c
	gcc ./src/date.c -o ./bin/date

./bin/rm: ./src/rm.c
	gcc ./src/rm.c -o ./bin/rm