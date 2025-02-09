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
    // Evita destruição múltipla
    if (cabecalho == nullptr)
        return;

    // Limpa os nós de dados (não mexe nos sentinelas)
    limpar();

    // Remover sentinelas das linhas
    Node *linhaAtual = cabecalho->abaixo;
    while (linhaAtual != cabecalho)
    {
        Node *proximoLinha = linhaAtual->abaixo;
        delete linhaAtual;
        linhaAtual = proximoLinha;
    }

    // Remover sentinelas das colunas
    Node *colunaAtual = cabecalho->direita;
    while (colunaAtual != cabecalho)
    {
        Node *proximoColuna = colunaAtual->direita;
        delete colunaAtual;
        colunaAtual = proximoColuna;
    }

    // Deletar o cabeçalho
    delete cabecalho;
    cabecalho = nullptr; // Evitar acessos inválidos após a exclusão
}

void Matriz::limpar()
{
    if (cabecalho == nullptr)
        return;

    // Obter o primeiro sentinela de linha.
    Node *LinhaAtual = cabecalho->abaixo;
    // Se não houver linhas (ou se o único nó for o cabeçalho), nada a fazer.
    if (LinhaAtual == cabecalho)
        return;

    // Quebrar a circularidade vertical: encontrar a última linha.
    Node *ColunaAtual = LinhaAtual;
    while (ColunaAtual->abaixo != cabecalho)
    {
        ColunaAtual = ColunaAtual->abaixo;
    }
    // Quebramos a circularidade: a última linha passa a apontar para nullptr.
    ColunaAtual->abaixo = nullptr;

    // Percorrer cada sentinela de linha (a cadeia agora é linear)
    for (Node *linha = LinhaAtual; linha != nullptr; linha = linha->abaixo)
    {

        // A lista horizontal de cada linha é circular, onde os nós de dados estão
        // entre 'linha->direita' e o próprio sentinela (linha).
        Node *cur = linha->direita;
        while (cur != linha)
        {
            Node *proximo = cur->direita; // Guarda o próximo nó antes de deletar
            delete cur;                   // Libera o nó de dado
            cur = proximo;
        }
        // Restaura o ponteiro horizontal do sentinela para ele mesmo.
        linha->direita = linha;
    }

    // Restaura a circularidade vertical: o último sentinela volta a apontar para o cabeçalho.
    ColunaAtual = LinhaAtual;
    while (ColunaAtual->abaixo != nullptr)
    {
        ColunaAtual = ColunaAtual->abaixo;
    }
    ColunaAtual->abaixo = cabecalho;
}

void Matriz::insert(const int &posI, const int &posJ, const double &value)
{
    // Não armazena valores iguais a zero
    if (value == 0)
        return;

    // Validação dos índices
    if (posI <= 0 || posI > linhas || posJ <= 0 || posJ > colunas)
        throw std::invalid_argument("Erro: Local de inserção inválido");

    // Busca na lista horizontal (linha)dede
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