// Painel do Feirante - JavaScript

let feiranteLogado = null;

// Inicialização
document.addEventListener('DOMContentLoaded', function() {
    verificarLoginFeirante();
    carregarMeusProdutos();
    carregarMensagens();
});

// ========== CONTROLE DE SESSÃO ==========

function verificarLoginFeirante() {
    const sessao = localStorage.getItem('sessao');

    if (!sessao) {
        window.location.href = 'login.html';
        return;
    }

    const usuario = JSON.parse(sessao);

    if (usuario.tipo !== 'feirante') {
        alert('Acesso restrito a feirantes!');
        window.location.href = 'login.html';
        return;
    }

    feiranteLogado = usuario;

    // Exibir informações do feirante
    document.getElementById('feiranteInfo').textContent =
        `${usuario.banca} - ${usuario.feira}`;
}

function logoutFeirante() {
    localStorage.removeItem('sessao');
    window.location.href = 'login.html';
}

// ========== GERENCIAR PRODUTOS ==========

async function carregarMeusProdutos() {
    if (!feiranteLogado) return;

    try {
        const response = await fetch('http://localhost:8080/api/feiras');
        const data = await response.json();

        // Encontrar a feira do feirante
        const minhaFeira = data.feiras.find(f => f.nome === feiranteLogado.feira);

        if (!minhaFeira) {
            document.getElementById('listaProdutos').innerHTML = `
                <div class="alert alert-warning">
                    <i class="bi bi-exclamation-triangle"></i> Feira não encontrada.
                </div>
            `;
            return;
        }

        const produtos = minhaFeira.produtos || [];

        if (produtos.length === 0) {
            document.getElementById('listaProdutos').innerHTML = `
                <div class="alert alert-info">
                    <i class="bi bi-info-circle"></i> Você ainda não tem produtos cadastrados.
                </div>
            `;
            return;
        }

        let html = '<div class="table-responsive"><table class="table table-striped table-hover">';
        html += `
            <thead class="table-success">
                <tr>
                    <th>#</th>
                    <th>Produto</th>
                    <th>Categoria</th>
                    <th>Preço</th>
                    <th>Avaliação</th>
                    <th>Ações</th>
                </tr>
            </thead>
            <tbody>
        `;

        produtos.forEach((produto, index) => {
            const nota = produto.nota || 0;
            const numAvaliacoes = produto.numAvaliacoes || 0;
            let estrelas = '';
            for (let i = 1; i <= 5; i++) {
                if (i <= Math.floor(nota)) {
                    estrelas += '<i class="bi bi-star-fill text-warning"></i>';
                } else {
                    estrelas += '<i class="bi bi-star text-warning"></i>';
                }
            }

            html += `
                <tr>
                    <td>${index + 1}</td>
                    <td><strong>${produto.nome}</strong></td>
                    <td><span class="badge bg-secondary">${produto.categoria}</span></td>
                    <td>R$ ${produto.preco.toFixed(2)}</td>
                    <td>${estrelas} ${nota.toFixed(1)} (${numAvaliacoes})</td>
                    <td>
                        <button class="btn btn-sm btn-danger" onclick="removerProduto('${produto.nome}')">
                            <i class="bi bi-trash"></i> Remover
                        </button>
                    </td>
                </tr>
            `;
        });

        html += '</tbody></table></div>';
        document.getElementById('listaProdutos').innerHTML = html;

    } catch (error) {
        console.error('Erro ao carregar produtos:', error);
        document.getElementById('listaProdutos').innerHTML = `
            <div class="alert alert-danger">
                <i class="bi bi-exclamation-triangle"></i> Erro ao carregar produtos.
            </div>
        `;
    }
}

async function adicionarProduto(event) {
    event.preventDefault();

    if (!feiranteLogado) return;

    const nome = document.getElementById('nomeProduto').value;
    const preco = parseFloat(document.getElementById('precoProduto').value);
    const categoria = document.getElementById('categoriaProduto').value;

    const resultDiv = document.getElementById('resultadoAdicionar');
    resultDiv.innerHTML = '<div class="alert alert-info"><i class="bi bi-hourglass-split"></i> Adicionando produto...</div>';

    try {
        const url = `http://localhost:8080/api/admin/produto/adicionar?feira=${encodeURIComponent(feiranteLogado.feira)}&nome=${encodeURIComponent(nome)}&preco=${preco}&categoria=${encodeURIComponent(categoria)}`;

        const response = await fetch(url, { method: 'POST' });
        const data = await response.json();

        if (data.success) {
            resultDiv.innerHTML = `
                <div class="alert alert-success">
                    <i class="bi bi-check-circle"></i> Produto adicionado com sucesso!
                </div>
            `;

            document.getElementById('formAdicionarProduto').reset();

            // Atualizar lista após 1 segundo
            setTimeout(() => {
                carregarMeusProdutos();
                resultDiv.innerHTML = '';
            }, 1500);
        } else {
            resultDiv.innerHTML = `
                <div class="alert alert-danger">
                    <i class="bi bi-x-circle"></i> ${data.error || 'Erro ao adicionar produto'}
                </div>
            `;
        }
    } catch (error) {
        console.error('Erro:', error);
        resultDiv.innerHTML = `
            <div class="alert alert-danger">
                <i class="bi bi-exclamation-triangle"></i> Erro ao conectar com o servidor.
            </div>
        `;
    }
}

async function removerProduto(nomeProduto) {
    if (!feiranteLogado) return;

    if (!confirm(`Tem certeza que deseja remover "${nomeProduto}"?`)) {
        return;
    }

    try {
        const url = `http://localhost:8080/api/admin/produto/remover?feira=${encodeURIComponent(feiranteLogado.feira)}&nome=${encodeURIComponent(nomeProduto)}`;

        const response = await fetch(url, { method: 'POST' });
        const data = await response.json();

        if (data.success) {
            alert('Produto removido com sucesso!');
            carregarMeusProdutos();
        } else {
            alert('Erro ao remover produto: ' + (data.error || 'Erro desconhecido'));
        }
    } catch (error) {
        console.error('Erro:', error);
        alert('Erro ao conectar com o servidor.');
    }
}

// ========== MENSAGENS ==========

/**
 * Carregar mensagens recebidas da feira
 */
function carregarMensagens() {
    if (!feiranteLogado) return;

    // Carregar mensagens do localStorage
    const mensagens = JSON.parse(localStorage.getItem('mensagens') || '[]');

    // Filtrar mensagens destinadas à feira do feirante
    const minhasMensagens = mensagens.filter(m => m.feira === feiranteLogado.feira);

    // Contar mensagens não lidas
    const naoLidas = minhasMensagens.filter(m => !m.lida).length;

    const badge = document.getElementById('badgeMensagens');
    badge.textContent = naoLidas;
    badge.classList.toggle('bg-danger', naoLidas > 0);
    badge.classList.toggle('bg-secondary', naoLidas === 0);

    const listaMensagens = document.getElementById('listaMensagens');

    if (minhasMensagens.length === 0) {
        listaMensagens.innerHTML = `
            <div class="alert alert-info">
                <i class="bi bi-inbox"></i> Nenhuma mensagem recebida ainda.
                <p class="mb-0 mt-2 small">
                    Quando clientes enviarem dúvidas sobre seus produtos, elas aparecerão aqui.
                </p>
            </div>
        `;
        return;
    }

    // Ordenar mensagens por data (mais recente primeiro)
    minhasMensagens.sort((a, b) => new Date(b.data) - new Date(a.data));

    let html = '<div class="list-group">';
    minhasMensagens.forEach((msg, index) => {
        const dataFormatada = new Date(msg.data).toLocaleString('pt-BR', {
            day: '2-digit',
            month: '2-digit',
            year: 'numeric',
            hour: '2-digit',
            minute: '2-digit'
        });

        const classeCard = msg.lida ? 'list-group-item' : 'list-group-item list-group-item-action border-primary';

        html += `
            <div class="${classeCard} mb-2">
                <div class="d-flex w-100 justify-content-between align-items-start">
                    <h6 class="mb-1">
                        <i class="bi bi-person-circle"></i> ${msg.de}
                        ${!msg.lida ? '<span class="badge bg-danger ms-2">Nova</span>' : ''}
                    </h6>
                    <small class="text-muted">${dataFormatada}</small>
                </div>
                <p class="mb-1">
                    <strong>Produto:</strong> ${msg.produto}
                </p>
                <p class="mb-2 mt-2 p-3 bg-light rounded">
                    <i class="bi bi-chat-quote"></i> ${msg.texto}
                </p>
                <div class="btn-group btn-group-sm">
                    ${!msg.lida ? `
                        <button class="btn btn-outline-success" onclick="marcarComoLida(${msg.id})">
                            <i class="bi bi-check2"></i> Marcar como lida
                        </button>
                    ` : ''}
                    <button class="btn btn-outline-primary" onclick="responderMensagem(${msg.id})">
                        <i class="bi bi-reply"></i> Responder
                    </button>
                </div>
            </div>
        `;
    });
    html += '</div>';

    listaMensagens.innerHTML = html;
}

/**
 * Marcar mensagem como lida
 */
function marcarComoLida(mensagemId) {
    let mensagens = JSON.parse(localStorage.getItem('mensagens') || '[]');
    const index = mensagens.findIndex(m => m.id === mensagemId);

    if (index !== -1) {
        mensagens[index].lida = true;
        localStorage.setItem('mensagens', JSON.stringify(mensagens));
        carregarMensagens();
        console.log('✅ Mensagem marcada como lida');
    }
}

/**
 * Responder mensagem
 */
function responderMensagem(mensagemId) {
    const mensagens = JSON.parse(localStorage.getItem('mensagens') || '[]');
    const msg = mensagens.find(m => m.id === mensagemId);

    if (!msg) return;

    const resposta = prompt(`Responder para ${msg.de} sobre "${msg.produto}":\n\nMensagem original: ${msg.texto}\n\nDigite sua resposta:`);

    if (resposta && resposta.trim()) {
        alert('✅ Resposta enviada com sucesso!\n\n(Em uma versão completa, a resposta seria enviada por email ou notificação ao cliente)');

        // Marcar como lida
        marcarComoLida(mensagemId);

        console.log('✅ Resposta:', resposta);
    }
}
