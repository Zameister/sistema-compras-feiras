/**
 * @file test_produto.cpp
 * @brief Testes unitários para a classe Produto
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 * 
 * Testes para Histórias de Usuário: EU001, EU002, EU004
 */

#include <gtest/gtest.h>
#include "produto.h"

// EU004: Teste de cadastro de produto
TEST(ProdutoTest, ConstrutroPadrao) {
  Produto p;
  EXPECT_EQ(p.GetNome(), "");
  EXPECT_EQ(p.GetPreco(), 0.0);
  EXPECT_EQ(p.GetCategoria(), "");
  EXPECT_EQ(p.GetFeira(), "");
}

// EU004: Teste de cadastro com parâmetros válidos
TEST(ProdutoTest, ConstrutorComParametros) {
  Produto p("Maçã", 5.50, "Frutas", "Feira da Torre");
  EXPECT_EQ(p.GetNome(), "Maçã");
  EXPECT_EQ(p.GetPreco(), 5.50);
  EXPECT_EQ(p.GetCategoria(), "Frutas");
  EXPECT_EQ(p.GetFeira(), "Feira da Torre");
}

// EU004: Teste de validação de preço negativo
TEST(ProdutoTest, PrecoNegativo) {
  EXPECT_THROW({
    Produto p("Banana", -1.0, "Frutas", "Feira da Torre");
  }, std::invalid_argument);
}

// EU004: Teste de validação de nome vazio
TEST(ProdutoTest, NomeVazio) {
  EXPECT_THROW({
    Produto p("", 5.0, "Frutas", "Feira da Torre");
  }, std::invalid_argument);
}

// EU001: Teste de obtenção de nome
TEST(ProdutoTest, GetNome) {
  Produto p("Tomate", 3.50, "Verduras", "Feira da Ceilândia");
  EXPECT_EQ(p.GetNome(), "Tomate");
}

// EU001: Teste de obtenção de preço
TEST(ProdutoTest, GetPreco) {
  Produto p("Alface", 2.00, "Verduras", "Feira da Ceilândia");
  EXPECT_DOUBLE_EQ(p.GetPreco(), 2.00);
}

// EU004: Teste de modificação de nome
TEST(ProdutoTest, SetNome) {
  Produto p("Laranja", 4.00, "Frutas", "Feira do Guará");
  p.SetNome("Tangerina");
  EXPECT_EQ(p.GetNome(), "Tangerina");
}

// EU004: Teste de modificação de preço
TEST(ProdutoTest, SetPreco) {
  Produto p("Abacaxi", 6.00, "Frutas", "Feira do Guará");
  p.SetPreco(7.50);
  EXPECT_DOUBLE_EQ(p.GetPreco(), 7.50);
}

// EU004: Teste de validação ao modificar nome vazio
TEST(ProdutoTest, SetNomeVazio) {
  Produto p("Uva", 8.00, "Frutas", "Feira da Torre");
  EXPECT_THROW({
    p.SetNome("");
  }, std::invalid_argument);
}

// EU004: Teste de validação ao modificar preço negativo
TEST(ProdutoTest, SetPrecoNegativo) {
  Produto p("Morango", 10.00, "Frutas", "Feira da Torre");
  EXPECT_THROW({
    p.SetPreco(-5.0);
  }, std::invalid_argument);
}

// EU004: Teste de categoria
TEST(ProdutoTest, GetSetCategoria) {
  Produto p("Cenoura", 3.00, "Legumes", "Feira da Asa Norte");
  EXPECT_EQ(p.GetCategoria(), "Legumes");
  
  p.SetCategoria("Verduras");
  EXPECT_EQ(p.GetCategoria(), "Verduras");
}

// EU004: Teste de feira
TEST(ProdutoTest, GetSetFeira) {
  Produto p("Batata", 4.50, "Legumes", "Feira da Ceilândia");
  EXPECT_EQ(p.GetFeira(), "Feira da Ceilândia");
  
  p.SetFeira("Feira do Guará");
  EXPECT_EQ(p.GetFeira(), "Feira do Guará");
}

// EU004: Teste de validação de categoria vazia
TEST(ProdutoTest, SetCategoriaVazia) {
  Produto p("Pimentão", 5.00, "Verduras", "Feira da Torre");
  EXPECT_THROW({
    p.SetCategoria("");
  }, std::invalid_argument);
}

// EU004: Teste de validação de feira vazia
TEST(ProdutoTest, SetFeiraVazia) {
  Produto p("Cebola", 2.50, "Temperos", "Feira da Asa Sul");
  EXPECT_THROW({
    p.SetFeira("");
  }, std::invalid_argument);
}
