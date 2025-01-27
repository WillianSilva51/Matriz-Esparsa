#ifndef UTILS_HPP
#define UTILS_HPP

#include "matriz/Matriz.hpp"

/**
 * @brief Soma duas matrizes de mesmo tamanho.
 *
 * Esta função realiza a soma elemento a elemento das matrizes passadas por parâmetro,
 * retornando uma nova matriz com o resultado.
 *
 * @param matrixA Primeira matriz de entrada, cujas dimensões (linhas e colunas)
 *                devem ser iguais às de \p matrizB.
 * @param matrizB Segunda matriz de entrada, com dimensões compatíveis com \p matrixA,
 *                para que a soma seja realizada corretamente.
 *
 * @exception std::invalid_argument Exceção lançada caso as matrizes fornecidas não
 * possuam as mesmas dimensões, impossibilitando a operação de soma.
 *
 * @return Uma nova matriz que representa o resultado da soma elemento a elemento
 *         de \p matrixA e \p matrizB, mantendo as mesmas dimensões das matrizes de entrada.
 */
Matriz sum(const Matriz &matrixA, const Matriz &matrizB)
{
    if (matrixA.getLinhas() != matrizB.getLinhas() || matrixA.getColunas() != matrizB.getColunas())
        throw std::invalid_argument("Erro: As matrizes não possuem o mesmo tamanho");

    Matriz matriz(matrixA.getLinhas(), matrixA.getColunas());

    for (int i = 1, linha = matrixA.getLinhas(); i <= linha; i++)
    {
        for (int j = 1, coluna = matrixA.getColunas(); j <= coluna; j++)
        {
            double valor = matrixA.get(i, j) + matrizB.get(i, j);

            matriz.insert(i, j, valor);
        }
    }

    return matriz;
}

/**
 * @brief Multiplica duas matrizes e retorna a matriz resultante.
 *
 * Esta função realiza a multiplicação de duas matrizes, matrizA e matrizB, e retorna a matriz resultante.
 * A multiplicação de matrizes é possível apenas se o número de colunas de matrizA for igual ao número de linhas de matrizB.
 * Caso contrário, uma exceção std::invalid_argument será lançada.
 *
 * @param matrizA A primeira matriz a ser multiplicada.
 * @param matrizB A segunda matriz a ser multiplicada.
 * @return Matriz A matriz resultante da multiplicação de matrizA e matrizB.
 * @throws std::invalid_argument Se o número de colunas de matrizA for diferente do número de linhas de matrizB.
 *
 * @details
 * A multiplicação de matrizes é realizada da seguinte forma:
 * - Para cada linha i de matrizA e cada coluna j de matrizB, calcula-se o produto escalar entre a linha i de matrizA e a coluna j de matrizB.
 * - O valor resultante é inserido na posição (i, j) da matriz resultante.
 */
Matriz multiply(const Matriz &matrizA, const Matriz &matrizB)
{
    // Verificação se a multiplicação é possível
    if (matrizA.getColunas() != matrizB.getLinhas())
    {
        throw std::invalid_argument("Erro: As matrizes precisam ter o mesmo número de colunas e linhas");
    }

    // Criando a matriz resultante (C)
    Matriz matriz(matrizA.getLinhas(), matrizB.getColunas());

    // Percorrendo as linhas de matrizA e as colunas de matrizB
    for (int i = 1, linha = matrizA.getLinhas(); i <= linha; i++)
    {
        for (int j = 1, coluna = matrizB.getColunas(); j <= coluna; j++)
        {
            double valor = 0;

            // Calculando o produto escalar entre a linha i de A e a coluna j de B
            for (int k = 1; k <= matrizA.getColunas(); k++)
            {
                valor += matrizA.get(i, k) * matrizB.get(k, j);
            }

            matriz.insert(i, j, valor);
        }
    }

    return matriz; // Retorna a matriz resultante
}

#endif