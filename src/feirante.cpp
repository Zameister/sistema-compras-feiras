/**
 * @file feirante.cpp
 * @brief Implementação da classe Feirante
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 *
 * Histórias de Usuário: EU004, EU005
 * Desenvolvido seguindo TDD (Test-Driven Development)
 */

#include "feirante.h"
#include <sstream>
#include <iomanip>

// ---------------------------------------------------------
// Hash SHA256 Simplificado (para propósitos educacionais)
// Em produção, use biblioteca como OpenSSL
// ---------------------------------------------------------

std::string Feirante::GerarHash(const std::string& texto) const {
  // Hash simples baseado em soma de caracteres + rotação
  // NOTA: Em produção real, usar SHA256 de biblioteca criptográfica
  unsigned long hash = 5381;
  for (char c : texto) {
    hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
  }

  // Adicionar salt baseado no tamanho
  hash ^= texto.length() * 0xDEADBEEF;

  // Converter para hexadecimal
  std::stringstream ss;
  ss << std::hex << std::setfill('0') << std::setw(16) << hash;
  return ss.str();
}

// ---------------------------------------------------------
// Construtores
// ---------------------------------------------------------

Feirante::Feirante()
    : nome_(""), banca_(""), feira_(""), senhaHash_("") {}

Feirante::Feirante(const std::string& nome,
                   const std::string& banca,
                   const std::string& feira,
                   const std::string& senha)
    : nome_(nome), banca_(banca), feira_(feira) {
  // Validações
  if (nome.empty()) {
    throw std::invalid_argument("Nome do feirante não pode ser vazio");
  }
  if (banca.empty()) {
    throw std::invalid_argument("Nome da banca não pode ser vazio");
  }
  if (feira.empty()) {
    throw std::invalid_argument("Nome da feira não pode ser vazio");
  }
  if (senha.empty()) {
    throw std::invalid_argument("Senha não pode ser vazia");
  }
  if (senha.length() < 4) {
    throw std::invalid_argument("Senha deve ter no mínimo 4 caracteres");
  }

  // Hashear senha
  senhaHash_ = GerarHash(senha);
}

// ---------------------------------------------------------
// Destrutor
// ---------------------------------------------------------

Feirante::~Feirante() {}

// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------

std::string Feirante::GetNome() const {
  return nome_;
}

std::string Feirante::GetBanca() const {
  return banca_;
}

std::string Feirante::GetFeira() const {
  return feira_;
}

std::string Feirante::GetSenhaHash() const {
  return senhaHash_;
}

// ---------------------------------------------------------
// Setters
// ---------------------------------------------------------

void Feirante::SetNome(const std::string& nome) {
  if (nome.empty()) {
    throw std::invalid_argument("Nome do feirante não pode ser vazio");
  }
  nome_ = nome;
}

void Feirante::SetBanca(const std::string& banca) {
  if (banca.empty()) {
    throw std::invalid_argument("Nome da banca não pode ser vazio");
  }
  banca_ = banca;
}

void Feirante::SetFeira(const std::string& feira) {
  if (feira.empty()) {
    throw std::invalid_argument("Nome da feira não pode ser vazio");
  }
  feira_ = feira;
}

// ---------------------------------------------------------
// Autenticação
// ---------------------------------------------------------

bool Feirante::ValidarSenha(const std::string& senha) const {
  std::string hashFornecido = GerarHash(senha);
  return hashFornecido == senhaHash_;
}

void Feirante::AlterarSenha(const std::string& senhaAntiga,
                            const std::string& senhaNova) {
  // Validar senha antiga
  if (!ValidarSenha(senhaAntiga)) {
    throw std::invalid_argument("Senha antiga incorreta");
  }

  // Validar senha nova
  if (senhaNova.empty()) {
    throw std::invalid_argument("Nova senha não pode ser vazia");
  }
  if (senhaNova.length() < 4) {
    throw std::invalid_argument("Nova senha deve ter no mínimo 4 caracteres");
  }

  // Atualizar hash
  senhaHash_ = GerarHash(senhaNova);
}

// ---------------------------------------------------------
// Serialização
// ---------------------------------------------------------

std::string Feirante::ParaJSON() const {
  std::stringstream ss;
  ss << "{\n";
  ss << "  \"nome\": \"" << nome_ << "\",\n";
  ss << "  \"banca\": \"" << banca_ << "\",\n";
  ss << "  \"feira\": \"" << feira_ << "\",\n";
  ss << "  \"senhaHash\": \"" << senhaHash_ << "\"\n";
  ss << "}";
  return ss.str();
}
