/**
 * @file produto.h
 * @brief Definicao da classe Produto
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 * @date 2025
 * 
 * Historias de Usuario relacionadas: EU001, EU002, EU004
 */

#ifndef PRODUTO_H_
#define PRODUTO_H_

#include <string>

/**
 * @class Produto
 * @brief Representa um produto disponivel em uma feira
 * 
 * Esta classe armazena informacoes sobre produtos cadastrados
 * por feirantes, incluindo nome, preco, categoria e localizacao.
 */
class Produto {
 public:
  /**
   * @brief Construtor padrao
   * 
   * @pre Nenhuma
   * @post Cria um produto com valores padrao
   */
  Produto();

  /**
   * @brief Construtor com parametros
   * 
   * @param nome Nome do produto
   * @param preco Preco do produto
   * @param categoria Categoria do produto
   * @param feira Nome da feira onde esta disponivel
   * 
   * @pre preco >= 0.0
   * @pre nome nao vazio
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
   * @brief Obtem o nome do produto
   * @return Nome do produto
   * 
   * @pre Nenhuma
   * @post Retorna o nome do produto sem modifica-lo
   */
  std::string GetNome() const;

  /**
   * @brief Obtem o preco do produto
   * @return Preco do produto
   * 
   * @pre Nenhuma
   * @post Retorna o preco do produto
   */
  double GetPreco() const;

  /**
   * @brief Obtem a categoria do produto
   * @return Categoria do produto
   * 
   * @pre Nenhuma
   * @post Retorna a categoria do produto
   */
  std::string GetCategoria() const;

  /**
   * @brief Obtem o nome da feira
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
   * @pre nome nao vazio
   * @post O nome do produto e atualizado
   */
  void SetNome(const std::string& nome);

  /**
   * @brief Define o preco do produto
   * @param preco Novo preco do produto
   * 
   * @pre preco >= 0.0
   * @post O preco do produto e atualizado
   */
  void SetPreco(double preco);

  /**
   * @brief Define a categoria do produto
   * @param categoria Nova categoria do produto
   * 
   * @pre categoria nao vazia
   * @post A categoria do produto e atualizada
   */
  void SetCategoria(const std::string& categoria);

  /**
   * @brief Define a feira do produto
   * @param feira Novo nome da feira
   *
   * @pre feira nao vazia
   * @post A feira do produto e atualizada
   */
  void SetFeira(const std::string& feira);

  /**
   * @brief Obtem a nota media do produto
   * @return Nota media (0.0 a 5.0)
   *
   * @pre Nenhuma
   * @post Retorna a nota media do produto
   */
  double GetNota() const;

  /**
   * @brief Obtem o numero de avaliacoes do produto
   * @return Numero de avaliacoes
   *
   * @pre Nenhuma
   * @post Retorna o numero de avaliacoes
   */
  int GetNumAvaliacoes() const;

  /**
   * @brief Adiciona uma avaliacao ao produto
   * @param nota Nota da avaliacao (1.0 a 5.0)
   *
   * @pre 1.0 <= nota <= 5.0
   * @post A nota media e recalculada
   */
  void AdicionarAvaliacao(double nota);

 private:
  std::string nome_;        ///< Nome do produto
  double preco_;            ///< Preco do produto
  std::string categoria_;   ///< Categoria do produto
  std::string feira_;       ///< Nome da feira
  double notaMedia_;        ///< Nota media do produto (0.0 a 5.0)
  int numAvaliacoes_;       ///< Numero de avaliacoes recebidas
};

#endif  // PRODUTO_H_
