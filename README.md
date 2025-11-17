# Sistema de Compras em Feiras

Sistema de compras baseado em preço e posição geográfica para feiras.

## 👥 Integrantes
- Luidgi Varela Carneiro - 231011669
- Arthur Souza Chagas - 221037385

## 📝 Descrição
Sistema que permite usuários procurarem produtos em feiras próximas, comparando preços e distâncias. Feirantes podem cadastrar seus produtos e responder mensagens de clientes.

## 🚀 Como Compilar

```bash
make
```

## ▶️ Como Executar

```bash
./bin/sistema_feiras
```

## 🧪 Como Executar os Testes

```bash
make test
```

## 📊 Verificar Cobertura de Testes

```bash
make coverage
```

## 🔍 Análise Estática

```bash
make static-analysis
```

## 📚 Gerar Documentação

```bash
make docs
```

## 🛠️ Tecnologias Utilizadas
- **Linguagem:** C++
- **Framework de Testes:** Google Test (GTest)
- **Análise Estática:** cppcheck
- **Verificador de Estilo:** cpplint
- **Cobertura:** gcov
- **Documentação:** Doxygen
- **Gerenciamento:** GitHub + Trello

## 📋 Padrão de Codificação
Google C++ Style Guide: https://google.github.io/styleguide/cppguide.html

## 📦 Estrutura do Projeto

```
sistema-compras-feiras/
├── src/           # Código fonte (.cpp)
├── include/       # Headers (.h)
├── tests/         # Testes unitários
├── docs/          # Documentação
├── obj/           # Objetos compilados
├── bin/           # Executáveis
├── data/          # Arquivos JSON
└── Makefile       # Sistema de build
```

## 📖 Histórias de Usuário

### Usuário Comum
- **EU001:** Como usuário, quero procurar produtos pelo nome
- **EU002:** Como usuário, quero ordenar produtos por preço/distância/nota
- **EU003:** Como usuário, quero filtrar por feira ou distância máxima

### Feirante
- **EU004:** Como feirante, quero cadastrar meus produtos
- **EU005:** Como feirante, quero visualizar e responder mensagens

### Administrador
- **EU006:** Como administrador, quero cadastrar categorias
- **EU007:** Como administrador, quero gerar relatórios

## 📅 Cronograma
- **04/11/2025:** Entrega do protótipo final

## 📄 Licença
MIT License
