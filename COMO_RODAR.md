# 🚀 COMO RODAR O SERVIDOR - GUIA SIMPLIFICADO

## ⚡ Versão Ultra-Rápida (Copie e Cole)

### Windows
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32 && ./bin/webserver.exe
```

### Mac/Linux
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver && ./bin/webserver
```

Depois acesse: **http://localhost:8080/login.html**

---

## 📖 Passo a Passo Completo (Primeira Vez)

### 1. Instalar G++ (se ainda não tiver)

#### Windows
1. Baixe MSYS2: https://www.msys2.org/
2. Instale e abra o terminal MSYS2
3. Execute:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```
4. Adicione ao PATH: `C:\msys64\mingw64\bin`

#### Mac
```bash
# Instalar Xcode Command Line Tools
xcode-select --install
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install g++ make
```

### 2. Clonar o Projeto
```bash
git clone https://github.com/Zameister/sistema-compras-feiras.git
cd sistema-compras-feiras
```

### 3. Compilar

**Cole este comando completo no terminal (da raiz do projeto):**

#### Windows
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32
```

#### Mac/Linux
```bash
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver
```

Se aparecer um aviso sobre `#pragma comment`, pode ignorar (é normal).

### 4. Executar o Servidor

**⚠️ ATENÇÃO: Execute sempre da pasta raiz do projeto (onde está o README.md)**

#### Windows
```bash
./bin/webserver.exe
```

#### Mac/Linux
```bash
./bin/webserver
```

Você verá:
```
Servidor HTTP rodando em http://localhost:8080
Pressione Ctrl+C para parar.
```

### 5. Acessar no Navegador

Abra o navegador e acesse:
```
http://localhost:8080/login.html
```

### 6. Usar o Sistema

#### Criar Conta de Usuário
1. Na tela de login, clique em "Cadastrar Usuário"
2. Preencha: Nome, RA (qualquer número), Senha
3. Clique em "Cadastrar"
4. Faça login com as credenciais criadas

#### Criar Conta de Feirante
1. Na tela de login, clique em "Cadastrar Feirante"
2. Preencha: Nome, Nome da Banca, Feira (escolha uma), Senha
3. Clique em "Cadastrar"
4. Faça login como feirante

#### Acessar como Admin
- **Usuário:** admin
- **Senha:** admin123

### 7. Parar o Servidor

**Opção 1: No próprio terminal**
```bash
Ctrl+C
```

**Opção 2: Fechar e reabrir terminal (Windows)**
```bash
netstat -ano | findstr ":8080"
taskkill //F //PID <número_da_coluna_direita>
```

**Opção 3: Mac/Linux**
```bash
pkill webserver
```

---

## 🔧 Problemas Comuns

### ❌ "g++ não é reconhecido"
**Solução:** G++ não está instalado ou não está no PATH. Veja o passo 1.

### ❌ "404 - Página não encontrada"
**Causa:** Você rodou o webserver de dentro da pasta `bin/`

**Solução:** Volte para a raiz do projeto:
```bash
cd ..
./bin/webserver.exe
```

### ❌ "Porta 8080 já está em uso"
**Solução Windows:**
```bash
netstat -ano | findstr ":8080"
taskkill //F //PID <PID>
```

**Solução Mac/Linux:**
```bash
lsof -i :8080
kill -9 <PID>
```

### ❌ "Permission denied" ao compilar
**Causa:** O webserver ainda está rodando

**Solução:** Pare o servidor (Ctrl+C) e compile novamente

---

## 📂 Estrutura Esperada

Certifique-se de estar nesta estrutura:
```
sistema-compras-feiras/        ← VOCÊ DEVE ESTAR AQUI
├── bin/
│   └── webserver.exe          ← Arquivo compilado
├── src/                       ← Códigos fonte
├── include/                   ← Headers
├── web/                       ← Arquivos HTML/JS/CSS
├── data/                      ← Dados JSON
└── README.md                  ← Documentação
```

**Teste se está no lugar certo:**
```bash
# Windows
dir README.md

# Mac/Linux
ls README.md
```

Se o arquivo README.md aparecer, você está no lugar certo!

---

## 🎯 Checklist de Verificação

- [ ] G++ instalado (`g++ --version`)
- [ ] Dentro da pasta `sistema-compras-feiras/`
- [ ] Compilou com sucesso (criou `bin/webserver.exe` ou `bin/webserver`)
- [ ] Executou da raiz do projeto (`./bin/webserver.exe`)
- [ ] Acessou http://localhost:8080/login.html no navegador
- [ ] Conseguiu ver a página de login

---

## 📞 Ainda com Problemas?

1. Verifique se está na pasta raiz do projeto
2. Verifique se a pasta `web/` existe e tem arquivos HTML
3. Verifique se a porta 8080 não está ocupada
4. Tente recompilar do zero:
   ```bash
   # Remover executável antigo
   rm bin/webserver.exe  # ou bin/webserver no Mac/Linux

   # Recompilar
   g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32
   ```

---

## 🎉 Dica Final

**Criar um script para facilitar (Windows - salve como `rodar.bat`):**
```batch
@echo off
echo Compilando...
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver.exe -lws2_32
if errorlevel 1 (
    echo Erro na compilacao!
    pause
    exit /b 1
)
echo.
echo Iniciando servidor...
start http://localhost:8080/login.html
bin\webserver.exe
```

**Mac/Linux (salve como `rodar.sh`):**
```bash
#!/bin/bash
echo "Compilando..."
g++ -std=c++17 -Wall -I./include src/database.cpp src/distancias.cpp src/feira.cpp src/feirante.cpp src/location.cpp src/produto.cpp src/sistema.cpp src/usuario.cpp src/webserver.cpp -o bin/webserver
if [ $? -eq 0 ]; then
    echo "Iniciando servidor..."
    open http://localhost:8080/login.html  # ou xdg-open no Linux
    ./bin/webserver
else
    echo "Erro na compilação!"
fi
```

Depois é só:
```bash
# Windows
rodar.bat

# Mac/Linux
chmod +x rodar.sh
./rodar.sh
```
