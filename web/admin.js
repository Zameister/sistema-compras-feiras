// Painel Administrativo - JavaScript
// Sistema de Compras em Feiras

let feirasData = [];

// Inicialização
document.addEventListener('DOMContentLoaded', function() {
    carregarFeiras();
    carregarUsuarios();
});

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
