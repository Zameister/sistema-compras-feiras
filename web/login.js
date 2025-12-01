// Sistema de Login e Cadastro - JavaScript

// Localização das RAs do DF
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

/**
 * Cadastro de novo usuário
 */
async function cadastrarUsuario(event) {
    event.preventDefault();

    const nome = document.getElementById('cadastroNome').value;
    const ra = document.getElementById('cadastroRA').value;
    const senha = document.getElementById('cadastroSenha').value;

    const resultDiv = document.getElementById('resultadoCadastroUsuario');
    resultDiv.innerHTML = '<div class="alert alert-info"><i class="bi bi-hourglass-split"></i> Criando conta...</div>';

    // Verificar se usuário já existe
    const usuarios = JSON.parse(localStorage.getItem('usuarios') || '[]');
    const usuarioExistente = usuarios.find(u => u.nome.toLowerCase() === nome.toLowerCase());

    if (usuarioExistente) {
        resultDiv.innerHTML = `
            <div class="alert alert-danger">
                <i class="bi bi-x-circle"></i> Usuário já cadastrado! Use o formulário de login.
            </div>
        `;
        return;
    }

    // Criar novo usuário
    const novoUsuario = {
        nome: nome,
        ra: ra,
        senha: senha,
        dataCadastro: new Date().toISOString()
    };

    usuarios.push(novoUsuario);
    localStorage.setItem('usuarios', JSON.stringify(usuarios));

    // Registrar no backend
    try {
        const url = `http://localhost:8080/api/admin/usuario?nome=${encodeURIComponent(nome)}&ra=${encodeURIComponent(ra)}`;
        await fetch(url);
        console.log('✅ Usuário registrado no backend');
    } catch (error) {
        console.warn('⚠️ Não foi possível registrar no backend:', error);
    }

    resultDiv.innerHTML = `
        <div class="alert alert-success">
            <i class="bi bi-check-circle"></i> Conta criada com sucesso! Faça login para continuar.
        </div>
    `;

    // Limpar formulário
    document.getElementById('formCadastroUsuario').reset();

    // Mudar para aba de login após 1.5 segundos
    setTimeout(() => {
        const loginTab = document.getElementById('user-login-tab');
        loginTab.click();
    }, 1500);
}

/**
 * Login de usuário existente
 */
async function loginUsuario(event) {
    event.preventDefault();

    const nome = document.getElementById('loginNome').value;
    const senha = document.getElementById('loginSenha').value;

    const resultDiv = document.getElementById('resultadoLoginUsuario');
    resultDiv.innerHTML = '<div class="alert alert-info"><i class="bi bi-hourglass-split"></i> Autenticando...</div>';

    // Verificar credenciais
    const usuarios = JSON.parse(localStorage.getItem('usuarios') || '[]');
    const usuario = usuarios.find(u =>
        u.nome.toLowerCase() === nome.toLowerCase() && u.senha === senha
    );

    if (!usuario) {
        resultDiv.innerHTML = `
            <div class="alert alert-danger">
                <i class="bi bi-x-circle"></i> Nome ou senha incorretos!
            </div>
        `;
        return;
    }

    // Criar sessão
    const sessao = {
        tipo: 'usuario',
        nome: usuario.nome,
        ra: usuario.ra,
        localizacao: localizacoes[usuario.ra] || { lat: -15.794, lng: -47.883 }
    };

    localStorage.setItem('sessao', JSON.stringify(sessao));

    resultDiv.innerHTML = '<div class="alert alert-success"><i class="bi bi-check-circle"></i> Login realizado com sucesso!</div>';

    // Redirecionar para a página principal
    setTimeout(() => {
        window.location.href = 'index.html';
    }, 1000);
}

/**
 * Cadastro de novo administrador
 */
async function cadastrarAdmin(event) {
    event.preventDefault();

    const usuario = document.getElementById('cadastroAdminUser').value;
    const senha = document.getElementById('cadastroAdminSenha').value;

    const resultDiv = document.getElementById('resultadoCadastroAdmin');
    resultDiv.innerHTML = '<div class="alert alert-info"><i class="bi bi-hourglass-split"></i> Criando conta admin...</div>';

    // Verificar se admin já existe
    const admins = JSON.parse(localStorage.getItem('admins') || '[]');
    const adminExistente = admins.find(a => a.usuario.toLowerCase() === usuario.toLowerCase());

    if (adminExistente) {
        resultDiv.innerHTML = `
            <div class="alert alert-danger">
                <i class="bi bi-x-circle"></i> Administrador já cadastrado! Use o formulário de login.
            </div>
        `;
        return;
    }

    // Criar novo admin
    const novoAdmin = {
        usuario: usuario,
        senha: senha,
        dataCadastro: new Date().toISOString()
    };

    admins.push(novoAdmin);
    localStorage.setItem('admins', JSON.stringify(admins));

    resultDiv.innerHTML = `
        <div class="alert alert-success">
            <i class="bi bi-check-circle"></i> Conta de administrador criada! Faça login para continuar.
        </div>
    `;

    // Limpar formulário
    document.getElementById('formCadastroAdmin').reset();

    // Mudar para aba de login após 1.5 segundos
    setTimeout(() => {
        const loginTab = document.getElementById('admin-login-tab');
        loginTab.click();
    }, 1500);
}

/**
 * Login de administrador existente
 */
async function loginAdmin(event) {
    event.preventDefault();

    const usuario = document.getElementById('loginAdminUser').value;
    const senha = document.getElementById('loginAdminSenha').value;

    const resultDiv = document.getElementById('resultadoLoginAdmin');
    resultDiv.innerHTML = '<div class="alert alert-info"><i class="bi bi-hourglass-split"></i> Verificando credenciais...</div>';

    // Verificar credenciais
    const admins = JSON.parse(localStorage.getItem('admins') || '[]');
    const admin = admins.find(a =>
        a.usuario.toLowerCase() === usuario.toLowerCase() && a.senha === senha
    );

    if (!admin) {
        resultDiv.innerHTML = `
            <div class="alert alert-danger">
                <i class="bi bi-x-circle"></i> Usuário ou senha incorretos!
            </div>
        `;
        return;
    }

    // Criar sessão de admin
    const sessao = {
        tipo: 'admin',
        usuario: admin.usuario
    };

    localStorage.setItem('sessao', JSON.stringify(sessao));

    resultDiv.innerHTML = '<div class="alert alert-success"><i class="bi bi-check-circle"></i> Login de administrador realizado!</div>';

    // Redirecionar para o painel administrativo
    setTimeout(() => {
        window.location.href = 'admin.html';
    }, 1000);
}
