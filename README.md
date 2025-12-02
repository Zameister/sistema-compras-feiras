# Sistema de Compras em Feiras

Sistema de compras baseado em preço e posição geográfica para feiras.

## 👥 Integrantes
- Luidgi Varela Carneiro - 231011669
- Arthur Souza Chagas - 221037385

## 📝 Descrição
Sistema completo de compras em feiras com interface web interativa. Permite usuários procurarem produtos em feiras próximas, comparando preços e distâncias. Feirantes podem cadastrar seus produtos e responder mensagens de clientes. Administradores têm acesso a relatórios e gerenciamento completo do sistema.

### ✨ Funcionalidades Principais

#### 👤 Para Usuários
- Sistema de login e cadastro por região administrativa
- Busca de produtos por nome com filtros avançados
- Ordenação por preço, distância (GPS) ou nota (avaliações)
- Visualização de produtos com sistema de estrelas (1-5)
- Cálculo automático de distância usando fórmula de Haversine
- Envio de mensagens para feirantes sobre produtos

#### 🏪 Para Feirantes
- Painel exclusivo com gestão de produtos
- Visualização de todos os produtos da feira
- Adicionar e remover produtos com preços
- Sistema de mensagens com clientes
- Badge de notificações para mensagens não lidas
- Responder dúvidas dos clientes

#### 🛡️ Para Administradores
- Visualização de todos os usuários cadastrados
- Gerenciamento de produtos (adicionar/remover)
- Sistema dinâmico de categorias
- Relatórios com estatísticas:
  - Top 5 produtos mais bem avaliados
  - Produtos mais baratos do sistema
  - Feiras mais populares
  - Estatísticas gerais (totais, médias)

## 🚀 Como Compilar e Executar o Servidor

### ⚡ Início Rápido (3 Passos)

#### Windows
```bash
# 1. Compilar (da raiz do projeto)
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32

# 2. Executar (IMPORTANTE: da raiz do projeto, não de dentro de bin/)
./bin/webserver.exe

# 3. Abrir no navegador
start http://localhost:8080/login.html
```

#### Mac/Linux
```bash
# 1. Compilar (da raiz do projeto)
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver

# 2. Executar (IMPORTANTE: da raiz do projeto, não de dentro de bin/)
./bin/webserver

# 3. Abrir no navegador
open http://localhost:8080/login.html  # Mac
xdg-open http://localhost:8080/login.html  # Linux
```

---

### 📋 Instruções Detalhadas

#### Pré-requisitos

**Windows:**
- MinGW-w64 ou MSYS2 com g++ instalado
- Git Bash ou terminal compatível

**Mac/Linux:**
- g++ ou clang++
- Make (opcional, mas recomendado)

#### 1. Clonar o Repositório
```bash
git clone https://github.com/Zameister/sistema-compras-feiras.git
cd sistema-compras-feiras
```

#### 2. Compilar o Servidor

**Opção 1: Usando Make (recomendado)**
```bash
make
```

**Opção 2: Manualmente no Windows**
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32
```

**Opção 3: Manualmente no Mac/Linux**
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver
```

#### 3. Executar o Servidor

**⚠️ IMPORTANTE: Execute sempre da RAIZ do projeto (onde está o README.md)**

**Windows:**
```bash
./bin/webserver.exe
```

**Mac/Linux:**
```bash
./bin/webserver
```

Você verá a mensagem: `Servidor rodando em http://localhost:8080`

#### 4. Acessar o Sistema

Abra o navegador e acesse uma destas URLs:

- **Login/Cadastro:** http://localhost:8080/login.html
- **Catálogo de Produtos:** http://localhost:8080/index.html (após login)
- **Painel do Feirante:** http://localhost:8080/feirante.html (após login como feirante)
- **Painel Admin:** http://localhost:8080/admin.html (login: admin / senha: admin123)

#### 5. Parar o Servidor

**Windows:**
```bash
# Ctrl+C no terminal do servidor

# Ou, se rodou em background:
netstat -ano | findstr ":8080"
taskkill //F //PID <PID>
```

**Mac/Linux:**
```bash
# Ctrl+C no terminal do servidor

# Ou:
pkill webserver
```

---

### 🧪 Executar Testes

```bash
# Compilar e rodar todos os testes
make test

# Ou rodar teste simples manualmente
g++ -std=c++17 -Wall -I./include tests/test_feirante_simple.cpp src/feirante.cpp -o bin/test_feirante.exe
./bin/test_feirante.exe
```

---

### 🔧 Solução de Problemas

#### ❌ Erro: "404 - Página não encontrada"
**Causa:** Você executou o webserver de dentro da pasta `bin/`

**Solução:** Sempre execute da raiz do projeto:
```bash
# Certo ✅
cd sistema-compras-feiras
./bin/webserver.exe

# Errado ❌
cd bin
./webserver.exe
```

#### ❌ Erro: "Porta 8080 já está em uso"
**Causa:** Outro processo está usando a porta 8080

**Solução no Windows:**
```bash
netstat -ano | findstr ":8080"
taskkill //F //PID <número_do_processo>
```

**Solução no Mac/Linux:**
```bash
lsof -i :8080
kill -9 <PID>
```

#### ❌ Erro: "Permission denied" ao compilar
**Causa:** O servidor ainda está rodando e bloqueando o arquivo

**Solução:** Pare o servidor primeiro (Ctrl+C ou mate o processo) e compile novamente

---

## 🧪 Testes e Análise

### Verificar Cobertura de Testes
```bash
make coverage
```

### Análise Estática
```bash
make static-analysis
```

### Gerar Documentação
```bash
make docs
```

## 🛠️ Tecnologias Utilizadas
- **Linguagem:** C++
- **Framework de Testes:** Google Test (GTest)
- **Análise Estática:** cppcheck
- **Verificador de Estilo:** cpplint
- **Cobertura:** gcov
- **Documentação:** Doxygen
- **Gerenciamento:** GitHub + Trello

## 📋 Padrão de Codificação
Google C++ Style Guide: https://google.github.io/styleguide/cppguide.html

## 📦 Estrutura do Projeto

```
sistema-compras-feiras/
├── src/           # Código fonte (.cpp)
├── include/       # Headers (.h)
├── tests/         # Testes unitários
├── docs/          # Documentação
├── obj/           # Objetos compilados
├── bin/           # Executáveis
├── data/          # Arquivos JSON
└── Makefile       # Sistema de build
```

## 📖 Histórias de Usuário

### Usuário Comum
- **EU001:** Como usuário, quero procurar produtos pelo nome
- **EU002:** Como usuário, quero ordenar produtos por preço/distância/nota
- **EU003:** Como usuário, quero filtrar por feira ou distância máxima

### Feirante
- **EU004:** Como feirante, quero cadastrar meus produtos
- **EU005:** Como feirante, quero visualizar e responder mensagens

### Administrador
- **EU006:** Como administrador, quero cadastrar categorias
- **EU007:** Como administrador, quero gerar relatórios

## 📅 Cronograma
- **04/11/2025:** Entrega do protótipo final

## 📄 Licença
MIT License
