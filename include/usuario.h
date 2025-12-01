/**
 * @file usuario.h
 * @brief Declaração da classe Usuario
 * @author Luidgi Varela Carneiro
 * @date 2025
 */

#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "location.h"
#include "feira.h"

/**
 * @class Usuario
 * @brief Representa um usuário do sistema com nome e localização GPS
 *
 * Esta classe armazena informações do usuário incluindo nome e
 * localização geográfica para cálculo de distâncias até feiras.
 */
class Usuario {
private:
    std::string nome;  ///< Nome do usuário
    Location localizacao;  ///< Localização GPS do usuário

public:
    /**
     * @brief Construtor padrão
     *
     * @pre Nenhuma
     * @post Cria usuário com valores padrão
     * @post nome vazio, localizacao em (0,0)
     */
    Usuario();

    /**
     * @brief Construtor com parâmetros (EU005)
     *
     * @param nome Nome do usuário
     * @param local Localização GPS do usuário
     *
     * @pre nome não vazio
     * @pre local com coordenadas válidas
     * @post Usuario criado com valores fornecidos
     * @post this->nome == nome
     * @post this->localizacao == local
     */
    Usuario(const std::string& nome, const Location& local);

    /**
     * @brief Obtém o nome do usuário
     *
     * @return Nome do usuário
     *
     * @pre Nenhuma
     * @post Retorna nome sem modificar o estado
     */
    std::string GetNome() const;

    /**
     * @brief Obtém a localização GPS do usuário
     *
     * @return Referência constante para a localização
     *
     * @pre Nenhuma
     * @post Retorna localização sem modificar o estado
     */
    const Location& GetLocalizacao() const;

    /**
     * @brief Define novo nome para o usuário
     *
     * @param novoNome Novo nome do usuário
     *
     * @pre novoNome não vazio
     * @post this->nome == novoNome
     */
    void SetNome(const std::string& novoNome);

    /**
     * @brief Define nova localização GPS para o usuário (EU005)
     *
     * @param novaLocalizacao Nova localização GPS
     *
     * @pre novaLocalizacao com coordenadas válidas
     * @post this->localizacao == novaLocalizacao
     */
    void SetLocalizacao(const Location& novaLocalizacao);

    /**
     * @brief Calcula distância do usuário até uma feira (EU003)
     *
     * @param feira Feira de destino
     * @return Distância em quilômetros usando fórmula de Haversine
     *
     * @pre feira válida com localização definida
     * @post Retorna distância >= 0.0
     * @post Estado do usuário não modificado
     */
    double DistanciaPara(const Feira& feira) const;
};

#endif
