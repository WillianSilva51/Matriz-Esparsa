#include <fstream>
#include <unordered_map>
#include "matriz/Matriz.hpp"

using string = std::string;
using unordered_map = std::unordered_map<string, Matriz>;

enum Opcoes
{
    LER_MATRIZ = 1,
    IMPRIMIR_MATRIZ,
    SOMAR_MATRIZES,
    MULTIPLICAR_MATRIZES,
    SAIR
};

void readMatrix(Matriz &matriz, const std::string filename)
{
    try
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
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

Matriz sum(const Matriz &matrizaA, const Matriz &matrizB)
{
}

Matriz multiply(const Matriz &matrizA, const Matriz &matrizB)
{
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
        }

        else
        {
            std::cout << "Opção inválida" << std::endl;
            break;
        }
    }
}

void escolherMatrizes(string &filename, string &filename2, const unordered_map &matrizes)
{
    std::cout << "Coloque o nome da primeira matriz: ";
    std::getline(std::cin, filename);

    if (!existeMatriz(filename, matrizes))
    {
        std::cout << "Matriz não encontrada" << std::endl;
        return;
    }

    std::cout << "Coloque o nome da segunda matriz: ";
    std::getline(std::cin, filename2);

    if (!existeMatriz(filename2, matrizes))
    {
        std::cout << "Matriz não encontrada" << std::endl;
        return;
    }
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

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    std::cout << "Bem-vindo ao programa de manipulação de matrizes esparsas" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;

    unordered_map matrizes;

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

            readMatrix(matriz, filename);

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

            matrizes[filename].print();

            break;
        }

        case SOMAR_MATRIZES:
        {
            std::cout << "Quais as matrizes irá usar para somar" << std::endl;

            printMatrizes(matrizes);

            std::string filename, filename2;

            escolherMatrizes(filename, filename2, matrizes);

            Matriz matriz = sum(matrizes[filename], matrizes[filename2]);

            matriz.print();

            salvarMatriz(matriz, matrizes);

            break;
        }

        case MULTIPLICAR_MATRIZES:
        {
            std::cout << "Quais as matrizes irá usar para multiplicar" << std::endl;

            printMatrizes(matrizes);

            std::string filename, filename2;

            escolherMatrizes(filename, filename2, matrizes);

            Matriz matriz = sum(matrizes[filename], matrizes[filename2]);

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
            std::cout << "Opção inválida" << std::endl;
            break;
        }

        std::system("pause || read -p 'Pressione enter para continuar...' var");
        std::system("cls||clear");
    }
}