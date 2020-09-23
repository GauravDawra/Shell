all: ./bin/ls ./bin/date

./bin/ls: ./src/ls.c
	gcc ./src/ls.c -o ./bin/ls

./bin/date: ./src/date.c
	gcc ./src/date.c -o ./bin/date