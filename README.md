# Hangman (Jogo da Forca)

Implementação simplificada do clássico Jogo da Forca em linha de comando, escrita em C.

> Projeto da disciplina **Linguagem de Programação I** (Prof. Alex Martins) — *Projeto Hangman (v1)*.

## Sobre

O jogador precisa adivinhar uma palavra secreta. Ele sabe quantas letras ela tem
(mostradas como traços). A cada rodada o jogador escolhe uma letra:

- Se a letra está na palavra, todas as posições correspondentes são reveladas.
- Se não está, uma tentativa é consumida.

O jogo termina quando o jogador completa a palavra ou quando as
tentativas acabam. Em caso de derrota, a palavra secreta é revelada.

## Estrutura do projeto

```
.
├── Makefile        regras de build
├── words.txt       lista de palavras (uma por linha)
├── src/
│   ├── main.c      main
│   ├── utils.c     funções auxiliares
│   └── utils.h     declarações
└── bin/            saída da compilação
```

## Compilação

Requer `gcc` e `make`.

```sh
make
```

Compila com `-Wall -Wextra -Wpedantic -ggdb` gerando `bin/hangman`.

Limpa a build com:

```sh
make clean
```

## Execução

Execute a partir da raiz do projeto para que o `words.txt` seja encontrado:
```sh
./bin/hangman
```

## Como jogar

- Digite uma única letra e pressione Enter.
- Letras já escolhidas e entradas inválidas são rejeitadas sem consumir tentativa.
- Padrão: 10 tentativas, tamanho máximo da palavra 10.

## Lista de palavras

O `words.txt` contém uma palavra por linha. Edite-o para mudar o conjunto de
palavras secretas.
