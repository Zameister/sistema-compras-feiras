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

## 🚀 Como Compilar e Executar

### Windows

#### Pré-requisitos
- MinGW-w64 ou MSYS2 com g++
- Make

#### Compilação
```bash
# Compilar o servidor web
make

# Ou compilar apenas o webserver
g++ -std=c++17 -Wall -I./include src/*.cpp -o bin/webserver.exe -lws2_32
```

#### Executar o Servidor Web
```bash
# Iniciar o servidor na porta 8080
./bin/webserver.exe

# Em outro terminal, ou abra no navegador:
start http://localhost:8080/login.html
```

#### Executar Testes
```bash
make test
```

#### Parar o Servidor
```bash
# Encontrar o processo
netstat -ano | findstr ":8080"

# Matar o processo (substitua PID pelo número encontrado)
taskkill //F //PID <PID>
```

---

### Mac/Linux

#### Pré-requisitos
- g++ ou clang++
- Make
- Google Test (para testes)

#### Compilação
```bash
# Compilar o projeto completo
make

# Ou compilar apenas o webserver
g++ -std=c++17 -Wall -I./include src/*.cpp -o bin/webserver
```

#### Executar o Servidor Web
```bash
# Iniciar o servidor na porta 8080
./bin/webserver

# Em outro terminal, ou abra no navegador:
open http://localhost:8080/login.html  # Mac
xdg-open http://localhost:8080/login.html  # Linux
```

#### Executar Testes
```bash
make test
```

#### Parar o Servidor
```bash
# Encontrar o processo
lsof -i :8080

# Ou simplesmente use Ctrl+C no terminal do servidor

# Ou matar o processo
pkill webserver
```

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
