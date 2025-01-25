/**
 *  @authors
 * - Antonio Willian Silva Oliveira - 567294 (
 * - Iago de Oliveira Lo - 565321 (
 */

#include <fstream>
#include <unordered_map>
#include "matriz/Matriz.hpp"

using string = std::string;
using unordered_map = std::unordered_map<string, Matriz>;

enum Opcoes // Enumeração para as opções do menu
{
    LER_MATRIZ = 1,
    IMPRIMIR_MATRIZ,
    SOMAR_MATRIZES,
    MULTIPLICAR_MATRIZES,
    SAIR
};

/**
 * @brief Lê dados de um arquivo e insere em uma matriz esparsa.
 *
 * Esta função abre um arquivo contendo o número de linhas e colunas de uma
 * matriz, seguido por múltiplas linhas que descrevem itens não nulos da matriz.
 * Cada linha deve conter índices (i, j) e o valor correspondente.
 *
 * @param matriz Referência para o objeto Matriz que será inicializado e populado.
 * @param filename Nome do arquivo a ser lido (sem o caminho completo).
 *
 * @throws std::runtime_error Quando não é possível acessar ou abrir o arquivo.
 *
 * @details
 * - O arquivo é aberto a partir do diretório "src/arquivos/" concatenado ao
 *   nome do arquivo passado em \p filename.
 * - Os primeiros valores lidos do arquivo correspondem ao número de linhas
 *   (\p linhas) e de colunas (\p colunas) para inicializar corretamente a matriz.
 * - Em seguida, cada conjunto de três valores (índice de linha, índice de
 *   coluna e valor) é lido e inserido na matriz usando \c matriz.insert().
 * - Caso o arquivo não seja encontrado ou ocorra algum outro problema,
 *   é gerada uma exceção do tipo \c std::runtime_error.
 */
void readMatrix(Matriz &matriz, const std::string filename);

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
Matriz sum(const Matriz &matrixA, const Matriz &matrizB);

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
Matriz multiply(const Matriz &matrizA, const Matriz &matrizB);

/**
 * @brief Verifica se existe uma matriz previamente armazenada em um \c unordered_map.
 *
 * Esta função realiza uma busca no \c unordered_map pelo nome do arquivo (\p filename)
 * para determinar se já existe uma matriz associada a ele.
 *
 * @param filename O nome do arquivo cujo registro de matriz deve ser verificado.
 * @param matrizes O \c unordered_map que mantém o mapeamento entre nomes de arquivos e matrizes.
 * @return Retorna \c true se existir a matriz correspondente ao nome do arquivo; caso contrário, \c false.
 *
 * @note O uso do \c unordered_map permite que a busca ocorra de maneira eficiente,
 * pois a busca possui complexidade média O(1).
 */
bool existeMatriz(const std::string filename, const unordered_map &matrizes);

/**
 * @brief Salva uma matriz em um mapa associativo de matrizes, permitindo que seja recuperada posteriormente.
 *
 * @details
 * A função solicita ao usuário se deseja salvar a matriz atual. Caso a resposta seja afirmativa,
 * é solicitado um nome para identificar a nova matriz no mapa. Se esse nome já existir, o usuário
 * é informado para tentar novamente com outro nome. Em caso de sucesso, a matriz é inserida no mapa
 * com a chave fornecida pelo usuário, e é exibida uma mensagem de confirmação.
 *
 * @param matriz Objeto do tipo Matriz que será salvo.
 * @param matrizes Estrutura (unordered_map) onde a matriz será armazenada, associada a um nome (string).
 *
 * @note Essa função não retorna valores. É importante que o usuário insira corretamente as opções (s ou n) para prosseguir ou cancelar
 *       o salvamento, e que forneça um nome válido quando optar por salvar a matriz.
 */
void salvarMatriz(const Matriz &matriz, unordered_map &matrizes);

/**
 * @brief Solicita ao usuário o nome de duas matrizes a serem processadas.
 *
 * @param filename  Referência para a string que armazenará o nome da primeira matriz.
 * @param filename2 Referência para a string que armazenará o nome da segunda matriz.
 */
void escolherMatrizes(string &filename, string &filename2);

/**
 * @brief Exibe informações sobre as matrizes armazenadas em um std::unordered_map.
 *
 * @param matrizes Um std::unordered_map que mapeia uma chave (nome da matriz) para
 *                 uma instância de uma classe que fornece métodos getLinhas() e getColunas().
 *
 * As dimensões exibidas são obtidas diretamente da instância armazenada em cada valor do map.
 * A exibição é formatada para melhor leitura e compreensão dos dados de cada matriz.
 */
void printMatrizes(const unordered_map &matrizes);

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    std::cout << "Bem-vindo ao programa de manipulação de matrizes esparsas" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;

    unordered_map matrizes; /**< Mapa associativo para armazenar as matrizes */

    while (true)
    {
        std::cout << "Escolha uma opção:" << std::endl;
        std::cout << "[1] - Ler Matriz" << std::endl;
        std::cout << "[2] - Imprimir Matriz" << std::endl;
        std::cout << "[3] - Somar Matrizes" << std::endl;
        std::cout << "[4] - Multiplicar Matrizes" << std::endl;
        std::cout << "[5] - Sair" << std::endl;
        int opcao;
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao)
        {
        case LER_MATRIZ:
        {
            string filename;

            std::cout << "Digite o nome do arquivo: ";
            std::getline(std::cin, filename);

            Matriz matriz;

            try
            {
                readMatrix(matriz, filename);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                break;
            }

            matrizes.insert(std::make_pair(filename, matriz));
            break;
        }

        case IMPRIMIR_MATRIZ:
        {
            std::cout << "Qual matriz deseja imprimir?" << std::endl;

            printMatrizes(matrizes);

            std::cout << "Coloque o nome do arquivo que deseja imprimir: ";
            string filename;
            std::getline(std::cin, filename);

            if (existeMatriz(filename, matrizes))
                matrizes[filename].print();

            else
                std::cout << "Matriz não encontrada" << std::endl;

            break;
        }

        case SOMAR_MATRIZES:
        {
            std::cout << "Quais as matrizes irá usar para somar" << std::endl;

            printMatrizes(matrizes);

            std::string filename, filename2;

            escolherMatrizes(filename, filename2);

            if (!existeMatriz(filename, matrizes) || !existeMatriz(filename2, matrizes))
            {
                std::cout << "Alguma matriz não foi encontrada" << std::endl;
                break;
            }

            Matriz matriz;

            try
            {
                matriz = sum(matrizes[filename], matrizes[filename2]);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                break;
            }

            matriz.print();

            salvarMatriz(matriz, matrizes);

            break;
        }

        case MULTIPLICAR_MATRIZES:
        {
            std::cout << "Quais as matrizes irá usar para multiplicar" << std::endl;

            printMatrizes(matrizes);

            std::string filename, filename2;

            escolherMatrizes(filename, filename2);

            if (!existeMatriz(filename, matrizes) || !existeMatriz(filename2, matrizes))
            {
                std::cout << "Alguma matriz não foi encontrada" << std::endl;
                break;
            }

            Matriz matriz;

            try
            {
                matriz = multiply(matrizes[filename], matrizes[filename2]);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                break;
            }

            matriz.print();

            salvarMatriz(matriz, matrizes);

            break;
        }

        case SAIR:
        {
            std::cout << "Saindo..." << std::endl;
            return 0;
        }

        default:
        {
            std::cout << "Opção inválida" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            break;
        }
        }

        std::system("pause || read -p 'Pressione enter para continuar...' var");
        std::system("cls||clear");
    }
}

void readMatrix(Matriz &matriz, const std::string filename)
{
    std::ifstream file("src/arquivos/" + filename);

    if (!file || !file.is_open())
        throw std::runtime_error("Erro ao abrir o arquivo");

    int linhas{0}, colunas{0};
    file >> linhas >> colunas;

    matriz = Matriz(linhas, colunas);

    int i{0}, j{0};
    double valor{0.0f};

    while (file >> i >> j >> valor)
    {
        matriz.insert(i, j, valor);
    }

    file.close();
}

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

bool existeMatriz(const std::string filename, const unordered_map &matrizes)
{
    return matrizes.find(filename) != matrizes.end();
}

void salvarMatriz(const Matriz &matriz, unordered_map &matrizes)
{
    while (true)
    {
        std::cout << "Deseja salvar a matriz? [s/n]: ";
        char resposta;
        std::cin >> resposta;
        std::cin.ignore();

        if (resposta == 'n' || resposta == 'N')
            break;

        else if (resposta == 's' || resposta == 'S')
        {
            std::cout << "Digite o nome que deseja salvar a matriz: ";
            string filename;

            std::getline(std::cin, filename);

            if (existeMatriz(filename, matrizes))
            {
                std::cout << "Já existe uma matriz com esse nome, tente outro nome para salvar" << std::endl;
                break;
            }

            matrizes.insert(std::make_pair(filename, matriz));

            std::cout << "Matriz salva com sucesso" << std::endl;

            break;
        }

        else
        {
            std::cout << "Opção inválida" << std::endl;
            break;
        }
    }
}

void escolherMatrizes(string &filename, string &filename2)
{
    std::cout << "Coloque o nome da primeira matriz: ";
    std::getline(std::cin, filename);

    std::cout << "Coloque o nome da segunda matriz: ";
    std::getline(std::cin, filename2);
}

void printMatrizes(const unordered_map &matrizes)
{
    for (const auto &par : matrizes)
    {
        std::cout << "------------------" << std::endl;
        std::cout << par.first << " |" << par.second.getLinhas() << " x " << par.second.getColunas() << "|" << std::endl;
        std::cout << "------------------" << std::endl;
    }
}