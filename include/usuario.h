/**
 * @file usuario.h
 * @brief Declaração da classe Usuario
 * @author Luidgi
 * @date 2025
 */

#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "location.h"
#include "feira.h"

/**
 * @brief Representa um usuário do sistema, contendo nome e localização.
 */
class Usuario {
private:
    std::string nome;
    Location localizacao;

public:
    // Construtores
    Usuario();
    Usuario(const std::string& nome, const Location& local);

    // Getters
    std::string GetNome() const;
    const Location& GetLocalizacao() const;

    // Setters
    void SetNome(const std::string& novoNome);
    void SetLocalizacao(const Location& novaLocalizacao);

    // Funcionalidade principal
    double DistanciaPara(const Feira& feira) const;
};

#endif
