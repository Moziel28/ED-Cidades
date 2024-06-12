#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) return NULL;

    Estrada *estrada = (Estrada *) malloc(sizeof(Estrada));
    if (!estrada) return NULL;

    fscanf(arquivo, "%d", &estrada->T);
    if (estrada->T < 3 || estrada->T > 1000000) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    fscanf(arquivo, "%d", &estrada->N);
    if (estrada->N < 2 || estrada->N > 10000) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    estrada->C = (Cidade *) malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        fscanf(arquivo, "%d %[^\n]", &estrada->C[i].Posicao, estrada->C[i].Nome);
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1.0;

    double menorVizinhanca = estrada->T;
    for (int i = 0; i < estrada->N; i++) {
        for (int j = i + 1; j < estrada->N; j++) {
            double distancia = (estrada->C[j].Posicao - estrada->C[i].Posicao) / 2.0;
            if (distancia < menorVizinhanca) {
                menorVizinhanca = distancia;
            }
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    if (menorVizinhanca == -1.0) return NULL;

    char *cidade = NULL;
    for (int i = 0; i < estrada->N; i++) {
        for (int j = i + 1; j < estrada->N; j++) {
            double distancia = (estrada->C[j].Posicao - estrada->C[i].Posicao) / 2.0;
            if (distancia == menorVizinhanca) {
                cidade = estrada->C[i].Nome;
                break;
            }
        }
        if (cidade) break;
    }

    free(estrada->C);
    free(estrada);
    return cidade;
}
