# Como Fizemos o Projeto

## Quem Somos
- **Luidgi Varela Carneiro** - 231011669
- **Arthur Souza Chagas** - 221037385

---

## O Que Fizemos

Criamos um sistema web de compras em feiras. O usuário pode buscar produtos, ver preços, calcular distâncias e enviar mensagens para feirantes. Os feirantes gerenciam seus produtos e respondem clientes. O admin vê relatórios e gerencia tudo.

---

## Histórias de Usuário

São as funcionalidades que o usuário pediu. Cada uma tem um código (EU001, EU002...).

### Para Usuários Comuns
- **EU001:** Buscar produtos por nome
- **EU002:** Ordenar por preço, distância ou avaliação
- **EU003:** Filtrar por feira ou distância máxima

### Para Feirantes
- **EU004:** Cadastrar produtos (nome, preço, categoria)
- **EU005:** Ver e responder mensagens dos clientes

### Para Administradores
- **EU006:** Criar e gerenciar categorias
- **EU007:** Gerar relatórios (top produtos, estatísticas)

---

## TDD (Test-Driven Development)

**O que é:** Escrever os testes ANTES de escrever o código.

**Como fizemos:**
1. **RED:** Escrevemos testes que falham (porque o código ainda não existe)
2. **GREEN:** Escrevemos o código mínimo para passar nos testes
3. **REFACTOR:** Melhoramos o código mantendo os testes passando

**Exemplo prático:**
```cpp
// 1. RED - Teste que falha
TEST(FeiranteTest, CriarFeirante) {
  Feirante f("João", "Banca do João", "Feira 1", "senha123");
  EXPECT_EQ(f.GetNome(), "João");  // FALHA - classe não existe ainda
}

// 2. GREEN - Implementamos o mínimo
class Feirante {
  string nome_;
  Feirante(string nome) : nome_(nome) {}
  string GetNome() { return nome_; }
};  // PASSA!

// 3. REFACTOR - Melhoramos depois
```

**Por que TDD?**
- Garante que o código funciona
- Facilita mudanças (os testes protegem contra bugs)
- Documentação viva (os testes mostram como usar)

---

## Linguagem e Padrão de Código

### Linguagem Escolhida
**C++17** - Linguagem moderna, rápida e poderosa.

**Por que C++?**
- Performance (importante para servidor web)
- Orientação a objetos (organiza bem o código)
- Amplamente usada na indústria

### Padrão de Codificação
Seguimos o **Google C++ Style Guide**: https://google.github.io/styleguide/cppguide.html

**Principais regras:**
- Nomes de classes começam com maiúscula: `Feirante`, `Produto`
- Nomes de funções em CamelCase: `GetNome()`, `AdicionarProduto()`
- Variáveis privadas terminam com `_`: `nome_`, `preco_`
- Sempre usar `const` quando possível
- 2 espaços de indentação (não tabs)

**Exemplo:**
```cpp
class Produto {
 private:
  std::string nome_;    // ✅ Variável privada com _
  double preco_;

 public:
  std::string GetNome() const { return nome_; }  // ✅ CamelCase e const
  void SetPreco(double p) { preco_ = p; }
};
```

---

## Verificadores de Código

### 1. CPPCheck (Análise Estática)
Encontra bugs sem rodar o código.

**Como usar:**
```bash
cppcheck --enable=warning --std=c++17 src/ include/
```

**O que verifica:**
- Vazamento de memória
- Divisão por zero
- Variáveis não inicializadas
- Código morto (nunca executado)

### 2. CPPLint (Verificador de Estilo)
Verifica se o código segue o Google Style Guide.

**Como usar:**
```bash
cpplint --recursive src/ include/
```

**O que verifica:**
- Espaçamento e indentação
- Nomes de variáveis/funções
- Comentários e documentação
- Include guards

---

## Bibliotecas e Frameworks

### 1. Google Test (GTest)
Framework de testes unitários.

**Como funciona:**
```cpp
TEST(ProdutoTest, PrecoPositivo) {
  Produto p("Maçã", 5.0);
  EXPECT_GT(p.GetPreco(), 0);  // Espera que preço seja > 0
}
```

**Instalação (Windows):**
```bash
# Baixar do GitHub
git clone https://github.com/google/googletest.git
cd googletest
mkdir build && cd build
cmake .. && make
```

### 2. Bootstrap (Frontend)
Framework CSS para interface bonita e responsiva.

**Por que usar:**
- Componentes prontos (botões, modais, tabelas)
- Design responsivo (funciona em mobile)
- Documentação excelente

### 3. Winsock2 (Windows)
Biblioteca para sockets (comunicação de rede) no Windows.

**Como usar:**
```cpp
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
```

---

## Controle de Versão

### GitHub
Repositório: https://github.com/Zameister/sistema-compras-feiras

**Branches:**
- `main` - Código estável (produção)
- `feature/arthur` - Features em desenvolvimento

**Workflow:**
1. Criar branch para cada funcionalidade
2. Fazer commits pequenos e frequentes
3. Push para GitHub
4. Mesclar na `main` quando estiver pronto

**Padrão de Commits:**
```bash
test: criar testes para Feirante (TDD - RED)
feat: implementar classe Feirante (TDD - GREEN)
docs: atualizar documentação
fix: corrigir bug na validação
```

---

## Cobertura de Testes

### GCov
Ferramenta que mede quantas linhas do código foram testadas.

**Como usar:**
```bash
make coverage
```

**O que mostra:**
- % de linhas executadas
- % de funções testadas
- Quais linhas NÃO foram testadas (em vermelho)

**Exemplo de saída:**
```
File 'src/produto.cpp'
Lines executed: 92.5% of 80
Functions executed: 100% of 12
```

**Meta:** Mínimo 80% de cobertura.

---

## Documentação

### Doxygen
Gera documentação HTML a partir dos comentários no código.

**Como documentar:**
```cpp
/**
 * @brief Calcula o preço total com desconto
 * @param preco Preço original
 * @param desconto Percentual de desconto (0-100)
 * @return Preço final com desconto aplicado
 *
 * @pre preco deve ser positivo
 * @pre desconto deve estar entre 0 e 100
 * @post Retorna preço >= 0
 */
double CalcularPrecoComDesconto(double preco, double desconto);
```

**Gerar documentação:**
```bash
make docs
```

Abre em: `docs/html/index.html`

---

## Arquitetura: Backend + Frontend

### Backend (C++)
Servidor HTTP que responde requisições.

**Responsabilidades:**
- Servir arquivos HTML/CSS/JS
- Fornecer API REST para dados (produtos, feiras)
- Calcular distâncias (fórmula de Haversine)

**Estrutura:**
```
src/
├── webserver.cpp    → Servidor HTTP na porta 8080
├── database.cpp     → Lê/escreve JSON
├── produto.cpp      → Classe Produto
├── feirante.cpp     → Classe Feirante
├── feira.cpp        → Classe Feira
└── sistema.cpp      → Lógica de negócio
```

**Exemplo de endpoint:**
```cpp
// GET /api/produtos
if (path == "/api/produtos") {
  std::string json = sistema.ListarProdutos();
  SendResponse(clientSocket, json, "application/json");
}
```

### Frontend (HTML/CSS/JavaScript)
Interface web que o usuário vê.

**Tecnologias:**
- HTML5 - Estrutura das páginas
- CSS3 + Bootstrap - Estilização
- JavaScript (Vanilla) - Interatividade

**Páginas:**
```
web/
├── login.html       → Login e cadastro
├── index.html       → Catálogo de produtos (usuário)
├── feirante.html    → Painel do feirante
├── admin.html       → Painel do administrador
├── app.js           → Lógica do catálogo
├── login.js         → Lógica de autenticação
├── feirante.js      → Lógica do painel feirante
└── admin.js         → Lógica do painel admin
```

**Como funciona:**
```javascript
// Frontend faz requisição
fetch('http://localhost:8080/api/produtos')
  .then(res => res.json())
  .then(produtos => {
    // Exibe produtos na tela
    produtos.forEach(p => mostrarProduto(p));
  });

// Backend responde com JSON
{
  "produtos": [
    {"nome": "Maçã", "preco": 5.0, "feira": "Ceilândia"},
    {"nome": "Banana", "preco": 3.0, "feira": "Taguatinga"}
  ]
}
```

**Fluxo completo:**
```
Usuário clica no botão "Buscar"
    ↓
JavaScript captura o evento
    ↓
Faz requisição HTTP para backend (fetch)
    ↓
Backend C++ recebe e processa
    ↓
Retorna JSON com dados
    ↓
JavaScript renderiza na tela
```

---

## Estrutura do Projeto

```
sistema-compras-feiras/
│
├── src/                     # Código fonte C++
│   ├── webserver.cpp        # Servidor HTTP
│   ├── produto.cpp          # Classe Produto
│   ├── feirante.cpp         # Classe Feirante (TDD!)
│   ├── feira.cpp            # Classe Feira
│   ├── database.cpp         # Persistência JSON
│   └── sistema.cpp          # Lógica de negócio
│
├── include/                 # Headers (.h)
│   ├── produto.h
│   ├── feirante.h
│   └── ...
│
├── tests/                   # Testes unitários
│   ├── test_produto.cpp     # Testes do Produto
│   ├── test_feirante.cpp    # Testes do Feirante (TDD)
│   └── test_sistema.cpp     # Testes do Sistema
│
├── web/                     # Interface web
│   ├── login.html           # Tela de login
│   ├── index.html           # Catálogo
│   ├── feirante.html        # Painel feirante
│   ├── admin.html           # Painel admin
│   └── *.js, *.css          # Scripts e estilos
│
├── data/                    # Dados persistentes
│   ├── feiras.json          # Lista de feiras
│   └── produtos.json        # Lista de produtos
│
├── bin/                     # Executáveis compilados
│   └── webserver.exe
│
├── Makefile                 # Automação de build
├── README.md                # Documentação principal
├── COMO_RODAR.md            # Como executar
└── DESENVOLVIMENTO.md       # Este arquivo!
```

---

## Ferramentas de Build

### Makefile
Automatiza compilação, testes e verificações.

**Comandos principais:**
```bash
make              # Compila o projeto
make test         # Roda os testes
make coverage     # Verifica cobertura
make docs         # Gera documentação
make clean        # Remove arquivos temporários
```

**Exemplo de regra do Makefile:**
```makefile
# Compilar webserver
$(BIN_DIR)/webserver: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lws2_32
```

---

## Fluxo de Desenvolvimento

1. **Planejamento:** Definir história de usuário
2. **TDD RED:** Escrever testes que falham
3. **TDD GREEN:** Implementar código mínimo
4. **TDD REFACTOR:** Melhorar código
5. **Verificação:** Rodar cpplint e cppcheck
6. **Cobertura:** Garantir > 80% com gcov
7. **Documentação:** Adicionar comentários Doxygen
8. **Commit:** Fazer commit descritivo
9. **Push:** Enviar para GitHub

**Ciclo completo para adicionar uma funcionalidade:**
```bash
# 1. Escrever teste
vim tests/test_nova_feature.cpp

# 2. Compilar e ver falhar (RED)
make test
# FAILED!

# 3. Implementar funcionalidade
vim src/nova_feature.cpp

# 4. Compilar e ver passar (GREEN)
make test
# PASSED!

# 5. Verificar estilo
cpplint src/nova_feature.cpp

# 6. Verificar cobertura
make coverage

# 7. Gerar docs
make docs

# 8. Commit
git add .
git commit -m "test/feat: adicionar nova feature (TDD)"

# 9. Push
git push origin feature/arthur
```

---

## Conclusão

Desenvolvemos um sistema completo seguindo boas práticas:
- ✅ TDD (testes antes do código)
- ✅ Padrão Google C++ Style Guide
- ✅ Verificadores automatizados (cpplint, cppcheck)
- ✅ Cobertura de testes > 80%
- ✅ Documentação completa (Doxygen)
- ✅ Controle de versão (Git/GitHub)
- ✅ Arquitetura limpa (backend C++ + frontend web)

O resultado é um código confiável, bem testado e fácil de manter.
