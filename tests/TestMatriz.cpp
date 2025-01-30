#include <iostream>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include "matriz/Matriz.hpp"
#include <cassert>
#include "utils/utils.hpp"

/*
 *   @brief Função de teste de inserção de valores na matriz.
 *
 *  Esta função cria uma matriz 5x5 e insere valores em posições específicas.
 *  Em seguida, a função verifica se os valores foram inseridos corretamente.
 * Se algum valor não for inserido corretamente, a função lança uma exceção.
 *
 *   @throw std::runtime_error Se algum valor não for inserido corretamente.
 */
void testeInsercao()
{
    Matriz matriz(5, 5);
    matriz.insert(1, 1, 1);
    assert(matriz.get(1, 1) == 1); // Garantir que o valor foi inserido corretamente
    matriz.insert(5, 5, 2);
    assert(matriz.get(5, 5) == 2); // Garantir que o valor foi inserido corretamente
    matriz.insert(3, 2, 2);
    assert(matriz.get(3, 2) == 2); // Garantir que o valor foi inserido corretamente
    std::cout << "Teste de inserção passou" << std::endl;
}

/*
 *    @brief Função de teste de soma de matrizes.
 *
 *   Esta função recebe duas matrizes A e B e a matriz resultante da soma dessas matrizes.
 *  A função calcula a soma das matrizes A e B e compara com a matriz resultante esperada.
 * Se a matriz resultante da soma for diferente da matriz esperada, a função lança uma exceção.
 *
 *   @param A Matriz A.
 *  @param B Matriz B.
 *
 *   @throw std::runtime_error Se a matriz resultante da soma for diferente da matriz esperada.
 */
void testeSoma(const Matriz &A, const Matriz &B, const Matriz &soma)
{

    Matriz D = sum(A, B);

    // Verificando as dimensões
    if (D.getColunas() != soma.getColunas() || D.getLinhas() != soma.getLinhas())
    {
        throw std::runtime_error("Erro: Dimensões incorretas na soma das matrizes.");
    }

    // Verificando cada valor da matriz resultante
    for (int i = 1; i <= soma.getLinhas(); i++)
    {
        for (int j = 1; j <= soma.getColunas(); j++)
        {
            if (D.get(i, j) != soma.get(i, j))
            {
                throw std::runtime_error("Erro na soma das matrizes: Valor incorreto na posição (" +
                                         std::to_string(i) + ", " + std::to_string(j) + "). Esperado: " +
                                         std::to_string(soma.get(i, j)) + ", Obtido: " + std::to_string(D.get(i, j)));
            }
        }
    }

    std::cout << "Teste de soma passou" << std::endl;
}

/*
 *    @brief Função de teste de multiplicação de matrizes.
 *
 *   Esta função recebe duas matrizes A e B e a matriz resultante da multiplicação dessas matrizes.
 *  A função calcula a multiplicação das matrizes A e B e compara com a matriz resultante esperada.
 * Se a matriz resultante da multiplicação for diferente da matriz esperada, a função lança uma exceção.
 *
 *   @param A Matriz A.
 *  @param B Matriz B.
 *
 *   @throw std::runtime_error Se a matriz resultante da multiplicação for diferente da matriz esperada.
 */
void testeMultiplicacao(const Matriz &A, const Matriz &B, const Matriz &soma)
{
    Matriz D = multiply(A, B);

    // Verificando as dimensões
    if (D.getColunas() != soma.getColunas() || D.getLinhas() != soma.getLinhas())
    {
        throw std::runtime_error("Erro: Dimensões incorretas na multiplicação das matrizes.");
    }

    // Verificando cada valor da matriz resultante
    for (int i = 1; i <= soma.getLinhas(); i++)
    {
        for (int j = 1; j <= soma.getColunas(); j++)
        {
            if (D.get(i, j) != soma.get(i, j))
            {
                throw std::runtime_error("Erro na multiplicação das matrizes: Valor incorreto na posição (" +
                                         std::to_string(i) + ", " + std::to_string(j) + "). Esperado: " +
                                         std::to_string(soma.get(i, j)) + ", Obtido: " + std::to_string(D.get(i, j)));
            }
        }
    }

    std::cout << "Teste de multiplicação passou" << std::endl;
}

/*
 * @brief Função para ler uma matriz de um arquivo.
 *
 * @param arquivo Nome do arquivo a ser lido.
 * @return Matriz Matriz lida do arquivo.
 */
Matriz leitura(const std::string &arquivo)
{
    std::ifstream file("tests/arquivosTestes/" + arquivo); // Abre o arquivo
    if (!file.is_open())
    {
        throw std::runtime_error("Erro ao abrir o arquivo: " + arquivo);
    }

    int linhas, colunas;
    file >> linhas >> colunas;

    Matriz matriz(linhas, colunas);

    int linha, coluna;
    double valor;
    while (file >> linha >> coluna >> valor)
    {                                        // Lê os valores da matriz
        matriz.insert(linha, coluna, valor); // Insere na matriz
    }

    file.close(); // Fecha o arquivo
    return matriz;
}

/*
 * @brief função para verificar se um arquivo existe
 *
 * @param caminho Caminho do arquivo a ser verificado.
 * @return bool Verdadeiro se o arquivo existir, falso caso contrário.
 */
bool arquivoExiste(const std::string &caminho)
{
    std::ifstream file(caminho);
    return file.good();
}

/**
 * @brief Testa a performance das operações de soma e multiplicação de matrizes.
 *
 * Esta função cria duas matrizes A e B de tamanho 100x100, preenche-as com valores específicos,
 * e então mede o tempo necessário para realizar a soma e a multiplicação dessas matrizes.
 *
 * A matriz A é preenchida com valores onde cada elemento é a soma dos índices de linha e coluna (i + j).
 * A matriz B é preenchida com valores onde cada elemento é a diferença dos índices de linha e coluna (i - j).
 *
 * A função utiliza a biblioteca <chrono> para medir o tempo de execução das operações de soma e multiplicação.
 *
 * @details
 * Passos executados pela função:
 * 1. Cria duas matrizes A e B de tamanho 100x100.
 * 2. Preenche as matrizes A e B com valores específicos.
 * 3. Exibe uma mensagem indicando que as matrizes foram preenchidas com sucesso.
 * 4. Mede o tempo necessário para somar as matrizes A e B.
 * 5. Exibe o tempo de execução da soma.
 * 6. Mede o tempo necessário para multiplicar as matrizes A e B.
 * 7. Exibe o tempo de execução da multiplicação.
 *
 * @return void
 */
void testePerformance()
{
    Matriz A(100, 100);
    Matriz B(100, 100);

    // Preenche as matrizes com valores
    for (int i = 1; i <= A.getLinhas(); ++i)
    {
        for (int j = 1; j <= A.getColunas(); ++j)
        {
            A.insert(i, j, i + j);
            B.insert(i, j, i - j);
        }
    }
    std::cout << "Matrizes preenchidas com sucesso" << std::endl;

    std::cout << "Iniciando teste de performance" << std::endl;

    auto inicio = std::chrono::high_resolution_clock::now();
    Matriz soma = sum(A, B); // Soma as matrizes
    auto fim = std::chrono::high_resolution_clock::now();

    auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);
    std::cout << "Tempo para Soma: " << duracao.count() << "ms" << std::endl;

    auto inicio2 = std::chrono::high_resolution_clock::now();
    Matriz multi = multiply(A, B); // Soma as matrizes
    auto fim2 = std::chrono::high_resolution_clock::now();

    auto duracao2 = std::chrono::duration_cast<std::chrono::milliseconds>(fim2 - inicio2);
    std::cout << "Tempo para Multiplição: " << duracao2.count() << "ms" << std::endl;
}

/**
 * @file TestMatriz.cpp
 * @brief Arquivo de teste para operações com matrizes esparsas.
 *
 * Este arquivo contém a função principal que realiza testes de operações com matrizes esparsas,
 * incluindo leitura de arquivos, soma, multiplicação, inserção e performance.
 */
int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    try
    {
        // Verificando se os arquivos existem
        if (!arquivoExiste("tests/arquivosTestes/Matrix1.txt"))
        {
            throw std::runtime_error("Arquivo Matrix1.txt não encontrado.");
        }
        if (!arquivoExiste("tests/arquivosTestes/Matrix2.txt"))
        {
            throw std::runtime_error("Arquivo Matrix2.txt não encontrado.");
        }
        if (!arquivoExiste("tests/arquivosTestes/MatrixResult.txt"))
        {
            throw std::runtime_error("Arquivo MatrixResult.txt não encontrado.");
        }

        // Lê as matrizes de arquivos
        Matriz A = leitura("Matrix1.txt");
        Matriz B = leitura("Matrix2.txt");
        Matriz soma = leitura("MatrixResult.txt");
        Matriz multi = leitura("MatrixMulti.txt");
        std::cout << "Matrizes lidas com sucesso" << std::endl;
        // Executa os testes
        testeSoma(A, B, soma);
        testeMultiplicacao(A, B, multi);
        testeInsercao();    // Teste básico de inserção
        testePerformance(); // Teste de performance para matrizes grandes
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Erro main: " << e.what() << std::endl;
    }

    return 0;
}
