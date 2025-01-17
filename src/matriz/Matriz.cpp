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
    cabecalho->direita = cabecalho;
    cabecalho->abaixo = cabecalho;

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

    while (linhaAtual != aux) {
        while (colunaAtual != linhaAtual) {
            Node *temp = colunaAtual;
            colunaAtual = colunaAtual->direita;
            delete temp;
        }   
        Node *temp = linhaAtual;
        linhaAtual = linhaAtual->abaixo;
        delete temp;
    }

}

Matriz &Matriz::operator=(const Matriz &matriz)
{
    // Evitar autoatribuição
    if (this == &matriz)
        return *this;

    // Limpar a matriz atual
    limpar(); // Supondo que exista um método para desalocar a matriz atual

    // Copiar as dimensões
    this->linhas = matriz.linhas;
    this->colunas = matriz.colunas;

    // Criar o cabeçalho
    cabecalho = new Node(0, 0, 0);
    cabecalho->direita = cabecalho;
    cabecalho->abaixo = cabecalho;

    // Criar os nós das linhas
    Node *auxLinha = cabecalho;
    for (int i = 1; i <= linhas; ++i)
    {
        Node *novo = new Node(i, 0, 0);
        auxLinha->abaixo = novo;
        novo->direita = novo;
        auxLinha = novo;
    }

    auxLinha->abaixo = cabecalho;

    // Criar os nós das colunas

    Node *auxColuna = cabecalho;
    for (int j = 1; j <= colunas; ++j)
    {
        Node *novo = new Node(0, j, 0);
        auxColuna->direita = novo;
        novo->abaixo = novo;
        auxColuna = novo;
    }

    auxColuna->direita = cabecalho;

    // Copiar os valores
    Node *linhaAtual = matriz.cabecalho->abaixo;
    Node *linhaDestino = cabecalho->abaixo;

    while (linhaAtual != matriz.cabecalho)
    {
        Node *noAtual = linhaAtual->direita;
        Node *noDestino = linhaDestino->direita;

        while (noAtual != linhaAtual)
        {
            Node *novo = new Node(noAtual->linha, noAtual->coluna, noAtual->valor);
            noDestino->direita = novo;
            novo->direita = novo;
            noDestino = novo;
            noAtual = noAtual->direita;
        }

        noDestino->direita = linhaDestino;
        linhaAtual = linhaAtual->abaixo;
        linhaDestino = linhaDestino->abaixo;
    }

    return *this;
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
        aux->direita->valor = value; // Atualiza o valor
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

    Node *auxLinha = cabecalho;

    while (auxLinha->linha < posI && auxLinha->abaixo != cabecalho)
    {
        auxLinha = auxLinha->abaixo;
    }

    Node *auxColuna = auxLinha;
    while (auxColuna->coluna < posJ && auxColuna->direita != auxLinha)
    {
        auxColuna = auxColuna->direita;

        if (auxColuna->coluna == posJ)
        {
            return auxColuna->valor;
        }
    }

    return 0;
}

void Matriz::print()
{
    Node *linhaAtual = cabecalho->abaixo;
    Node *noAtual = linhaAtual->direita;
    Node *aux = cabecalho->abaixo;
    for (int i = 1; i <= linhas; i++)
    {
        for (int j = 1; j <= colunas; j++)
        {

            if (noAtual->linha == i && noAtual->coluna == j && noAtual != aux)
            {
                std::cout << noAtual->valor;
                noAtual = noAtual->direita;
            }
            else
            {
                std::cout << "0";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
        linhaAtual = linhaAtual->abaixo;
        aux = aux->abaixo;
        noAtual = linhaAtual->direita;
    }
}