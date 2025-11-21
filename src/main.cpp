/**
 * @file main.cpp
 * @brief Teste integrado das classes Produto, Feira e Feirante
 */

#include <iostream>
#include "produto.h"
#include "feira.h"
#include "feirante.h"

int main() {
    std::cout << "=== Sistema de Compras em Feiras ===\n\n";

    // ---------------------------------------
    // 1) Criando produtos de exemplo
    // ---------------------------------------
    Produto p1("Tomate", 3.50, "Hortifruti");
    Produto p2("Banana", 4.20, "Frutas");
    Produto p3("Alface", 2.00, "Verduras");

    // ---------------------------------------
    // 2) Criando uma feira
    // ---------------------------------------
    Feira feira1("Feira da Ceilândia", "Quadra 12, Ceilândia Sul");

    feira1.AdicionarProduto(p1);
    feira1.AdicionarProduto(p2);
    feira1.AdicionarProduto(p3);

    std::cout << "Feira cadastrada: " << feira1.GetNome() << "\n";
    std::cout << "Endereço: " << feira1.GetEndereco() << "\n\n";

    std::cout << "Produtos na feira:\n";
    for (const auto& produto : feira1.GetProdutos()) {
        std::cout << " - " << produto.getNome()
                  << " | R$ " << produto.getPreco()
                  << " | Categoria: " << produto.getCategoria()
                  << "\n";
    }
    std::cout << "\n";

    // ---------------------------------------
    // 3) Criando um feirante
    // ---------------------------------------
    Feirante f1("Jose da Silva", "123.456.789-00", feira1.GetNome());

    f1.AdicionarProduto(p1);
    f1.AdicionarProduto(p3);

    std::cout << "Feirante cadastrado: " << f1.GetNome()
              << "\nCPF: " << f1.GetCPF()
              << "\nFeira: " << f1.GetNomeFeira() << "\n\n";

    std::cout << "Produtos vendidos pelo feirante:\n";
    for (const auto& produto : f1.GetProdutos()) {
        std::cout << " - " << produto.getNome()
                  << " | R$ " << produto.getPreco() << "\n";
    }

    // ---------------------------------------
    // 4) Teste de busca de produto
    // ---------------------------------------
    Produto* encontrado = feira1.BuscarProduto("Tomate");

    if (encontrado != nullptr) {
        std::cout << "\nProduto encontrado na feira:\n";
        std::cout << "Nome: " << encontrado->getNome() << "\n";
        std::cout << "Preço: R$ " << encontrado->getPreco() << "\n";
    } else {
        std::cout << "Produto não encontrado.\n";
    }

    return 0;
}
