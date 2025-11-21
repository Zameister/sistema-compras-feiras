/**
 * @file produto.cpp
 * @brief Implementação da classe Produto
 * @author Luidgi
 * @date 2025
 */

#include "produto.h"

// ---------------------------------------------------------
// Construtores
// ---------------------------------------------------------

Produto::Produto()
    : nome(""), preco(0.0), categoria("") {}

Produto::Produto(const std::string& nome,
                 double preco,
                 const std::string& categoria)
    : nome(nome), preco(preco), categoria(categoria) {}


// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------

std::string Produto::getNome() const {
    return nome;
}

double Produto::getPreco() const {
    return preco;
}

std::string Produto::getCategoria() const {
    return categoria;
}


// ---------------------------------------------------------
// Setters
// ---------------------------------------------------------

void Produto::setNome(const std::string& novoNome) {
    nome = novoNome;
}

void Produto::setPreco(double novoPreco) {
    preco = novoPreco;
}

void Produto::setCategoria(const std::string& novaCategoria) {
    categoria = novaCategoria;
}
