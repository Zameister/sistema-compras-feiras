/**
 * @file distancias.cpp
 * @brief Implementacao das funcoes utilitarias de calculos de distancia
 */

#include "distancias.h"

// ---------------------------------------------------------
// Funcao principal
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
