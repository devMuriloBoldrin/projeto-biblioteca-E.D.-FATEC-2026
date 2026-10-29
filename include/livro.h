#ifndef LIVRO_H
#define LIVRO_H

// Dados do TAD para livro
typedef struct {
    int id;
    char titulo[80];
    char autor[80];
    int ano;
} Livro;

int ler_texto(char *campo, int tam);
int ler_inteiro(int *num);

#endif