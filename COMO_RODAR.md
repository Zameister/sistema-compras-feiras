# Como Rodar o Projeto

Guia rápido para compilar e executar o servidor em qualquer computador.

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

**Cole este comando no terminal (da raiz do projeto):**

### Windows
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32
```

### Mac/Linux
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver
```

Se aparecer um aviso sobre `#pragma comment`, pode ignorar (é normal).

---

## Passo 3: Executar o Servidor

⚠️ **IMPORTANTE:** Execute sempre da pasta raiz (onde está o README.md), não de dentro de `bin/`!

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

Abra seu navegador favorito e acesse:
```
http://localhost:8080/login.html
```

### Páginas Disponíveis
- **Login/Cadastro:** http://localhost:8080/login.html
- **Catálogo:** http://localhost:8080/index.html (após login)
- **Painel Feirante:** http://localhost:8080/feirante.html (após login como feirante)
- **Painel Admin:** http://localhost:8080/admin.html (login: `admin` / senha: `admin123`)

---

## Passo 5: Usar o Sistema

### Criar Conta de Usuário
1. Clique em "Cadastrar Usuário"
2. Preencha: Nome, RA (ex: 123456), Senha
3. Clique em "Cadastrar"
4. Faça login

### Criar Conta de Feirante
1. Clique em "Cadastrar Feirante"
2. Preencha: Nome, Nome da Banca, Feira (escolha uma), Senha
3. Clique em "Cadastrar"
4. Faça login

### Acessar como Admin
- Usuário: `admin`
- Senha: `admin123`

---

## Passo 6: Parar o Servidor

### Opção 1: No Terminal
Pressione **Ctrl+C**

### Opção 2: Windows (se não funcionar)
```bash
netstat -ano | findstr ":8080"
taskkill //F //PID <número_encontrado>
```

### Opção 3: Mac/Linux
```bash
pkill webserver
```

---

## Problemas Comuns

### ❌ "g++ não é reconhecido"
**Problema:** G++ não está instalado ou não está no PATH.
**Solução:** Instale o G++ seguindo o Passo "O Que Você Precisa".

### ❌ "404 - Página não encontrada"
**Problema:** Você rodou o servidor de dentro da pasta `bin/`.
**Solução:** Volte para a raiz do projeto:
```bash
cd ..
./bin/webserver.exe
```

### ❌ "Porta 8080 já está em uso"
**Problema:** Outro programa está usando a porta 8080.
**Solução:**

**Windows:**
```bash
netstat -ano | findstr ":8080"
taskkill //F //PID <número>
```

**Mac/Linux:**
```bash
lsof -i :8080
kill -9 <PID>
```

### ❌ "Permission denied" ao compilar
**Problema:** O servidor ainda está rodando e bloqueou o arquivo.
**Solução:** Pare o servidor (Ctrl+C) e compile novamente.

---

## Verificações Rápidas

Se algo não funcionar, verifique:

**1. Você está na pasta certa?**
```bash
# Windows
dir README.md

# Mac/Linux
ls README.md
```
Se o arquivo README.md aparecer, você está no lugar certo!

**2. O executável foi criado?**
```bash
# Windows
dir bin\webserver.exe

# Mac/Linux
ls bin/webserver
```
Se não existir, precisa compilar novamente (Passo 2).

**3. A pasta `web/` existe?**
```bash
# Windows
dir web

# Mac/Linux
ls web
```
Deve ter arquivos como `login.html`, `index.html`, etc.

---

## Dica: Script para Facilitar

### Windows (salve como `rodar.bat`)
```batch
@echo off
echo Compilando...
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32

if errorlevel 1 (
    echo Erro na compilacao!
    pause
    exit /b 1
)

echo Iniciando servidor...
start http://localhost:8080/login.html
bin\webserver.exe
```

Depois é só:
```bash
rodar.bat
```

### Mac/Linux (salve como `rodar.sh`)
```bash
#!/bin/bash
echo "Compilando..."
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver

if [ $? -eq 0 ]; then
    echo "Iniciando servidor..."
    open http://localhost:8080/login.html  # Mac
    # xdg-open http://localhost:8080/login.html  # Linux
    ./bin/webserver
else
    echo "Erro na compilação!"
fi
```

Dar permissão e executar:
```bash
chmod +x rodar.sh
./rodar.sh
```

---

## Executar Testes (Opcional)

Se você quiser rodar os testes unitários:

### Compilar e Rodar Teste Simples
```bash
# Windows
g++ -std=c++17 -Wall -I./include tests/test_feirante_simple.cpp src/feirante.cpp -o bin/test_feirante.exe
./bin/test_feirante.exe

# Mac/Linux
g++ -std=c++17 -Wall -I./include tests/test_feirante_simple.cpp src/feirante.cpp -o bin/test_feirante
./bin/test_feirante
```

Você verá:
```
🧪 Testando classe Feirante (TDD - Fase GREEN)

✅ Construtor padrão OK
✅ Construtor com parâmetros OK
✅ Validação nome vazio OK
...
🎉 Todos os testes passaram!
```

---

## Resumo: Comando Único

Se você só quer compilar e rodar rapidamente:

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

## Estrutura Esperada

Para o projeto funcionar, a estrutura deve ser:

```
sistema-compras-feiras/     ← VOCÊ ESTÁ AQUI
├── bin/
│   └── webserver.exe       ← Criado após compilar
├── src/                    ← Código fonte C++
├── include/                ← Headers (.h)
├── web/                    ← HTML/CSS/JS
│   ├── login.html
│   ├── index.html
│   └── ...
├── data/                   ← JSON com dados
│   ├── feiras.json
│   └── produtos.json
└── README.md
```

---

Pronto! Agora você consegue rodar o projeto em qualquer computador. 🚀

Se tiver qualquer problema, verifique as "Verificações Rápidas" acima.
