/**
 * @file feirante.h
 * @brief Declaracao da classe Feirante
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 *
 * Define a classe Feirante para representar vendedores em feiras.
 * Suporta cadastro, autenticacao segura com hash de senha, e gestao de dados.
 *
 * Historias de Usuario: EU004, EU005
 * Desenvolvido seguindo TDD (Test-Driven Development)
 */

#ifndef FEIRANTE_H_
#define FEIRANTE_H_

#include <string>
#include <stdexcept>

/**
 * @class Feirante
 * @brief Representa um feirante (vendedor) em uma feira
 *
 * Esta classe gerencia informacoes de feirantes, incluindo:
 * - Dados pessoais (nome, banca, feira)
 * - Autenticacao segura com hash de senha
 * - Serializacao para JSON
 *
 * @invariant Nome nao pode ser vazio
 * @invariant Banca nao pode ser vazia
 * @invariant Feira nao pode ser vazia
 * @invariant Senha deve ter no minimo 4 caracteres
 */
class Feirante {
 public:
  /**
   * @brief Construtor padrao
   *
   * @post Cria feirante com todos os campos vazios
   */
  Feirante();

  /**
   * @brief Construtor com parametros
   * @param nome Nome completo do feirante
   * @param banca Nome da banca/barraca
   * @param feira Nome da feira onde trabalha
   * @param senha Senha em texto puro (sera hasheada)
   *
   * @pre nome, banca, feira nao podem ser vazios
   * @pre senha deve ter no minimo 4 caracteres
   * @post Feirante criado com senha hasheada
   * @throws std::invalid_argument se algum parametro for invalido
   */
  Feirante(const std::string& nome,
           const std::string& banca,
           const std::string& feira,
           const std::string& senha);

  /**
   * @brief Destrutor
   */
  ~Feirante();

  // ---------------------------------------------------------
  // Getters
  // ---------------------------------------------------------

  /**
   * @brief Obtem o nome do feirante
   * @return Nome do feirante
   *
   * @pre Nenhuma (metodo const)
   * @post Retorna nome_ sem modifica-lo
   * @post Estado do objeto permanece inalterado
   */
  std::string GetNome() const;

  /**
   * @brief Obtem o nome da banca
   * @return Nome da banca
   *
   * @pre Nenhuma (metodo const)
   * @post Retorna banca_ sem modifica-la
   * @post Estado do objeto permanece inalterado
   */
  std::string GetBanca() const;

  /**
   * @brief Obtem o nome da feira
   * @return Nome da feira
   *
   * @pre Nenhuma (metodo const)
   * @post Retorna feira_ sem modifica-la
   * @post Estado do objeto permanece inalterado
   */
  std::string GetFeira() const;

  /**
   * @brief Obtem o hash da senha (para persistencia)
   * @return Hash SHA256 da senha
   *
   * @pre Nenhuma (metodo const)
   * @post Retorna senhaHash_ sem modifica-lo
   * @post Estado do objeto permanece inalterado
   * @warning Nunca exponha a senha em texto puro
   */
  std::string GetSenhaHash() const;

  // ---------------------------------------------------------
  // Setters
  // ---------------------------------------------------------

  /**
   * @brief Define o nome do feirante
   * @param nome Novo nome
   *
   * @pre nome nao pode ser vazio
   * @post Nome atualizado
   * @throws std::invalid_argument se nome for vazio
   */
  void SetNome(const std::string& nome);

  /**
   * @brief Define o nome da banca
   * @param banca Novo nome da banca
   *
   * @pre banca nao pode ser vazia
   * @post Banca atualizada
   * @throws std::invalid_argument se banca for vazia
   */
  void SetBanca(const std::string& banca);

  /**
   * @brief Define o nome da feira
   * @param feira Novo nome da feira
   *
   * @pre feira nao pode ser vazia
   * @post Feira atualizada
   * @throws std::invalid_argument se feira for vazia
   */
  void SetFeira(const std::string& feira);

  // ---------------------------------------------------------
  // Autenticacao
  // ---------------------------------------------------------

  /**
   * @brief Valida se a senha fornecida esta correta
   * @param senha Senha em texto puro para validar
   * @return true se a senha estiver correta, false caso contrario
   *
   * @pre Nenhuma
   * @post Nenhuma alteracao no objeto
   */
  bool ValidarSenha(const std::string& senha) const;

  /**
   * @brief Altera a senha do feirante
   * @param senhaAntiga Senha atual (para validacao)
   * @param senhaNova Nova senha
   *
   * @pre senhaAntiga deve estar correta
   * @pre senhaNova deve ter no minimo 4 caracteres
   * @post Senha alterada e hasheada
   * @throws std::invalid_argument se senhaAntiga estiver incorreta ou senhaNova for muito curta
   */
  void AlterarSenha(const std::string& senhaAntiga, const std::string& senhaNova);

  // ---------------------------------------------------------
  // Serializacao
  // ---------------------------------------------------------

  /**
   * @brief Serializa o feirante para JSON
   * @return String JSON com os dados do feirante
   *
   * @post Retorna JSON sem a senha em texto puro
   */
  std::string ParaJSON() const;

 private:
  std::string nome_;       ///< Nome completo do feirante
  std::string banca_;      ///< Nome da banca/barraca
  std::string feira_;      ///< Nome da feira onde trabalha
  std::string senhaHash_;  ///< Hash SHA256 da senha

  /**
   * @brief Gera hash SHA256 de uma string
   * @param texto Texto para hashear
   * @return Hash SHA256 em hexadecimal
   */
  std::string GerarHash(const std::string& texto) const;
};

#endif  // FEIRANTE_H_
