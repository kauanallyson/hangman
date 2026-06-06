hangman: src/main.c src/utils.c
	gcc -Wall -Wextra -Wpedantic -ggdb -o bin/hangman src/main.c src/utils.c

clean:
	rm -f bin/hangman