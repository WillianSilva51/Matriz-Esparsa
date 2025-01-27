//Arquivo de testes para a Matriz Esparsa
#include <iostream>
#include "matriz/Matriz.hpp"

void testeInsercao() {
    Matriz matriz;
    matriz.insert(1, 1, 1);

    if (matriz.get(1, 1) != 1) {
        std::cout << "Erro no teste de inserção" << std::endl;
    } else {
        std::cout << "Teste de inserção passou" << std::endl;
    }
}

void testeSoma() {
    Matriz matriz;
    matriz.insert(1, 1, 1);
    matriz.insert(2, 2, 1);
    matriz.insert(3, 3, 1);
    matriz.insert(1, 3, 1);

    Matriz matriz2;
    matriz2.insert(1, 1, 1);
    matriz2.insert(2, 2, 1);
    matriz2.insert(3, 3, 1);
    matriz2.insert(1, 3, 1);
    matriz2.insert(2, 3, 1);

    Matriz matriz3 = matriz + matriz2;


}

int main() {
    testeInsercao();
    return 0;
}
