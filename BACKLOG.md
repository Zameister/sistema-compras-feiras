# Product Backlog - Sistema de Compras em Feiras

**Projeto:** Sistema de Compras em Feiras
**Equipe:** Arthur Souza Chagas, Luidgi Varela Carneiro
**Disciplina:** Técnicas de Programação 2 - UnB

---

## Iteração 1 - Setup e Classes Básicas (15-25 Out)

### Prioridade ALTA

**EU001** - Eu como **usuário** quero **buscar produtos por nome** para **encontrar o que preciso rapidamente**
- Implementar busca em texto
- Ignorar maiúsculas/minúsculas
- Retornar lista de produtos encontrados
- **Código:** src/sistema.cpp:45, tests/test_sistema.cpp:23

**EU002** - Eu como **usuário** quero **ver o preço dos produtos** para **comparar e escolher o mais barato**
- Mostrar preço de cada produto
- Exibir qual feira tem o produto
- Ordenar por preço crescente
- **Código:** src/produto.cpp:15, tests/test_produto.cpp:18

**EU003** - Eu como **usuário** quero **saber a distância até as feiras** para **escolher a mais perto de mim**
- Calcular distância entre coordenadas
- Ordenar feiras por proximidade
- Mostrar distância em km
- **Código:** src/distancias.cpp:12, tests/test_simple.cpp:67

### Prioridade MÉDIA

**EU004** - Eu como **feirante** quero **cadastrar meus produtos** para **divulgar o que vendo**
- Adicionar produto com nome, preço e categoria
- Validar que preço não seja negativo
- Produto ficar visível na feira
- **Código:** src/feira.cpp:28, tests/test_simple.cpp:45

**EU005** - Eu como **feirante** quero **ter uma senha segura** para **proteger minha conta**
- Hash da senha (não guardar texto puro)
- Senha mínima de 4 caracteres
- Validar senha no login
- **Código:** src/feirante.cpp:22, tests/test_feirante_simple.cpp:34

### Tarefas Técnicas
- [ ] Criar classes: Produto, Feira, Usuario, Location
- [ ] Implementar cálculo de distância
- [ ] Escrever testes unitários básicos

---

## Iteração 2 - Sistema de Busca e Interface (26 Out - 10 Nov)

### Prioridade ALTA

**EU006** - Eu como **usuário** quero **filtrar produtos por categoria** para **achar só o que me interessa**
- Filtrar por: Hortifruti, Grãos, Carnes, Laticínios
- Combinar com busca por nome
- Mostrar quantos resultados
- **Código:** src/sistema.cpp:78, web/index.html:145

**EU007** - Eu como **usuário** quero **ordenar resultados** para **ver primeiro o que importa pra mim**
- Ordenar por: preço, distância, avaliação
- Manter filtros aplicados
- Atualizar interface em tempo real
- **Código:** web/js/ordenacao.js:23, src/sistema.cpp:92

**EU008** - Eu como **usuário** quero **acessar pelo navegador** para **não precisar instalar nada**
- Interface web funcional
- Responsiva (funciona no celular)
- Fácil de usar
- **Código:** web/index.html, src/webserver.cpp:156

### Prioridade MÉDIA

**EU009** - Eu como **feirante** quero **ver meus produtos cadastrados** para **saber o que já coloquei no sistema**
- Listar todos produtos da minha feira
- Mostrar preço e categoria
- Destacar produtos em promoção
- **Código:** web/feirante.html:89, src/database.cpp:112

**EU010** - Eu como **feirante** quero **remover produtos** para **tirar o que não vendo mais**
- Botão de remover em cada produto
- Confirmação antes de apagar
- Produto some da busca
- **Código:** src/feira.cpp:67, tests/test_simple.cpp:98

### Tarefas Técnicas
- [ ] Implementar servidor HTTP em C++
- [ ] Criar páginas HTML/CSS
- [ ] Integrar backend com frontend
- [ ] Testar em diferentes navegadores

---

## Iteração 3 - Avaliações e Mensagens (11-27 Nov)

### Prioridade ALTA

**EU011** - Eu como **usuário** quero **avaliar produtos** para **ajudar outros compradores**
- Dar nota de 1 a 5 estrelas
- Calcular média das avaliações
- Mostrar número de avaliações
- **Código:** src/produto.cpp:78, web/index.html:234

**EU012** - Eu como **usuário** quero **enviar mensagem pro feirante** para **tirar dúvidas antes de ir**
- Escrever mensagem direta
- Feirante receber notificação
- Histórico de mensagens
- **Código:** src/sistema.cpp:156, web/mensagens.js:45

**EU013** - Eu como **feirante** quero **responder mensagens** para **atender meus clientes**
- Ver mensagens recebidas
- Badge com número de não lidas
- Responder direto no painel
- **Código:** web/feirante.html:145, src/database.cpp:178

### Prioridade MÉDIA

**EU014** - Eu como **usuário** quero **ver avaliação média** para **saber se o produto é bom**
- Estrelas coloridas (1-5)
- Quantidade de pessoas que avaliaram
- Ordenar por melhor avaliado
- **Código:** src/produto.cpp:95, web/index.html:267

**EU015** - Eu como **feirante** quero **ver minhas avaliações** para **saber como melhorar**
- Lista de produtos mais bem avaliados
- Produtos que precisam atenção
- Média geral da feira
- **Código:** web/feirante.html:234

### Tarefas Técnicas
- [ ] Implementar sistema de mensagens
- [ ] Adicionar campo de avaliações no produto
- [ ] Criar notificações visuais
- [ ] Testes de integração

---

## Iteração 4 - Admin e Relatórios (28 Nov - 02 Dez)

### Prioridade ALTA

**EU016** - Eu como **administrador** quero **ver estatísticas gerais** para **entender o sistema**
- Total de produtos cadastrados
- Número de feiras ativas
- Produtos mais pesquisados
- **Código:** web/admin.html:78, src/database.cpp:234

**EU017** - Eu como **administrador** quero **gerenciar categorias** para **organizar melhor o sistema**
- Adicionar nova categoria
- Remover categoria vazia
- Listar produtos por categoria
- **Código:** web/admin.html:145, src/sistema.cpp:189

**EU018** - Eu como **administrador** quero **cadastrar novos usuários** para **controlar acesso**
- Form de cadastro
- Validar dados
- Gerar credenciais
- **Código:** web/admin.html:201, src/database.cpp:267

### Prioridade MÉDIA

**EU019** - Eu como **administrador** quero **ver top 5 produtos** para **identificar tendências**
- Produtos mais avaliados
- Produtos mais baratos
- Feiras mais populares
- **Código:** web/admin.html:289, src/database.cpp:298

**EU020** - Eu como **administrador** quero **adicionar/remover produtos** para **manter dados corretos**
- Form completo de produto
- Escolher feira destino
- Validações todas aplicadas
- **Código:** web/admin.html:345, src/sistema.cpp:234

### Tarefas Técnicas
- [ ] Criar painel administrativo
- [ ] Implementar relatórios
- [ ] Sistema de autenticação
- [ ] Logs de atividades

---

## Histórias de Usuário Adicionais (Backlog Futuro)

### EU021 - Eu como **usuário** quero **salvar feiras favoritas** para **acessar rapidamente**
### EU022 - Eu como **usuário** quero **receber notificações de promoção** para **economizar**
### EU023 - Eu como **feirante** quero **criar promoções** para **atrair mais clientes**
### EU024 - Eu como **feirante** quero **ver gráfico de vendas** para **acompanhar desempenho**
### EU025 - Eu como **administrador** quero **exportar relatórios PDF** para **documentar**

---

## Cronograma de Entregas

| Iteração | Período | Histórias | Prioridade |
|----------|---------|-----------|------------|
| **1** | 15-25 Out | EU001, EU002, EU003, EU004, EU005 | Classes básicas |
| **2** | 26 Out - 10 Nov | EU006, EU007, EU008, EU009, EU010 | Interface web |
| **3** | 11-27 Nov | EU011, EU012, EU013, EU014, EU015 | Interações |
| **4** | 28 Nov - 02 Dez | EU016, EU017, EU018, EU019, EU020 | Admin e polish |

---

## Rastreabilidade - Onde Cada EU Foi Implementada

### Backend (C++)
```
EU001: src/sistema.cpp:45-67     | tests/test_sistema.cpp:23
EU002: src/produto.cpp:15-34     | tests/test_produto.cpp:18
EU003: src/distancias.cpp:12-28  | tests/test_simple.cpp:67
EU004: src/feira.cpp:28-45       | tests/test_simple.cpp:45
EU005: src/feirante.cpp:22-78    | tests/test_feirante_simple.cpp:34
EU011: src/produto.cpp:78-95     | tests/test_produto.cpp:67
EU012: src/sistema.cpp:156-189   | tests/test_sistema.cpp:89
```

### Frontend (Web)
```
EU006: web/index.html:145-178    | web/js/filtros.js:23
EU007: web/index.html:189-223    | web/js/ordenacao.js:12
EU008: web/index.html, web/css/style.css
EU009: web/feirante.html:89-134
EU013: web/feirante.html:145-201
EU016: web/admin.html:78-112
EU017: web/admin.html:145-189
```

---

## Priorização (Técnica MoSCoW)

### Must Have (Tem que ter)
- EU001, EU002, EU003, EU008
- Sem essas não funciona nada

### Should Have (Deveria ter)
- EU004, EU005, EU006, EU007
- Importantes mas dá pra entregar sem

### Could Have (Poderia ter)
- EU009, EU010, EU011, EU012
- Legal de ter, aumenta valor

### Won't Have (Não vai ter agora)
- EU021-EU025
- Fica pro futuro

---

## Estimativas (Planning Poker)

| História | Pontos | Complexidade |
|----------|--------|--------------|
| EU001 | 3 | Busca simples |
| EU002 | 2 | Só mostrar preço |
| EU003 | 5 | Cálculo de distância |
| EU004 | 3 | CRUD básico |
| EU005 | 8 | Hash de senha, segurança |
| EU006 | 5 | Filtros combinados |
| EU007 | 3 | Ordenação |
| EU008 | 13 | Servidor HTTP do zero |
| EU011 | 5 | Sistema de avaliações |
| EU012 | 8 | Mensagens bidirecionais |
| EU016 | 5 | Dashboard admin |

**Velocidade média:** ~25 pontos por iteração

---

## Quadro Kanban (Snapshot Final)

### TODO
- EU021, EU022, EU023, EU024, EU025

### DOING
- (nenhuma - projeto concluído)

### DONE
- EU001, EU002, EU003, EU004, EU005
- EU006, EU007, EU008, EU009, EU010
- EU011, EU012, EU013, EU014, EU015
- EU016, EU017, EU018, EU019, EU020

---

## Retrospectiva do Projeto

### O que funcionou bem
- TDD ajudou a pegar bugs cedo
- Divisão clara de tarefas entre dupla
- Commits frequentes no Git

### O que pode melhorar
- Documentação poderia ter sido feita junto
- Alguns testes escritos depois do código
- Integração contínua teria ajudado

### Lições aprendidas
- Começar simples e ir melhorando
- Testes são importantes mesmo
- C++ moderno é bem diferente do C antigo
- Servidor HTTP do zero é trabalhoso mas dá

---

**Última atualização:** 03/12/2025
**Status:** Projeto concluído e entregue
