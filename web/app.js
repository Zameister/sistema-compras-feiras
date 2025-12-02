// Sistema de Compras em Feiras - JavaScript
// INTEGRADO COM BACKEND C++ via API REST

// Dados carregados do backend
let feirasData = [];

// Estado da aplicação
let usuarioAtual = null;

// Inicialização
document.addEventListener('DOMContentLoaded', function() {
    verificarLogin();
    carregarFeirasDoBackend();
    carregarUsuario();
});

// ========== CONTROLE DE SESSÃO ==========

/**
 * Verificar se usuário está logado
 */
function verificarLogin() {
    const sessao = localStorage.getItem('sessao');

    if (!sessao) {
        window.location.href = 'login.html';
        return;
    }

    const usuario = JSON.parse(sessao);

    if (usuario.tipo !== 'usuario') {
        alert('Acesso restrito a usuários!');
        window.location.href = 'login.html';
        return;
    }
}

/**
 * Logout do sistema
 */
function logout() {
    localStorage.removeItem('sessao');
    localStorage.removeItem('usuario');
    window.location.href = 'login.html';
}

// ========== INTEGRAÇÃO COM BACKEND C++ ==========

/**
 * Carregar feiras do backend C++
 */
async function carregarFeirasDoBackend() {
    try {
        const response = await fetch('http://localhost:8080/api/feiras');
        const data = await response.json();
        feirasData = data.feiras || [];

        console.log('✅ Feiras carregadas do backend C++:', feirasData.length);
        carregarFeiras();
    } catch (error) {
        console.error('❌ Erro ao carregar feiras do backend:', error);
        alert('Erro ao conectar com o backend. Verifique se o servidor está rodando.');
    }
}

/**
 * Buscar produtos via API
 */
async function buscarProdutos() {
    const termo = document.getElementById('searchInput').value.trim();

    if (!termo) {
        alert('Digite algo para buscar!');
        return;
    }

    try {
        const response = await fetch(`http://localhost:8080/api/buscar?termo=${encodeURIComponent(termo)}`);
        const data = await response.json();

        mostrarResultados(data.resultados, `Resultados para "${termo}"`);
        console.log('✅ Busca realizada no backend C++');
    } catch (error) {
        console.error('❌ Erro ao buscar produtos:', error);
        alert('Erro ao buscar produtos. Verifique a conexão com o backend.');
    }
}

/**
 * Aplicar filtros via API
 */
async function aplicarFiltros() {
    const categoria = document.getElementById('filterCategoria').value;
    const precoMax = document.getElementById('filterPreco').value;
    const ra = document.getElementById('filterRA').value;

    try {
        let url = 'http://localhost:8080/api/filtrar?';
        if (categoria) url += `categoria=${encodeURIComponent(categoria)}&`;
        if (precoMax) url += `precoMax=${precoMax}&`;
        if (ra) url += `ra=${encodeURIComponent(ra)}&`;

        const response = await fetch(url);
        const data = await response.json();

        const titulo = `Filtros: ${categoria || 'Todas'} - Max R$ ${precoMax || '∞'} - ${ra || 'Todas RAs'}`;
        mostrarResultados(data.resultados, titulo);
        console.log('✅ Filtros aplicados no backend C++');
    } catch (error) {
        console.error('❌ Erro ao filtrar:', error);
        alert('Erro ao filtrar. Verifique a conexão com o backend.');
    }
}

// ========== FUNÇÕES DE INTERFACE ==========

// Carregar feiras na interface
function carregarFeiras() {
    const container = document.getElementById('listaFeiras');
    container.innerHTML = '';

    // Encontrar feira mais próxima
    let feiraMaisProxima = null;
    let menorDistancia = Infinity;

    if (usuarioAtual) {
        feirasData.forEach(feira => {
            const dist = parseFloat(calcularDistancia(feira));
            if (dist < menorDistancia) {
                menorDistancia = dist;
                feiraMaisProxima = feira;
            }
        });
    }

    feirasData.forEach(feira => {
        const isMaisProxima = feiraMaisProxima && feira.nome === feiraMaisProxima.nome;
        const card = criarCardFeira(feira, isMaisProxima);
        container.innerHTML += card;
    });

    // Mostrar alerta da feira mais próxima
    if (feiraMaisProxima) {
        mostrarFeiraMaisProxima(feiraMaisProxima, menorDistancia);
    }
}

/**
 * Mostrar destaque da feira mais próxima
 */
function mostrarFeiraMaisProxima(feira, distancia) {
    const container = document.getElementById('feiraMaisProxima');
    if (!container) return;

    container.innerHTML = `
        <div class="alert alert-success alert-dismissible fade show">
            <h5 class="alert-heading"><i class="bi bi-geo-alt-fill"></i> Feira Mais Próxima de Você!</h5>
            <p class="mb-1"><strong>${feira.nome}</strong> - ${feira.endereco}</p>
            <p class="mb-0"><i class="bi bi-compass"></i> Apenas <strong>${distancia.toFixed(1)} km</strong> de distância</p>
            <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
        </div>
    `;
}

// Criar card de feira
function criarCardFeira(feira, isMaisProxima = false) {
    const numProdutos = feira.produtos.length;
    const distancia = usuarioAtual ? calcularDistancia(feira) : '...';
    const destaque = isMaisProxima ? 'border-success border-3' : '';
    const badge = isMaisProxima ? '<span class="badge bg-warning text-dark"><i class="bi bi-star-fill"></i> Mais Próxima!</span>' : '';

    return `
        <div class="col fade-in">
            <div class="card feira-card shadow-sm h-100 ${destaque}">
                <div class="card-body">
                    <h5 class="card-title">
                        <i class="bi bi-shop text-success"></i> ${feira.nome}
                        ${badge}
                    </h5>
                    <p class="card-text">
                        <i class="bi bi-geo-alt"></i> ${feira.endereco}<br>
                    </p>
                    <div class="d-flex justify-content-between align-items-center">
                        <span class="badge bg-success">${numProdutos} produtos</span>
                        ${usuarioAtual ? `<small class="feira-distancia"><i class="bi bi-compass"></i> ${distancia} km</small>` : ''}
                    </div>
                    <button class="btn btn-outline-success btn-sm mt-3 w-100" onclick="verProdutosFeira('${feira.nome}')">
                        <i class="bi bi-eye"></i> Ver Produtos
                    </button>
                </div>
            </div>
        </div>
    `;
}

// Limpar filtros
function limparFiltros() {
    document.getElementById('filterCategoria').value = '';
    document.getElementById('filterPreco').value = '';
    document.getElementById('filterRA').value = '';
    document.getElementById('resultadoBusca').innerHTML = '';
}

// Mostrar resultados
function mostrarResultados(produtos, titulo, ordenacao = 'preco') {
    const container = document.getElementById('resultadoBusca');

    if (produtos.length === 0) {
        container.innerHTML = `
            <div class="col-12">
                <div class="alert alert-warning">
                    <i class="bi bi-exclamation-triangle"></i> Nenhum produto encontrado.
                </div>
            </div>
        `;
        return;
    }

    // Salvar produtos globalmente para reordenação
    window.produtosAtivos = produtos;
    window.tituloAtivo = titulo;

    // Aplicar ordenação
    ordenarProdutos(ordenacao);
}

// Função para ordenar produtos
function ordenarProdutos(criterio) {
    if (!window.produtosAtivos) return;

    const produtos = [...window.produtosAtivos];
    let textoOrdenacao = '';

    switch(criterio) {
        case 'preco':
            produtos.sort((a, b) => a.preco - b.preco);
            textoOrdenacao = 'menor preço';
            break;
        case 'distancia':
            if (usuarioAtual) {
                produtos.forEach(p => {
                    const feira = feirasData.find(f => f.nome === p.feira);
                    if (feira) {
                        p.distanciaCalculada = parseFloat(calcularDistancia(feira));
                    }
                });
                produtos.sort((a, b) => (a.distanciaCalculada || 999) - (b.distanciaCalculada || 999));
                textoOrdenacao = 'menor distância';
            } else {
                textoOrdenacao = 'menor preço (faça login para ordenar por distância)';
                produtos.sort((a, b) => a.preco - b.preco);
            }
            break;
        case 'nota':
            produtos.sort((a, b) => (b.nota || 0) - (a.nota || 0));
            textoOrdenacao = 'maior nota';
            break;
    }

    const container = document.getElementById('resultadoBusca');
    container.innerHTML = `
        <div class="col-12 mb-3">
            <div class="d-flex justify-content-between align-items-center flex-wrap mb-3">
                <div>
                    <h4><i class="bi bi-search"></i> ${window.tituloAtivo}</h4>
                    <p class="text-muted">Encontrados ${produtos.length} produto(s) - ordenados por ${textoOrdenacao}</p>
                    <p class="badge bg-success">Dados do Backend C++</p>
                </div>
                <div class="btn-group" role="group">
                    <button type="button" class="btn btn-sm btn-outline-primary ${criterio === 'preco' ? 'active' : ''}" onclick="ordenarProdutos('preco')">
                        <i class="bi bi-currency-dollar"></i> Preço
                    </button>
                    <button type="button" class="btn btn-sm btn-outline-primary ${criterio === 'distancia' ? 'active' : ''}" onclick="ordenarProdutos('distancia')">
                        <i class="bi bi-geo-alt"></i> Distância
                    </button>
                    <button type="button" class="btn btn-sm btn-outline-primary ${criterio === 'nota' ? 'active' : ''}" onclick="ordenarProdutos('nota')">
                        <i class="bi bi-star-fill"></i> Nota
                    </button>
                </div>
            </div>
        </div>
    `;

    produtos.forEach(produto => {
        const card = criarCardProduto(produto);
        container.innerHTML += card;
    });

    // Scroll suave para resultados
    container.scrollIntoView({ behavior: 'smooth' });
}

// Criar card de produto
function criarCardProduto(produto) {
    const corCategoria = {
        'Hortifruti': 'success',
        'Grãos': 'warning',
        'Carnes': 'danger',
        'Laticínios': 'info',
        'Padaria': 'secondary',
        'Frutas': 'success'
    };

    const cor = corCategoria[produto.categoria] || 'primary';

    // Gerar estrelas baseado na nota
    const nota = produto.nota || 0;
    const numAvaliacoes = produto.numAvaliacoes || 0;
    let estrelas = '';

    for (let i = 1; i <= 5; i++) {
        if (i <= Math.floor(nota)) {
            estrelas += '<i class="bi bi-star-fill text-warning"></i>';
        } else if (i === Math.ceil(nota) && nota % 1 !== 0) {
            estrelas += '<i class="bi bi-star-half text-warning"></i>';
        } else {
            estrelas += '<i class="bi bi-star text-warning"></i>';
        }
    }

    const notaHtml = numAvaliacoes > 0 ? `
        <div class="mb-2">
            <span class="small">${estrelas} <strong>${nota.toFixed(1)}</strong> (${numAvaliacoes} avaliações)</span>
        </div>
    ` : '<div class="mb-2"><small class="text-muted">Sem avaliações</small></div>';

    return `
        <div class="col fade-in">
            <div class="card produto-card shadow-sm h-100">
                <div class="card-body">
                    <div class="d-flex justify-content-between align-items-start mb-2">
                        <h5 class="card-title mb-0">${produto.nome}</h5>
                        <span class="badge bg-${cor} badge-categoria">${produto.categoria}</span>
                    </div>
                    ${notaHtml}
                    <p class="produto-preco mb-2">R$ ${produto.preco.toFixed(2)}</p>
                    <p class="card-text text-muted">
                        <i class="bi bi-shop"></i> ${produto.feira}<br>
                        <small><i class="bi bi-geo-alt"></i> ${produto.feiraRA}</small>
                    </p>
                    <div class="d-grid gap-2">
                        <button class="btn btn-success btn-sm" onclick="abrirModalMensagem('${produto.nome}', '${produto.feira}')">
                            <i class="bi bi-chat-dots"></i> Enviar Mensagem
                        </button>
                    </div>
                </div>
            </div>
        </div>
    `;
}

// Ver produtos de uma feira específica
function verProdutosFeira(nomeFeira) {
    const feira = feirasData.find(f => f.nome === nomeFeira);

    if (!feira) return;

    const produtos = feira.produtos.map(p => ({
        ...p,
        feira: feira.nome,
        feiraRA: feira.endereco
    }));

    mostrarResultados(produtos, `Produtos da ${nomeFeira}`);
}

// ========== CADASTRO DE USUÁRIO ==========

// Cadastrar usuário
async function cadastrarUsuario(event) {
    event.preventDefault();

    const nome = document.getElementById('userName').value;
    const ra = document.getElementById('userRA').value;

    // Localização das RAs (simulado - coordenadas aproximadas)
    const localizacoes = {
        'Ceilândia': { lat: -15.817, lng: -48.112 },
        'Taguatinga': { lat: -15.839, lng: -48.052 },
        'Samambaia': { lat: -15.878, lng: -48.085 },
        'Plano Piloto': { lat: -15.794, lng: -47.883 },
        'Águas Claras': { lat: -15.834, lng: -48.026 },
        'Gama': { lat: -16.009, lng: -48.064 },
        'Santa Maria': { lat: -16.007, lng: -48.015 },
        'Recanto das Emas': { lat: -15.903, lng: -48.063 },
        'Sobradinho': { lat: -15.649, lng: -47.784 },
        'Planaltina': { lat: -15.614, lng: -47.641 }
    };

    usuarioAtual = {
        nome: nome,
        ra: ra,
        localizacao: localizacoes[ra] || { lat: -15.794, lng: -47.883 }
    };

    // Salvar no localStorage
    localStorage.setItem('usuario', JSON.stringify(usuarioAtual));

    // Registrar no backend (para admin ver)
    try {
        const url = `http://localhost:8080/api/admin/usuario?nome=${encodeURIComponent(nome)}&ra=${encodeURIComponent(ra)}`;
        await fetch(url);
        console.log('✅ Usuário registrado no backend');
    } catch (error) {
        console.warn('⚠️ Não foi possível registrar no backend:', error);
    }

    // Mostrar informações
    document.getElementById('displayName').textContent = nome;
    document.getElementById('displayRA').textContent = ra;
    document.getElementById('userInfo').classList.remove('d-none');

    // Recarregar feiras com distâncias
    carregarFeiras();

    // Scroll suave
    document.getElementById('userInfo').scrollIntoView({ behavior: 'smooth' });
}

// Carregar usuário do localStorage
function carregarUsuario() {
    const saved = localStorage.getItem('usuario');

    if (saved) {
        usuarioAtual = JSON.parse(saved);
        document.getElementById('userName').value = usuarioAtual.nome;
        document.getElementById('userRA').value = usuarioAtual.ra;
        document.getElementById('displayName').textContent = usuarioAtual.nome;
        document.getElementById('displayRA').textContent = usuarioAtual.ra;
        document.getElementById('userInfo').classList.remove('d-none');
    }
}

// ========== CÁLCULO DE DISTÂNCIA GPS ==========

// Calcular distância entre usuário e feira (Haversine)
function calcularDistancia(feira) {
    if (!usuarioAtual) return '?';

    const R = 6371; // Raio da Terra em km
    const lat1 = usuarioAtual.localizacao.lat * Math.PI / 180;
    const lat2 = feira.latitude * Math.PI / 180;
    const dLat = (feira.latitude - usuarioAtual.localizacao.lat) * Math.PI / 180;
    const dLon = (feira.longitude - usuarioAtual.localizacao.lng) * Math.PI / 180;

    const a = Math.sin(dLat/2) * Math.sin(dLat/2) +
              Math.cos(lat1) * Math.cos(lat2) *
              Math.sin(dLon/2) * Math.sin(dLon/2);

    const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
    const distancia = R * c;

    return distancia.toFixed(1);
}

// ========== SMOOTH SCROLL ==========

// Smooth scroll para âncoras
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        e.preventDefault();
        const target = document.querySelector(this.getAttribute('href'));
        if (target) {
            target.scrollIntoView({ behavior: 'smooth' });
        }
    });
});

// ========== SISTEMA DE MENSAGENS ==========

let mensagemAtual = { produto: '', feira: '' };

/**
 * Abrir modal de mensagem
 */
function abrirModalMensagem(produto, feira) {
    // Verificar se usuário está logado
    const sessao = localStorage.getItem('sessao');

    if (!sessao) {
        alert('Por favor, faça login para enviar mensagens aos feirantes.');
        window.location.href = 'login.html';
        return;
    }

    const usuario = JSON.parse(sessao);

    if (usuario.tipo !== 'usuario') {
        alert('Apenas usuários podem enviar mensagens aos feirantes.');
        return;
    }

    // Definir informações da mensagem
    mensagemAtual = { produto, feira };

    document.getElementById('mensagemProduto').textContent = produto;
    document.getElementById('mensagemFeira').textContent = feira;
    document.getElementById('textoMensagem').value = '';
    document.getElementById('resultadoMensagem').innerHTML = '';

    // Abrir modal
    const modal = new bootstrap.Modal(document.getElementById('modalMensagem'));
    modal.show();
}

/**
 * Enviar mensagem ao feirante
 */
async function enviarMensagem(event) {
    event.preventDefault();

    const sessao = JSON.parse(localStorage.getItem('sessao') || '{}');
    const texto = document.getElementById('textoMensagem').value.trim();
    const resultDiv = document.getElementById('resultadoMensagem');

    if (!texto) {
        resultDiv.innerHTML = `
            <div class="alert alert-warning">
                <i class="bi bi-exclamation-triangle"></i> Por favor, digite uma mensagem.
            </div>
        `;
        return;
    }

    resultDiv.innerHTML = '<div class="alert alert-info"><i class="bi bi-hourglass-split"></i> Enviando mensagem...</div>';

    // Criar objeto de mensagem
    const novaMensagem = {
        id: Date.now(),
        de: sessao.nome || 'Usuário',
        produto: mensagemAtual.produto,
        feira: mensagemAtual.feira,
        texto: texto,
        data: new Date().toISOString(),
        lida: false
    };

    // Obter mensagens existentes do localStorage
    let mensagens = JSON.parse(localStorage.getItem('mensagens') || '[]');
    mensagens.push(novaMensagem);
    localStorage.setItem('mensagens', JSON.stringify(mensagens));

    resultDiv.innerHTML = `
        <div class="alert alert-success alert-dismissible fade show">
            <i class="bi bi-check-circle"></i> Mensagem enviada com sucesso!
            O feirante receberá sua mensagem em breve.
            <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
        </div>
    `;

    // Limpar formulário
    document.getElementById('formMensagem').reset();

    // Fechar modal após 2 segundos
    setTimeout(() => {
        const modalElement = document.getElementById('modalMensagem');
        const modal = bootstrap.Modal.getInstance(modalElement);
        if (modal) modal.hide();
    }, 2000);

    console.log('✅ Mensagem enviada:', novaMensagem);
}
