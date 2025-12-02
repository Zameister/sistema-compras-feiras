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

  /**
   * @brief Obtém a nota média do produto
   * @return Nota média (0.0 a 5.0)
   *
   * @pre Nenhuma
   * @post Retorna a nota média do produto
   */
  double GetNota() const;

  /**
   * @brief Obtém o número de avaliações do produto
   * @return Número de avaliações
   *
   * @pre Nenhuma
   * @post Retorna o número de avaliações
   */
  int GetNumAvaliacoes() const;

  /**
   * @brief Adiciona uma avaliação ao produto
   * @param nota Nota da avaliação (1.0 a 5.0)
   *
   * @pre 1.0 <= nota <= 5.0
   * @post A nota média é recalculada
   */
  void AdicionarAvaliacao(double nota);

 private:
  std::string nome_;        ///< Nome do produto
  double preco_;            ///< Preço do produto
  std::string categoria_;   ///< Categoria do produto
  std::string feira_;       ///< Nome da feira
  double notaMedia_;        ///< Nota média do produto (0.0 a 5.0)
  int numAvaliacoes_;       ///< Número de avaliações recebidas
};

#endif
