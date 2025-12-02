// Painel Administrativo - JavaScript
// Sistema de Compras em Feiras

let feirasData = [];

// Inicialização
document.addEventListener('DOMContentLoaded', function() {
    verificarLoginAdmin();
    carregarFeiras();
    carregarUsuarios();
});

// ========== CONTROLE DE SESSÃO ==========

/**
 * Verificar se administrador está logado
 */
function verificarLoginAdmin() {
    const sessao = localStorage.getItem('sessao');

    if (!sessao) {
        window.location.href = 'login.html';
        return;
    }

    const usuario = JSON.parse(sessao);

    if (usuario.tipo !== 'admin') {
        alert('Acesso restrito a administradores!');
        window.location.href = 'login.html';
        return;
    }
}

/**
 * Logout do sistema
 */
function logoutAdmin() {
    localStorage.removeItem('sessao');
    window.location.href = 'login.html';
}

// ========== CARREGAR DADOS ==========

/**
 * Carregar feiras do backend
 */
async function carregarFeiras() {
    try {
        const response = await fetch('http://localhost:8080/api/feiras');
        const data = await response.json();
        feirasData = data.feiras || [];

        // Preencher selects de feira
        preencherSelectFeiras();

        console.log('✅ Feiras carregadas:', feirasData.length);
    } catch (error) {
        console.error('❌ Erro ao carregar feiras:', error);
        alert('Erro ao conectar com o backend!');
    }
}

/**
 * Preencher selects com nomes das feiras
 */
function preencherSelectFeiras() {
    const selectAdicionar = document.getElementById('feiraAdicionar');
    const selectRemover = document.getElementById('feiraRemover');

    // Limpar selects
    selectAdicionar.innerHTML = '<option value="">Selecione a feira...</option>';
    selectRemover.innerHTML = '<option value="">Selecione a feira...</option>';

    // Adicionar opções
    feirasData.forEach(feira => {
        const option1 = document.createElement('option');
        option1.value = feira.nome;
        option1.textContent = feira.nome;
        selectAdicionar.appendChild(option1);

        const option2 = document.createElement('option');
        option2.value = feira.nome;
        option2.textContent = `${feira.nome} (${feira.produtos.length} produtos)`;
        selectRemover.appendChild(option2);
    });
}

// ========== USUÁRIOS ==========

/**
 * Carregar usuários cadastrados
 */
async function carregarUsuarios() {
    try {
        const response = await fetch('http://localhost:8080/api/admin/usuarios');
        const data = await response.json();

        const tbody = document.getElementById('tabelaUsuarios');
        const totalDiv = document.getElementById('totalUsuarios');

        if (data.usuarios.length === 0) {
            tbody.innerHTML = `
                <tr>
                    <td colspan="4" class="text-center text-muted">
                        <i class="bi bi-inbox"></i> Nenhum usuário cadastrado ainda
                    </td>
                </tr>
            `;
            totalDiv.innerHTML = '<i class="bi bi-info-circle"></i> <strong>Total:</strong> 0 usuários';
        } else {
            tbody.innerHTML = '';
            data.usuarios.forEach((user, index) => {
                const row = document.createElement('tr');
                row.innerHTML = `
                    <td>${index + 1}</td>
                    <td><i class="bi bi-person-circle"></i> ${user.nome}</td>
                    <td><i class="bi bi-geo-alt-fill"></i> ${user.ra}</td>
                    <td><i class="bi bi-calendar-check"></i> ${user.dataCadastro}</td>
                `;
                tbody.appendChild(row);
            });

            totalDiv.innerHTML = `
                <i class="bi bi-people-fill"></i> <strong>Total:</strong> ${data.total} usuário(s) cadastrado(s)
            `;
        }

        console.log('✅ Usuários carregados:', data.total);
    } catch (error) {
        console.error('❌ Erro ao carregar usuários:', error);
        document.getElementById('tabelaUsuarios').innerHTML = `
            <tr>
                <td colspan="4" class="text-center text-danger">
                    <i class="bi bi-exclamation-triangle"></i> Erro ao carregar usuários
                </td>
            </tr>
        `;
    }
}

// ========== ADICIONAR PRODUTO ==========

/**
 * Adicionar produto via formulário
 */
async function adicionarProduto(event) {
    event.preventDefault();

    const feira = document.getElementById('feiraAdicionar').value;
    const nome = document.getElementById('nomeProduto').value;
    const preco = document.getElementById('precoProduto').value;
    const categoria = document.getElementById('categoriaProduto').value;

    const resultDiv = document.getElementById('resultadoAdicionar');
    resultDiv.innerHTML = '<div class="alert alert-info"><i class="bi bi-hourglass-split"></i> Adicionando produto...</div>';

    try {
        const url = `http://localhost:8080/api/admin/produto/adicionar?` +
                    `feira=${encodeURIComponent(feira)}&` +
                    `nome=${encodeURIComponent(nome)}&` +
                    `preco=${preco}&` +
                    `categoria=${encodeURIComponent(categoria)}`;

        const response = await fetch(url);
        const data = await response.json();

        if (data.success) {
            resultDiv.innerHTML = `
                <div class="alert alert-success alert-dismissible fade show">
                    <i class="bi bi-check-circle-fill"></i> ${data.message}
                    <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
                </div>
            `;

            // Limpar formulário
            document.getElementById('formAdicionarProduto').reset();

            // Recarregar feiras
            await carregarFeiras();

            console.log('✅ Produto adicionado:', nome);
        } else {
            resultDiv.innerHTML = `
                <div class="alert alert-danger alert-dismissible fade show">
                    <i class="bi bi-x-circle-fill"></i> ${data.error}
                    <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
                </div>
            `;
        }
    } catch (error) {
        console.error('❌ Erro ao adicionar produto:', error);
        resultDiv.innerHTML = `
            <div class="alert alert-danger alert-dismissible fade show">
                <i class="bi bi-exclamation-triangle-fill"></i> Erro ao conectar com o backend
                <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
            </div>
        `;
    }
}

// ========== REMOVER PRODUTO ==========

/**
 * Carregar produtos da feira selecionada
 */
function carregarProdutosFeira() {
    const feiraSelect = document.getElementById('feiraRemover');
    const produtoSelect = document.getElementById('produtoRemover');
    const feiraName = feiraSelect.value;

    if (!feiraName) {
        produtoSelect.innerHTML = '<option value="">Selecione a feira primeiro...</option>';
        return;
    }

    const feira = feirasData.find(f => f.nome === feiraName);

    if (!feira || feira.produtos.length === 0) {
        produtoSelect.innerHTML = '<option value="">Nenhum produto nesta feira</option>';
        return;
    }

    produtoSelect.innerHTML = '<option value="">Selecione o produto...</option>';
    feira.produtos.forEach(produto => {
        const option = document.createElement('option');
        option.value = produto.nome;
        option.textContent = `${produto.nome} - R$ ${produto.preco.toFixed(2)} (${produto.categoria})`;
        produtoSelect.appendChild(option);
    });
}

/**
 * Remover produto via formulário
 */
async function removerProduto(event) {
    event.preventDefault();

    const feira = document.getElementById('feiraRemover').value;
    const nome = document.getElementById('produtoRemover').value;

    // Confirmação
    if (!confirm(`Tem certeza que deseja remover "${nome}" da ${feira}?\n\nEsta ação não pode ser desfeita!`)) {
        return;
    }

    const resultDiv = document.getElementById('resultadoRemover');
    resultDiv.innerHTML = '<div class="alert alert-info"><i class="bi bi-hourglass-split"></i> Removendo produto...</div>';

    try {
        const url = `http://localhost:8080/api/admin/produto/remover?` +
                    `feira=${encodeURIComponent(feira)}&` +
                    `nome=${encodeURIComponent(nome)}`;

        const response = await fetch(url);
        const data = await response.json();

        if (data.success) {
            resultDiv.innerHTML = `
                <div class="alert alert-success alert-dismissible fade show">
                    <i class="bi bi-check-circle-fill"></i> ${data.message}
                    <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
                </div>
            `;

            // Limpar formulário
            document.getElementById('formRemoverProduto').reset();

            // Recarregar feiras e produtos
            await carregarFeiras();
            carregarProdutosFeira();

            console.log('✅ Produto removido:', nome);
        } else {
            resultDiv.innerHTML = `
                <div class="alert alert-danger alert-dismissible fade show">
                    <i class="bi bi-x-circle-fill"></i> ${data.error}
                    <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
                </div>
            `;
        }
    } catch (error) {
        console.error('❌ Erro ao remover produto:', error);
        resultDiv.innerHTML = `
            <div class="alert alert-danger alert-dismissible fade show">
                <i class="bi bi-exclamation-triangle-fill"></i> Erro ao conectar com o backend
                <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
            </div>
        `;
    }
}

// ========== RELATÓRIOS ==========

/**
 * Gerar relatórios e estatísticas
 */
async function gerarRelatorio() {
    try {
        const response = await fetch('http://localhost:8080/api/feiras');
        const data = await response.json();
        const feiras = data.feiras || [];

        // Coletar todos os produtos
        let todosProdutos = [];
        feiras.forEach(feira => {
            feira.produtos.forEach(produto => {
                todosProdutos.push({
                    ...produto,
                    feira: feira.nome,
                    distancia: parseFloat(calcularDistancia(feira)) || 0
                });
            });
        });

        // Top 5 Produtos Mais Bem Avaliados
        const topAvaliacoes = [...todosProdutos]
            .filter(p => p.nota > 0)
            .sort((a, b) => b.nota - a.nota)
            .slice(0, 5);

        let htmlTopAvaliacoes = '<ol class="list-group list-group-numbered">';
        topAvaliacoes.forEach(p => {
            const estrelas = gerarEstrelas(p.nota);
            htmlTopAvaliacoes += `
                <li class="list-group-item d-flex justify-content-between align-items-start">
                    <div class="ms-2 me-auto">
                        <div class="fw-bold">${p.nome}</div>
                        <small class="text-muted">${p.feira} - R$ ${p.preco.toFixed(2)}</small>
                    </div>
                    <span class="badge bg-warning rounded-pill">${estrelas} ${p.nota.toFixed(1)}</span>
                </li>
            `;
        });
        htmlTopAvaliacoes += '</ol>';
        document.getElementById('topAvaliacoes').innerHTML = htmlTopAvaliacoes;

        // Produtos Mais Baratos
        const maisBaratos = [...todosProdutos]
            .sort((a, b) => a.preco - b.preco)
            .slice(0, 5);

        let htmlMaisBaratos = '<ol class="list-group list-group-numbered">';
        maisBaratos.forEach(p => {
            htmlMaisBaratos += `
                <li class="list-group-item d-flex justify-content-between align-items-start">
                    <div class="ms-2 me-auto">
                        <div class="fw-bold">${p.nome}</div>
                        <small class="text-muted">${p.feira} - ${p.categoria}</small>
                    </div>
                    <span class="badge bg-success rounded-pill">R$ ${p.preco.toFixed(2)}</span>
                </li>
            `;
        });
        htmlMaisBaratos += '</ol>';
        document.getElementById('maisBaratos').innerHTML = htmlMaisBaratos;

        // Feiras Mais Populares (por número de produtos)
        const feirasComProdutos = feiras.map(f => ({
            nome: f.nome,
            produtos: f.produtos.length,
            mediaPreco: f.produtos.reduce((sum, p) => sum + p.preco, 0) / f.produtos.length
        })).sort((a, b) => b.produtos - a.produtos);

        let htmlFeirasPopulares = '<div class="list-group">';
        feirasPopulares.forEach(f => {
            htmlFeirasPopulares += `
                <div class="list-group-item">
                    <div class="d-flex w-100 justify-content-between">
                        <h6 class="mb-1"><i class="bi bi-shop-window"></i> ${f.nome}</h6>
                        <small class="text-success">${f.produtos} produtos</small>
                    </div>
                    <p class="mb-1">
                        <small class="text-muted">Preço médio: R$ ${f.mediaPreco.toFixed(2)}</small>
                    </p>
                </div>
            `;
        });
        htmlFeirasPopulares += '</div>';
        document.getElementById('feirasPopulares').innerHTML = htmlFeirasPopulares;

        // Estatísticas Gerais
        const totalProdutos = todosProdutos.length;
        const totalFeiras = feiras.length;
        const precoMedio = todosProdutos.reduce((sum, p) => sum + p.preco, 0) / totalProdutos;
        const notaMedia = todosProdutos.filter(p => p.nota > 0)
            .reduce((sum, p) => sum + p.nota, 0) / todosProdutos.filter(p => p.nota > 0).length;

        let htmlEstatisticas = `
            <div class="row text-center">
                <div class="col-6 mb-3">
                    <div class="card">
                        <div class="card-body">
                            <h3 class="text-primary">${totalProdutos}</h3>
                            <p class="mb-0 text-muted">Total de Produtos</p>
                        </div>
                    </div>
                </div>
                <div class="col-6 mb-3">
                    <div class="card">
                        <div class="card-body">
                            <h3 class="text-info">${totalFeiras}</h3>
                            <p class="mb-0 text-muted">Total de Feiras</p>
                        </div>
                    </div>
                </div>
                <div class="col-6">
                    <div class="card">
                        <div class="card-body">
                            <h3 class="text-success">R$ ${precoMedio.toFixed(2)}</h3>
                            <p class="mb-0 text-muted">Preço Médio</p>
                        </div>
                    </div>
                </div>
                <div class="col-6">
                    <div class="card">
                        <div class="card-body">
                            <h3 class="text-warning">${gerarEstrelas(notaMedia)} ${notaMedia.toFixed(1)}</h3>
                            <p class="mb-0 text-muted">Nota Média</p>
                        </div>
                    </div>
                </div>
            </div>
        `;
        document.getElementById('estatisticasGerais').innerHTML = htmlEstatisticas;

        console.log('✅ Relatório gerado com sucesso');
    } catch (error) {
        console.error('❌ Erro ao gerar relatório:', error);
        document.getElementById('topAvaliacoes').innerHTML = '<p class="text-danger">Erro ao carregar dados</p>';
    }
}

/**
 * Gerar HTML de estrelas
 */
function gerarEstrelas(nota) {
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
    return estrelas;
}

/**
 * Calcular distância (função auxiliar)
 */
function calcularDistancia(feira) {
    const sessao = JSON.parse(localStorage.getItem('sessao') || '{}');
    if (!sessao.localizacao || !feira.localizacao) return '999';

    const lat1 = sessao.localizacao.lat;
    const lon1 = sessao.localizacao.lng;
    const lat2 = feira.localizacao.lat;
    const lon2 = feira.localizacao.lng;

    const R = 6371; // Raio da Terra em km
    const dLat = (lat2 - lat1) * Math.PI / 180;
    const dLon = (lon2 - lon1) * Math.PI / 180;
    const a = Math.sin(dLat / 2) * Math.sin(dLat / 2) +
              Math.cos(lat1 * Math.PI / 180) * Math.cos(lat2 * Math.PI / 180) *
              Math.sin(dLon / 2) * Math.sin(dLon / 2);
    const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
    const distancia = R * c;

    return distancia.toFixed(1);
}

// ========== CATEGORIAS ==========

/**
 * Adicionar nova categoria
 */
function adicionarCategoria(event) {
    event.preventDefault();

    const nomeCategoria = document.getElementById('novaCategoria').value.trim();
    const resultDiv = document.getElementById('resultadoCategoria');

    if (!nomeCategoria) {
        resultDiv.innerHTML = `
            <div class="alert alert-warning">
                <i class="bi bi-exclamation-triangle"></i> Por favor, digite um nome para a categoria.
            </div>
        `;
        return;
    }

    // Obter categorias atuais do localStorage
    let categorias = JSON.parse(localStorage.getItem('categorias') || '["Hortifruti","Grãos","Carnes","Laticínios","Padaria","Frutas"]');

    // Verificar se categoria já existe
    if (categorias.includes(nomeCategoria)) {
        resultDiv.innerHTML = `
            <div class="alert alert-warning alert-dismissible fade show">
                <i class="bi bi-exclamation-circle"></i> Categoria "${nomeCategoria}" já existe!
                <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
            </div>
        `;
        return;
    }

    // Adicionar nova categoria
    categorias.push(nomeCategoria);
    localStorage.setItem('categorias', JSON.stringify(categorias));

    resultDiv.innerHTML = `
        <div class="alert alert-success alert-dismissible fade show">
            <i class="bi bi-check-circle"></i> Categoria "${nomeCategoria}" adicionada com sucesso!
            <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
        </div>
    `;

    // Limpar formulário
    document.getElementById('formAdicionarCategoria').reset();

    // Atualizar lista de categorias
    atualizarListaCategorias();

    // Atualizar selects em outras abas
    atualizarSelectsCategorias();

    console.log('✅ Categoria adicionada:', nomeCategoria);
}

/**
 * Atualizar lista de categorias exibida
 */
function atualizarListaCategorias() {
    const categorias = JSON.parse(localStorage.getItem('categorias') || '["Hortifruti","Grãos","Carnes","Laticínios","Padaria","Frutas"]');
    const divLista = document.getElementById('listaCategorias');

    const cores = ['success', 'warning', 'danger', 'info', 'secondary', 'primary'];
    let html = '';

    categorias.forEach((cat, index) => {
        const cor = cores[index % cores.length];
        html += `<span class="badge bg-${cor} m-1">${cat}</span>`;
    });

    divLista.innerHTML = html;
}

/**
 * Atualizar selects de categoria nas outras abas
 */
function atualizarSelectsCategorias() {
    const categorias = JSON.parse(localStorage.getItem('categorias') || '["Hortifruti","Grãos","Carnes","Laticínios","Padaria","Frutas"]');
    const selectCategoria = document.getElementById('categoriaProduto');

    // Manter valor selecionado atual
    const valorAtual = selectCategoria.value;

    // Reconstruir opções
    selectCategoria.innerHTML = '<option value="">Selecione...</option>';
    categorias.forEach(cat => {
        const option = document.createElement('option');
        option.value = cat;
        option.textContent = cat;
        if (cat === valorAtual) option.selected = true;
        selectCategoria.appendChild(option);
    });
}

// Inicializar lista de categorias ao carregar a página
document.addEventListener('DOMContentLoaded', function() {
    atualizarListaCategorias();
});
