CC            = gcc # compiler
LIB_FILE_SRC  = ./src/libs/HealthQueue/HealthQueue.c
MAIN_FILE_SRC = ./src/main.c
EXEC          = ./bin/main
OBJECTS       = ./obj/*
BINARIES      = ./bin/*

OBJECT1 = ./obj/HealthQueue.o

# ./bin: executables
# ./obj: .o files
# ./src: .c files

# run: make or make all
all: $(LIB_FILE_SRC) $(MAIN_FILE_SRC)
	$(CC) -c $(LIB_FILE_SRC) -o $(OBJECT1)
	$(CC) $(MAIN_FILE_SRC) $(OBJECTS) -o $(EXEC)

# run: make run
run: $(EXEC)
	$(EXEC)

# run: make clean
clean: $(OBJECTS) $(BINARIES)
	rm -f $(OBJECTS)
	rm -f $(BINARIES)
