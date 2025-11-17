/**
 * @file main.cpp
 * @brief Ponto de entrada do Sistema de Compras em Feiras
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 */

#include <iostream>
#include "produto.h"

int main() {
  std::cout << "=== Sistema de Compras em Feiras ===" << std::endl;
  std::cout << "Versão 1.0 - Protótipo Inicial" << std::endl;
  std::cout << std::endl;

  // EU004: Exemplo de cadastro de produto
  try {
    Produto p1("Tomate", 3.50, "Verduras", "Feira da Ceilândia");
    std::cout << "Produto cadastrado com sucesso!" << std::endl;
    std::cout << "Nome: " << p1.GetNome() << std::endl;
    std::cout << "Preço: R$ " << p1.GetPreco() << std::endl;
    std::cout << "Categoria: " << p1.GetCategoria() << std::endl;
    std::cout << "Feira: " << p1.GetFeira() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Erro: " << e.what() << std::endl;
  }

  return 0;
}
