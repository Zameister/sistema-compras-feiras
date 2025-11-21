#include "produto.h"
#include <stdexcept>

// Construtor padrão
Produto::Produto() : nome(""), preco(0.0), categoria("") {}

// Construtor completo (3 parâmetros)
Produto::Produto(const std::string& nome,
                 double preco,
                 const std::string& categoria)
    : nome(nome), preco(preco), categoria(categoria) {

    if (nome.empty()) {
        throw std::invalid_argument("Nome não pode ser vazio");
    }
    if (categoria.empty()) {
        throw std::invalid_argument("Categoria não pode ser vazia");
    }
    if (preco < 0.0) {
        throw std::invalid_argument("Preço não pode ser negativo");
    }
}

// ===== GETTERS =====
std::string Produto::getNome() const {
    return nome;
}

double Produto::getPreco() const {
    return preco;
}

std::string Produto::getCategoria() const {
    return categoria;
}

// ===== SETTERS =====
void Produto::setNome(const std::string& novoNome) {
    if (novoNome.empty()) {
        throw std::invalid_argument("Nome não pode ser vazio");
    }
    nome = novoNome;
}

void Produto::setPreco(double novoPreco) {
    if (novoPreco < 0.0) {
        throw std::invalid_argument("Preço não pode ser negativo");
    }
    preco = novoPreco;
}

void Produto::setCategoria(const std::string& novaCategoria) {
    if (novaCategoria.empty()) {
        throw std::invalid_argument("Categoria não pode ser vazia");
    }
    categoria = novaCategoria;
}
