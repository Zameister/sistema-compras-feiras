# Sistema de Compras em Feiras

Sistema web para buscar produtos em feiras, comparar preços e calcular distâncias.

## Quem Somos
- **Luidgi Varela Carneiro** - 231011669
- **Arthur Souza Chagas** - 221037385

## O Que É

Sistema onde:
- **Usuários** buscam produtos, comparam preços e veem distâncias das feiras
- **Feirantes** cadastram produtos e respondem mensagens
- **Admin** gerencia categorias e vê relatórios

---

## Como Rodar

### 1. Compilar
```bash
# Windows (MSYS2/MinGW)
mingw32-make

# Linux/Mac
make
```

### 2. Executar Servidor Web
```bash
# Windows
./bin/webserver.exe

# Linux/Mac
./bin/webserver
```

### 3. Acessar
Abrir no navegador: **http://localhost:8080/login.html**

**Usuário admin padrão:**
- Login: `admin`
- Senha: `admin123`

---

## Comandos Disponíveis

### Compilação
```bash
mingw32-make              # Compila o projeto
mingw32-make clean        # Limpa arquivos compilados
```

### Testes e Qualidade
```bash
mingw32-make test         # Roda 30 testes
mingw32-make coverage     # Cobertura com gcov (89%)
mingw32-make static-analysis    # Análise com cppcheck
mingw32-make style-check        # Verifica estilo com cpplint
```

### Documentação
```bash
mingw32-make docs         # Gera documentação Doxygen
# Abre: docs/html/index.html
```

### Executar
```bash
mingw32-make run-web      # Inicia servidor HTTP
```

---

## Estrutura do Projeto

```
sistema-compras-feiras/
├── include/              # Headers (.h)
│   ├── feira.h
│   ├── feirante.h
│   ├── produto.h
│   ├── sistema.h
│   └── usuario.h
├── src/                  # Código C++ (.cpp)
│   ├── main.cpp
│   ├── sistema.cpp
│   ├── webserver.cpp
│   └── ...
├── tests/                # Testes unitários
│   ├── test_simple.cpp
│   └── ...
├── web/                  # Frontend HTML/JS
│   ├── index.html
│   ├── feirante.html
│   ├── admin.html
│   ├── app.js
│   └── styles.css
├── data/                 # Dados persistentes
│   └── dados.txt
├── docs/                 # Documentação Doxygen
├── obj/                  # Objetos compilados (.o)
├── bin/                  # Executáveis
├── Makefile              # Build system
├── Doxyfile              # Config do Doxygen
└── *.md                  # Documentação
```

---

## Funcionalidades

### Usuários
- Buscar produtos por nome
- Ordenar por preço, distância ou avaliação
- Filtrar por feira
- Calcular distância até as feiras
- Enviar mensagens para feirantes
- Avaliar produtos

### Feirantes
- Cadastrar produtos
- Ver produtos da feira
- Receber mensagens
- Responder dúvidas

### Admin
- Gerenciar usuários e feirantes
- Criar categorias
- Ver relatórios:
  - Top 5 produtos mais avaliados
  - Produtos mais baratos
  - Feiras mais populares
  - Estatísticas gerais

---

## Tecnologias

### Backend
- **C++17** com g++
- Servidor HTTP custom
- API REST JSON

### Frontend
- **HTML/CSS/JavaScript**
- Bootstrap 5
- Fetch API

### Ferramentas
- **Make** - Build system
- **gcov** - Cobertura de testes (89%)
- **cppcheck** - Análise estática
- **cpplint** - Verificação de estilo
- **Doxygen** - Documentação

---

## Documentação Completa

### [📖 COMO_RODAR.md](COMO_RODAR.md)
Instruções detalhadas de instalação e execução

### [🛠️ DESENVOLVIMENTO.md](DESENVOLVIMENTO.md)
Como fizemos: TDD, testes, arquitetura, verificadores, assertivas, etc.

### [📋 BACKLOG.md](BACKLOG.md)
Histórias de usuário (EU001-EU025) com rastreabilidade

### [📘 docs/html/index.html](docs/html/index.html)
Documentação Doxygen (gerar com `make docs`)

---

## Requisitos Atendidos

- ✅ **Multiplataforma** - Windows, Linux, Mac
- ✅ **TDD** - 30 testes, 89% cobertura
- ✅ **Verificadores** - gcov, cppcheck, cpplint
- ✅ **Assertivas** - 161 @pre/@post em todas as funções
- ✅ **Doxygen** - 63 páginas HTML geradas
- ✅ **7 Histórias de Usuário** implementadas
- ✅ **Backend C++** + Frontend JS integrados

---

## Problemas Comuns

### Erro: "g++ não encontrado"
**Windows:** Instale MSYS2 e rode `pacman -S mingw-w64-x86_64-gcc`

**Linux:** `sudo apt install g++ make`

**Mac:** `xcode-select --install`

### Erro: "Permission denied" no bin/
```bash
rm -rf bin
mkdir bin
```

### Erro: "ws2_32" no Windows
Use o Makefile fornecido - ele já linka Winsock automaticamente.

---

## Licença

Projeto acadêmico - UnB - Técnicas de Programação 2
