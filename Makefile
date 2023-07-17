####### MAKEFILE #######

# Directories
BIN_PATH := ./bin
OBJ_PATH := ./obj
SRC_PATH := ./src
INC_PATH := ./includes

# Sources
MAIN_SRC         := $(SRC_PATH)/Main.c
HEALTH_QUEUE_SRC := $(SRC_PATH)/HealthQueue.c

# Objects
MAIN_OBJ         := $(OBJ_PATH)/Main.o
HEALTH_QUEUE_OBJ := $(OBJ_PATH)/HealthQueue.o

# Others
CC           := gcc
EXEC         := $(BIN_PATH)/Main
OBJECTS      := $(OBJ_PATH)/*
BINARIES     := $(BIN_PATH)/*
PROJECT_NAME := HealthQueue

# To run: make [target] (all, main.o, HealthQueue.o, etc.). Ex.: make all

# Generates the executable file
all: Main.o HealthQueue.o
	@$(CC) $(OBJECTS) -o $(EXEC)
	@echo "Done."

# Generates dependency (object file)
Main.o: $(MAIN_SRC)
	@$(CC) -c $(MAIN_SRC) -o $(MAIN_OBJ)

HealthQueue.o: $(HEALTH_QUEUE_SRC)
	@$(CC) -c $(HEALTH_QUEUE_SRC) -o $(HEALTH_QUEUE_OBJ)

run:
	@$(EXEC)

# Generates a compiled and compressed archive of all project files
zip:
	@zip -rq9 ${PROJECT_NAME} bin src obj Makerfile README.md LICENSE
	@echo "Done."

# Removes all binary and object files
clean:
	@rm -f $(OBJECTS)
	@rm -f $(BINARIES)
	@echo "Done."
