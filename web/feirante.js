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

function carregarMensagens() {
    if (!feiranteLogado) return;

    // Carregar mensagens do localStorage
    const mensagens = JSON.parse(localStorage.getItem('mensagens') || '[]');
    const minhasMensagens = mensagens.filter(m =>
        m.feirante === feiranteLogado.nome || m.feira === feiranteLogado.feira
    );

    const badge = document.getElementById('badgeMensagens');
    badge.textContent = minhasMensagens.length;

    if (minhasMensagens.length === 0) {
        document.getElementById('listaMensagens').innerHTML = `
            <div class="alert alert-info">
                <i class="bi bi-info-circle"></i> Nenhuma mensagem recebida ainda.
            </div>
        `;
        return;
    }

    let html = '';
    minhasMensagens.forEach((msg, index) => {
        html += `
            <div class="card mb-3">
                <div class="card-header">
                    <strong><i class="bi bi-person"></i> ${msg.cliente || 'Cliente'}</strong>
                    <small class="text-muted float-end">${new Date(msg.data).toLocaleString('pt-BR')}</small>
                </div>
                <div class="card-body">
                    <p class="card-text">${msg.mensagem}</p>
                    <button class="btn btn-sm btn-primary" onclick="responderMensagem(${index})">
                        <i class="bi bi-reply"></i> Responder
                    </button>
                </div>
            </div>
        `;
    });

    document.getElementById('listaMensagens').innerHTML = html;
}

function responderMensagem(index) {
    const mensagens = JSON.parse(localStorage.getItem('mensagens') || '[]');
    const msg = mensagens[index];

    const resposta = prompt('Digite sua resposta:');
    if (resposta) {
        alert('Resposta enviada! (Funcionalidade em desenvolvimento)');
        // Aqui você implementaria o envio real da resposta
    }
}
