/**
 * @file produto.h
 * @brief Definição da classe Produto
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 * @date 2025
 * 
 * Histórias de Usuário relacionadas: EU001, EU002, EU004
 */

#ifndef PRODUTO_H_
#define PRODUTO_H_

#include <string>

/**
 * @class Produto
 * @brief Representa um produto disponível em uma feira
 * 
 * Esta classe armazena informações sobre produtos cadastrados
 * por feirantes, incluindo nome, preço, categoria e localização.
 */
class Produto {
 public:
  /**
   * @brief Construtor padrão
   * 
   * @pre Nenhuma
   * @post Cria um produto com valores padrão
   */
  Produto();

  /**
   * @brief Construtor com parâmetros
   * 
   * @param nome Nome do produto
   * @param preco Preço do produto
   * @param categoria Categoria do produto
   * @param feira Nome da feira onde está disponível
   * 
   * @pre preco >= 0.0
   * @pre nome não vazio
   * @post Cria um produto com os valores especificados
   */
  Produto(const std::string& nome, double preco, 
          const std::string& categoria, const std::string& feira);

  /**
   * @brief Destrutor
   */
  ~Produto();

  // Getters
  /**
   * @brief Obtém o nome do produto
   * @return Nome do produto
   * 
   * @pre Nenhuma
   * @post Retorna o nome do produto sem modificá-lo
   */
  std::string GetNome() const;

  /**
   * @brief Obtém o preço do produto
   * @return Preço do produto
   * 
   * @pre Nenhuma
   * @post Retorna o preço do produto
   */
  double GetPreco() const;

  /**
   * @brief Obtém a categoria do produto
   * @return Categoria do produto
   * 
   * @pre Nenhuma
   * @post Retorna a categoria do produto
   */
  std::string GetCategoria() const;

  /**
   * @brief Obtém o nome da feira
   * @return Nome da feira
   * 
   * @pre Nenhuma
   * @post Retorna o nome da feira
   */
  std::string GetFeira() const;

  // Setters
  /**
   * @brief Define o nome do produto
   * @param nome Novo nome do produto
   * 
   * @pre nome não vazio
   * @post O nome do produto é atualizado
   */
  void SetNome(const std::string& nome);

  /**
   * @brief Define o preço do produto
   * @param preco Novo preço do produto
   * 
   * @pre preco >= 0.0
   * @post O preço do produto é atualizado
   */
  void SetPreco(double preco);

  /**
   * @brief Define a categoria do produto
   * @param categoria Nova categoria do produto
   * 
   * @pre categoria não vazia
   * @post A categoria do produto é atualizada
   */
  void SetCategoria(const std::string& categoria);

  /**
   * @brief Define a feira do produto
   * @param feira Novo nome da feira
   * 
   * @pre feira não vazia
   * @post A feira do produto é atualizada
   */
  void SetFeira(const std::string& feira);

 private:
  std::string nome_;        ///< Nome do produto
  double preco_;            ///< Preço do produto
  std::string categoria_;   ///< Categoria do produto
  std::string feira_;       ///< Nome da feira
};

#endif  // PRODUTO_H_
