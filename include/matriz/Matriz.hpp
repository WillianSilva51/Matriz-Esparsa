#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <iostream>
#include "node/Node.hpp"
#include "IteratorM/IteratorM.hpp"

/**
 * @class Matriz
 * @brief Classe que representa uma matriz esparsa.
 *
 * A classe Matriz implementa uma estrutura de dados para armazenar matrizes esparsas,
 * onde a maioria dos elementos são zeros. Utiliza uma lista encadeada de nós para
 * armazenar apenas os elementos não-zero, economizando memória e permitindo operações
 * eficientes.
 *
 * @details
 * A matriz é representada por um nó-cabeçalho que atua como sentinela para a estrutura
 * interna. Este nó-cabeçalho aponta para si mesmo em ambas as direções (direita e abaixo)
 * quando a matriz está vazia. A classe fornece métodos para inserir, acessar e remover
 * elementos, além de obter o número de linhas e colunas e imprimir a matriz.
 *
 * @note
 * - A matriz é inicializada com um nó-cabeçalho que aponta para si mesmo.
 * - Os índices das linhas e colunas começam em 1.
 * - A inserção de elementos é feita apenas em posições válidas (dentro dos limites da matriz).
 *
 * @warning
 * - A tentativa de acessar ou inserir elementos em posições inválidas (fora dos limites da matriz)
 *   resultará em uma exceção std::invalid_argument.
 */
class Matriz
{
private:
    Node *cabecalho; /**< Nó-cabeçalho da matriz. */
    int linhas;      /**< Números de linhas. */
    int colunas;     /**< Números de colunas. */

public:
    /**
     * @brief Construtor padrão da classe Matriz.
     *
     * Este construtor inicializa os valores de linhas e colunas com zero
     * e cria o nó-cabeçalho. Este nó-cabeçalho atua como sentinela para
     * a estrutura interna da matriz, permitindo operações de inserção,
     * remoção e acesso eficientes. Inicialmente, o nó-cabeçalho aponta
     * para si mesmo em ambas as direções (direita e abaixo), indicando
     * que a matriz ainda não possui elementos de dados.
     */
    Matriz();

    /**
     * @brief Construtor da classe Matriz que inicializa uma matriz esparsa com linhas e colunas especificadas.
     *
     * Este construtor verifica primeiro se os valores passados para o número de linhas (lin) e colunas (col)
     * são maiores que zero. Caso contrário, é lançada uma exceção std::invalid_argument, garantindo que
     * somente matrizes com dimensões válidas sejam criadas.
     *
     * @details
     * Em seguida, são inicializadas:
     * - As variáveis internas para armazenar a quantidade de linhas e colunas.
     * - Um nó-cabeçalho que serve como referência principal da estrutura, mantendo laços para si mesmo
     *   tanto à direita quanto abaixo.
     * - Um conjunto de nós auxiliares, linkados entre si de maneira circular:
     *   - Nós responsáveis pelas linhas (um nó para cada linha),
     *   - Nós responsáveis pelas colunas (um nó para cada coluna).
     *
     * Cada nó de linha aponta para si mesmo à direita, enquanto cada nó de coluna aponta para si mesmo
     * abaixo, formando estruturas circulares independentes para linhas e colunas, todas centralizadas
     * no nó-cabeçalho.
     *
     * @param lin Quantidade de linhas da matriz (deve ser um valor maior que zero).
     * @param col Quantidade de colunas da matriz (deve ser um valor maior que zero).
     *
     * @throw std::invalid_argument Exceção lançada quando lin ou col são menores ou iguais a zero.
     */
    Matriz(const int &ln, const int &cl);

    /**
     * @brief Construtor de cópia para a classe Matriz.
     *
     * Este construtor cria uma nova instância de Matriz a partir de outra instância existente, realizando uma cópia profunda dos
     * elementos da matriz original. Inicialmente, ele chama o construtor principal da classe, passando como argumentos o número
     * de linhas e colunas da matriz a ser copiada, garantindo que a nova matriz possua a mesma estrutura de armazenamento.
     *
     * Após a alocação da estrutura adequada, o construtor itera por todos os elementos da matriz original ("outra") usando um
     * iterador (IteratorM). Para cada elemento encontrado, o método insert é invocado para inserir o valor na nova matriz,
     * mantendo a posição indicada pelos atributos "linha" e "coluna" presentes na estrutura apontada pelo iterador.
     *
     * @param outra Referência para a instância da matriz que será copiada.
     */
    Matriz(const Matriz &outra);

    /**
     * @brief Destrutor da classe Matriz.
     *
     * Este destrutor é responsável por desalocar toda a memória alocada pela matriz esparsa, incluindo os nós de dados e os nós sentinela.
     *
     * @details
     * A operação é realizada em várias etapas para evitar vazamento de memória e acessos inválidos:
     *
     *    - Verifica se o nó cabeçalho é nulo. Se for, a matriz está vazia e não há nada a ser desalocado
     *
     *    - Inicia a partir do primeiro nó sentinela abaixo do cabeçalho e, enquanto não retorna para o cabeçalho,
     *      desaloca cada nó.
     *
     *    - Inicia a partir do primeiro nó sentinela à direita do cabeçalho e, seguindo até retornar ao cabeçalho,
     *      desaloca cada nó.
     *
     *    - Após remover todos os nós sentinela nas linhas e colunas, o cabeçalho é removido.
     *
     *    - O ponteiro do cabeçalho é então definido como nullptr para evitar acessos inválidos posteriores.
     *
     * @note Este método garante que todos os nós foram corretamente liberados, evitando vazamentos de memória e a
     *       tentativa de desalocar a mesma memória mais de uma vez.
     */
    ~Matriz();

    /**
     * @brief Inicializa um iterador que aponta para o primeiro elemento significativo da matriz.
     *
     * Esta função permite obter um iterador para o primeiro nó principal da matriz esparsa
     * (localizado logo abaixo do cabeçalho), facilitando o acesso aos elementos e a
     * manipulação da estrutura de dados. O iterador retornado aponta para o primeiro
     * nó relevante da linha principal, permitindo assim percorrer as colunas de forma
     * apropriada.
     *
     * @return Retorna um objeto de iterador (IteratorM) posicionado no início da matriz esparsa.
     *
     * @note Esse método presume que a matriz está devidamente inicializada e que o cabeçalho
     *       aponta para posicionamentos válidos da estrutura.
     */
    IteratorM begin();

    /**
     * @brief Iterador que aponta para o final da matriz.
     *
     * Esta função provê um objeto IteratorM associado à lista principal
     * de nós da matriz esparsa, indicando uma posição que corresponde
     * ao final da estrutura de dados.
     *
     * @return IteratorM Objeto iterador apontando para o final da matriz.
     */
    IteratorM end();

    /**
     * @brief Iterador que aponta para o primeiro elemento significativo da matriz (versão const).
     *
     * Esta função é uma sobrecarga da função begin() que permite obter um iterador
     * para o primeiro nó principal da matriz esparsa, sem permitir alterações nos
     * valores da matriz. O iterador retornado aponta para o primeiro nó relevante
     *
     * @return IteratorM Objeto iterador apontando para o início da matriz.
     *
     */
    IteratorM begin() const;

    /**
     * @brief Iterador que aponta para o final da matriz (versão const).
     *
     * Esta função é uma sobrecarga da função end() que permite obter um iterador
     * para o final da matriz esparsa, sem permitir alterações nos valores da matriz.
     * O iterador retornado aponta para o final da estrutura de dados.
     *
     * @return IteratorM Objeto iterador apontando para o final da matriz.
     */
    IteratorM end() const;

    /**
     * @brief Sobrecarga do operador de atribuição para a classe Matriz.
     *
     * Esta função utiliza a técnica de cópia e troca (copy-and-swap) para implementar o operador de atribuição de forma segura e eficiente.
     * Ao receber o objeto 'matriz' por valor, ele garante que todos os recursos sejam copiados e que, em seguida, uma troca
     * (std::swap) seja realizada entre os atributos do objeto atual e os do objeto recebido. Assim, os dados antigos do objeto
     * atual serão automaticamente liberados quando o objeto 'matriz' passado por valor for destruído, proporcionando uma forte
     * garantia de exceção.
     *
     * @param matriz Objeto do tipo Matriz que contém os novos dados a serem atribuídos. Por ser passado por valor, uma cópia
     * dos dados é criada, permitindo que a operação de troca seja efetuada sem riscos de perda de recursos em caso de erros.
     *
     * @return Retorna o próprio objeto (*this) já contendo os dados do objeto 'matriz'. O retorno por valor, nesse contexto,
     * assegura que o objeto resultante possui os recursos de forma consistente.
     *
     * @details
     * - std::swap: São trocados os atributos 'cabecalho', 'linhas' e 'colunas' entre o objeto atual e o objeto recebido,
     *   o que permite que o estado do objeto atual seja atualizado com o novo conteúdo.
     * - Ao final da função, o objeto local 'matriz' é destruído, liberando os recursos que anteriormente pertenciam ao objeto
     *   atual, evitando assim possíveis vazamentos de memória.
     */
    Matriz operator=(Matriz matriz);

    /**
     * @brief Retorna a quantidade de linhas da matriz.
     *
     * @return Número de linhas da matriz.
     *
     * Esta função permite consultar o total de linhas para verificação
     * de limites ou para iterações relacionadas ao tamanho da matriz.
     */
    int getLinhas() const;

    /**
     * @brief Retorna a quantidade de colunas da matriz.
     *
     * @return Número de colunas da matriz.
     *
     * Semelhante a getLinhas(), utilizada para consultar o total de
     * colunas da estrutura.
     */
    int getColunas() const;

    /**
     * @brief Limpa os dados armazenados na matriz esparsa.
     *
     * Esta função remove todos os nós de dados presentes na matriz esparsa, liberando a memória alocada para estes nós.
     *
     * @details
     * Procedimento:
     * 1. Verifica se o nó cabeçalho da matriz é nulo. Se for, a função retorna imediatamente,
     *    pois não há estrutura alocada para ser limpa.
     * 2. Obtém o primeiro sentinela de linha a partir do cabeçalho (cabecalho->abaixo). Caso esse
     *    sentinela seja o próprio cabeçalho, a matriz está vazia, e a função retorna sem realizar nenhuma ação.
     * 3. Quebra a circularidade vertical:
     *    - Percorre a lista de sentinelas de linha até encontrar a última linha (um nó cujo ponteiro "abaixo" aponta para o cabeçalho).
     *    - Ajusta o ponteiro "abaixo" do último nó para nullptr, transformando a lista circular em uma lista linear,
     *      o que facilita a iteração e remoção dos nós.
     * 4. Para cada linha (sentinela) na lista linear:
     *    - Percorre a lista horizontal de nós de dados. Essa lista é circular, com os dados localizados entre
     *      o ponteiro "direita" do sentinela e o próprio sentinela.
     *    - Exclui cada nó de dado da linha, armazenando o nó seguinte antes de chamar delete, de forma a não perder a referência.
     *    - Após excluir os nós de dados, restaura o ponteiro "direita" do sentinela para que ele aponte para ele mesmo.
     * 5. Restaura a circularidade vertical:
     *    - Após a limpeza, percorre novamente a lista linear de linhas até o último nó.
     *    - Reconfigura o ponteiro "abaixo" do último nó para apontar novamente ao cabeçalho da matriz.
     *
     * @note
     * - A função somente remove os nós de dados e restaura os ponteiros dos sentinelas, mantendo o nó cabeçalho intacto.
     * - A estrutura original da matriz esparsa é preservada, permitindo que a mesma seja reutilizada posteriormente.
     */
    void limpar();

    /**
     * @brief Insere um valor em uma posição específica da matriz esparsa.
     *
     * Esta função permite inserir uma nova célula com valor diferente de zero
     * em uma matriz esparsa, levando em conta sua organização em listas
     * duplamente encadeadas na horizontal e vertical. Qualquer valor igual a zero
     * é ignorado, pois não se armazena valores nulos na estrutura. Caso a posição
     * informada não seja válida, uma exceção de argumento inválido é lançada.
     *
     * @param posI Índice da linha na qual a célula será inserida.
     *             Deve ser um valor positivo e menor ou igual ao número total
     *             de linhas da matriz.
     * @param posJ Índice da coluna na qual a célula será inserida.
     *             Deve ser um valor positivo e menor ou igual ao número total
     *             de colunas da matriz.
     * @param value Valor a ser armazenado na nova célula. Valores iguais a zero
     *              não são inseridos na matriz.
     *
     * @throws std::invalid_argument Lançada quando (posI, posJ) excede os
     *                               limites de linhas ou colunas definidos
     *                               para a matriz.
     *
     * @details
     * A função percorre primeiro a lista horizontal (linha) correspondente
     * para localizar a posição adequada. Caso já exista um nó na mesma coluna,
     * o valor é atualizado. Se não existir, cria-se um novo nó para armazenar
     * o valor na posição indicada. Após isso, a função também atualiza a
     * referência vertical (coluna), posicionando o novo nó de forma adequada
     * na estrutura de dados.
     */
    void insert(const int &posI, const int &posJ, const double &value);

    /**
     * @brief Retorna o valor armazenado na matriz em uma posição específica.
     *
     * @details
     * Esta função busca o valor localizado na linha e coluna indicadas
     * por @p posI e @p posJ. Se não houver nenhum valor armazenado nessa
     * posição (ou seja, se o nó correspondente não existir), a função
     * retornará 0. Caso a posição seja inválida, será lançada uma
     * exceção do tipo std::invalid_argument.
     *
     * @param posI Índice da linha solicitada.
     * @param posJ Índice da coluna solicitada.
     * @return O valor do tipo double encontrado na posição indicada, ou 0
     *         caso não exista nenhum valor armazenado.
     *
     * @exception std::invalid_argument Se @p posI ou @p posJ forem menores
     *            ou iguais a 0 ou excederem as dimensões da matriz.
     */
    double get(const int &posI, const int &posJ);

    /**
     * @brief Retorna o valor armazenado na matriz em uma posição específica (versão const).
     *
     * Mesma funcionalidade da versão não-const, mas permite consultar
     * valores em matrizes constantes, sem modificá-las.
     *
     * @details
     * Esta função é uma sobrecarga da função get() que permite consultar valores
     * em matrizes constantes, sem alterar seu conteúdo. A diferença é que esta
     * versão não permite alterar o conteúdo da matriz, garantindo a integridade
     * dos dados.
     *
     * @param posI Índice da linha solicitada.
     * @param posJ Índice da coluna solicitada.
     * @return O valor do tipo double encontrado na posição indicada, ou 0
     *
     * @exception std::invalid_argument Se @p posI ou @p posJ forem menores
     *           ou iguais a 0 ou excederem as dimensões da matriz.
     */
    double get(const int &posI, const int &posJ) const;

    /**
     * @brief Imprime a matriz no console.
     *
     * Exibe todas as linhas e colunas da matriz, mostrando os valores
     * armazenados. Para posições onde não há valor armazenado (na forma
     * esparsa), é imprimido o número 0.
     */
    void print();
};

#endif