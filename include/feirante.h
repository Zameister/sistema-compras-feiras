/**
 * @file feirante.h
 * @brief Definição da classe Feirante
 */

#ifndef FEIRANTE_H
#define FEIRANTE_H

#include <string>
#include <vector>
#include "produto.h"

class Feirante {
private:
    std::string nome;
    std::string cpf;               // Identificação única do feirante
    std::string nomeFeira;         // Nome da feira onde trabalha
    std::vector<Produto> produtos; // Produtos que ele vende

public:
    // Construtores
    Feirante();
    Feirante(const std::string& nome, const std::string& cpf, const std::string& nomeFeira);

    // Getters
    std::string GetNome() const;
    std::string GetCPF() const;
    std::string GetNomeFeira() const;
    const std::vector<Produto>& GetProdutos() const;

    // Setters
    void SetNome(const std::string& nome);
    void SetCPF(const std::string& cpf);
    void SetNomeFeira(const std::string& nomeFeira);

    // Manipulação de produtos
    void AdicionarProduto(const Produto& produto);
    bool RemoverProduto(const std::string& nomeProduto);
    Produto* BuscarProduto(const std::string& nomeProduto);
};

#endif
