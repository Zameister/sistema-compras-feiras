/**
 * @file usuario.cpp
 * @brief Implementacao da classe Usuario
 */

#include "usuario.h"

// ---------------------------------------------------------
// Construtores
// ---------------------------------------------------------

Usuario::Usuario() : nome(""), localizacao() {}

Usuario::Usuario(const std::string& nome, const Location& local)
    : nome(nome), localizacao(local) {}


// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------

std::string Usuario::GetNome() const {
    return nome;
}

const Location& Usuario::GetLocalizacao() const {
    return localizacao;
}


// ---------------------------------------------------------
// Setters
// ---------------------------------------------------------

void Usuario::SetNome(const std::string& novoNome) {
    nome = novoNome;
}

void Usuario::SetLocalizacao(const Location& novaLocalizacao) {
    localizacao = novaLocalizacao;
}


// ---------------------------------------------------------
// Funcionalidades
// ---------------------------------------------------------

double Usuario::DistanciaPara(const Feira& feira) const {
    return localizacao.DistanciaPara(feira.GetLocal());
}
