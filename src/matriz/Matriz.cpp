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
    // Limpa apenas os nós de dados (não exclui os sentinelas)
    limpar();  

    if (!cabecalho) {
        std::cout << "Cabeçalho já é nulo. Nada para destruir." << std::endl;
        return;  // Prevenção de acesso inválido à memória
    }

    // Remover sentinelas das linhas
    std::cout << "Removendo sentinelas das linhas..." << std::endl;
    Node *linhaAtual = cabecalho->abaixo;
    while (linhaAtual != cabecalho)
    {   
        std::cout << "Nó da linha atual: " << linhaAtual << std::endl;
        Node *proximoLinha = linhaAtual->abaixo;
        if (linhaAtual != cabecalho) {
            std::cout << "Deletando linha sentinela: " << linhaAtual << std::endl;
            delete linhaAtual;
        }
        linhaAtual = proximoLinha;
    }

    // Remover sentinelas das colunas
    std::cout << "Removendo sentinelas das colunas..." << std::endl;
    Node *colunaAtual = cabecalho->direita;
    while (colunaAtual != cabecalho)
    {   
        std::cout << "Nó da coluna atual: " << colunaAtual << std::endl;
        Node *proximoColuna = colunaAtual->direita;
        if (colunaAtual != cabecalho) {
            std::cout << "Deletando coluna sentinela: " << colunaAtual << std::endl;
            delete colunaAtual;
        }
        colunaAtual = proximoColuna;
    }

    // Deletar o cabeçalho
    std::cout << "Deletando o cabeçalho: " << cabecalho << std::endl;
    delete cabecalho;
    cabecalho = nullptr;  // Prevenir acessos inválidos após a exclusão

    std::cout << "Destruição da matriz concluída!" << std::endl;
}


void Matriz::limpar()
{
    Node *linhaAtual = cabecalho->abaixo; // Começa na primeira linha (ignorando o cabeçalho)

    while (linhaAtual != cabecalho) // Enquanto não voltarmos ao cabeçalho
    {
        Node *colunaAtual = linhaAtual->direita;

        // Percorre a linha e remove os nós de dados (mas não o sentinela da linha)
        while (colunaAtual != linhaAtual) // Para quando encontrar o sentinela da linha
        {
            Node *temp = colunaAtual;
            colunaAtual = colunaAtual->direita;
            delete temp;
        }

        linhaAtual = linhaAtual->abaixo; // Move para a próxima linha
    }
}

Matriz::~Matriz()
{
    limpar(); // Remove apenas os nós de dados

    // Agora remover os sentinelas das linhas
    Node *linhaAtual = cabecalho->abaixo;
    while (linhaAtual != cabecalho)
    {
        Node *temp = linhaAtual;
        linhaAtual = linhaAtual->abaixo;
        delete temp; // Remove os sentinelas das linhas
    }

    // Agora remover os sentinelas das colunas
    Node *colunaAtual = cabecalho->direita;
    while (colunaAtual != cabecalho)
    {
        Node *temp = colunaAtual;
        colunaAtual = colunaAtual->direita;
        delete temp; // Remove os sentinelas das colunas
    }

    delete cabecalho; // Por fim, remove o cabeçalho
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

Matriz&Matriz::operator=(const Matriz& matriz){
    if (this == &matriz) return *this;

    limpar(); // Remove os nós de dados

    linhas = matriz.linhas;
    colunas = matriz.colunas;

    cabecalho = new Node(0, 0, 0);
    cabecalho->direita = cabecalho->abaixo = cabecalho;

    Node *auxLinha = cabecalho;
    for (int i = 1; i <= linhas; i++)
    {
        Node *novo = new Node(i, 0, 0);
        auxLinha->abaixo = novo;
        novo->direita = novo;
        auxLinha = novo;
    }
    auxLinha->abaixo = cabecalho;

    Node *auxColuna = cabecalho;
    for (int j = 1; j <= colunas; j++)
    {
        Node *novo = new Node(0, j, 0);
        auxColuna->direita = novo;
        novo->abaixo = novo;
        auxColuna = novo;
    }
    auxColuna->direita = cabecalho;
    
    IteratorM it = matriz.begin();
    while (it != matriz.end())
    {
        insert(it.current->linha, it.current->coluna, *it);
        ++it;
    }

    return *this;
}