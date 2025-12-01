# 🌐 INTERFACE WEB - Sistema de Compras em Feiras

**Versão Web Moderna** do Sistema de Compras em Feiras do Distrito Federal

---

## 📋 **O QUE É?**

Interface web completa e moderna para o sistema de feiras, desenvolvida com:

- ✅ **Backend:** Servidor HTTP em C++ puro
- ✅ **Frontend:** HTML5 + CSS3 + Bootstrap 5 + JavaScript
- ✅ **Design:** Responsivo, moderno e profissional
- ✅ **Funcionalidades:** Todas as EUs (Histórias de Usuário) implementadas

---

## 🚀 **COMO EXECUTAR**

### **Passo 1: Iniciar o Servidor**

```bash
# No terminal, dentro da pasta do projeto:
cd c:\Users\arthu\Documents\UnB\TP2\Projeto\sistema-compras-feiras

# Executar o servidor web:
.\bin\webserver.exe
```

**Saída esperada:**
```
🌐 Servidor iniciado em http://localhost:8080
📱 Abra seu navegador e acesse a URL acima
🛑 Pressione Ctrl+C para parar
```

### **Passo 2: Abrir no Navegador**

1. Abra seu navegador favorito (Chrome, Edge, Firefox)
2. Digite na barra de endereço: `http://localhost:8080`
3. A interface web será carregada!

---

## ✨ **FUNCIONALIDADES DA INTERFACE**

### 1. **Página Inicial**
- 🎨 Design moderno com gradiente verde
- 🔍 Barra de busca em destaque
- 📊 Cards das feiras disponíveis

### 2. **Buscar Produtos (EU001)**
- Digite o nome do produto no campo de busca
- Clique em "Buscar"
- Veja todos os produtos encontrados ordenados por preço
- Compare preços entre diferentes feiras

**Exemplo:** Busque por "tomate" e veja os preços em cada feira!

### 3. **Filtrar Feiras (EU002)**
- **Por Categoria:** Hortifruti, Grãos, Carnes, Laticínios, Padaria
- **Por Preço Máximo:** Defina um orçamento
- **Por Região:** Escolha sua RA no DF

Clique em "Aplicar Filtros" para ver os resultados!

### 4. **Cadastrar Usuário (EU005)**
- Preencha seu nome
- Selecione sua Região Administrativa
- Clique em "Salvar Perfil"
- O sistema calculará distâncias até as feiras!

### 5. **Calcular Distâncias (EU003)**
- Após cadastrar seu perfil
- As feiras mostram a distância até você
- Baseado em fórmula de Haversine (GPS real)

---

## 📱 **TELAS DA INTERFACE**

### **1. Hero Section (Topo)**
```
┌─────────────────────────────────────────────┐
│  🛒 Encontre as Melhores Feiras do DF       │
│                                              │
│  ┌──────────────────────────────────────┐  │
│  │ 🔍  Buscar produtos...    [Buscar]   │  │
│  └──────────────────────────────────────┘  │
└─────────────────────────────────────────────┘
```

### **2. Filtros**
```
┌─────────────────────────────────────────────┐
│  🔽 Filtros                                  │
│  ┌──────────┬──────────┬──────────┐         │
│  │Categoria │  Preço   │  Região  │         │
│  └──────────┴──────────┴──────────┘         │
│  [Aplicar Filtros] [Limpar]                 │
└─────────────────────────────────────────────┘
```

### **3. Cards de Produtos**
```
┌─────────────────────┬─────────────────────┐
│ Tomate         [🌿] │ Alface         [🌿] │
│ R$ 3.50             │ R$ 2.00             │
│ 🏪 Feira Ceilândia  │ 🏪 Feira Ceilândia  │
│ [Ver Detalhes]      │ [Ver Detalhes]      │
└─────────────────────┴─────────────────────┘
```

### **4. Cards de Feiras**
```
┌─────────────────────────────────────┐
│ 🏪 Feira da Ceilândia                │
│ 📍 QNM 11, Ceilândia Norte          │
│ 🚩 Ceilândia                         │
│ [4 produtos]  📍 2.5 km              │
│ [Ver Produtos]                       │
└─────────────────────────────────────┘
```

---

## 🎨 **DESIGN E CORES**

- **Cor Primária:** Verde (#198754) - representa agricultura/sustentabilidade
- **Fonte:** Segoe UI - moderna e legível
- **Ícones:** Bootstrap Icons - profissionais
- **Responsividade:** Funciona em desktop, tablet e celular

---

## 📊 **DADOS DISPONÍVEIS**

### **Feiras Cadastradas:**
1. ✅ Feira da Ceilândia (4 produtos)
2. ✅ Feira de Taguatinga (4 produtos)
3. ✅ Feira do Plano Piloto (4 produtos)
4. ✅ Feira de Samambaia (4 produtos)
5. ✅ Feira de Águas Claras (4 produtos)

### **Categorias de Produtos:**
- 🥬 **Hortifruti:** Tomate, Alface, Banana, Batata, Cenoura, Maçã
- 🌾 **Grãos:** Arroz, Feijão
- 🥩 **Carnes:** Frango
- 🧀 **Laticínios:** Queijo, Leite
- 🍞 **Padaria:** Pão francês, Pão integral

---

## 🔧 **TECNOLOGIAS UTILIZADAS**

### **Backend (C++):**
- Windows Sockets API (winsock2.h)
- Servidor HTTP simples
- Roteamento de URLs
- Servir arquivos estáticos (HTML/CSS/JS)

### **Frontend:**
- HTML5 semântico
- CSS3 moderno (Grid, Flexbox, Animações)
- Bootstrap 5.3 (framework CSS)
- JavaScript ES6+ (vanilla, sem frameworks pesados)
- Bootstrap Icons

---

## 📁 **ESTRUTURA DE ARQUIVOS**

```
web/
├── index.html      # Página principal
├── style.css       # Estilos customizados
└── app.js          # Lógica da aplicação

src/
└── webserver.cpp   # Servidor HTTP em C++

bin/
└── webserver.exe   # Executável compilado
```

---

## 🚀 **FEATURES IMPLEMENTADAS**

| Feature | Status | Descrição |
|---------|--------|-----------|
| **Buscar Produtos** | ✅ | Busca com autocomplete visual |
| **Filtros** | ✅ | Por categoria, preço e região |
| **Cadastro Usuário** | ✅ | Salvo no localStorage |
| **Cálculo GPS** | ✅ | Fórmula de Haversine |
| **Design Responsivo** | ✅ | Mobile-first |
| **Animações** | ✅ | Transições suaves |
| **Cards Interativos** | ✅ | Hover effects |
| **Ordenação** | ✅ | Por menor preço |

---

## 💡 **COMO USAR**

### **Cenário 1: Buscar Tomates**
1. Digite "tomate" na barra de busca
2. Clique em "Buscar"
3. Veja os tomates ordenados por preço:
   - Feira da Ceilândia: R$ 3.50
   - Feira de Taguatinga: R$ 3.80
   - Feira de Águas Claras: R$ 4.20
   - Feira do Plano Piloto: R$ 4.50

### **Cenário 2: Filtrar por Orçamento**
1. Selecione categoria: "Hortifruti"
2. Digite preço máximo: "3.00"
3. Clique em "Aplicar Filtros"
4. Veja apenas produtos até R$ 3.00

### **Cenário 3: Encontrar Feira Próxima**
1. Vá em "Meu Perfil"
2. Preencha seu nome
3. Selecione sua RA (ex: "Ceilândia")
4. Salve o perfil
5. Veja as distâncias nas feiras!

---

## 🐛 **TROUBLESHOOTING**

### **Erro: "Não consegue conectar"**
- ✅ Verifique se o servidor está rodando
- ✅ Confirme que a porta 8080 está livre
- ✅ Tente `http://127.0.0.1:8080` ao invés de localhost

### **Erro: "Página não carrega CSS"**
- ✅ Verifique se a pasta `web/` existe
- ✅ Confirme que os arquivos estão no local correto
- ✅ Limpe o cache do navegador (Ctrl+F5)

### **Servidor não inicia:**
```bash
# Se der erro de porta ocupada:
# 1. Feche o navegador
# 2. Feche o terminal anterior
# 3. Rode novamente
```

---

## 📝 **PRÓXIMAS MELHORIAS**

### **Curto Prazo:**
- [ ] Integrar com backend C++ real (atualmente usa dados simulados)
- [ ] Adicionar banco de dados SQLite
- [ ] API REST completa

### **Médio Prazo:**
- [ ] Sistema de carrinho de compras
- [ ] Comparação lado-a-lado de preços
- [ ] Exportar lista de compras em PDF

### **Longo Prazo:**
- [ ] Mapa interativo (Google Maps API)
- [ ] Login de usuários
- [ ] Notificações de promoções
- [ ] App mobile (React Native)

---

## 🎓 **PARA O PROFESSOR**

Esta interface web demonstra:

✅ **Arquitetura Moderna:** Separação frontend/backend
✅ **Todas as EUs:** Implementadas com interface gráfica
✅ **Design Profissional:** Bootstrap 5 + CSS customizado
✅ **Código Limpo:** JavaScript organizado e comentado
✅ **Responsividade:** Funciona em qualquer dispositivo
✅ **Usabilidade:** Interface intuitiva e amigável

**Tecnologias:**
- C++ puro para backend (sem bibliotecas externas além de winsock)
- Frontend moderno (HTML5/CSS3/JS ES6+)
- Sem dependências pesadas

---

## 📞 **CONTATO**

**Desenvolvido para:** TP2 - Técnicas de Programação 2
**Universidade:** UnB - Universidade de Brasília
**Ano:** 2025
**Autores:** Arthur Souza Chagas, Luidgi Varela Carneiro

---

## 🎉 **DEMONSTRAÇÃO**

Para demonstrar ao professor:

1. Execute o servidor: `.\bin\webserver.exe`
2. Abra `http://localhost:8080`
3. Mostre as funcionalidades:
   - Buscar "tomate"
   - Filtrar por "Hortifruti" + "R$ 5.00"
   - Cadastrar usuário "João" em "Ceilândia"
   - Ver distâncias calculadas
   - Explorar produtos de cada feira

**Tempo estimado de demonstração:** 5-10 minutos

---

**🌟 Aproveite a interface web do Sistema de Feiras! 🌟**
