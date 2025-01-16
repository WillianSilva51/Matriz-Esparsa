#include "matriz/Matriz.hpp"

Matriz::Matriz() : linhas(0), colunas(0)
{
    cabecalho = new Node(0, 0, 0);
    cabecalho->direita = cabecalho;
    cabecalho->abaixo = cabecalho;
}

Matriz::Matriz(const int &lin, const int &col)
{
    if (lin <= 0 || col <= 0)
        throw std::invalid_argument("Erro: Tamanho de matriz inválido, insira valores maiores que 0");

    linhas = lin;
    colunas = col;

    cabecalho = new Node(0, 0, 0);

    Node *aux = cabecalho;

    for (int i = 1; i <= lin; i++)
    {
        aux->direita = new Node(i, 0, 0);
        aux = aux->direita;
    }
    aux->direita = cabecalho;

    aux = cabecalho;
    for (int j = 1; j <= col; j++)
    {
        aux->abaixo = new Node(0, j, 0);
        aux = aux->abaixo;
    }
    aux->abaixo = cabecalho;
}

Matriz::~Matriz()
{
}

void Matriz::insert(const int &posI, const int &posJ, const double &value)
{

    if (value == 0)
        return;

    if (posI <= 0 || posI >= linhas || posJ <= 0 || posJ >= colunas)
        throw std::invalid_argument("Erro: Local de inserção inválido");

    Node *aux = cabecalho;

    for (int i = 1; i <= posI; i++)
    {
        aux = aux->direita;
        if (aux->linha == posI)
        {
            for (int j = 1; j <= posJ; j++)
            {
                aux = aux->abaixo;
                if (aux->coluna == posJ)
                {
                    aux->atualizaValor(value);
                    return;
                }
            }
        }
    }

    aux = cabecalho;
    for (int i = 0; i <= posI; i++)
    {
        aux = aux->direita;
        if (aux->linha == posI)
        {
            for (int j = 0; j <= posJ; ++j)
            {
                if (aux->abaixo->coluna > posJ)
                {
                    Node *novo = new Node(posI, posJ, value);
                    novo->abaixo = aux->abaixo;
                    aux->abaixo = novo;
                    return;
                }
                aux = aux->abaixo;
            }
        }
    }
}

double Matriz::get(const int &posI, const int &posJ)
{
    if (posI <= 0 || posI >= linhas || posJ <= 0 || posJ >= colunas)
        throw std::invalid_argument("Erro: Local de acesso inválido");

    Node *aux = cabecalho;

    for (int i = 1; i <= posI; i++)
    {
        aux = aux->direita;
        if (i == posI)
        {
            for (int j = 1; j <= posJ; j++)
            {
                aux = aux->abaixo;
                if (j == posJ)
                    ;
                {
                    return aux->valor;
                }
            }
        }
    }
}

void Matriz::print()
{
}