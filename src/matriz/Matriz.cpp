#include "matriz/Matriz.hpp"
#include <iomanip>

Matriz::Matriz() : cabecalho(new Node(0, 0, 0)), linhas(0), colunas(0)
{
    cabecalho->direita = cabecalho->abaixo = cabecalho;
}

Matriz::Matriz(const int &lin, const int &col)

{
    if (lin <= 0 || col <= 0)
        throw std::invalid_argument("Erro: Tamanho de matriz inválido, insira valores maiores que 0");

    linhas = lin;
    colunas = col;

    cabecalho = new Node(0, 0, 0);
    cabecalho->direita = cabecalho->abaixo = cabecalho;

    Node *auxLinha = cabecalho;
    for (int i = 1; i <= lin; i++)
    {
        Node *novo = new Node(i, 0, 0);
        auxLinha->abaixo = novo;
        novo->direita = novo;
        auxLinha = novo;
    }
    auxLinha->abaixo = cabecalho;

    Node *auxColuna = cabecalho;
    for (int j = 1; j <= col; j++)
    {
        Node *novo = new Node(0, j, 0);
        auxColuna->direita = novo;
        novo->abaixo = novo;
        auxColuna = novo;
    }
    auxColuna->direita = cabecalho;
}

IteratorM Matriz::begin()
{
    return IteratorM(cabecalho->abaixo, cabecalho->abaixo->direita);
}

IteratorM Matriz::end()
{
    return IteratorM(cabecalho, cabecalho->direita);
}

IteratorM Matriz::begin() const
{
    return IteratorM(cabecalho->abaixo, cabecalho->abaixo->direita);
}

IteratorM Matriz::end() const
{
    return IteratorM(cabecalho, cabecalho->direita);
}

int Matriz::getLinhas() const
{
    return linhas;
}

int Matriz::getColunas() const
{
    return colunas;
}

Matriz::~Matriz()
{
    limpar();
}

void Matriz::limpar()
{
    Node *linhaAtual = cabecalho->abaixo;
    Node *colunaAtual = linhaAtual->direita;
    Node *aux = cabecalho->abaixo;

    while (linhaAtual != aux)
    {
        while (colunaAtual != linhaAtual)
        {
            Node *temp = colunaAtual;
            colunaAtual = colunaAtual->direita;
            delete temp;
        }
        Node *temp = linhaAtual;
        linhaAtual = linhaAtual->abaixo;
        delete temp;
    }
}

void Matriz::insert(const int &posI, const int &posJ, const double &value)
{
    // Não armazena valores iguais a zero
    if (value == 0)
        return;

    // Validação dos índices
    if (posI <= 0 || posI > linhas || posJ <= 0 || posJ > colunas)
        throw std::invalid_argument("Erro: Local de inserção inválido");

    // Busca na lista horizontal (linha)
    Node *linhaAtual = cabecalho;
    while (linhaAtual->linha < posI)
    {
        linhaAtual = linhaAtual->abaixo;
    }

    // Procura pela posição correta na linha
    Node *aux = linhaAtual;
    while (aux->direita != linhaAtual && aux->direita->coluna < posJ)
    {
        aux = aux->direita;
    }

    // Verifica se o nó já existe
    if (aux->direita->coluna == posJ)
    {
        aux->direita->atualizaValor(value); // Atualiza o valor
        return;
    }

    // Cria um novo nó
    Node *novo = new Node(posI, posJ, value);

    // Insere o nó na lista horizontal
    novo->direita = aux->direita;
    aux->direita = novo;

    // Busca na lista vertical (coluna)
    Node *colunaAtual = cabecalho;
    while (colunaAtual->coluna < posJ)
    {
        colunaAtual = colunaAtual->direita;
    }

    // Procura pela posição correta na coluna
    aux = colunaAtual;
    while (aux->abaixo != colunaAtual && aux->abaixo->linha < posI)
    {
        aux = aux->abaixo;
    }

    // Insere o nó na lista vertical
    novo->abaixo = aux->abaixo;
    aux->abaixo = novo;
}

double Matriz::get(const int &posI, const int &posJ)
{
    if (posI <= 0 || posI > linhas || posJ <= 0 || posJ > colunas)
        throw std::invalid_argument("Erro: Local de acesso inválido");

    IteratorM it = begin();

    while (it != end())
    {
        if (it.current->linha == posI && it.current->coluna == posJ)
            return *it;

        if (it.current->linha > posI || (it.current->linha == posI && it.current->coluna > posJ))
            return 0;

        ++it;
    }

    return 0;
}

double Matriz::get(const int &posI, const int &posJ) const
{
    if (posI <= 0 || posI > linhas || posJ <= 0 || posJ > colunas)
        throw std::invalid_argument("Erro: Local de acesso inválido");

    IteratorM it = begin();

    while (it != end())
    {
        if (it.current->linha == posI && it.current->coluna == posJ)
            return *it;

        if (it.current->linha > posI || (it.current->linha == posI && it.current->coluna > posJ))
            return 0;

        ++it;
    }

    return 0;
}

void Matriz::print()
{
    IteratorM it = begin();
    
    for (int i = 1; i <= linhas; i++)
    {
        for (int j = 1; j <= colunas; j++)
        {
            if (it.current->linha == i && it.current->coluna == j)
            {
                std::cout << std::fixed << std::setprecision(1) << *it;
                ++it;
            }
            else
            {
                std::cout << "0.0";
            }
            std::cout << " ";
            
        }
        std::cout << std::endl;
    }
}