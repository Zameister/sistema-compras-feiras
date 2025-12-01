/**
 * @file feira.h
 * @brief Definição da classe Feira com localização GPS
 * @author Luidgi
 * @date 2025
 */

#ifndef FEIRA_H
#define FEIRA_H

#include <string>
#include <vector>
#include "produto.h"
#include "location.h"

class Feira {
private:
    std::string nome;
    std::string endereco;
    Location local;  ///< localização (latitude/longitude)
    std::vector<Produto> produtos;

public:
    // Construtores
    Feira();
    Feira(const std::string& nome,
          const std::string& endereco,
          const Location& local);

    // Getters
    std::string GetNome() const;
    std::string GetEndereco() const;
    const Location& GetLocal() const;
    const std::vector<Produto>& GetProdutos() const;

    // Setters
    void SetNome(const std::string& nome);
    void SetEndereco(const std::string& endereco);
    void SetLocal(const Location& novaLocalizacao);

    // Manipulação de produtos
    void AdicionarProduto(const Produto& produto);
    bool RemoverProduto(const std::string& nomeProduto);
    Produto* BuscarProduto(const std::string& nomeProduto);

    // Distância da feira até uma localização
    double DistanciaPara(const Location& destino) const;
};

#endif
