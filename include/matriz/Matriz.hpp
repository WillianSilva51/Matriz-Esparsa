#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include "node/Node.hpp"

class Matriz
{
private:
    Node *cabecalho;
    int linhas;
    int colunas;

public:
    Matriz(/* args */);
    ~Matriz();
};

#endif