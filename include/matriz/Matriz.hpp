#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <iostream>
#include "node/Node.hpp"

class Matriz
{
private:
    Node *cabecalho;
    int linhas;
    int colunas;

public:
    Matriz();

    // Construtor da Matriz
    // ****** INCOMPLETA ******
    Matriz(const int &ln, const int &cl);

    ~Matriz();

    // Função que irá inserir um valor em um local específico da lista
    // Deverá ser feita uma verificação dos valores
    // ****** INCOMPLETA *******
    void insert(const int &posI, const int &posJ, const double &value);

    // Devolve o valor na célula (i, j) da matriz, onde i ´e a linha e j ´e a coluna.
    // Essa função também faz uma verificação dos índices passados
    // ****** INCOMPLETA *******
    double get(const int &i, const int &j);

    // Esta função imprime a matriz A no terminal, inclusive os elementos iguais a zero.
    // ****** INCOMPLETA *******
    void print();
};

#endif