/**
 * @file test_feirante_simple.cpp
 * @brief Teste simples da classe Feirante (sem Google Test)
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 *
 * Teste manual para verificar funcionalidade basica (TDD - Fase GREEN)
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
  std::cout << "✅ Construtor padrao OK" << std::endl;
}

void testarConstrutorComParametros() {
  Feirante f("Joao Silva", "Frutas do Joao", "Feira da Ceilandia", "senha123");
  assert(f.GetNome() == "Joao Silva");
  assert(f.GetBanca() == "Frutas do Joao");
  assert(f.GetFeira() == "Feira da Ceilandia");
  assert(f.GetSenhaHash() != "senha123");  // Deve estar hasheada
  assert(!f.GetSenhaHash().empty());
  std::cout << "✅ Construtor com parametros OK" << std::endl;
}

void testarValidacaoNomeVazio() {
  try {
    Feirante f("", "Banca", "Feira", "senha");
    assert(false);  // Nao deve chegar aqui
  } catch (const std::invalid_argument& e) {
    std::cout << "✅ Validacao nome vazio OK: " << e.what() << std::endl;
  }
}

void testarValidacaoSenhaCurta() {
  try {
    Feirante f("Joao", "Banca", "Feira", "123");
    assert(false);  // Nao deve chegar aqui
  } catch (const std::invalid_argument& e) {
    std::cout << "✅ Validacao senha curta OK: " << e.what() << std::endl;
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
  std::cout << "✅ Validacao de senha OK" << std::endl;
}

void testarAlterarSenha() {
  Feirante f("Carlos", "Temperos", "Feira 4", "senhaantiga");
  f.AlterarSenha("senhaantiga", "senhanova123");
  assert(f.ValidarSenha("senhaantiga") == false);
  assert(f.ValidarSenha("senhanova123") == true);
  std::cout << "✅ Alteracao de senha OK" << std::endl;
}

void testarAlterarSenhaErrada() {
  try {
    Feirante f("Ana", "Graos", "Feira 5", "senhareal");
    f.AlterarSenha("senhaerrada", "senhanova");
    assert(false);  // Nao deve chegar aqui
  } catch (const std::invalid_argument& e) {
    std::cout << "✅ Alteracao com senha errada bloqueada OK: " << e.what() << std::endl;
  }
}

void testarParaJSON() {
  Feirante f("Rafael", "Laticinios", "Feira 6", "senha789");
  std::string json = f.ParaJSON();
  assert(json.find("Rafael") != std::string::npos);
  assert(json.find("Laticinios") != std::string::npos);
  assert(json.find("Feira 6") != std::string::npos);
  assert(json.find("senha789") == std::string::npos);  // Nao deve ter senha em texto puro
  std::cout << "✅ Serializacao JSON OK" << std::endl;
  std::cout << "   JSON gerado:\n" << json << std::endl;
}

int main() {
  std::cout << "\n🧪 Testando classe Feirante (TDD - Fase GREEN)\n" << std::endl;
  std::cout << "Historias de Usuario: EU004, EU005\n" << std::endl;

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
