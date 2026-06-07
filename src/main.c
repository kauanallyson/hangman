#include "utils.h"

#define MAX_NUM_OF_ERRORS 5
#define MAX_WORD_LEN 10

int main(void) {
    char word[MAX_WORD_LEN];

    if (!get_random_word("words.txt", word, sizeof(word))){
        fprintf(stderr, "ERRO: Nao foi possivel carregar palavras de 'words.txt'. Verifique se o arquivo existe e nao esta vazio.\n");
        exit(1);
    }

    char guesses[27] = {0};           // 26 letras + 1 '\0'
    char line[256]; // buffer de entrada
    int error_count = 0;
    bool won = false;

    clear_screen();
    printf("Jogo da Forca! (Hangman)\n");
    render_secret_word(word, guesses);
    printf("Voce tem %d tentativas para adivinhar a palavra secreta.\n", MAX_NUM_OF_ERRORS);

    while (error_count < MAX_NUM_OF_ERRORS) {
        printf("Digite uma letra: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            int error_code = 1;
            fprintf(stderr, "ERRO (%d): Nao foi possivel ler a entrada. Saindo...\n", error_code);
            exit(1); // se der erro sai do progarma
        }

        char c = line[0];
        if (isspace(c) || !isalpha(c)) {
            printf("Digite uma letra valida.\n");
            continue; // linha inválida, tenta novamente
        }

        c = (char)tolower((unsigned char)c); // cast to lower

        if (is_char_in(guesses, c)) {
            printf("Voce ja tentou essa letra, tente outra.\n");
            continue;
        }

        strncat(guesses, &c, 1); // registra a letra (certa ou errada)

        clear_screen();

        if (is_char_in(word, c)) {
            printf("Boa! A letra '%c' esta na palavra.\n", c);
        } else {
            printf("Ops! A letra '%c' nao esta na palavra.\n", c);
            ++error_count;
        }

        render_secret_word(word, guesses);
        print_used_letters(guesses);
        printf("Tentativas restantes: %d\n", MAX_NUM_OF_ERRORS - error_count);

        if (has_won(word, guesses)) {
            won = true;
            break;
        }
    }

    if (won) {
        printf("Voce Venceu!\n");
    } else {
        printf("Voce Perdeu!\n");
        printf("A palavra era: %s\n", word);
    }

    return 0;
}
