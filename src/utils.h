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
void render_hangman(int error_count);
void print_used_letters(const char *guesses);
bool has_won(const char *word, const char *guesses);
int get_amount_of_words(const char* filename);
bool get_random_word(const char* filename, char* output, size_t max_len, int word_count);

#endif // UTILS_H
