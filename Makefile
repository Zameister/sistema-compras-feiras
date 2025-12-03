# Makefile Multiplataforma - Sistema de Compras em Feiras
# Tecnicas de Programacao 2 - UnB
# Versao: 2.0 - Portavel Windows/Linux

# Deteccao automatica de plataforma
ifeq ($(OS),Windows_NT)
    PLATFORM = Windows
    EXE_EXT = .exe
    RM = del /Q
    RMDIR = rmdir /S /Q
    MKDIR = if not exist
    MKDIR_CMD = mkdir
    PATH_SEP = \\
    LDFLAGS_PLATFORM = -lws2_32
else
    PLATFORM = Linux
    EXE_EXT =
    RM = rm -f
    RMDIR = rm -rf
    MKDIR = mkdir -p
    MKDIR_CMD =
    PATH_SEP = /
    LDFLAGS_PLATFORM =
endif

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TESTFLAGS = -lgtest -lgtest_main -pthread
COVFLAGS = -fprofile-arcs -ftest-coverage

# Diretorios
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin
DOC_DIR = docs

# Arquivos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Testes do Google Test (sem main)
GTEST_SOURCES = $(TEST_DIR)/test_feirante.cpp $(TEST_DIR)/test_produto.cpp $(TEST_DIR)/test_sistema.cpp
GTEST_OBJECTS = $(GTEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Objetos comuns (sem main.cpp e webserver.cpp)
COMMON_OBJECTS = $(filter-out $(OBJ_DIR)/main.o $(OBJ_DIR)/webserver.o, $(OBJECTS))

# Executaveis
TARGET = $(BIN_DIR)/sistema_feiras$(EXE_EXT)
WEBSERVER_TARGET = $(BIN_DIR)/webserver$(EXE_EXT)
TEST_TARGET = $(BIN_DIR)/run_tests$(EXE_EXT)

# Regra padrao - compila webserver
all: directories $(WEBSERVER_TARGET)
	@echo "==================================="
	@echo "Compilacao concluida com sucesso!"
	@echo "Plataforma: $(PLATFORM)"
	@echo "==================================="

# Criar diretorios necessarios
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)

# Compilar programa console principal
$(TARGET): $(COMMON_OBJECTS) $(OBJ_DIR)/main.o
	@echo "Linkando executavel console..."
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Compilacao concluida: $(TARGET)"

# Compilar servidor web
$(WEBSERVER_TARGET): $(COMMON_OBJECTS) $(OBJ_DIR)/webserver.o
	@echo "Linkando servidor web..."
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS_PLATFORM)
	@echo "Compilacao concluida: $(WEBSERVER_TARGET)"

# Compilar objetos do codigo fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Executar testes simples (padrao - nao requer Google Test)
test: test-simple
	@echo ""
	@echo "NOTA: Para executar testes do Google Test, use 'make test-gtest'"
ifeq ($(PLATFORM),Windows)
	@echo "      Requer instalacao: pacman -S mingw-w64-x86_64-gtest"
else
	@echo "      Requer instalacao: sudo apt install libgtest-dev"
endif

# Compilar e executar testes do Google Test (opcional)
test-gtest: directories $(TEST_TARGET)
	@echo "Executando testes do Google Test..."
	./$(TEST_TARGET)
	@echo "Testes executados com sucesso"

# Compilar testes do Google Test
$(TEST_TARGET): $(COMMON_OBJECTS) $(GTEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(TESTFLAGS)

# Compilar objetos dos testes
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Testes simples individuais (sem Google Test)
test-simple: test-feirante-simple test-simple-basic
	@echo ""
	@echo "==================================="
	@echo "Testes simples concluidos!"
	@echo "==================================="

test-feirante-simple: directories
	@echo "Compilando teste simples do Feirante..."
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_feirante_simple.cpp $(SRC_DIR)/feirante.cpp -o $(BIN_DIR)/test_feirante_simple$(EXE_EXT)
	@echo "Executando teste simples do Feirante..."
	./$(BIN_DIR)/test_feirante_simple$(EXE_EXT)

test-simple-basic: directories
	@echo "Compilando teste simples basico..."
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_simple.cpp $(SRC_DIR)/location.cpp $(SRC_DIR)/feira.cpp $(SRC_DIR)/usuario.cpp $(SRC_DIR)/produto.cpp $(SRC_DIR)/distancias.cpp -o $(BIN_DIR)/test_simple$(EXE_EXT)
	@echo "Executando teste simples basico..."
	./$(BIN_DIR)/test_simple$(EXE_EXT)

# Cobertura de testes
coverage: clean directories
	@echo "Compilando com cobertura de codigo..."
	$(CXX) -std=c++17 -Wall -Wextra -Iinclude -fprofile-arcs -ftest-coverage -c $(SRC_DIR)/feirante.cpp -o $(OBJ_DIR)/feirante_cov.o
	$(CXX) -std=c++17 -Wall -Wextra -Iinclude -fprofile-arcs -ftest-coverage $(TEST_DIR)/test_feirante_simple.cpp $(OBJ_DIR)/feirante_cov.o -o $(BIN_DIR)/test_coverage$(EXE_EXT) -lgcov
	@echo "Executando testes para cobertura..."
	./$(BIN_DIR)/test_coverage$(EXE_EXT)
	@echo ""
	@echo "Gerando relatorio de cobertura..."
	gcov $(OBJ_DIR)/feirante_cov.gcno -o $(OBJ_DIR)
	@echo ""
	@echo "Cobertura gerada! Verifique os arquivos .gcov"
	@echo "Resumo:"
	@grep -A 3 "File.*feirante.cpp" feirante.cpp.gcov 2>/dev/null || echo "Arquivo feirante.cpp.gcov gerado"

# Analise estatica com cppcheck
static-analysis:
	@echo "Executando analise estatica com cppcheck..."
	@if [ -f "./cppcheck" ]; then \
		./cppcheck --enable=warning --std=c++17 $(SRC_DIR)/*.cpp 2>&1 | grep -E "(error|warning|style|performance)" || echo "Nenhum problema encontrado"; \
	elif command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=warning,style,performance --std=c++17 --quiet $(SRC_DIR)/ $(INCLUDE_DIR)/; \
	else \
		echo "AVISO: cppcheck nao encontrado. Resultados podem estar incompletos."; \
	fi
	@echo "Analise estatica concluida"

# Verificar estilo de codigo
style-check:
	@echo "Verificando estilo de codigo com cpplint..."
	@if [ -f "/c/Users/arthu/AppData/Local/Programs/Python/Python312/Scripts/cpplint.exe" ]; then \
		/c/Users/arthu/AppData/Local/Programs/Python/Python312/Scripts/cpplint.exe --recursive src/*.cpp include/*.h 2>&1 | head -50 || echo "Analise completa"; \
	elif command -v cpplint >/dev/null 2>&1; then \
		cpplint --recursive $(SRC_DIR)/ $(INCLUDE_DIR)/; \
	else \
		echo "AVISO: cpplint nao encontrado. Instale com: pip install cpplint"; \
	fi
	@echo "Verificacao de estilo concluida"

# Gerar documentacao com Doxygen
docs:
	@echo "Gerando documentacao com Doxygen..."
	@if [ -f "./doxygen.exe" ]; then \
		./doxygen.exe Doxyfile; \
	elif command -v doxygen >/dev/null 2>&1; then \
		doxygen Doxyfile; \
	else \
		echo "ERRO: doxygen nao encontrado. Execute: curl -L -o doxygen-windows.zip https://www.doxygen.nl/files/doxygen-1.9.8.windows.x64.bin.zip && unzip doxygen-windows.zip"; \
		exit 1; \
	fi
	@echo ""
	@echo "=========================================="
	@echo "  DOCUMENTACAO GERADA COM SUCESSO!"
	@echo "=========================================="
	@echo "Arquivo principal: docs/html/index.html"
	@echo ""
	@echo "Para visualizar:"
ifeq ($(PLATFORM),Windows)
	@echo "  start docs\\html\\index.html"
else
	@echo "  xdg-open docs/html/index.html"
endif
	@echo ""

# Debug com GDB
debug: CXXFLAGS += -g
debug: clean all
	@echo "Compilado com simbolos de debug"

# Limpar arquivos gerados
clean:
	-@rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*.exe $(BIN_DIR)/webserver $(BIN_DIR)/sistema_feiras *.gcov *.gcda *.gcno 2>/dev/null || true
	@echo "Arquivos de build removidos"

# Limpar tudo incluindo documentacao
clean-all: clean
	-@rm -rf $(DOC_DIR)/html $(DOC_DIR)/latex 2>/dev/null || true
	@echo "Tudo limpo"

# Executar o programa console
run: $(TARGET)
	@echo "Executando programa console..."
	./$(TARGET)

# Executar o servidor web
run-web: $(WEBSERVER_TARGET)
	@echo "Iniciando servidor web em http://localhost:8080"
	@echo "Pressione Ctrl+C para parar"
	./$(WEBSERVER_TARGET)

# Mostrar ajuda
help:
	@echo "==================================="
	@echo "Sistema de Compras em Feiras"
	@echo "Plataforma: $(PLATFORM)"
	@echo "==================================="
	@echo ""
	@echo "Comandos disponiveis:"
ifeq ($(PLATFORM),Windows)
	@echo "  mingw32-make              - Compila o servidor web"
	@echo "  mingw32-make test         - Executa testes simples (recomendado)"
	@echo "  mingw32-make test-gtest   - Executa testes Google Test (requer instalacao)"
	@echo "  mingw32-make coverage     - Gera relatorio de cobertura"
	@echo "  mingw32-make docs         - Gera documentacao (Doxygen)"
	@echo "  mingw32-make clean        - Remove arquivos de build"
	@echo "  mingw32-make run-web      - Executa o servidor web"
	@echo ""
	@echo "Ou use o arquivo build.bat:"
	@echo "  build.bat                 - Compila tudo"
else
	@echo "  make                      - Compila o servidor web"
	@echo "  make test                 - Executa testes simples (recomendado)"
	@echo "  make test-gtest           - Executa testes Google Test (requer instalacao)"
	@echo "  make coverage             - Gera relatorio de cobertura"
	@echo "  make docs                 - Gera documentacao (Doxygen)"
	@echo "  make clean                - Remove arquivos de build"
	@echo "  make run-web              - Executa o servidor web"
endif
	@echo ""
	@echo "Para compilar rapidamente e rodar:"
	@echo "  make && make run-web"

.PHONY: all directories test test-simple test-feirante-simple test-simple-basic test-gtest coverage static-analysis docs debug clean clean-all run run-web help
