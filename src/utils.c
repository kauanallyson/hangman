#include "utils.h"

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

void render_hangman(int error_count) {
    printf(
    "  ╭───╮\n"
    "  %c   │\n"
    " %c%c%c  │\n"
    " %c %c  │\n",
    error_count > 0 ? 'o' : ' ',
    error_count > 1 ? '/' : ' ',
    error_count > 1 ? '|' : ' ',
    error_count > 2 ? '\\' : ' ',
    error_count > 3 ? '/' : ' ',
    error_count > 4 ? '\\' : ' ');
}

void print_used_letters(const char *guesses) {
    const size_t len = strlen(guesses);
    printf("Letras usadas: ");
    for (size_t i = 0; i < len; ++i) {
        printf("%c ", guesses[i]);
    }
    printf("\n");
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

bool get_random_word(const char* filename, char* output, size_t max_len) {
    srand(time(NULL));
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return false;
    }
    char buffer[256];
    int word_count = 0;

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (!isspace(buffer[0]) || buffer[0] != '\0'){
            ++word_count;
        }
    }

    if (word_count == 0) {
        fclose(f);
        return false;
    }

    int target_line = rand() % word_count;

    rewind(f);
    int curr_line = 0;

    while(fgets(buffer, sizeof(buffer), f) !=  NULL) {
        if (!isspace(buffer[0]) || buffer[0] != '\0'){
            if (curr_line == target_line){
                buffer[strcspn(buffer, "\r\n")] = '\0';

                strncpy(output, buffer, max_len - 1);
                output[max_len - 1] = '\0';
                
                fclose(f);
                return true;
            }
            ++curr_line;
        }
    }
    
    fclose(f);
    return false;
}
