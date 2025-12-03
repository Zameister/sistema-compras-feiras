/**
 * @file test_produto.cpp
 * @brief Testes unitarios para a classe Produto
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 * 
 * Testes para Historias de Usuario: EU001, EU002, EU004
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

// EU004: Teste de cadastro com parametros validos
TEST(ProdutoTest, ConstrutorComParametros) {
  Produto p("Maca", 5.50, "Frutas", "Feira da Torre");
  EXPECT_EQ(p.GetNome(), "Maca");
  EXPECT_EQ(p.GetPreco(), 5.50);
  EXPECT_EQ(p.GetCategoria(), "Frutas");
  EXPECT_EQ(p.GetFeira(), "Feira da Torre");
}

// EU004: Teste de validacao de preco negativo
TEST(ProdutoTest, PrecoNegativo) {
  EXPECT_THROW({
    Produto p("Banana", -1.0, "Frutas", "Feira da Torre");
  }, std::invalid_argument);
}

// EU004: Teste de validacao de nome vazio
TEST(ProdutoTest, NomeVazio) {
  EXPECT_THROW({
    Produto p("", 5.0, "Frutas", "Feira da Torre");
  }, std::invalid_argument);
}

// EU001: Teste de obtencao de nome
TEST(ProdutoTest, GetNome) {
  Produto p("Tomate", 3.50, "Verduras", "Feira da Ceilandia");
  EXPECT_EQ(p.GetNome(), "Tomate");
}

// EU001: Teste de obtencao de preco
TEST(ProdutoTest, GetPreco) {
  Produto p("Alface", 2.00, "Verduras", "Feira da Ceilandia");
  EXPECT_DOUBLE_EQ(p.GetPreco(), 2.00);
}

// EU004: Teste de modificacao de nome
TEST(ProdutoTest, SetNome) {
  Produto p("Laranja", 4.00, "Frutas", "Feira do Guara");
  p.SetNome("Tangerina");
  EXPECT_EQ(p.GetNome(), "Tangerina");
}

// EU004: Teste de modificacao de preco
TEST(ProdutoTest, SetPreco) {
  Produto p("Abacaxi", 6.00, "Frutas", "Feira do Guara");
  p.SetPreco(7.50);
  EXPECT_DOUBLE_EQ(p.GetPreco(), 7.50);
}

// EU004: Teste de validacao ao modificar nome vazio
TEST(ProdutoTest, SetNomeVazio) {
  Produto p("Uva", 8.00, "Frutas", "Feira da Torre");
  EXPECT_THROW({
    p.SetNome("");
  }, std::invalid_argument);
}

// EU004: Teste de validacao ao modificar preco negativo
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
  Produto p("Batata", 4.50, "Legumes", "Feira da Ceilandia");
  EXPECT_EQ(p.GetFeira(), "Feira da Ceilandia");
  
  p.SetFeira("Feira do Guara");
  EXPECT_EQ(p.GetFeira(), "Feira do Guara");
}

// EU004: Teste de validacao de categoria vazia
TEST(ProdutoTest, SetCategoriaVazia) {
  Produto p("Pimentao", 5.00, "Verduras", "Feira da Torre");
  EXPECT_THROW({
    p.SetCategoria("");
  }, std::invalid_argument);
}

// EU004: Teste de validacao de feira vazia
TEST(ProdutoTest, SetFeiraVazia) {
  Produto p("Cebola", 2.50, "Temperos", "Feira da Asa Sul");
  EXPECT_THROW({
    p.SetFeira("");
  }, std::invalid_argument);
}
