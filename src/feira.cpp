/**
 * @file feira.cpp
 * @brief Implementação da classe Feira
 */

#include "feira.h"
#include <algorithm> // std::find_if

Feira::Feira() : nome(""), endereco("") {}

Feira::Feira(const std::string& nome, const std::string& endereco)
    : nome(nome), endereco(endereco) {}

// ======= GETTERS =======
std::string Feira::GetNome() const { return nome; }
std::string Feira::GetEndereco() const { return endereco; }
const std::vector<Produto>& Feira::GetProdutos() const { return produtos; }

// ======= SETTERS =======
void Feira::SetNome(const std::string& nome) { this->nome = nome; }
void Feira::SetEndereco(const std::string& endereco) { this->endereco = endereco; }

// ======= MÉTODOS DE PRODUTOS =======
void Feira::AdicionarProduto(const Produto& produto) {
    produtos.push_back(produto);
}

bool Feira::RemoverProduto(const std::string& nomeProduto) {
    auto it = std::remove_if(produtos.begin(), produtos.end(),
        [&](const Produto& p) { return p.getNome() == nomeProduto; });

    if (it != produtos.end()) {
        produtos.erase(it, produtos.end());
        return true;
    }
    return false;
}

Produto* Feira::BuscarProduto(const std::string& nomeProduto) {
    for (auto& p : produtos) {
        if (p.getNome() == nomeProduto) {
            return &p;
        }
    }
    return nullptr;
}
