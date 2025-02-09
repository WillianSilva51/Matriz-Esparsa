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

Matriz::Matriz(const Matriz &outra) : Matriz(outra.linhas, outra.colunas)
{
    for (IteratorM it = outra.begin(); it != outra.end(); ++it)
        this->insert(it.current->linha, it.current->coluna, *it);
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

Matriz Matriz::operator=(Matriz matriz)
{
    // Troca os dados do objeto atual com os dados de 'matriz'
    std::swap(cabecalho, matriz.cabecalho);
    std::swap(linhas, matriz.linhas);
    std::swap(colunas, matriz.colunas);
    // 'matriz' é destruída, liberando os recursos antigos
    return *this;
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
    if (cabecalho == nullptr)
        return;

    limpar();

    Node *linhaAtual = cabecalho->abaixo;
    while (linhaAtual != cabecalho)
    {
        Node *proximoLinha = linhaAtual->abaixo;
        delete linhaAtual;
        linhaAtual = proximoLinha;
    }

    Node *colunaAtual = cabecalho->direita;
    while (colunaAtual != cabecalho)
    {
        Node *proximoColuna = colunaAtual->direita;
        delete colunaAtual;
        colunaAtual = proximoColuna;
    }

    delete cabecalho;
    cabecalho = nullptr;
}

void Matriz::limpar()
{
    if (cabecalho == nullptr)
        return;

    Node *LinhaAtual = cabecalho->abaixo;
    if (LinhaAtual == cabecalho)
        return;

    Node *ColunaAtual = LinhaAtual;
    while (ColunaAtual->abaixo != cabecalho)
    {
        ColunaAtual = ColunaAtual->abaixo;
    }

    ColunaAtual->abaixo = nullptr;

    for (Node *linha = LinhaAtual; linha != nullptr; linha = linha->abaixo)
    {

        Node *atual = linha->direita;
        while (atual != linha)
        {
            Node *proximo = atual->direita;
            delete atual;
            atual = proximo;
        }
        linha->direita = linha;
    }

    ColunaAtual = LinhaAtual;
    while (ColunaAtual->abaixo != nullptr)
    {
        ColunaAtual = ColunaAtual->abaixo;
    }
    ColunaAtual->abaixo = cabecalho;
}

void Matriz::insert(const int &posI, const int &posJ, const double &value)
{
    if (value == 0)
        return;

    if (posI <= 0 || posI > linhas || posJ <= 0 || posJ > colunas)
        throw std::invalid_argument("Erro: Local de inserção inválido");

    Node *linhaAtual = cabecalho;
    while (linhaAtual->linha < posI)
    {
        linhaAtual = linhaAtual->abaixo;
    }

    Node *aux = linhaAtual;
    while (aux->direita != linhaAtual && aux->direita->coluna < posJ)
    {
        aux = aux->direita;
    }

    if (aux->direita->coluna == posJ)
    {
        aux->direita->atualizaValor(value);
        return;
    }

    Node *novo = new Node(posI, posJ, value);

    novo->direita = aux->direita;
    aux->direita = novo;

    Node *colunaAtual = cabecalho;
    while (colunaAtual->coluna < posJ)
    {
        colunaAtual = colunaAtual->direita;
    }

    aux = colunaAtual;
    while (aux->abaixo != colunaAtual && aux->abaixo->linha < posI)
    {
        aux = aux->abaixo;
    }

    novo->abaixo = aux->abaixo;
    aux->abaixo = novo;
}

double Matriz::get(const int &posI, const int &posJ)
{
    if (posI <= 0 || posI > linhas || posJ <= 0 || posJ > colunas)
        throw std::invalid_argument("Erro: Local de acesso inválido");

    IteratorM it = begin();

    // Avança enquanto o nó atual estiver "antes" da posição desejada.
    while (it != end() &&
           (it.current->linha < posI ||
            (it.current->linha == posI && it.current->coluna < posJ)))
    {
        ++it;
    }

    // Se o nó atual corresponde exatamente à posição, retorna o valor.
    if (it != end() && it.current->linha == posI && it.current->coluna == posJ)
        return *it;

    return 0;
}

double Matriz::get(const int &posI, const int &posJ) const
{
    if (posI <= 0 || posI > linhas || posJ <= 0 || posJ > colunas)
        throw std::invalid_argument("Erro: Local de acesso inválido");

    IteratorM it = begin();

    // Avança enquanto o nó atual estiver "antes" da posição desejada.
    while (it != end() &&
           (it.current->linha < posI ||
            (it.current->linha == posI && it.current->coluna < posJ)))
    {
        ++it;
    }

    // Se o nó atual corresponde exatamente à posição, retorna o valor.
    if (it != end() && it.current->linha == posI && it.current->coluna == posJ)
        return *it;

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