#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUM_OF_ERRORS 5

void clear_screen() {
    printf("\033[1;1H\033[2J");
    fflush(stdout);
}

bool is_char_in(const char *word, char c) {
    const size_t len = strlen(word);
    for (size_t i = 0; i < len; ++i) {
        if (word[i] == c) {
            return true;
        }
    }
    return false;
}

void render_secret_word(const char *word, const char *guesses) {
    const size_t len = strlen(word);
    const size_t inner = 2 * len + 1; // largura interna da caixa

    // borda de cima
    printf("╭");
    for (size_t i = 0; i < inner; ++i)
        printf("─");
    printf("╮\n");

    // a palavra
    printf("│ ");
    for (size_t i = 0; i < len; ++i) {
        if (is_char_in(guesses, word[i])) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("│\n");

    // borda de baixo
    printf("╰");
    for (size_t i = 0; i < inner; ++i)
        printf("─");
    printf("╯\n");
}

bool has_won(const char *word, const char *guesses) {
    const size_t len = strlen(word);
    for (size_t i = 0; i < len; ++i) {
        if (!is_char_in(guesses, word[i])) {
            return false;
        }
    }
    return true;
}

int main(void) {
    const char *word = "programacao"; // TODO: sortear de forma aleatoria (Requisito 1)
    char guesses[27] = {0};           // 26 letras + 1 '\0'
    int error_count = 0;
    char line[256]; // buffer de entrada
    bool won = false;

    clear_screen();
    printf("Today's game is Hangman!\n");
    render_secret_word(word, guesses);
    printf("You have %d tries to guess the secret word.\n", MAX_NUM_OF_ERRORS);

    while (error_count < MAX_NUM_OF_ERRORS) {
        printf("Insert a letter: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            int error_code = 1;
            fprintf(stderr, "ERROR (%d): Could not read any inputs. Exiting...\n", error_code);
            exit(1); // se der erro sai do progarma
        }

        char c = line[0];
        if (isspace(c) || !isalpha(c)) {
            printf("Insert a valid letter.\n");
            continue; // linha inválida, tenta novamente
        }

        c = (char)tolower((unsigned char)c); // cast to lower

        if (is_char_in(guesses, c)) {
            printf("You have already guessed that, try again.\n");
            continue;
        }

        strncat(guesses, &c, 1); // registra a letra (certa ou errada)

        clear_screen();

        if (is_char_in(word, c)) {
            printf("Nice! The letter '%c' was in the word.\n", c);
        } else {
            printf("Ops! The letter '%c' was not in the word.\n", c);
            ++error_count;
        }

        render_secret_word(word, guesses);
        printf("Tries left: %d\n", MAX_NUM_OF_ERRORS - error_count);

        if (has_won(word, guesses)) {
            won = true;
            break;
        }
    }

    if (won) {
        printf("You Win!\n");
    } else {
        printf("You Lose!\n");
        printf("The word was: %s\n", word);
    }

    return 0;
}