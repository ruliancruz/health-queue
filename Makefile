####### MAKEFILE #######

# Directories
BIN_PATH := ./bin
OBJ_PATH := ./obj
SRC_PATH := ./src

# Sources
MAIN_SRC         := $(SRC_PATH)/main.c
HEALTH_QUEUE_SRC := $(SRC_PATH)/libs/HealthQueue/HealthQueue.c

# Objects
MAIN_OBJ         := $(OBJ_PATH)/main.o
HEALTH_QUEUE_OBJ := $(OBJ_PATH)/HealthQueue.o

# Others
CC           := gcc
EXEC         := $(BIN_PATH)/main
OBJECTS      := $(OBJ_PATH)/*
BINARIES     := $(BIN_PATH)/*
PROJECT_NAME := HealthQueue

# To run: make [target] (all, main.o, HealthQueue.o, etc.). Ex.: make all

# Generates the executable file
all: main.o HealthQueue.o
	@$(CC) $(OBJECTS) -o $(EXEC)
	@echo "Done."
	
# Generates dependency (object file)
main.o: $(MAIN_SRC)
	@$(CC) -c $(MAIN_SRC) -o $(MAIN_OBJ)
	
HealthQueue.o: $(HEALTH_QUEUE_SRC)
	@$(CC) -c $(HEALTH_QUEUE_SRC) -o $(HEALTH_QUEUE_OBJ)
	
run:
	@$(EXEC)

# Generates a compiled and compressed archive of all project files
zip:
	@zip -rq9 $(PROJECT_NAME) *
	@echo "Done."

# Removes all binary and object files
clean:
	@rm -f $(OBJECTS)
	@rm -f $(BINARIES)
	@echo "Done."
