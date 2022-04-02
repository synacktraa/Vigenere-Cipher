BIN=gcc
FLAGS=-g -Wall

all: vigit

vigenere_cipher.o: vigenere_cipher.c
	$(BIN) $(FLAGS) -c $^

vigit: vigenere_cipher.o
	$(BIN) $(FLAGS) $^ -o $@

clean:

ifeq ($(OS),Windows_NT)
	del *.o, vigit*
else
	rm *.o vigit*
endif