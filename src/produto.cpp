/**
 * @file produto.cpp
 * @brief Implementação da classe Produto
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 * @date 2025
 */

#include "produto.h"

// ---------------------------------------------------------
// Construtores
// ---------------------------------------------------------

Produto::Produto()
    : nome_(""), preco_(0.0), categoria_(""), feira_("") {}

Produto::Produto(const std::string& nome,
                 double preco,
                 const std::string& categoria,
                 const std::string& feira)
    : nome_(nome), preco_(preco), categoria_(categoria), feira_(feira) {}

// ---------------------------------------------------------
// Destrutor
// ---------------------------------------------------------

Produto::~Produto() {}


// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------

std::string Produto::GetNome() const {
    return nome_;
}

double Produto::GetPreco() const {
    return preco_;
}

std::string Produto::GetCategoria() const {
    return categoria_;
}

std::string Produto::GetFeira() const {
    return feira_;
}


// ---------------------------------------------------------
// Setters
// ---------------------------------------------------------

void Produto::SetNome(const std::string& nome) {
    nome_ = nome;
}

void Produto::SetPreco(double preco) {
    preco_ = preco;
}

void Produto::SetCategoria(const std::string& categoria) {
    categoria_ = categoria;
}

void Produto::SetFeira(const std::string& feira) {
    feira_ = feira;
}
