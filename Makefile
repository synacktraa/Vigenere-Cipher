BIN=gcc
FLAGS=-g -Wall

all: vigit

vigcipher.o: vigcipher.c
	$(BIN) $(FLAGS) -c $^

vigit: vigcipher.o
	$(BIN) $(FLAGS) $^ -o $@

clean:

ifeq ($(OS),Windows_NT)
	del *.o, vigit*
else
	rm *.o vigit*
endif