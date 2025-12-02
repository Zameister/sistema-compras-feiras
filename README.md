# Sistema de Compras em Feiras

Sistema web para buscar produtos em feiras, comparar preços e calcular distâncias.

## 👥 Integrantes
- **Luidgi Varela Carneiro** - 231011669
- **Arthur Souza Chagas** - 221037385

## 📝 O Que É

Um sistema completo onde:
- **Usuários** buscam produtos, comparam preços e distâncias
- **Feirantes** cadastram produtos e respondem mensagens
- **Administradores** geram relatórios e gerenciam tudo

**Acesse:** http://localhost:8080/login.html (depois de rodar o servidor)

---

## 🚀 Começar Rápido

### 1. Compilar
```bash
# Com Make (recomendado)
make

# Ou compilar manualmente no Windows:
mkdir obj bin
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/*.cpp
g++ -std=c++17 obj/produto.o obj/feirante.o obj/feira.o obj/sistema.o obj/usuario.o obj/location.o obj/distancias.o obj/database.o obj/main.o -o bin/sistema_feiras.exe
g++ -std=c++17 obj/produto.o obj/feirante.o obj/feira.o obj/sistema.o obj/usuario.o obj/location.o obj/distancias.o obj/database.o obj/webserver.o -o bin/webserver.exe -lws2_32
```

### 2. Executar
```bash
# Servidor Web
make run-web          # Com Make
./bin/webserver.exe   # Windows
./bin/webserver       # Mac/Linux

# Ou programa console
make run              # Com Make
./bin/sistema_feiras.exe   # Windows
./bin/sistema_feiras       # Mac/Linux
```

### 3. Acessar
Abra: http://localhost:8080/login.html

**Problemas?** Veja [COMO_RODAR.md](COMO_RODAR.md)

---

## 📚 Documentação

### [📖 COMO_RODAR.md](COMO_RODAR.md)
Como compilar e executar o projeto em Windows/Mac/Linux.
- Pré-requisitos (instalar G++)
- Passo a passo completo
- Solução de problemas
- Scripts prontos (rodar.bat / rodar.sh)

### [🛠️ DESENVOLVIMENTO.md](DESENVOLVIMENTO.md)
Como o projeto foi desenvolvido.
- Histórias de Usuário
- TDD (Test-Driven Development)
- Linguagem e Padrões de Código
- Verificadores (cpplint, cppcheck)
- Bibliotecas (Google Test, Bootstrap)
- Controle de Versão (Git/GitHub)
- Cobertura de Testes (gcov)
- Documentação (Doxygen)
- Arquitetura (Backend C++ + Frontend Web)

---

## ✨ Funcionalidades

### Usuários
- Buscar produtos por nome
- Ordenar por preço, distância ou avaliação
- Filtrar por feira
- Enviar mensagens para feirantes
- Avaliar produtos (1-5 estrelas)

### Feirantes
- Cadastrar produtos (nome, preço, categoria)
- Ver todos os produtos da feira
- Receber e responder mensagens
- Badge de notificações (mensagens não lidas)

### Administradores
- Gerenciar produtos e categorias
- Relatórios:
  - Top 5 produtos mais avaliados
  - Produtos mais baratos
  - Feiras mais populares
  - Estatísticas gerais

**Credenciais Admin:**
- Usuário: `admin`
- Senha: `admin123`

---

## 🏗️ Estrutura

```
sistema-compras-feiras/
├── src/              # Backend C++
│   ├── webserver.cpp # Servidor HTTP
│   ├── feirante.cpp  # Classe Feirante (TDD!)
│   └── ...
├── include/          # Headers
├── tests/            # Testes unitários
├── web/              # Frontend (HTML/CSS/JS)
│   ├── login.html
│   ├── index.html
│   └── ...
├── data/             # Dados JSON
└── bin/              # Executáveis
```

---

## 🧪 Tecnologias

- **Linguagem:** C++17
- **Testes:** Google Test
- **Frontend:** HTML5, CSS3, Bootstrap, JavaScript
- **Servidor:** HTTP customizado em C++
- **Dados:** JSON
- **Análise:** cppcheck, cpplint
- **Cobertura:** gcov
- **Docs:** Doxygen

---

## 🔗 Links

- **GitHub:** https://github.com/Zameister/sistema-compras-feiras
- **Como Rodar:** [COMO_RODAR.md](COMO_RODAR.md)
- **Desenvolvimento:** [DESENVOLVIMENTO.md](DESENVOLVIMENTO.md)

---

## 📄 Licença
MIT License
