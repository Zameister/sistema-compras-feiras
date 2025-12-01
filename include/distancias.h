/**
 * @file distancias.h
 * @brief Funções utilitárias para cálculo de distâncias entre usuário e feiras
 * @author Luidgi
 * @date 2025
 */

#ifndef DISTANCIAS_H
#define DISTANCIAS_H

#include <vector>
#include <utility>
#include "usuario.h"
#include "feira.h"

/**
 * @brief Calcula a distância do usuário até cada feira.
 *
 * @param usuario Referência ao usuário.
 * @param feiras Vetor contendo todas as feiras cadastradas.
 * @return std::vector<std::pair<Feira, double>> Vetor com pares (Feira, distância).
 */
std::vector<std::pair<Feira, double>>
CalcularDistancias(const Usuario& usuario, const std::vector<Feira>& feiras);

#endif
