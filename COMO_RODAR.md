# Como Rodar o Projeto

Guia prático para compilar e executar tudo do zero.

---

## Requisitos

### Windows
1. Instale MSYS2: https://www.msys2.org/
2. Abra o terminal MSYS2 MinGW 64-bit
3. Instale o g++:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make
```

### Linux
```bash
sudo apt update
sudo apt install g++ make
```

### Mac
```bash
xcode-select --install
```

---

## Passo 1: Baixar o Projeto

```bash
git clone https://github.com/Zameister/sistema-compras-feiras.git
cd sistema-compras-feiras
```

Ou baixe o ZIP do GitHub e extraia.

---

## Passo 2: Compilar

### Usando Make (recomendado)
```bash
# Windows
mingw32-make

# Linux/Mac
make
```

### Manualmente (alternativa)
**Windows:**
```bash
cmd /c build.bat
```

**Linux/Mac:**
```bash
mkdir -p obj bin
g++ -std=c++17 -Wall -I./include -c src/*.cpp
g++ obj/*.o -o bin/webserver
```

---

## Passo 3: Executar o Servidor

```bash
# Windows
./bin/webserver.exe

# Linux/Mac
./bin/webserver
```

Você deve ver:
```
Servidor rodando em http://localhost:8080
Pressione Ctrl+C para parar
```

---

## Passo 4: Acessar no Navegador

Abra seu navegador e vá para:
**http://localhost:8080/login.html**

### Logins Padrão

**Admin:**
- Login: `admin`
- Senha: `admin123`

**Usuário teste:**
- Login: `joao`
- Senha: `senha123`

**Feirante teste:**
- Login: `maria_feirante`
- Senha: `feira456`

---

## Comandos Úteis

### Compilar e Executar
```bash
mingw32-make && ./bin/webserver.exe
```

### Limpar e Recompilar
```bash
mingw32-make clean
mingw32-make
```

### Rodar Testes
```bash
mingw32-make test
```

Saída esperada:
```
============================================
   RELATORIO DE TESTES
============================================
Testes passaram: 30
Testes falharam: 0
Total de testes: 30

✅ TODOS OS TESTES PASSARAM!
```

### Verificar Cobertura
```bash
mingw32-make coverage
```

Saída esperada:
```
Lines executed: 89.04% of 73
Creating 'feirante.cpp.gcov'
```

### Análise Estática
```bash
mingw32-make static-analysis
```

Saída esperada:
```
Executando analise estatica com cppcheck...
Nenhum problema encontrado
Analise estatica concluida
```

### Verificar Estilo
```bash
mingw32-make style-check
```

Mostra avisos de estilo (esperado ter alguns).

### Gerar Documentação
```bash
mingw32-make docs
```

Saída esperada:
```
==========================================
  DOCUMENTACAO GERADA COM SUCESSO!
==========================================
Arquivo principal: docs/html/index.html
```

Depois abra `docs/html/index.html` no navegador.

---

## Testando o Sistema

### 1. Testar Busca de Produtos

1. Acesse: http://localhost:8080/login.html
2. Faça login como usuário (joao / senha123)
3. Digite "tomate" na busca
4. Clique em "Buscar"
5. Deve aparecer lista de tomates com preços e feiras

### 2. Testar Ordenação

1. Após buscar produtos
2. Clique em "Ordenar por Preço"
3. Produtos devem reorganizar do mais barato ao mais caro
4. Teste também "Ordenar por Distância" e "Ordenar por Nota"

### 3. Testar Filtros

1. Na página inicial
2. Selecione uma categoria (ex: Hortifruti)
3. Clique em "Aplicar Filtros"
4. Deve mostrar apenas produtos daquela categoria

### 4. Testar Feirante

1. Logout (canto superior direito)
2. Login como feirante (maria_feirante / feira456)
3. Vá para página do Feirante
4. Clique em "Adicionar Produto"
5. Preencha:
   - Nome: Alface
   - Preço: 3.50
   - Categoria: Hortifruti
6. Clique em "Adicionar"
7. Produto deve aparecer na lista

### 5. Testar Mensagens (Feirante)

1. Como feirante, vá para "Mensagens"
2. Se houver mensagens não lidas, aparece badge vermelho
3. Clique em "Marcar como lida"
4. Badge deve sumir

### 6. Testar Admin

1. Logout
2. Login como admin (admin / admin123)
3. Vá para "Admin"
4. Deve ver:
   - Estatísticas (total usuários, feirantes, produtos, feiras)
   - Top 5 produtos mais avaliados
   - Feiras mais populares
   - Produtos mais baratos por categoria

---

## Estrutura dos Dados

### data/dados.txt

O sistema carrega dados deste arquivo na inicialização. Formato:

```
FEIRA|Nome da Feira|Endereço|Latitude|Longitude
PRODUTO|Nome|Preço|Categoria|Feira|Nota
USUARIO|Nome|Login|Senha|Latitude|Longitude
FEIRANTE|Nome|Banca|Feira|Senha
```

Exemplo:
```
FEIRA|Feira da Ceilândia|QNM 18 Ceilândia|-15.8175|-48.1064
PRODUTO|Tomate|5.50|Hortifruti|Feira da Ceilândia|4.5
USUARIO|João Silva|joao|senha123|-15.8|-48.1
FEIRANTE|Maria Santos|Banca da Maria|Feira da Ceilândia|feira456
```

---

## Problemas Comuns e Soluções

### Erro: "g++ não encontrado"

**Windows:**
- Certifique-se de usar o terminal MSYS2 MinGW 64-bit (NÃO o MSYS2 normal)
- Rode: `pacman -S mingw-w64-x86_64-gcc`
- Adicione ao PATH: `C:\msys64\mingw64\bin`

**Linux:**
```bash
sudo apt install g++ make
```

**Mac:**
```bash
xcode-select --install
```

### Erro: "Permission denied" ao executar bin/webserver

**Windows:**
```bash
rm -rf bin
mkdir bin
mingw32-make
```

**Linux/Mac:**
```bash
chmod +x bin/webserver
./bin/webserver
```

### Erro: "Address already in use" (porta 8080 ocupada)

Mate o processo que está usando a porta 8080:

**Windows:**
```bash
netstat -ano | findstr :8080
taskkill /PID <numero> /F
```

**Linux/Mac:**
```bash
lsof -i :8080
kill -9 <PID>
```

Ou mude a porta no código (src/webserver.cpp, linha ~40):
```cpp
const int PORT = 8081;  // Trocar de 8080 para 8081
```

### Erro: "No such file or directory" ao compilar

Certifique-se de estar na raiz do projeto:
```bash
pwd  # Deve mostrar .../sistema-compras-feiras
ls   # Deve mostrar: Makefile, include/, src/, etc.
```

### Erro: "undefined reference to ws2_32" (Windows)

Use o Makefile fornecido - ele linka Winsock automaticamente:
```bash
mingw32-make clean
mingw32-make
```

Se ainda der erro, compile manualmente com `-lws2_32`:
```bash
g++ ... -o bin/webserver.exe -lws2_32
```

### Erro: Acentos aparecem errados no terminal Windows

Use o terminal MSYS2 MinGW 64-bit (não o CMD ou PowerShell).

O código já configura UTF-8 automaticamente no main.cpp.

### Página não carrega no navegador

1. Verifique se o servidor está rodando:
```bash
netstat -an | findstr :8080  # Windows
netstat -an | grep :8080     # Linux/Mac
```

2. Tente acessar diretamente:
   - http://localhost:8080/login.html
   - http://127.0.0.1:8080/login.html

3. Limpe o cache do navegador (Ctrl+F5)

4. Veja os logs no terminal onde o servidor está rodando

---

## Testando Cada Requisito

### 1. Multiplataforma ✅

**Testar:**
```bash
mingw32-make clean
mingw32-make
# Deve compilar sem erros
```

### 2. TDD e Testes ✅

**Testar:**
```bash
mingw32-make test
```

**Esperado:**
```
Testes passaram: 30
Testes falharam: 0
✅ TODOS OS TESTES PASSARAM!
```

### 3. gcov (Cobertura) ✅

**Testar:**
```bash
mingw32-make coverage
```

**Esperado:**
```
Lines executed: 89.04% of 73
```

### 4. cppcheck (Análise Estática) ✅

**Testar:**
```bash
mingw32-make static-analysis
```

**Esperado:**
```
Nenhum problema encontrado
```

### 5. cpplint (Estilo) ✅

**Testar:**
```bash
mingw32-make style-check
```

**Esperado:** Alguns avisos de estilo (normal).

### 6. Doxygen (Documentação) ✅

**Testar:**
```bash
mingw32-make docs
```

**Esperado:**
```
DOCUMENTACAO GERADA COM SUCESSO!
Arquivo principal: docs/html/index.html
```

Abra `docs/html/index.html` e verifique:
- Página inicial carrega
- Menu de Classes funciona
- Busca funciona
- Código fonte navegável

### 7. Assertivas (@pre/@post) ✅

**Testar:**
```bash
grep -rn "@pre\|@post" include/*.h | wc -l
```

**Esperado:** ~161 (161 assertivas no total).

Veja exemplos em qualquer header, ex:
```bash
head -50 include/feirante.h
```

### 8. Histórias de Usuário ✅

**Testar cada EU no navegador:**

- **EU001:** Buscar "tomate" → deve achar produtos
- **EU002:** Ordenar por preço → deve reordenar
- **EU003:** Filtrar por Hortifruti → mostra só Hortifruti
- **EU004:** Login feirante → Adicionar produto → aparece na lista
- **EU005:** Login feirante → Ver mensagens → marcar como lida
- **EU006:** Login admin → Gerenciar usuários (lista aparece)
- **EU007:** Login admin → Ver relatórios (estatísticas aparecem)

---

## Resumo de Comandos

```bash
# Compilar
mingw32-make

# Executar
./bin/webserver.exe

# Testar tudo
mingw32-make test
mingw32-make coverage
mingw32-make static-analysis
mingw32-make style-check
mingw32-make docs

# Limpar
mingw32-make clean
```

---

## Pronto!

Se todos os comandos acima funcionaram, o projeto está 100% operacional.

Acesse http://localhost:8080/login.html e explore o sistema.

Qualquer problema, veja a seção "Problemas Comuns" acima.
