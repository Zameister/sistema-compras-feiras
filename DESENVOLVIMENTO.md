# Como Fizemos o Projeto

## Quem Somos
- **Luidgi Varela Carneiro** - 231011669
- **Arthur Souza Chagas** - 221037385

---

## O Que Fizemos

Sistema web de compras em feiras onde usuários buscam produtos, comparam preços e distâncias. Feirantes cadastram produtos e respondem mensagens. Admin gerencia tudo e vê relatórios.

---

## Histórias de Usuário (7 no total)

### Usuários
- **EU001:** Buscar produtos por nome
- **EU002:** Ordenar por preço, distância ou nota
- **EU003:** Filtrar por feira ou distância máxima

### Feirantes
- **EU004:** Cadastrar produtos
- **EU005:** Ver e responder mensagens

### Admin
- **EU006:** Gerenciar categorias e permissões
- **EU007:** Gerar relatórios e estatísticas

Todas implementadas no backend C++ e frontend JavaScript com API REST.

---

## TDD (Test-Driven Development)

Escrevemos os testes ANTES do código:

1. **RED:** Teste que falha
2. **GREEN:** Código mínimo pra passar
3. **REFACTOR:** Melhorar mantendo testes

**Resultados:**
- 30 testes passando
- 89.04% de cobertura com gcov
- 0 erros no cppcheck

---

## Assertivas (Design by Contract)

Documentamos o que cada função espera e garante:

```cpp
/**
 * @pre nome não pode ser vazio
 * @pre senha deve ter no mínimo 4 caracteres
 * @post Feirante criado com senha hasheada
 */
```

**Total:** 161 assertivas (@pre/@post) em todas as funções.

---

## Linguagem e Ferramentas

### Linguagem
**C++17** - Performance e orientação a objetos

### Compilador
- Windows: MinGW/g++
- Linux/Mac: g++

### Verificadores

#### gcov (Cobertura de Testes)
```bash
mingw32-make coverage
# Resultado: 89.04% de cobertura
```

#### cppcheck (Análise Estática)
```bash
mingw32-make static-analysis
# Resultado: 0 problemas encontrados
```

#### cpplint (Estilo de Código)
```bash
mingw32-make style-check
# Verifica padrões do Google C++ Style Guide
```

Todos os três verificadores funcionando perfeitamente.

---

## Documentação Doxygen

Geramos documentação HTML completa com Doxygen:

```bash
mingw32-make docs
# Gera: docs/html/index.html
```

**Características:**
- Comentários estilo Javadoc (`/** */`)
- 100% do código documentado
- 63 páginas HTML geradas
- Busca integrada
- Código fonte navegável

Para ver: abrir `docs/html/index.html` no navegador.

---

## Arquitetura do Projeto

### Backend (C++)
```
include/        # Headers (.h)
src/           # Implementações (.cpp)
  - main.cpp          # Ponto de entrada
  - sistema.cpp       # Lógica principal
  - webserver.cpp     # Servidor HTTP
  - feira.cpp         # Gerencia feiras
  - feirante.cpp      # Gerencia feirantes
  - produto.cpp       # Gerencia produtos
  - usuario.cpp       # Gerencia usuários
```

### Frontend (HTML/JS)
```
web/
  - index.html        # Página do usuário
  - feirante.html     # Página do feirante
  - admin.html        # Página do admin
  - app.js           # Lógica do usuário
  - feirante.js      # Lógica do feirante
  - admin.js         # Lógica do admin
```

### Integração
Backend C++ expõe API REST que o frontend JavaScript consome:
- `/api/buscar` - Buscar produtos
- `/api/filtrar` - Filtrar produtos
- `/api/feirante/produto` - Gerenciar produtos
- `/api/admin/relatorios` - Relatórios

---

## Classes Principais

### Produto
Representa um produto na feira.
```cpp
class Produto {
  string nome_;
  double preco_;
  string categoria_;
  double nota_;
};
```

### Feira
Representa uma feira com produtos.
```cpp
class Feira {
  string nome_;
  string endereco_;
  Location localizacao_;
  vector<Produto> produtos_;
};
```

### Feirante
Vendedor que cadastra produtos.
```cpp
class Feirante {
  string nome_;
  string banca_;
  string feira_;
  string senhaHash_;  // Senha criptografada
};
```

### Usuario
Cliente que busca produtos.
```cpp
class Usuario {
  string nome_;
  string login_;
  Location localizacao_;
};
```

### Sistema
Gerencia tudo.
```cpp
class Sistema {
  vector<Feira> feiras_;
  vector<Usuario> usuarios_;
  vector<Feirante> feirantes_;

  vector<Produto> BuscarProdutos(string nome);
  void FiltrarProdutos(string feira, double distMax);
};
```

---

## Portabilidade

O projeto compila em Windows, Linux e Mac sem modificações.

### Mudanças para Portabilidade

#### 1. Sockets Cross-Platform
```cpp
#ifdef _WIN32
  #include <winsock2.h>
  #define closesocket close
#else
  #include <sys/socket.h>
#endif
```

#### 2. Makefile Inteligente
```makefile
ifeq ($(OS),Windows_NT)
  LDFLAGS = -lws2_32  # Winsock no Windows
else
  LDFLAGS =           # Nada no Linux
endif
```

#### 3. UTF-8 no Windows
```cpp
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);  // Aceita acentos
#endif
```

Resultado: mesmo código funciona em todos os sistemas operacionais.

---

## Build System

### Makefile
Principal forma de compilar:
```bash
mingw32-make           # Compila tudo
mingw32-make test      # Roda testes
mingw32-make coverage  # Cobertura gcov
mingw32-make docs      # Gera Doxygen
mingw32-make clean     # Limpa
```

### build.bat (alternativo Windows)
```bash
cmd /c build.bat
```

Compila usando g++ diretamente com tratamento de erros.

---

## Testes

### Estrutura
```
tests/
  - test_simple.cpp           # Testes básicos
  - test_feirante_simple.cpp  # Testes do feirante
  - test_sistema.cpp          # Testes do sistema
```

### Exemplos de Teste

#### Buscar Produtos (EU001)
```cpp
void TestBuscarProdutos() {
  Sistema s;
  auto resultado = s.BuscarProdutosPorNome("tomate");
  assert(resultado.size() > 0);
  cout << "✅ EU001: Buscar produtos - OK" << endl;
}
```

#### Calcular Distância (EU003)
```cpp
void TestCalcularDistancia() {
  Location loc1(1.0, 1.0);
  Location loc2(2.0, 2.0);
  double dist = CalcularDistancia(loc1, loc2);
  assert(dist > 0);
  cout << "✅ EU003: Distância - OK" << endl;
}
```

### Rodar Testes
```bash
mingw32-make test
# 30/30 testes passando ✅
```

---

## Servidor Web

### Como Funciona
1. Backend C++ cria servidor HTTP na porta 8080
2. Recebe requisições do navegador
3. Processa (busca, filtra, adiciona produtos)
4. Retorna JSON
5. Frontend renderiza na página

### Exemplo de Endpoint
```cpp
// GET /api/buscar?termo=tomate
if (path == "/api/buscar") {
  string termo = params["termo"];
  auto produtos = sistema.BuscarProdutos(termo);
  return JSON(produtos);
}
```

### Executar
```bash
mingw32-make run-web
# Servidor rodando em http://localhost:8080
```

---

## Dados e Persistência

### Arquivo: data/dados.txt
Armazena feiras, produtos, usuários e feirantes:
```
FEIRA|Feira da Ceilândia|QNM 18 Ceilândia|-15.8175|-48.1064
PRODUTO|Tomate|5.50|Hortifruti|Feira da Ceilândia|4.5
USUARIO|João Silva|joao|senha123|-15.8|-48.1
FEIRANTE|Maria|Banca da Maria|Feira da Ceilândia|senha456
```

### Formato
- Pipes (`|`) separam campos
- Uma linha por registro
- Carregado na inicialização
- Salvo ao adicionar/modificar

---

## Principais Desafios e Soluções

### 1. Winsock no Windows
**Problema:** Código não compilava no Windows (erro ws2_32)
**Solução:** Adicionamos `-lws2_32` no Makefile só para Windows

### 2. Dependências do cppcheck
**Problema:** pacman não conseguia instalar (conflito GCC)
**Solução:** Compilamos cppcheck da fonte

### 3. cpplint não instalado
**Problema:** Python não estava no sistema
**Solução:** Instalamos Python 3.12 e pip install cpplint

### 4. Doxygen não encontrado
**Problema:** doxygen não no PATH
**Solução:** Baixamos binário Windows e usamos ./doxygen.exe

### 5. UTF-8 no Windows
**Problema:** Acentos apareciam errados no console
**Solução:** SetConsoleOutputCP(CP_UTF8) no main

---

## Boas Práticas Utilizadas

### 1. SOLID
- **S**ingle Responsibility: Cada classe tem uma responsabilidade
- **O**pen/Closed: Aberto pra extensão, fechado pra modificação
- **L**iskov: Classes derivadas substituem base
- **I**nterface Segregation: Interfaces específicas
- **D**ependency Inversion: Depende de abstrações

### 2. DRY (Don't Repeat Yourself)
Criamos funções reutilizáveis em vez de copiar código.

### 3. KISS (Keep It Simple)
Código simples e direto, sem overengineering.

### 4. Naming Conventions
- Classes: `PascalCase`
- Funções: `PascalCase`
- Variáveis: `snake_case_`
- Constantes: `UPPER_CASE`

### 5. Const Correctness
Usamos `const` sempre que possível para proteger dados.

---

## Métricas do Projeto

### Código
- **Linhas de código:** ~2500 (C++)
- **Linhas de frontend:** ~2000 (JS/HTML/CSS)
- **Total:** ~4500 linhas
- **Classes:** 7 principais
- **Funções:** 150+
- **Arquivos:** 30+

### Qualidade
- **Cobertura de testes:** 89.04%
- **Testes passando:** 30/30
- **Assertivas:** 161
- **Warnings cppcheck:** 0
- **Compilação:** sem warnings

### Documentação
- **Páginas Doxygen:** 63
- **Arquivos documentados:** 18
- **Comentários Javadoc:** 100%
- **README:** completo
- **Guias:** 4 arquivos

---

## O Que Aprendemos

### Técnico
- TDD realmente funciona e economiza tempo
- Assertivas ajudam muito na documentação
- C++ cross-platform não é trivial
- API REST é um bom padrão
- Verificadores encontram bugs cedo

### Trabalho em Equipe
- Git facilita colaboração
- Commits pequenos são melhores
- Documentar enquanto faz é mais fácil
- Code review ajuda a melhorar

### Processo
- Planejar antes economiza retrabalho
- Testes dão confiança pra refatorar
- Backlog mantém tudo organizado
- Histórias de usuário guiam o desenvolvimento

---

## Tecnologias e Ferramentas

### Desenvolvimento
- **Linguagem:** C++17
- **Compilador:** g++ (MinGW/GCC)
- **Build:** Make
- **IDE:** VS Code
- **Controle de versão:** Git/GitHub

### Testes e Qualidade
- **Testes:** Custom test framework
- **Cobertura:** gcov
- **Análise estática:** cppcheck
- **Estilo:** cpplint
- **Documentação:** Doxygen

### Web
- **Backend:** C++ HTTP server (custom)
- **Frontend:** HTML/CSS/JavaScript
- **API:** REST JSON
- **Bootstrap:** CSS framework

---

## Estrutura de Pastas Completa

```
sistema-compras-feiras/
├── include/              # Headers com declarações
│   ├── feira.h
│   ├── feirante.h
│   ├── produto.h
│   ├── sistema.h
│   ├── usuario.h
│   ├── location.h
│   └── distancias.h
├── src/                  # Código fonte C++
│   ├── main.cpp
│   ├── sistema.cpp
│   ├── webserver.cpp
│   ├── feira.cpp
│   ├── feirante.cpp
│   ├── produto.cpp
│   ├── usuario.cpp
│   ├── location.cpp
│   ├── distancias.cpp
│   └── database.cpp
├── tests/                # Testes unitários
│   ├── test_simple.cpp
│   ├── test_feirante_simple.cpp
│   └── test_sistema.cpp
├── web/                  # Frontend
│   ├── index.html
│   ├── feirante.html
│   ├── admin.html
│   ├── login.html
│   ├── app.js
│   ├── feirante.js
│   ├── admin.js
│   ├── login.js
│   └── styles.css
├── data/                 # Dados persistentes
│   └── dados.txt
├── docs/                 # Documentação Doxygen
│   └── html/
│       └── index.html
├── obj/                  # Objetos compilados
├── bin/                  # Executáveis
├── cfg/                  # Configs do cppcheck
├── Makefile              # Build system
├── build.bat             # Build Windows
├── Doxyfile              # Config do Doxygen
├── README.md             # Visão geral
├── COMO_RODAR.md         # Instruções de uso
├── DESENVOLVIMENTO.md    # Este arquivo
└── BACKLOG.md            # Histórias de usuário
```

---

## Checklist Final

### Funcionalidades
- [x] EU001 - Buscar produtos
- [x] EU002 - Ordenar resultados
- [x] EU003 - Filtrar por feira/distância
- [x] EU004 - Feirante cadastrar produtos
- [x] EU005 - Feirante ver mensagens
- [x] EU006 - Admin gerenciar
- [x] EU007 - Admin relatórios

### Qualidade
- [x] TDD aplicado
- [x] 30 testes passando
- [x] 89% cobertura gcov
- [x] 0 erros cppcheck
- [x] cpplint configurado
- [x] 161 assertivas
- [x] Documentação Doxygen

### Portabilidade
- [x] Compila Windows
- [x] Compila Linux
- [x] Compila Mac
- [x] Makefile cross-platform
- [x] Sem dependências externas críticas

### Documentação
- [x] README completo
- [x] COMO_RODAR detalhado
- [x] DESENVOLVIMENTO explicativo
- [x] BACKLOG organizado
- [x] Doxygen gerado
- [x] Código comentado

---

## Conclusão

Projeto completo atendendo todos os requisitos da disciplina:
- ✅ Multiplataforma (Windows/Linux/Mac)
- ✅ TDD rigoroso (30 testes, 89% cobertura)
- ✅ Verificadores funcionando (gcov, cppcheck, cpplint)
- ✅ Assertivas em todas as funções (161 total)
- ✅ Documentação Doxygen completa (63 páginas)
- ✅ 7 histórias de usuário implementadas
- ✅ Backend C++ + Frontend JS integrados
- ✅ API REST funcional

O sistema está pronto para uso e demonstra domínio completo das técnicas de programação ensinadas.
