// Sistema de Compras em Feiras - JavaScript
// INTEGRADO COM BACKEND C++ via API REST

// Dados carregados do backend
let feirasData = [];

// Estado da aplicação
let usuarioAtual = null;

// Inicialização
document.addEventListener('DOMContentLoaded', function() {
    carregarFeirasDoBackend();
    carregarUsuario();
});

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

    feirasData.forEach(feira => {
        const card = criarCardFeira(feira);
        container.innerHTML += card;
    });
}

// Criar card de feira
function criarCardFeira(feira) {
    const numProdutos = feira.produtos.length;
    const distancia = usuarioAtual ? calcularDistancia(feira) : '...';

    return `
        <div class="col fade-in">
            <div class="card feira-card shadow-sm h-100">
                <div class="card-body">
                    <h5 class="card-title">
                        <i class="bi bi-shop text-success"></i> ${feira.nome}
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
function mostrarResultados(produtos, titulo) {
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

    // Ordenar por preço
    produtos.sort((a, b) => a.preco - b.preco);

    container.innerHTML = `
        <div class="col-12 mb-3">
            <h4><i class="bi bi-search"></i> ${titulo}</h4>
            <p class="text-muted">Encontrados ${produtos.length} produto(s) - ordenados por menor preço</p>
            <p class="badge bg-success">Dados do Backend C++</p>
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
        'Padaria': 'secondary'
    };

    const cor = corCategoria[produto.categoria] || 'primary';

    return `
        <div class="col fade-in">
            <div class="card produto-card shadow-sm h-100">
                <div class="card-body">
                    <div class="d-flex justify-content-between align-items-start mb-2">
                        <h5 class="card-title mb-0">${produto.nome}</h5>
                        <span class="badge bg-${cor} badge-categoria">${produto.categoria}</span>
                    </div>
                    <p class="produto-preco mb-2">R$ ${produto.preco.toFixed(2)}</p>
                    <p class="card-text text-muted">
                        <i class="bi bi-shop"></i> ${produto.feira}<br>
                        <small><i class="bi bi-geo-alt"></i> ${produto.feiraRA}</small>
                    </p>
                    <button class="btn btn-success btn-sm w-100">
                        <i class="bi bi-cart-plus"></i> Ver Detalhes
                    </button>
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
function cadastrarUsuario(event) {
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
