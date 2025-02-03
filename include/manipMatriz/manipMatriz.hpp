#pragma once

#include "matriz/Matriz.hpp"

void manipMatrix(Matriz &matriz, const std::string &nomeMatriz)
{
    while (true)
    {
        std::cout << "Matriz selecionada: " << nomeMatriz << std::endl;
        matriz.print();
        std::cout << "Escolha uma opção:" << std::endl;
        std::cout << "[1] - Inserir Valor" << std::endl;
        std::cout << "[2] - Remover Valor" << std::endl;
        std::cout << "[3] - Limpar Matriz" << std::endl;
        std::cout << "[4] - Voltar" << std::endl;

        int opcao;
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao)
        {
        case 1:
        {
            int i, j;
            double valor;

            std::cout << "Digite a linha: ";
            std::cin >> i;
            std::cin.ignore();

            std::cout << "Digite a coluna: ";
            std::cin >> j;
            std::cin.ignore();

            std::cout << "Digite o valor: ";
            std::cin >> valor;
            std::cin.ignore();

            try
            {
                matriz.insert(i, j, valor);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        }

        case 2:
        {
            int i, j;

            std::cout << "Digite a linha: ";
            std::cin >> i;
            std::cin.ignore();

            std::cout << "Digite a coluna: ";
            std::cin >> j;
            std::cin.ignore();

            try
            {
                std::cout << "Valor: " << matriz.get(i, j) << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        }

        case 3:
        {
            matriz.limpar();
            std::cout << "Matriz limpa" << std::endl;
            break;
        }

        case 4:
        {
            return;
        }

        default:
        {
            std::cout << "Opção inválida" << std::endl;
            break;
        }
        }
    }
}