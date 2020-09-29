INCL = include

BIN = ./bin
SRC = ./src
TARGET = ./source
C_FLAGS = -I$(INCL)
# BINARIES = $(addprefic)
DIRECTORY = $(sort $(dir $(wildcard $(BIN)/*)))

BINARIES=cat date ls mkdir rm
LIST_BINARIES=$(addprefix $(BIN)/, $(BINARIES))

# all: ./bin/ls ./bin/cat ./bin/date ./bin/rm ./bin/mkdir source
all: $(LIST_BINARIES) $(TARGET) $(DIRECTORY)
# ./bin/ls: ./src/ls.c
# 	gcc ./src/ls.c -o ./bin/ls

# ./bin/cat: ./src/cat.c
# 	gcc ./src/cat.c -o ./bin/cat

# ./bin/date: ./src/date.c
# 	gcc ./src/date.c -o ./bin/date

# ./bin/rm: ./src/rm.c
# 	gcc ./src/rm.c -o ./bin/rm

# ./bin/mkdir: ./src/mkdir.c
# 	gcc ./src/mkdir.c -o ./bin/mkdir

$(BIN)/% : $(SRC)/%.c
	gcc $< -o $@

$(TARGET): $(TARGET).c
	gcc $(C_FLAGS) $(TARGET).c -o $(TARGET)


run:
	$(TARGET)

clean:
	rm $(BIN)/* $(TARGET)