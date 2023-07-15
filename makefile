all:
	gcc -c ./src/libs/HealthQueue/HealthQueue.c -o ./obj/HealthQueue.o
	gcc ./src/main.c ./obj/* -o ./bin/main
run:
	./bin/main
clean:
	rm ./obj/*
	rm ./bin/*