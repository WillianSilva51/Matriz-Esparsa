/**
 *  @authors
 * - Antonio Willian Silva Oliveira - 567294 (
 * - Iago de Oliveira Lo - 565321 (
 */

#include <fstream>
#include <unordered_map>
#include "matriz/Matriz.hpp"
#include "utils/utils.hpp"
#include "manipMatriz/manipMatriz.hpp"

using string = std::string;
using unordered_map = std::unordered_map<string, Matriz>;

enum Opcoes // Enumeração para as opções do menu
{
    LER_MATRIZ = 1,
    MANIPULAR_MATRIZ,
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

/**
 * @file main.cpp
 * @brief Programa para manipulação de matrizes esparsas.
 *
 * Este programa permite ao usuário ler, imprimir, somar e multiplicar matrizes esparsas.
 * As matrizes são armazenadas em um mapa associativo, onde a chave é o nome do arquivo
 * e o valor é a matriz correspondente.
 *
 * @details
 * O programa apresenta um menu interativo com as seguintes opções:
 * - Ler Matriz: Lê uma matriz a partir de um arquivo.
 * - Imprimir Matriz: Imprime uma matriz armazenada.
 * - Somar Matrizes: Soma duas matrizes armazenadas.
 * - Multiplicar Matrizes: Multiplica duas matrizes armazenadas.
 * - Sair: Encerra o programa.
 */
int main()
{
    // Configura a localização para suportar caracteres especiais em português
    setlocale(LC_ALL, "pt_BR.UTF-8");

    std::cout << "Bem-vindo ao programa de manipulação de matrizes esparsas" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;

    // Mapa associativo para armazenar as matrizes
    unordered_map matrizes;

    while (true)
    {
        // Exibe o menu de opções
        std::cout << "Escolha uma opção:" << std::endl;
        std::cout << "[1] - Ler Matriz" << std::endl;
        std::cout << "[2] - Manipular Matriz" << std::endl;
        std::cout << "[3] - Imprimir Matriz" << std::endl;
        std::cout << "[4] - Somar Matrizes" << std::endl;
        std::cout << "[5] - Multiplicar Matrizes" << std::endl;
        std::cout << "[6] - Sair" << std::endl;
        int opcao;
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao)
        {
        case LER_MATRIZ:
        {
            // Lê uma matriz a partir de um arquivo
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
                std::cout << "Exemplo de arquivo: matrix.txt" << std::endl;
                break;
            }

            // Armazena a matriz no mapa associativo
            matrizes.insert(std::make_pair(filename, matriz));
            break;
        }

        case MANIPULAR_MATRIZ:
        {
            if (matrizes.empty())
            {
                std::cout << "Não há matrizes armazenadas" << std::endl;
                break;
            }

            // Manipula uma matriz armazenada
            printMatrizes(matrizes);

            std::cout << "Qual matriz deseja manipular?" << std::endl;
            string filename;
            std::getline(std::cin, filename);

            if (!existeMatriz(filename, matrizes))
            {
                std::cout << "Matriz não encontrada" << std::endl;
                break;
            }

            std::system("clear||cls");
            manipMatrix(matrizes[filename], filename);

            break;
        }

        case IMPRIMIR_MATRIZ:
        {
            if (matrizes.empty())
            {
                std::cout << "Não há matrizes armazenadas" << std::endl;
                break;
            }

            // Imprime uma matriz armazenada
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
            if (matrizes.empty())
            {
                std::cout << "Não há matrizes armazenadas" << std::endl;
                break;
            }

            // Soma duas matrizes armazenadas
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
            if (matrizes.empty())
            {
                std::cout << "Não há matrizes armazenadas" << std::endl;
                break;
            }

            // Multiplica duas matrizes armazenadas
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
            // Encerra o programa
            std::cout << "Saindo..." << std::endl;
            return 0;
        }

        default:
        {
            // Opção inválida
            std::cout << "Opção inválida" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            break;
        }
        }

        // Pausa e limpa a tela
        std::system("read -p 'Pressione enter para continuar...' var");
        std::system("clear||cls");
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

bool existeMatriz(const std::string filename, const unordered_map &matrizes)
{
    return matrizes.find(filename) != matrizes.end();
}

void salvarMatriz(const Matriz &matriz, unordered_map &matrizes)
{
    while (true)
    {
        std::cout << "Deseja salvar a matriz? [S/N]: ";
        char resposta;
        std::cin >> resposta;
        std::cin.ignore();

        switch (tolower(resposta))
        {
        case 'n':
            return;

        case 's':
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
            return;
        }

        default:
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