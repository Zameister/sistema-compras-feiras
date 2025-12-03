@echo off
REM Script de compilacao para Windows - Note2.0
REM Sistema de Compras em Feiras

echo ====================================
echo  Sistema de Compras em Feiras
echo  Compilacao Windows - Note2.0
echo ====================================
echo.

REM Criar diretorios
if not exist "obj" mkdir obj
if not exist "bin" mkdir bin

echo [1/3] Compilando arquivos fonte...
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/produto.cpp -o obj/produto.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/feirante.cpp -o obj/feirante.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/feira.cpp -o obj/feira.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/sistema.cpp -o obj/sistema.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/usuario.cpp -o obj/usuario.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/location.cpp -o obj/location.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/distancias.cpp -o obj/distancias.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/database.cpp -o obj/database.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/main.cpp -o obj/main.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/webserver.cpp -o obj/webserver.o

if errorlevel 1 (
    echo.
    echo [ERRO] Falha na compilacao!
    pause
    exit /b 1
)

echo.
echo [2/3] Linkando executavel console...
g++ -std=c++17 obj/produto.o obj/feirante.o obj/feira.o obj/sistema.o obj/usuario.o obj/location.o obj/distancias.o obj/database.o obj/main.o -o bin/sistema_feiras.exe

if errorlevel 1 (
    echo.
    echo [ERRO] Falha ao linkar executavel console!
    pause
    exit /b 1
)

echo.
echo [3/3] Linkando servidor web...
g++ -std=c++17 obj/produto.o obj/feirante.o obj/feira.o obj/sistema.o obj/usuario.o obj/location.o obj/distancias.o obj/database.o obj/webserver.o -o bin/webserver.exe -lws2_32

if errorlevel 1 (
    echo.
    echo [ERRO] Falha ao linkar servidor web!
    pause
    exit /b 1
)

echo.
echo ====================================
echo  Compilacao concluida com sucesso!
echo ====================================
echo.
echo Executaveis criados:
echo  - bin/sistema_feiras.exe (programa console)
echo  - bin/webserver.exe (servidor web)
echo.
echo Para executar o servidor web:
echo  bin\webserver.exe
echo.
echo Depois acesse: http://localhost:8080/login.html
echo.
pause
