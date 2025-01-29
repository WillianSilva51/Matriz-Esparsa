#include <iostream>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include "matriz/Matriz.hpp"
#include <cassert>
#include "utils/utils.hpp"

// Função de teste de inserção
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

// Função de teste de soma de matrizes
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

// Função de teste de multiplicação de matrizes
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

// Função para ler uma matriz de um arquivo
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

// Função para verificar se um arquivo existe
bool arquivoExiste(const std::string &caminho)
{
    std::ifstream file(caminho);
    return file.good();
}

// Função para medir a performance
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
