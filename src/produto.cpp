/**
 * @file produto.cpp
 * @brief Implementação da classe Produto
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 * 
 * Histórias de Usuário: EU001, EU002, EU004
 */

#include "produto.h"
#include <stdexcept>

// EU004: Como feirante, quero cadastrar meus produtos
Produto::Produto() : nome_(""), preco_(0.0), categoria_(""), feira_("") {}

Produto::Produto(const std::string& nome, double preco,
                 const std::string& categoria, const std::string& feira)
    : nome_(nome), preco_(preco), categoria_(categoria), feira_(feira) {
  if (preco < 0.0) {
    throw std::invalid_argument("Preço não pode ser negativo");
  }
  if (nome.empty()) {
    throw std::invalid_argument("Nome não pode ser vazio");
  }
}

Produto::~Produto() {}

// Getters
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

// Setters
void Produto::SetNome(const std::string& nome) {
  if (nome.empty()) {
    throw std::invalid_argument("Nome não pode ser vazio");
  }
  nome_ = nome;
}

void Produto::SetPreco(double preco) {
  if (preco < 0.0) {
    throw std::invalid_argument("Preço não pode ser negativo");
  }
  preco_ = preco;
}

void Produto::SetCategoria(const std::string& categoria) {
  if (categoria.empty()) {
    throw std::invalid_argument("Categoria não pode ser vazia");
  }
  categoria_ = categoria;
}

void Produto::SetFeira(const std::string& feira) {
  if (feira.empty()) {
    throw std::invalid_argument("Feira não pode ser vazia");
  }
  feira_ = feira;
}
