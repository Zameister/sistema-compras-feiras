/**
 * @file feira.cpp
 * @brief Implementacao da classe Feira com localizacao GPS
 */

#include "feira.h"
#include <algorithm>

// ---------------------------------------------------------
// Construtores
// ---------------------------------------------------------

Feira::Feira() : nome(""), endereco(""), local() {}

Feira::Feira(const std::string& nome,
             const std::string& endereco,
             const Location& local)
    : nome(nome), endereco(endereco), local(local) {}


// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------

std::string Feira::GetNome() const {
    return nome;
}

std::string Feira::GetEndereco() const {
    return endereco;
}

const Location& Feira::GetLocal() const {
    return local;
}

const std::vector<Produto>& Feira::GetProdutos() const {
    return produtos;
}


// ---------------------------------------------------------
// Setters
// ---------------------------------------------------------

void Feira::SetNome(const std::string& nome) {
    this->nome = nome;
}

void Feira::SetEndereco(const std::string& endereco) {
    this->endereco = endereco;
}

void Feira::SetLocal(const Location& novaLocalizacao) {
    this->local = novaLocalizacao;
}


// ---------------------------------------------------------
// Manipulacao de Produtos
// ---------------------------------------------------------

void Feira::AdicionarProduto(const Produto& produto) {
    produtos.push_back(produto);
}

bool Feira::RemoverProduto(const std::string& nomeProduto) {
    auto it = std::find_if(produtos.begin(), produtos.end(),
        [&](const Produto& p) {
            return p.GetNome() == nomeProduto;
        });

    if (it != produtos.end()) {
        produtos.erase(it);
        return true;
    }
    return false;
}

Produto* Feira::BuscarProduto(const std::string& nomeProduto) {
    for (auto& p : produtos) {
        if (p.GetNome() == nomeProduto) {
            return &p;
        }
    }
    return nullptr;
}


// ---------------------------------------------------------
// Distancia ate uma localizacao
// ---------------------------------------------------------

double Feira::DistanciaPara(const Location& destino) const {
    return local.DistanciaPara(destino);
}
