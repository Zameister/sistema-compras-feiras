# Como Rodar o Projeto

Guia para compilar e executar o servidor.

---

## O Que Você Precisa

### Windows
- **G++** (compilador C++)
  - Baixe o MSYS2: https://www.msys2.org/
  - Instale e abra o terminal MSYS2
  - Digite: `pacman -S mingw-w64-x86_64-gcc`
  - Adicione ao PATH: `C:\msys64\mingw64\bin`

### Mac
- **Xcode Command Line Tools**
  - Abra o Terminal
  - Digite: `xcode-select --install`

### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install g++ make
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

Cole este comando no terminal (da raiz do projeto):

### Windows
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32
```

### Mac/Linux
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver
```

Se aparecer aviso sobre `#pragma comment`, pode ignorar (é normal).

---

## Passo 3: Executar o Servidor

**Execute sempre da raiz do projeto, não de dentro de `bin/`!**

### Windows
```bash
./bin/webserver.exe
```

### Mac/Linux
```bash
./bin/webserver
```

Você verá:
```
Servidor HTTP rodando em http://localhost:8080
Pressione Ctrl+C para parar.
```

---

## Passo 4: Abrir no Navegador

Acesse: **http://localhost:8080/login.html**

### Páginas Disponíveis
- **Login/Cadastro:** http://localhost:8080/login.html
- **Catálogo:** http://localhost:8080/index.html (após login)
- **Painel Feirante:** http://localhost:8080/feirante.html
- **Painel Admin:** http://localhost:8080/admin.html (usuário: `admin` / senha: `admin123`)

---

## Passo 5: Usar o Sistema

### Criar Conta de Usuário
1. Clique em "Cadastrar Usuário"
2. Preencha: Nome, RA (ex: 123456), Senha
3. Clique em "Cadastrar"
4. Faça login

### Criar Conta de Feirante
1. Clique em "Cadastrar Feirante"
2. Preencha: Nome, Nome da Banca, Feira, Senha
3. Clique em "Cadastrar"
4. Faça login

---

## Passo 6: Parar o Servidor

Pressione **Ctrl+C** no terminal onde o servidor está rodando.

---

## Executar Testes (Opcional)

### Teste Simples
```bash
# Windows
g++ -std=c++17 -Wall -I./include tests/test_feirante_simple.cpp src/feirante.cpp -o bin/test_feirante.exe
./bin/test_feirante.exe

# Mac/Linux
g++ -std=c++17 -Wall -I./include tests/test_feirante_simple.cpp src/feirante.cpp -o bin/test_feirante
./bin/test_feirante
```

Saída esperada:
```
🧪 Testando classe Feirante (TDD - Fase GREEN)
✅ Construtor padrão OK
✅ Construtor com parâmetros OK
...
🎉 Todos os testes passaram!
```

---

## Gerar Documentação (Doxygen)

### Instalar Doxygen

**Windows:**
- Baixe: https://www.doxygen.nl/download.html
- Instale e adicione ao PATH

**Mac:**
```bash
brew install doxygen
```

**Linux:**
```bash
sudo apt install doxygen
```

### Gerar Documentação

```bash
doxygen Doxyfile
```

Ou, se tiver Make instalado:
```bash
make docs
```

### Abrir Documentação

A documentação será gerada em `docs/html/`.

**Windows:**
```bash
start docs/html/index.html
```

**Mac:**
```bash
open docs/html/index.html
```

**Linux:**
```bash
xdg-open docs/html/index.html
```

Ou simplesmente abra o arquivo `docs/html/index.html` no seu navegador.

---

## Comando Único (Compilar + Executar)

Se quiser tudo de uma vez:

### Windows
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32 && ./bin/webserver.exe
```

### Mac/Linux
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver && ./bin/webserver
```

Depois acesse: http://localhost:8080/login.html

---

## Solucao de Problemas

### Erro: "Permission denied" ao compilar

**Problema:**
```
cannot open output file bin/webserver.exe: Permission denied
```

**Causa:** O servidor esta rodando e o compilador nao consegue sobrescrever o arquivo.

**Solucao:**

1. **Parar o servidor primeiro:**
   - Pressione `Ctrl+C` no terminal onde o servidor esta rodando
   - Ou feche a janela do terminal

2. **Se ainda nao funcionar, matar o processo manualmente:**

   **Windows:**
   ```bash
   # Ver processos na porta 8080
   netstat -ano | findstr :8080

   # Matar o processo (substitua PID pelo numero que apareceu)
   taskkill //PID 12345 //F
   ```

   **Mac/Linux:**
   ```bash
   # Ver processos na porta 8080
   lsof -i :8080

   # Matar o processo (substitua PID pelo numero)
   kill -9 12345
   ```

3. **Compilar novamente:**
   ```bash
   g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32
   ```

### Erro: "Erro ao fazer bind na porta 8080"

**Causa:** Ja existe um servidor rodando na porta 8080.

**Solucao:** Use os comandos acima para matar o processo na porta 8080.

### Erro: "No such file or directory" ao executar

**Causa:** Voce esta tentando executar de dentro da pasta `bin/`.

**Solucao:** Execute sempre da raiz do projeto:
```bash
# CORRETO (da raiz do projeto)
./bin/webserver.exe

# ERRADO (de dentro de bin/)
cd bin
./webserver.exe  # Nao funciona - nao encontra web/
```

### Erro: Pagina em branco ou 404

**Causa:** Voce esta acessando o endereco errado.

**Solucao:** Acesse http://localhost:8080/login.html (com `/login.html` no final)

### Warning sobre "#pragma comment"

**Mensagem:**
```
warning: ignoring '#pragma comment ' [-Wunknown-pragmas]
```

**Solucao:** Pode ignorar - e apenas um aviso, nao e um erro. O programa funciona normalmente.

### Caracteres estranhos no terminal

**Causa:** Terminal com encoding diferente.

**Solucao:** Nao afeta o funcionamento. O site funciona normalmente no navegador.
