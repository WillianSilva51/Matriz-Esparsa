#ifndef NODE_HPP
#define NODE_HPP

/**
 * @brief Representa um nó em uma matriz esparsa.
 *
 * Esta struct é usada para representar um nó em uma matriz esparsa, que contém
 * ponteiros para os nós à direita e abaixo, bem como a linha, coluna e valor
 * do elemento.
 */
struct Node
{
    Node *direita; /**< Ponteiro para o próximo nó na mesma linha. */
    Node *abaixo;  /**< Ponteiro para o próximo nó na mesma coluna. */
    int linha;     /**< Número da linha onde o nó está localizado. */
    int coluna;    /**< Número da coluna onde o nó está localizado. */
    double valor;  /**< Valor armazenado no nó. */

    /**
     * @brief Construtor da classe Node.
     *
     * Este construtor inicializa um objeto Node com os valores fornecidos para linha, coluna e valor.
     *
     * @param linha Referência constante para o número da linha.
     * @param coluna Referência constante para o número da coluna.
     * @param valor Referência constante para o valor armazenado no nó.
     */
    Node(const int &linha, const int &coluna, const double &valor) : linha(linha), coluna(coluna), valor(valor)
    {
        direita = nullptr;
        abaixo = nullptr;
    }

    /**
     * @brief Atualiza o valor do nó.
     *
     * Esta função atualiza o valor armazenado no nó com um novo valor fornecido.
     *
     * @param novoValor O novo valor que substituirá o valor atual do nó.
     */
    void atualizaValor(const double &novoValor)
    {
        valor = novoValor;
    }
};

#endif