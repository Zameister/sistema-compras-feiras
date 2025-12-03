/**
 * @file test_feirante.cpp
 * @brief Testes unitarios para a classe Feirante
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 *
 * Testes para Historias de Usuario: EU004, EU005
 * Desenvolvido seguindo TDD (Test-Driven Development)
 */

#include <gtest/gtest.h>
#include "feirante.h"

// EU004: Teste de construtor padrao
TEST(FeiranteTest, ConstrutroPadrao) {
  Feirante f;
  EXPECT_EQ(f.GetNome(), "");
  EXPECT_EQ(f.GetBanca(), "");
  EXPECT_EQ(f.GetFeira(), "");
  EXPECT_EQ(f.GetSenhaHash(), "");
}

// EU004: Teste de construtor com parametros validos
TEST(FeiranteTest, ConstrutorComParametros) {
  Feirante f("Joao Silva", "Frutas do Joao", "Feira da Ceilandia", "senha123");
  EXPECT_EQ(f.GetNome(), "Joao Silva");
  EXPECT_EQ(f.GetBanca(), "Frutas do Joao");
  EXPECT_EQ(f.GetFeira(), "Feira da Ceilandia");
  // Senha deve ser hashada, nao em texto puro
  EXPECT_NE(f.GetSenhaHash(), "senha123");
  EXPECT_FALSE(f.GetSenhaHash().empty());
}

// EU004: Teste de validacao de nome vazio
TEST(FeiranteTest, NomeVazio) {
  EXPECT_THROW({
    Feirante f("", "Banca Teste", "Feira Teste", "senha");
  }, std::invalid_argument);
}

// EU004: Teste de validacao de banca vazia
TEST(FeiranteTest, BancaVazia) {
  EXPECT_THROW({
    Feirante f("Joao", "", "Feira Teste", "senha");
  }, std::invalid_argument);
}

// EU004: Teste de validacao de feira vazia
TEST(FeiranteTest, FeiraVazia) {
  EXPECT_THROW({
    Feirante f("Joao", "Banca", "", "senha");
  }, std::invalid_argument);
}

// EU004: Teste de validacao de senha vazia
TEST(FeiranteTest, SenhaVazia) {
  EXPECT_THROW({
    Feirante f("Joao", "Banca", "Feira", "");
  }, std::invalid_argument);
}

// EU004: Teste de senha muito curta
TEST(FeiranteTest, SenhaCurta) {
  EXPECT_THROW({
    Feirante f("Joao", "Banca", "Feira", "123");  // Minimo 4 caracteres
  }, std::invalid_argument);
}

// EU004: Teste de obtencao de nome
TEST(FeiranteTest, GetNome) {
  Feirante f("Maria Santos", "Verduras da Maria", "Feira de Taguatinga", "senha123");
  EXPECT_EQ(f.GetNome(), "Maria Santos");
}

// EU004: Teste de obtencao de banca
TEST(FeiranteTest, GetBanca) {
  Feirante f("Carlos Pereira", "Temperos do Carlos", "Feira do Plano Piloto", "senha456");
  EXPECT_EQ(f.GetBanca(), "Temperos do Carlos");
}

// EU004: Teste de obtencao de feira
TEST(FeiranteTest, GetFeira) {
  Feirante f("Ana Costa", "Graos da Ana", "Feira de Samambaia", "senha789");
  EXPECT_EQ(f.GetFeira(), "Feira de Samambaia");
}

// EU004: Teste de modificacao de nome
TEST(FeiranteTest, SetNome) {
  Feirante f("Pedro Alves", "Carnes do Pedro", "Feira de Aguas Claras", "senha123");
  f.SetNome("Pedro Alves Junior");
  EXPECT_EQ(f.GetNome(), "Pedro Alves Junior");
}

// EU004: Teste de modificacao de banca
TEST(FeiranteTest, SetBanca) {
  Feirante f("Lucia Fernandes", "Padaria da Lucia", "Feira da Ceilandia", "senha123");
  f.SetBanca("Panificadora da Lucia");
  EXPECT_EQ(f.GetBanca(), "Panificadora da Lucia");
}

// EU004: Teste de modificacao de feira
TEST(FeiranteTest, SetFeira) {
  Feirante f("Roberto Lima", "Laticinios do Roberto", "Feira de Taguatinga", "senha123");
  f.SetFeira("Feira do Plano Piloto");
  EXPECT_EQ(f.GetFeira(), "Feira do Plano Piloto");
}

// EU004: Teste de validacao ao modificar nome vazio
TEST(FeiranteTest, SetNomeVazio) {
  Feirante f("Fernanda Souza", "Hortifruti da Fernanda", "Feira de Samambaia", "senha123");
  EXPECT_THROW({
    f.SetNome("");
  }, std::invalid_argument);
}

// EU004: Teste de validacao ao modificar banca vazia
TEST(FeiranteTest, SetBancaVazia) {
  Feirante f("Ricardo Gomes", "Graos do Ricardo", "Feira de Aguas Claras", "senha123");
  EXPECT_THROW({
    f.SetBanca("");
  }, std::invalid_argument);
}

// EU004: Teste de validacao ao modificar feira vazia
TEST(FeiranteTest, SetFeiraVazia) {
  Feirante f("Juliana Martins", "Frutas da Juliana", "Feira da Ceilandia", "senha123");
  EXPECT_THROW({
    f.SetFeira("");
  }, std::invalid_argument);
}

// EU005: Teste de validacao de senha
TEST(FeiranteTest, ValidarSenhaCorreta) {
  Feirante f("Marcos Silva", "Temperos do Marcos", "Feira de Taguatinga", "minhasenha123");
  EXPECT_TRUE(f.ValidarSenha("minhasenha123"));
}

// EU005: Teste de validacao de senha incorreta
TEST(FeiranteTest, ValidarSenhaIncorreta) {
  Feirante f("Patricia Costa", "Verduras da Patricia", "Feira do Plano Piloto", "senha456");
  EXPECT_FALSE(f.ValidarSenha("senhaerrada"));
}

// EU005: Teste de alteracao de senha
TEST(FeiranteTest, AlterarSenha) {
  Feirante f("Gustavo Oliveira", "Carnes do Gustavo", "Feira de Samambaia", "senhaantiga");

  // Alterar senha
  f.AlterarSenha("senhaantiga", "senhanova123");

  // Senha antiga nao deve funcionar
  EXPECT_FALSE(f.ValidarSenha("senhaantiga"));

  // Senha nova deve funcionar
  EXPECT_TRUE(f.ValidarSenha("senhanova123"));
}

// EU005: Teste de alteracao de senha com senha antiga incorreta
TEST(FeiranteTest, AlterarSenhaComSenhaAntigaIncorreta) {
  Feirante f("Beatriz Santos", "Padaria da Beatriz", "Feira de Aguas Claras", "senhareal");

  EXPECT_THROW({
    f.AlterarSenha("senhaerrada", "senhanova");
  }, std::invalid_argument);
}

// EU005: Teste de alteracao de senha com senha nova muito curta
TEST(FeiranteTest, AlterarSenhaComSenhaNovaCurta) {
  Feirante f("Rafael Lima", "Laticinios do Rafael", "Feira da Ceilandia", "senha123");

  EXPECT_THROW({
    f.AlterarSenha("senha123", "123");  // Muito curta
  }, std::invalid_argument);
}

// EU004: Teste de serializacao para JSON
TEST(FeiranteTest, ParaJSON) {
  Feirante f("Amanda Pereira", "Hortifruti da Amanda", "Feira de Taguatinga", "senha789");
  std::string json = f.ParaJSON();

  // JSON deve conter os dados do feirante
  EXPECT_NE(json.find("Amanda Pereira"), std::string::npos);
  EXPECT_NE(json.find("Hortifruti da Amanda"), std::string::npos);
  EXPECT_NE(json.find("Feira de Taguatinga"), std::string::npos);

  // JSON NAO deve conter senha em texto puro
  EXPECT_EQ(json.find("senha789"), std::string::npos);
}
