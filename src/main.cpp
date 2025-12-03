/**
 * @file main.cpp
 * @brief Ponto de entrada principal do sistema
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 *
 * Inicializa o sistema de compras em feiras e exibe o menu principal.
 * Configura codificacao UTF-8 no Windows para suporte a caracteres especiais.
 */

#include "sistema.h"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#endif

/**
 * @brief Funcao principal do programa
 * @return 0 em caso de sucesso
 *
 * Inicializa o sistema, configura UTF-8 no Windows, e exibe o menu interativo.
 */
int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    Sistema sistema;
    sistema.Menu();

    return 0;
}
