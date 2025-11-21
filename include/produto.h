#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

class Produto {
private:
    std::string nome;
    double preco;
    std::string categoria;

public:
    // Construtores
    Produto();
    Produto(const std::string& nome,
            double preco,
            const std::string& categoria);

    // Destrutor
    ~Produto() = default;

    // Getters
    std::string getNome() const;
    double getPreco() const;
    std::string getCategoria() const;

    // Setters
    void setNome(const std::string& novoNome);
    void setPreco(double novoPreco);
    void setCategoria(const std::string& novaCategoria);
};

#endif
