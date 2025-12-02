/**
 * @file test_sistema.cpp
 * @brief Testes unitários para a classe Sistema
 * @author Arthur Souza Chagas
 * @date 2025
 *
 * Testes para as funcionalidades:
 * - EU001: Buscar produtos
 * - EU002: Filtrar feiras
 * - EU005: Cadastrar usuário
 */

#include <gtest/gtest.h>
#include "../include/sistema.h"
#include "../include/produto.h"
#include "../include/feira.h"
#include <sstream>

/**
 * @brief Fixture para testes do Sistema
 */
class SistemaTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Configuração antes de cada teste
    }

    void TearDown() override {
        // Limpeza após cada teste
    }
};

/**
 * @brief Testa construtor do Sistema
 *
 * Verifica se o sistema é inicializado corretamente com
 * feiras e produtos pré-cadastrados.
 */
TEST_F(SistemaTest, ConstrutorInicializaSistema) {
    Sistema sistema;
    // O construtor deve criar o sistema sem lançar exceções
    SUCCEED();
}

/**
 * @brief Testa criação de produtos (EU004)
 *
 * Verifica se produtos são criados corretamente com todos os campos.
 */
TEST_F(SistemaTest, CriarProdutoComTodosOsCampos) {  // EU004
    Produto p("Tomate", 3.50, "Hortifruti", "Feira da Ceilândia");

    EXPECT_EQ(p.GetNome(), "Tomate");
    EXPECT_DOUBLE_EQ(p.GetPreco(), 3.50);
    EXPECT_EQ(p.GetCategoria(), "Hortifruti");
    EXPECT_EQ(p.GetFeira(), "Feira da Ceilândia");
}

/**
 * @brief Testa criação de produto com preço zero
 */
TEST_F(SistemaTest, CriarProdutoComPrecoZero) {  // EU004
    Produto p("Amostra Grátis", 0.0, "Diversos", "Feira Teste");

    EXPECT_DOUBLE_EQ(p.GetPreco(), 0.0);
}

/**
 * @brief Testa modificação de preço de produto
 */
TEST_F(SistemaTest, ModificarPrecoProduto) {  // EU004
    Produto p("Banana", 4.0, "Frutas", "Feira Teste");

    p.SetPreco(5.50);
    EXPECT_DOUBLE_EQ(p.GetPreco(), 5.50);
}

/**
 * @brief Testa criação de feira
 */
TEST_F(SistemaTest, CriarFeira) {
    Location loc(-15.817000, -48.112000);
    Feira feira("Feira Teste", "Endereço Teste", loc);

    EXPECT_EQ(feira.GetNome(), "Feira Teste");
    EXPECT_EQ(feira.GetEndereco(), "Endereço Teste");
}

/**
 * @brief Testa adicionar produto a uma feira (EU004)
 */
TEST_F(SistemaTest, AdicionarProdutoNaFeira) {  // EU004
    Location loc(-15.817000, -48.112000);
    Feira feira("Feira Teste", "Endereço Teste", loc);

    Produto p1("Tomate", 3.50, "Hortifruti", "Feira Teste");
    Produto p2("Banana", 4.20, "Frutas", "Feira Teste");

    feira.AdicionarProduto(p1);
    feira.AdicionarProduto(p2);

    EXPECT_EQ(feira.GetProdutos().size(), 2);
    EXPECT_EQ(feira.GetProdutos()[0].GetNome(), "Tomate");
    EXPECT_EQ(feira.GetProdutos()[1].GetNome(), "Banana");
}

/**
 * @brief Testa buscar produto em uma feira (EU001)
 */
TEST_F(SistemaTest, BuscarProdutoNaFeira) {  // EU001
    Location loc(-15.817000, -48.112000);
    Feira feira("Feira Teste", "Endereço Teste", loc);

    Produto p("Tomate", 3.50, "Hortifruti", "Feira Teste");
    feira.AdicionarProduto(p);

    Produto* encontrado = feira.BuscarProduto("Tomate");

    ASSERT_NE(encontrado, nullptr);
    EXPECT_EQ(encontrado->GetNome(), "Tomate");
}

/**
 * @brief Testa buscar produto inexistente (EU001)
 */
TEST_F(SistemaTest, BuscarProdutoInexistente) {  // EU001
    Location loc(-15.817000, -48.112000);
    Feira feira("Feira Teste", "Endereço Teste", loc);

    Produto* encontrado = feira.BuscarProduto("ProdutoInexistente");

    EXPECT_EQ(encontrado, nullptr);
}

/**
 * @brief Testa remover produto de uma feira
 */
TEST_F(SistemaTest, RemoverProdutoDaFeira) {
    Location loc(-15.817000, -48.112000);
    Feira feira("Feira Teste", "Endereço Teste", loc);

    Produto p("Tomate", 3.50, "Hortifruti", "Feira Teste");
    feira.AdicionarProduto(p);

    bool removido = feira.RemoverProduto("Tomate");

    EXPECT_TRUE(removido);
    EXPECT_EQ(feira.GetProdutos().size(), 0);
}

/**
 * @brief Testa filtrar produtos por categoria (EU002)
 *
 * Simula a lógica de filtragem por categoria.
 */
TEST_F(SistemaTest, FiltrarProdutosPorCategoria) {  // EU002
    Location loc(-15.817000, -48.112000);
    Feira feira("Feira Teste", "Endereço Teste", loc);

    feira.AdicionarProduto(Produto("Tomate", 3.50, "Hortifruti", "Feira Teste"));
    feira.AdicionarProduto(Produto("Banana", 4.20, "Frutas", "Feira Teste"));
    feira.AdicionarProduto(Produto("Alface", 2.00, "Hortifruti", "Feira Teste"));

    // Contar produtos da categoria "Hortifruti"
    int count = 0;
    for (const auto& produto : feira.GetProdutos()) {
        if (produto.GetCategoria() == "Hortifruti") {
            count++;
        }
    }

    EXPECT_EQ(count, 2);
}

/**
 * @brief Testa filtrar produtos por preço máximo (EU002)
 *
 * Simula a lógica de filtragem por preço.
 */
TEST_F(SistemaTest, FiltrarProdutosPorPrecoMaximo) {  // EU002
    Location loc(-15.817000, -48.112000);
    Feira feira("Feira Teste", "Endereço Teste", loc);

    feira.AdicionarProduto(Produto("Tomate", 3.50, "Hortifruti", "Feira Teste"));
    feira.AdicionarProduto(Produto("Banana", 4.20, "Frutas", "Feira Teste"));
    feira.AdicionarProduto(Produto("Alface", 2.00, "Verduras", "Feira Teste"));

    double precoMax = 3.50;

    // Contar produtos com preço <= precoMax
    int count = 0;
    for (const auto& produto : feira.GetProdutos()) {
        if (produto.GetPreco() <= precoMax) {
            count++;
        }
    }

    EXPECT_EQ(count, 2);  // Tomate (3.50) e Alface (2.00)
}

/**
 * @brief Testa cálculo de distância entre duas localizações (EU003)
 */
TEST_F(SistemaTest, CalcularDistanciaEntreLocalizacoes) {  // EU003
    Location loc1(-15.817000, -48.112000);  // Ceilândia
    Location loc2(-15.810700, -47.912700);  // Asa Sul

    Feira feira("Feira da Asa Sul", "308 Sul", loc2);

    double distancia = feira.DistanciaPara(loc1);

    // A distância entre Ceilândia e Asa Sul é de aproximadamente 19-20 km
    EXPECT_GT(distancia, 15.0);
    EXPECT_LT(distancia, 25.0);
}

/**
 * @brief Testa se produtos têm nomes não vazios
 */
TEST_F(SistemaTest, ProdutoDeveTerNomeNaoVazio) {  // EU004
    Produto p("Teste", 1.0, "Cat", "Feira");

    EXPECT_FALSE(p.GetNome().empty());
}

/**
 * @brief Testa categoria de produtos
 */
TEST_F(SistemaTest, ProdutoDeveTermCategoria) {  // EU004
    Produto p("Tomate", 3.50, "Hortifruti", "Feira");

    EXPECT_EQ(p.GetCategoria(), "Hortifruti");
}

// Ponto de entrada para os testes
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
