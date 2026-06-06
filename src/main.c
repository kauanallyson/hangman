#include "utils.h"

#define MAX_NUM_OF_ERRORS 10
#define MAX_WORD_LEN 10

int main(void) {
    char word[MAX_WORD_LEN];

    if (!get_random_word("words.txt", word, sizeof(word))){
        fprintf(stderr, "ERROR: Could not load words from 'words.txt'. Make sure the file exists and is not empty.\n");
        exit(1);
    }

    char guesses[27] = {0};           // 26 letras + 1 '\0'
    char line[256]; // buffer de entrada
    int error_count = 0;
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