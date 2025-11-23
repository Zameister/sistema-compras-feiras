/**
 * @file main_test.cpp
 * @brief Teste do sistema de localização: Usuario, Feira e cálculo de distâncias
 */

#include <iostream>
#include <vector>
#include "usuario.h"
#include "feira.h"
#include "distancias.h"

int main() {
    std::cout << "=== TESTE DO SISTEMA DE LOCALIZACAO ===\n\n";

    // ---------------------------------------------------------
    // 1) Criando um usuário com coordenadas reais
    // ---------------------------------------------------------
    Usuario usuario("Luidgi", Location(-15.793889, -47.882778));
    std::cout << "Usuario: " << usuario.GetNome() << "\n";
    std::cout << "Localizacao: Brasilia ( -15.79, -47.88 )\n\n";

    // ---------------------------------------------------------
    // 2) Criando feiras com localizações reais
    // ---------------------------------------------------------
    Feira f1(
        "Feira da Ceilandia",
        "Ceilandia Centro",
        Location(-15.817000, -48.112000)
    );

    Feira f2(
        "Feira da Asa Sul",
        "308 Sul",
        Location(-15.810700, -47.912700)
    );

    Feira f3(
        "Feira do Guara",
        "QE 25",
        Location(-15.842200, -47.980300)
    );

std::vector<Feira> feiras = {f1, f2, f3};

    // ---------------------------------------------------------
    // 3) Calculando distâncias
    // ---------------------------------------------------------
    std::cout << "Calculando distancias...\n\n";

    auto distancias = CalcularDistancias(usuario, feiras);

    for (const auto& par : distancias) {
        const Feira& feira = par.first;
        double distancia = par.second;

        std::cout << "Feira: " << feira.GetNome() << "\n";
        std::cout << "Distancia: " << distancia << " km\n\n";
    }

    return 0;
}
