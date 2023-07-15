# variáveis
OUTPUT = main
BIN    = ./bin
OBJ    = ./obj
SRC    = ./src
LIBS   = $(SRC)/libs

all:
	gcc -c $(LIBS)/HealthQueue/HealthQueue.c -o $(OBJ)/HealthQueue.o
	gcc $(SRC)/main.c $(OBJ)/* -o $(BIN)/$(OUTPUT)
run:
	$(BIN)/$(OUTPUT)
clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/*