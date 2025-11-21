/**
 * @file feirante.cpp
 * @brief Implementação da classe Feirante
 */

#include "feirante.h"
#include <algorithm> // std::remove_if

Feirante::Feirante() : nome(""), cpf(""), nomeFeira("") {}

Feirante::Feirante(const std::string& nome, const std::string& cpf, const std::string& nomeFeira)
    : nome(nome), cpf(cpf), nomeFeira(nomeFeira) {}

// ======= GETTERS =======
std::string Feirante::GetNome() const { return nome; }
std::string Feirante::GetCPF() const { return cpf; }
std::string Feirante::GetNomeFeira() const { return nomeFeira; }
const std::vector<Produto>& Feirante::GetProdutos() const { return produtos; }

// ======= SETTERS =======
void Feirante::SetNome(const std::string& nome) { this->nome = nome; }
void Feirante::SetCPF(const std::string& cpf) { this->cpf = cpf; }
void Feirante::SetNomeFeira(const std::string& nomeFeira) { this->nomeFeira = nomeFeira; }

// ======= MÉTODOS DE PRODUTOS =======

void Feirante::AdicionarProduto(const Produto& produto) {
    produtos.push_back(produto);
}

bool Feirante::RemoverProduto(const std::string& nomeProduto) {
    auto it = std::remove_if(produtos.begin(), produtos.end(),
        [&](const Produto& p) { return p.getNome() == nomeProduto; });

    if (it != produtos.end()) {
        produtos.erase(it, produtos.end());
        return true;
    }
    return false;
}

Produto* Feirante::BuscarProduto(const std::string& nomeProduto) {
    for (auto& p : produtos) {
        if (p.getNome() == nomeProduto) {
            return &p;
        }
    }
    return nullptr;
}
