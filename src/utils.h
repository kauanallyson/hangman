#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void clear_screen();
bool is_char_in(const char *word, char c);
void render_secret_word(const char *word, const char *guesses);
void print_used_letters(const char *guesses);
bool has_won(const char *word, const char *guesses);
bool get_random_word(const char* filename, char* output, size_t max_len);

#endif // UTILS_H