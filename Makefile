# Makefile para Sistema de Compras em Feiras
# Tecnicas de Programacao 2 - UnB

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TESTFLAGS = -lgtest -lgtest_main -pthread
COVFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS_WIN = -lws2_32

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

# Testes simples (com main)
SIMPLE_TESTS = test_feirante_simple test_simple

# Objetos comuns (sem main.cpp e webserver.cpp)
COMMON_OBJECTS = $(filter-out $(OBJ_DIR)/main.o $(OBJ_DIR)/webserver.o, $(OBJECTS))

# Executaveis
TARGET = $(BIN_DIR)/sistema_feiras
WEBSERVER_TARGET = $(BIN_DIR)/webserver
TEST_TARGET = $(BIN_DIR)/run_tests

# Regra padrao - compila webserver
all: directories $(WEBSERVER_TARGET)

# Criar diretorios necessarios
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)

# Compilar programa console principal
$(TARGET): $(COMMON_OBJECTS) $(OBJ_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Compilacao concluida: $(TARGET)"

# Compilar servidor web
$(WEBSERVER_TARGET): $(COMMON_OBJECTS) $(OBJ_DIR)/webserver.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS_WIN)
	@echo "Compilacao concluida: $(WEBSERVER_TARGET)"

# Compilar objetos do codigo fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Executar testes simples (padrao - nao requer Google Test)
test: test-simple
	@echo ""
	@echo "NOTA: Para executar testes do Google Test, use 'mingw32-make test-gtest'"
	@echo "      Requer instalacao: pacman -S mingw-w64-x86_64-gtest"

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

test-feirante-simple: directories
	@echo "Compilando teste simples do Feirante..."
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_feirante_simple.cpp $(SRC_DIR)/feirante.cpp -o $(BIN_DIR)/test_feirante_simple
	@echo "Executando teste simples do Feirante..."
	./$(BIN_DIR)/test_feirante_simple

test-simple-basic: directories
	@echo "Compilando teste simples basico..."
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_simple.cpp $(SRC_DIR)/location.cpp $(SRC_DIR)/feira.cpp $(SRC_DIR)/usuario.cpp $(SRC_DIR)/produto.cpp $(SRC_DIR)/distancias.cpp -o $(BIN_DIR)/test_simple
	@echo "Executando teste simples basico..."
	./$(BIN_DIR)/test_simple

test-sistema-simple: directories
	@echo "Compilando teste simples do Sistema..."
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_sistema.cpp $(SRC_DIR)/sistema.cpp $(SRC_DIR)/produto.cpp $(SRC_DIR)/feira.cpp $(SRC_DIR)/usuario.cpp $(SRC_DIR)/location.cpp $(SRC_DIR)/distancias.cpp $(SRC_DIR)/feirante.cpp -o $(BIN_DIR)/test_sistema
	@echo "Executando teste simples do Sistema..."
	./$(BIN_DIR)/test_sistema

# Todos os testes (Google Test + simples)
test-all: test test-simple

# Cobertura de testes
coverage: clean directories
	@echo "Compilando com cobertura de codigo..."
	$(CXX) -std=c++17 -Wall -Wextra -Iinclude -fprofile-arcs -ftest-coverage $(TEST_DIR)/test_feirante_simple.cpp $(SRC_DIR)/feirante.cpp -o $(BIN_DIR)/test_coverage
	@echo "Executando testes para cobertura..."
	./$(BIN_DIR)/test_coverage
	@echo ""
	@echo "Gerando relatorio de cobertura..."
	@gcov -o $(BIN_DIR) $(SRC_DIR)/feirante.cpp 2>/dev/null || echo "Nota: gcov pode nao estar instalado"
	@echo ""
	@echo "Cobertura gerada!"
	@echo "Arquivos de cobertura (.gcda/.gcno) em: $(BIN_DIR)/"
	@echo "Testes executados com sucesso - verifique a saida acima"

# Analise estatica com cppcheck
static-analysis:
	@echo "Executando analise estatica com cppcheck..."
	@which cppcheck > /dev/null 2>&1 || (echo "ERRO: cppcheck nao encontrado. Instale com: pacman -S mingw-w64-x86_64-cppcheck" && exit 1)
	cppcheck --enable=warning,style,performance --std=c++17 --quiet $(SRC_DIR)/ $(INCLUDE_DIR)/
	@echo "Analise estatica concluida"

# Verificar estilo de codigo
style-check:
	@echo "Verificando estilo de codigo..."
	@echo "NOTA: cpplint opcional. Se nao tiver instalado, ignore este target."
	@which cpplint > /dev/null 2>&1 && cpplint --recursive --quiet $(SRC_DIR)/ $(INCLUDE_DIR)/ || echo "cpplint nao instalado - pulando verificacao de estilo"
	@echo "Verificacao de estilo concluida (ou pulada)"

# Gerar documentacao com Doxygen
docs:
	@echo "Gerando documentacao com Doxygen..."
	@which doxygen > /dev/null 2>&1 || (echo "ERRO: doxygen nao encontrado. Instale com: pacman -S mingw-w64-x86_64-doxygen" && exit 1)
	doxygen Doxyfile
	@echo "Documentacao gerada em $(DOC_DIR)/html/index.html"
	@echo "Para abrir: start $(DOC_DIR)/html/index.html"

# Debug com GDB
debug: CXXFLAGS += -g
debug: clean all
	@echo "Compilado com simbolos de debug"

# Valgrind (verificacao de memoria) - nao disponivel no Windows
valgrind:
	@echo "Valgrind nao esta disponivel no Windows."
	@echo "Use o Visual Studio ou Dr. Memory para deteccao de vazamentos."

# Limpar arquivos gerados
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/* *.gcov *.gcda *.gcno
	@echo "Arquivos de build removidos"

# Limpar tudo incluindo documentacao
clean-all: clean
	rm -rf $(DOC_DIR)/html $(DOC_DIR)/latex
	@echo "Tudo limpo"

# Executar o programa console
run: $(TARGET)
	./$(TARGET)

# Executar o servidor web
run-web: $(WEBSERVER_TARGET)
	@echo "Iniciando servidor web em http://localhost:8080"
	@echo "Pressione Ctrl+C para parar"
	./$(WEBSERVER_TARGET)

# Mostrar ajuda
help:
	@echo "Comandos disponiveis:"
	@echo "  mingw32-make              - Compila o servidor web"
	@echo "  mingw32-make test         - Executa testes simples (recomendado)"
	@echo "  mingw32-make test-gtest   - Executa testes Google Test (requer instalacao)"
	@echo "  mingw32-make test-simple  - Executa testes simples individuais"
	@echo "  mingw32-make coverage     - Gera relatorio de cobertura de codigo"
	@echo "  mingw32-make docs         - Gera documentacao (Doxygen)"
	@echo "  mingw32-make clean        - Remove arquivos de build"
	@echo "  mingw32-make run-web      - Executa o servidor web"
	@echo ""
	@echo "Ferramentas opcionais (ignoram se nao instaladas):"
	@echo "  mingw32-make static-analysis - Analise estatica (cppcheck)"
	@echo "  mingw32-make style-check     - Verifica estilo (cpplint)"
	@echo ""
	@echo "Para compilar rapidamente e rodar:"
	@echo "  make && make run-web"

.PHONY: all directories test test-simple test-feirante-simple test-simple-basic test-sistema-simple test-all coverage static-analysis style-check docs debug valgrind clean clean-all run run-web help
