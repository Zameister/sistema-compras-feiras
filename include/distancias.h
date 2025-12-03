/**
 * @file distancias.h
 * @brief Funcoes utilitarias para calculo de distancias entre usuario e feiras
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
 * @brief Calcula distancia do usuario ate cada feira (EU003)
 *
 * Esta funcao percorre todas as feiras e calcula a distancia do usuario
 * ate cada uma delas usando a formula de Haversine.
 *
 * @param usuario Referencia ao usuario com localizacao definida
 * @param feiras Vetor contendo todas as feiras cadastradas
 * @return Vector de pares (Feira, distancia em km)
 *
 * @pre usuario com localizacao valida definida
 * @pre feiras nao vazio (size > 0)
 * @pre Todas as feiras com localizacoes validas
 * @post Retorna vetor com mesmo tamanho de feiras
 * @post Todas as distancias >= 0.0
 * @post Parametros de entrada nao sao modificados
 */
std::vector<std::pair<Feira, double>>
CalcularDistancias(const Usuario& usuario, const std::vector<Feira>& feiras);

#endif
