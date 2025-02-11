#ifndef ITERATORM_HPP
#define ITERATORM_HPP

#include "matriz/Matriz.hpp"

class Matriz;

/**
 * @class IteratorM
 * @brief Iterador para percorrer uma matriz esparsa.
 *
 * A classe IteratorM fornece um iterador para percorrer os elementos de uma matriz esparsa.
 *
 * @friend class Matriz
 */
class IteratorM
{
    friend class Matriz;

private:
    Node *cabecalho; /**< Ponteiro para o nó de cabeçalho. */
    Node *current;   /**< Ponteiro para o nó atual. */

public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = double;
    using pointer = double *;
    using reference = double &;

    /**
     * @brief Construtor padrão.
     *
     * Inicializa o iterador com ponteiros nulos.
     */
    IteratorM() : cabecalho(nullptr), current(nullptr) {}

    /**
     * @brief Construtor com parâmetros.
     *
     * Inicializa o iterador com o nó de cabeçalho e o nó atual.
     *
     * @param cabecalho Ponteiro para o nó de cabeçalho.
     * @param current Ponteiro para o nó atual (padrão é nullptr).
     */
    IteratorM(Node *cabecalho, Node *current) : cabecalho(cabecalho), current(current)
    {
        while (current == cabecalho)
        {
            cabecalho = cabecalho->abaixo;
            current = current->abaixo->direita;
        }
    }

    /**
     * @brief Operador de desreferenciação.
     *
     * Retorna uma referência ao valor do nó atual.
     *
     * @return Referência ao valor do nó atual.
     */
    reference operator*()
    {
        return current->valor;
    }

    /**
     * @brief Operador de desreferenciação (const).
     *
     * Retorna uma referência constante ao valor do nó atual.
     *
     * @return Referência constante ao valor do nó atual.
     */
    reference operator*() const
    {
        return current->valor;
    }

    /**
     * @brief Operador de acesso a membro (const).
     *
     * Retorna um ponteiro constante para o valor do nó atual.
     *
     * @return Ponteiro constante para o valor do nó atual.
     */
    pointer operator->()
    {
        return &current->valor;
    }

    /**
     * @brief Operador de acesso a membro (const).
     *
     * Retorna um ponteiro constante para o valor do nó atual.
     *
     * @return Ponteiro constante para o valor do nó atual.
     */
    pointer operator->() const
    {
        return &current->valor;
    }

    /**
     * @brief Operador de incremento prefixado.
     *
     * Avança o iterador para o próximo elemento na matriz esparsa.
     *
     * @return Referência ao próprio iterador após o incremento.
     */
    IteratorM &operator++()
    {
        current = current->direita;

        while (current == cabecalho)
        {
            cabecalho = cabecalho->abaixo;
            current = current->abaixo->direita;
        }

        return *this;
    }

    /**
     * @brief Operador de igualdade.
     *
     * Compara se dois iteradores são iguais.
     *
     * @param it Iterador a ser comparado.
     * @return true se os iteradores são iguais, false caso contrário.
     */
    bool operator==(const IteratorM &it) const
    {
        return cabecalho == it.cabecalho && current == it.current;
    }

    /**
     * @brief Operador de desigualdade.
     *
     * Compara se dois iteradores são diferentes.
     *
     * @param it Iterador a ser comparado.
     * @return true se os iteradores são diferentes, false caso contrário.
     */
    bool operator!=(const IteratorM &it) const
    {
        return cabecalho != it.cabecalho || current != it.current;
    }
};

#endif