/**
 * @file produto.cpp
 * @brief Implementacao da classe Produto
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 * @date 2025
 */

#include "produto.h"

// ---------------------------------------------------------
// Construtores
// ---------------------------------------------------------

Produto::Produto()
    : nome_(""), preco_(0.0), categoria_(""), feira_(""), notaMedia_(0.0), numAvaliacoes_(0) {}

Produto::Produto(const std::string& nome,
                 double preco,
                 const std::string& categoria,
                 const std::string& feira)
    : nome_(nome), preco_(preco), categoria_(categoria), feira_(feira), notaMedia_(0.0), numAvaliacoes_(0) {}

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


// ---------------------------------------------------------
// Metodos de Avaliacao
// ---------------------------------------------------------

double Produto::GetNota() const {
    return notaMedia_;
}

int Produto::GetNumAvaliacoes() const {
    return numAvaliacoes_;
}

void Produto::AdicionarAvaliacao(double nota) {
    if (nota < 1.0 || nota > 5.0) return;  // Validacao

    // Recalcular media
    double somaTotal = (notaMedia_ * numAvaliacoes_) + nota;
    numAvaliacoes_++;
    notaMedia_ = somaTotal / numAvaliacoes_;
}
