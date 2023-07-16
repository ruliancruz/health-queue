####### MAKEFILE #######

# directories
BIN_PATH = ./bin
OBJ_PATH = ./obj
SRC_PATH = ./src

# objects
OBJECT1 = $(OBJ_PATH)/HealthQueue.o
OBJECT2 = $(OBJ_PATH)/main.o

# others
CC            = gcc # compiler
LIB_FILE_SRC  = $(SRC_PATH)/libs/HealthQueue/HealthQueue.c
MAIN_FILE_SRC = $(SRC_PATH)/main.c
EXEC          = $(BIN_PATH)/main
OBJECTS       = $(OBJ_PATH)/*
BINARIES      = $(BIN_PATH)/*

# run: make or make all
all: $(LIB_FILE_SRC) $(MAIN_FILE_SRC)
	$(CC) -c $(LIB_FILE_SRC) -o $(OBJECT1)
	$(CC) -c $(MAIN_FILE_SRC) -o $(OBJECT2)
	$(CC) $(OBJECTS) -o $(EXEC)

# run: make run
run: $(EXEC)
	$(EXEC)

# run: make clean
clean: $(OBJECTS) $(BINARIES)
	rm -f $(OBJECTS)
	rm -f $(BINARIES)
