/**
 * @file test_feirante_simple.cpp
 * @brief Teste simples da classe Feirante (sem Google Test)
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 *
 * Teste manual para verificar funcionalidade básica (TDD - Fase GREEN)
 */

#include <iostream>
#include <cassert>
#include "feirante.h"

void testarConstrutorPadrao() {
  Feirante f;
  assert(f.GetNome() == "");
  assert(f.GetBanca() == "");
  assert(f.GetFeira() == "");
  assert(f.GetSenhaHash() == "");
  std::cout << "✅ Construtor padrão OK" << std::endl;
}

void testarConstrutorComParametros() {
  Feirante f("João Silva", "Frutas do João", "Feira da Ceilândia", "senha123");
  assert(f.GetNome() == "João Silva");
  assert(f.GetBanca() == "Frutas do João");
  assert(f.GetFeira() == "Feira da Ceilândia");
  assert(f.GetSenhaHash() != "senha123");  // Deve estar hasheada
  assert(!f.GetSenhaHash().empty());
  std::cout << "✅ Construtor com parâmetros OK" << std::endl;
}

void testarValidacaoNomeVazio() {
  try {
    Feirante f("", "Banca", "Feira", "senha");
    assert(false);  // Não deve chegar aqui
  } catch (const std::invalid_argument& e) {
    std::cout << "✅ Validação nome vazio OK: " << e.what() << std::endl;
  }
}

void testarValidacaoSenhaCurta() {
  try {
    Feirante f("João", "Banca", "Feira", "123");
    assert(false);  // Não deve chegar aqui
  } catch (const std::invalid_argument& e) {
    std::cout << "✅ Validação senha curta OK: " << e.what() << std::endl;
  }
}

void testarGettersSetters() {
  Feirante f("Pedro", "Carnes", "Feira 1", "senha456");
  f.SetNome("Pedro Junior");
  assert(f.GetNome() == "Pedro Junior");
  f.SetBanca("Carnes Premium");
  assert(f.GetBanca() == "Carnes Premium");
  f.SetFeira("Feira 2");
  assert(f.GetFeira() == "Feira 2");
  std::cout << "✅ Getters e Setters OK" << std::endl;
}

void testarValidarSenha() {
  Feirante f("Maria", "Verduras", "Feira 3", "minhasenha123");
  assert(f.ValidarSenha("minhasenha123") == true);
  assert(f.ValidarSenha("senhaerrada") == false);
  std::cout << "✅ Validação de senha OK" << std::endl;
}

void testarAlterarSenha() {
  Feirante f("Carlos", "Temperos", "Feira 4", "senhaantiga");
  f.AlterarSenha("senhaantiga", "senhanova123");
  assert(f.ValidarSenha("senhaantiga") == false);
  assert(f.ValidarSenha("senhanova123") == true);
  std::cout << "✅ Alteração de senha OK" << std::endl;
}

void testarAlterarSenhaErrada() {
  try {
    Feirante f("Ana", "Grãos", "Feira 5", "senhareal");
    f.AlterarSenha("senhaerrada", "senhanova");
    assert(false);  // Não deve chegar aqui
  } catch (const std::invalid_argument& e) {
    std::cout << "✅ Alteração com senha errada bloqueada OK: " << e.what() << std::endl;
  }
}

void testarParaJSON() {
  Feirante f("Rafael", "Laticínios", "Feira 6", "senha789");
  std::string json = f.ParaJSON();
  assert(json.find("Rafael") != std::string::npos);
  assert(json.find("Laticínios") != std::string::npos);
  assert(json.find("Feira 6") != std::string::npos);
  assert(json.find("senha789") == std::string::npos);  // Não deve ter senha em texto puro
  std::cout << "✅ Serialização JSON OK" << std::endl;
  std::cout << "   JSON gerado:\n" << json << std::endl;
}

int main() {
  std::cout << "\n🧪 Testando classe Feirante (TDD - Fase GREEN)\n" << std::endl;
  std::cout << "Histórias de Usuário: EU004, EU005\n" << std::endl;

  testarConstrutorPadrao();
  testarConstrutorComParametros();
  testarValidacaoNomeVazio();
  testarValidacaoSenhaCurta();
  testarGettersSetters();
  testarValidarSenha();
  testarAlterarSenha();
  testarAlterarSenhaErrada();
  testarParaJSON();

  std::cout << "\n🎉 Todos os testes passaram! (Fase GREEN completa)" << std::endl;
  std::cout << "✅ Classe Feirante implementada com sucesso seguindo TDD" << std::endl;

  return 0;
}
