========================================================
                  COMO FIZEMOS O PROJETO
========================================================

Quem Somos
----------------------------------------
- Luidgi Varela Carneiro – 231011669
- Arthur Souza Chagas – 221037385


Descrição Geral
----------------------------------------
O projeto é um sistema simples de compras em feiras.
O usuário pode buscar produtos, comparar preços e ver a distância das feiras.
Feirantes podem cadastrar produtos e o administrador possui funções básicas
de gerenciamento.


Histórias de Usuário
----------------------------------------

Usuário:
- EU001: Buscar produtos por nome
- EU002: Ordenar por preço, distância ou nota
- EU003: Filtrar por feira ou por distância máxima

Feirante:
- EU004: Cadastrar produtos
- EU005: Ver e responder mensagens (não finalizada)

Administrador:
- EU006: Gerenciar categorias e permissões
- EU007: Ver relatórios e estatísticas

Todas foram implementadas, exceto a EU005.


Processo de Desenvolvimento
----------------------------------------
Começamos criando as classes principais (Produto, Feira, Feirante,
Usuário e Sistema).
Depois disso, configuramos o servidor web em C++, que foi uma das partes
que mais deu trabalho, principalmente porque o comportamento variava
entre diferentes máquinas e sistemas.

A interface web foi feita por último, conectando HTML/JS com as funções
do backend.
Também usamos algumas assertivas simples para deixar as funções mais claras
e ajudar a identificar erros durante os testes.


Tecnologias Utilizadas
----------------------------------------
- C++17 para o backend
- HTML, CSS e JavaScript para o frontend
- Servidor HTTP simples em C++
- Git e GitHub para controle de versão


Integração Frontend–Backend
----------------------------------------

Para conectar o frontend ao backend, criamos um servidor HTTP simples em C++.
O JavaScript das páginas envia requisições usando "fetch()", e o servidor
responde com JSON. Cada endpoint corresponde a uma função do Sistema.

Com isso, a parte visual (HTML/JS) ficou separada da lógica em C++,
e conseguimos fazer o navegador comunicar diretamente com o backend.


Principais Dificuldades
----------------------------------------
- Fazer o servidor funcionar de maneira igual em todos os ambientes
  (no Windows só funcionou bem usando Git Bash / MSYS2 MinGW).
- Ligar corretamente o frontend com o backend.
- Organizar os dados das feiras e produtos.
- Implementar a parte dos feirantes e do administrador de forma consistente.


O que Ficou Faltando
----------------------------------------
A única funcionalidade não concluída foi a parte de mensagens entre
usuário e feirante (EU005).
Ela chegou a ser iniciada, mas não deu tempo de finalizar.


O Que Aprendemos
----------------------------------------
- Como organizar e estruturar um projeto maior em C++
- Importância de definir classes cedo para evitar retrabalho
- Diferenças entre rodar o programa no Windows, Linux e Git Bash
- Como integrar um backend em C++ com páginas web usando HTML/JS


Conclusão
----------------------------------------
O sistema implementa praticamente todas as histórias de usuário propostas.
Apesar das dificuldades técnicas, conseguimos entregar um projeto funcional,
com exceção da parte de mensagens, que não foi finalizada a tempo.
