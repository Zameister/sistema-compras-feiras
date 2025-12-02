/**
 * @file distancias.h
 * @brief Funções utilitárias para cálculo de distâncias entre usuário e feiras
 * @author Luidgi Varela Carneiro
 * @date 2025
 */

#ifndef DISTANCIAS_H
#define DISTANCIAS_H

#include <vector>
#include <utility>
#include "usuario.h"
#include "feira.h"

/**
 * @brief Calcula distância do usuário até cada feira (EU003)
 *
 * Esta função percorre todas as feiras e calcula a distância do usuário
 * até cada uma delas usando a fórmula de Haversine.
 *
 * @param usuario Referência ao usuário com localização definida
 * @param feiras Vetor contendo todas as feiras cadastradas
 * @return Vector de pares (Feira, distância em km)
 *
 * @pre usuario com localização válida definida
 * @pre feiras não vazio (size > 0)
 * @pre Todas as feiras com localizações válidas
 * @post Retorna vetor com mesmo tamanho de feiras
 * @post Todas as distâncias >= 0.0
 * @post Parâmetros de entrada não são modificados
 */
std::vector<std::pair<Feira, double>>
CalcularDistancias(const Usuario& usuario, const std::vector<Feira>& feiras);

#endif
