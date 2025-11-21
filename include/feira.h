/**
 * @file feira.h
 * @brief Definição da classe Feira
 * @author Luidgi
 * @date 2025
 */

#ifndef FEIRA_H
#define FEIRA_H

#include <string>
#include <vector>
#include "produto.h"

class Feira {
private:
    std::string nome;
    std::string endereco;

    // Cada feira contém vários produtos
    std::vector<Produto> produtos;

public:
    // Construtores
    Feira();
    Feira(const std::string& nome, const std::string& endereco);

    // Getters
    std::string GetNome() const;
    std::string GetEndereco() const;
    const std::vector<Produto>& GetProdutos() const;

    // Setters
    void SetNome(const std::string& nome);
    void SetEndereco(const std::string& endereco);

    // Manipulação de produtos
    void AdicionarProduto(const Produto& produto);
    bool RemoverProduto(const std::string& nomeProduto);
    Produto* BuscarProduto(const std::string& nomeProduto);
};

#endif
