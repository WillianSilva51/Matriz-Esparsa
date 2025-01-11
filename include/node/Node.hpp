#ifndef NODE_HPP
#define NODE_HPP

struct Node
{
    Node *direita;
    Node *abaixo;
    int linha;
    int coluna;
    double valor;

    Node(const int &linha, const int &coluna, const double &valor = 0) : linha(linha), coluna(coluna), valor(valor)
    {
    }
};

#endif