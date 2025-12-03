@echo off
REM ============================================
REM Script de Compilacao para Windows
REM Sistema de Compras em Feiras
REM Versao: 2.0 - Portavel e Independente
REM ============================================

setlocal enabledelayedexpansion

echo ============================================
echo  Sistema de Compras em Feiras
echo  Compilacao Windows - Versao 2.0
echo ============================================
echo.

REM Verificar se g++ esta disponivel
where g++ >nul 2>&1
if errorlevel 1 (
    echo [ERRO] Compilador g++ nao encontrado!
    echo.
    echo Por favor, instale o MinGW/MSYS2:
    echo 1. Baixe de: https://www.msys2.org/
    echo 2. Instale o compilador: pacman -S mingw-w64-x86_64-gcc
    echo 3. Adicione ao PATH: C:\msys64\mingw64\bin
    echo.
    pause
    exit /b 1
)

echo [INFO] Compilador encontrado:
g++ --version | findstr "g++"
echo.

REM Criar diretorios necessarios
echo [0/4] Criando diretorios...
if not exist "obj" mkdir obj
if not exist "bin" mkdir bin
if not exist "docs" mkdir docs
echo      Diretorios criados: obj/, bin/, docs/
echo.

REM Compilar arquivos fonte comuns
echo [1/4] Compilando arquivos fonte comuns...
set ERROR=0

for %%f in (produto feirante feira sistema usuario location distancias database) do (
    echo      - Compilando %%f.cpp...
    g++ -std=c++17 -Wall -Wextra -Iinclude -c src/%%f.cpp -o obj/%%f.o
    if errorlevel 1 set ERROR=1
)

if !ERROR! equ 1 (
    echo.
    echo [ERRO] Falha na compilacao dos arquivos comuns!
    echo        Verifique os erros acima.
    pause
    exit /b 1
)
echo      Arquivos comuns compilados com sucesso!
echo.

REM Compilar main.cpp
echo [2/4] Compilando programa console...
echo      - Compilando main.cpp...
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/main.cpp -o obj/main.o
if errorlevel 1 (
    echo.
    echo [ERRO] Falha ao compilar main.cpp!
    pause
    exit /b 1
)

echo      - Linkando sistema_feiras.exe...
g++ -std=c++17 obj/produto.o obj/feirante.o obj/feira.o obj/sistema.o obj/usuario.o obj/location.o obj/distancias.o obj/database.o obj/main.o -o bin/sistema_feiras.exe
if errorlevel 1 (
    echo.
    echo [ERRO] Falha ao linkar executavel console!
    pause
    exit /b 1
)
echo      Programa console criado: bin/sistema_feiras.exe
echo.

REM Compilar webserver.cpp
echo [3/4] Compilando servidor web...
echo      - Compilando webserver.cpp...
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/webserver.cpp -o obj/webserver.o
if errorlevel 1 (
    echo.
    echo [ERRO] Falha ao compilar webserver.cpp!
    pause
    exit /b 1
)

echo      - Linkando webserver.exe com Winsock...
g++ -std=c++17 obj/produto.o obj/feirante.o obj/feira.o obj/sistema.o obj/usuario.o obj/location.o obj/distancias.o obj/database.o obj/webserver.o -o bin/webserver.exe -lws2_32
if errorlevel 1 (
    echo.
    echo [ERRO] Falha ao linkar servidor web!
    echo        Verifique se a biblioteca ws2_32 esta disponivel.
    pause
    exit /b 1
)
echo      Servidor web criado: bin/webserver.exe
echo.

REM Verificar arquivos gerados
echo [4/4] Verificando arquivos gerados...
if not exist "bin\sistema_feiras.exe" (
    echo [ERRO] bin\sistema_feiras.exe nao foi criado!
    pause
    exit /b 1
)
if not exist "bin\webserver.exe" (
    echo [ERRO] bin\webserver.exe nao foi criado!
    pause
    exit /b 1
)
echo      Todos os executaveis foram criados com sucesso!
echo.

REM Mensagem final
echo ============================================
echo  COMPILACAO CONCLUIDA COM SUCESSO!
echo ============================================
echo.
echo Executaveis criados:
echo   [1] bin\sistema_feiras.exe  - Programa console
echo   [2] bin\webserver.exe       - Servidor web HTTP
echo.
echo Para executar:
echo   Servidor web:  bin\webserver.exe
echo   Console:       bin\sistema_feiras.exe
echo.
echo Depois acesse: http://localhost:8080
echo.
echo ============================================
echo.

REM Perguntar se deseja executar
set /p EXEC="Deseja executar o servidor web agora? (S/N): "
if /i "!EXEC!"=="S" (
    echo.
    echo Iniciando servidor web...
    echo Pressione Ctrl+C para parar o servidor
    echo.
    bin\webserver.exe
) else (
    echo.
    echo Para executar manualmente:
    echo   bin\webserver.exe
    echo.
)

pause
