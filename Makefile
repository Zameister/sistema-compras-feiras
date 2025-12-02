# Makefile para Sistema de Compras em Feiras
# Técnicas de Programação 2 - UnB

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TESTFLAGS = -lgtest -lgtest_main -pthread
COVFLAGS = -fprofile-arcs -ftest-coverage

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin
DOC_DIR = docs

# Arquivos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Objetos comuns (sem main.cpp e webserver.cpp)
COMMON_OBJECTS = $(filter-out $(OBJ_DIR)/main.o $(OBJ_DIR)/webserver.o, $(OBJECTS))

# Executáveis
TARGET = $(BIN_DIR)/sistema_feiras
WEBSERVER_TARGET = $(BIN_DIR)/webserver
TEST_TARGET = $(BIN_DIR)/run_tests

# Regra padrão - compila ambos os executáveis
all: directories $(TARGET) $(WEBSERVER_TARGET)

# Criar diretórios necessários
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)

# Compilar programa console principal
$(TARGET): $(COMMON_OBJECTS) $(OBJ_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Compilação concluída: $(TARGET)"

# Compilar servidor web
$(WEBSERVER_TARGET): $(COMMON_OBJECTS) $(OBJ_DIR)/webserver.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -lws2_32
	@echo "✅ Compilação concluída: $(WEBSERVER_TARGET)"

# Compilar objetos do código fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar e executar testes
test: directories $(TEST_TARGET)
	./$(TEST_TARGET)
	@echo "✅ Testes executados"

# Compilar testes
$(TEST_TARGET): $(COMMON_OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(TESTFLAGS)

# Compilar objetos dos testes
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cobertura de testes
coverage: CXXFLAGS += $(COVFLAGS)
coverage: clean directories $(TEST_TARGET)
	./$(TEST_TARGET)
	@echo "\n📊 Gerando relatório de cobertura..."
	gcov $(SOURCES) -o $(OBJ_DIR)
	@echo "✅ Arquivos .gcov gerados"

# Análise estática com cppcheck
static-analysis:
	@echo "🔍 Executando análise estática..."
	cppcheck --enable=warning --std=c++17 $(SRC_DIR)/ $(INCLUDE_DIR)/
	@echo "✅ Análise estática concluída"

# Verificar estilo de código
style-check:
	@echo "📝 Verificando estilo de código..."
	cpplint --recursive $(SRC_DIR)/ $(INCLUDE_DIR)/
	@echo "✅ Verificação de estilo concluída"

# Gerar documentação com Doxygen
docs:
	@echo "📚 Gerando documentação..."
	doxygen Doxyfile
	@echo "✅ Documentação gerada em $(DOC_DIR)/html/index.html"

# Debug com GDB
debug: CXXFLAGS += -g
debug: clean all
	@echo "🐛 Compilado com símbolos de debug"

# Valgrind (verificação de memória)
valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Limpar arquivos gerados
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/* *.gcov *.gcda *.gcno
	@echo "🧹 Arquivos de build removidos"

# Limpar tudo incluindo documentação
clean-all: clean
	rm -rf $(DOC_DIR)/html $(DOC_DIR)/latex
	@echo "🧹 Tudo limpo"

# Executar o programa console
run: $(TARGET)
	./$(TARGET)

# Executar o servidor web
run-web: $(WEBSERVER_TARGET)
	./$(WEBSERVER_TARGET)

# Mostrar ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make              - Compila o projeto (console + webserver)"
	@echo "  make test         - Compila e executa os testes"
	@echo "  make coverage     - Gera relatório de cobertura"
	@echo "  make static-analysis - Executa análise estática (cppcheck)"
	@echo "  make style-check  - Verifica estilo de código (cpplint)"
	@echo "  make docs         - Gera documentação (Doxygen)"
	@echo "  make debug        - Compila com símbolos de debug"
	@echo "  make valgrind     - Executa com Valgrind"
	@echo "  make clean        - Remove arquivos de build"
	@echo "  make clean-all    - Remove tudo incluindo docs"
	@echo "  make run          - Executa o programa console"
	@echo "  make run-web      - Executa o servidor web"

.PHONY: all directories test coverage static-analysis style-check docs debug valgrind clean clean-all run run-web help
