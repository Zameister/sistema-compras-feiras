/**
 * @file usuario.h
 * @brief Declaracao da classe Usuario
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
 * @brief Representa um usuario do sistema com nome e localizacao GPS
 *
 * Esta classe armazena informacoes do usuario incluindo nome e
 * localizacao geografica para calculo de distancias ate feiras.
 */
class Usuario {
private:
    std::string nome;  ///< Nome do usuario
    Location localizacao;  ///< Localizacao GPS do usuario

public:
    /**
     * @brief Construtor padrao
     *
     * @pre Nenhuma
     * @post Cria usuario com valores padrao
     * @post nome vazio, localizacao em (0,0)
     */
    Usuario();

    /**
     * @brief Construtor com parametros (EU005)
     *
     * @param nome Nome do usuario
     * @param local Localizacao GPS do usuario
     *
     * @pre nome nao vazio
     * @pre local com coordenadas validas
     * @post Usuario criado com valores fornecidos
     * @post this->nome == nome
     * @post this->localizacao == local
     */
    Usuario(const std::string& nome, const Location& local);

    /**
     * @brief Obtem o nome do usuario
     *
     * @return Nome do usuario
     *
     * @pre Nenhuma
     * @post Retorna nome sem modificar o estado
     */
    std::string GetNome() const;

    /**
     * @brief Obtem a localizacao GPS do usuario
     *
     * @return Referencia constante para a localizacao
     *
     * @pre Nenhuma
     * @post Retorna localizacao sem modificar o estado
     */
    const Location& GetLocalizacao() const;

    /**
     * @brief Define novo nome para o usuario
     *
     * @param novoNome Novo nome do usuario
     *
     * @pre novoNome nao vazio
     * @post this->nome == novoNome
     */
    void SetNome(const std::string& novoNome);

    /**
     * @brief Define nova localizacao GPS para o usuario (EU005)
     *
     * @param novaLocalizacao Nova localizacao GPS
     *
     * @pre novaLocalizacao com coordenadas validas
     * @post this->localizacao == novaLocalizacao
     */
    void SetLocalizacao(const Location& novaLocalizacao);

    /**
     * @brief Calcula distancia do usuario ate uma feira (EU003)
     *
     * @param feira Feira de destino
     * @return Distancia em quilometros usando formula de Haversine
     *
     * @pre feira valida com localizacao definida
     * @post Retorna distancia >= 0.0
     * @post Estado do usuario nao modificado
     */
    double DistanciaPara(const Feira& feira) const;
};

#endif
