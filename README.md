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

IMPORTANTE:
No Windows, o projeto só funciona corretamente usando
"GIT BASH".
Não funciona no CMD nem no PowerShell.

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

## Licença

Projeto acadêmico - UnB - Técnicas de Programação 2
