CC     = gcc
CFLAGS = -Wall -Wextra -Wpedantic

build/hangman: src/main.c build/utils.o | build
	$(CC) $(CFLAGS) -o $@ src/main.c build/utils.o

build/utils.o: src/utils.c src/utils.h | build
	$(CC) $(CFLAGS) -c -o $@ src/utils.c

build:
	mkdir -p build

clean:
	rm -rf build