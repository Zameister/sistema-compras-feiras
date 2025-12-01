/**
 * @file distancias.cpp
 * @brief Implementação das funções utilitárias de cálculos de distância
 */

#include "distancias.h"

// ---------------------------------------------------------
// Função principal
// ---------------------------------------------------------

std::vector<std::pair<Feira, double>>
CalcularDistancias(const Usuario& usuario, const std::vector<Feira>& feiras) {
    std::vector<std::pair<Feira, double>> resultado;

    for (const auto& feira : feiras) {
        double distancia = usuario.DistanciaPara(feira);
        resultado.push_back({feira, distancia});
    }

    return resultado;
}
