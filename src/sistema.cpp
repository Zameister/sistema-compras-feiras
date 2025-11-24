#include "sistema.h"
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

// ========================== AUXILIARES ===============================

void LimparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Pausar() {
    cout << "\nPressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string Sistema::NormalizarMinusculo(const string& s) const {
    string r = s;
    transform(r.begin(), r.end(), r.begin(),
              [](unsigned char c){ return static_cast<char>(tolower(c)); });
    return r;
}

// ========================== CONSTRUTOR ================================

Sistema::Sistema() :
    usuario("undefined", Location(0,0)),
    usuarioCadastrado(false)
{
    // Mapa de Regiões Administrativas do DF
    mapaRegioes = {
        {"plano piloto", Location(-15.793889, -47.882778)},
        {"asa norte", Location(-15.750000, -47.880000)},
        {"asa sul", Location(-15.830000, -47.920000)},
        {"gama", Location(-16.016667, -48.066667)},
        {"taguatinga", Location(-15.835000, -48.050000)},
        {"brazlandia", Location(-15.670000, -48.200000)},
        {"brazlândia", Location(-15.670000, -48.200000)},
        {"sobradinho", Location(-15.650000, -47.780000)},
        {"planaltina", Location(-15.610000, -47.640000)},
        {"paranoa", Location(-15.780000, -47.780000)},
        {"paranoá", Location(-15.780000, -47.780000)},
        {"nucleo bandeirante", Location(-15.870000, -47.950000)},
        {"núcleo bandeirante", Location(-15.870000, -47.950000)},
        {"ceilandia", Location(-15.817000, -48.112000)},
        {"ceilândia", Location(-15.817000, -48.112000)},
        {"guara", Location(-15.842200, -47.980300)},
        {"guará", Location(-15.842200, -47.980300)},
        {"cruzeiro", Location(-15.790000, -47.950000)},
        {"samambaia", Location(-15.860000, -48.080000)},
        {"santa maria", Location(-16.020000, -48.040000)},
        {"sao sebastiao", Location(-15.890000, -47.780000)},
        {"são sebastião", Location(-15.890000, -47.780000)},
        {"recanto das emas", Location(-15.905000, -48.050000)},
        {"lago sul", Location(-15.840000, -47.880000)},
        {"riacho fundo", Location(-15.880000, -47.970000)},
        {"lago norte", Location(-15.720000, -47.890000)},
        {"candangolandia", Location(-15.860000, -47.950000)},
        {"candangolândia", Location(-15.860000, -47.950000)},
        {"aguas claras", Location(-15.840000, -48.020000)},
        {"águas claras", Location(-15.840000, -48.020000)},
        {"riacho fundo ii", Location(-15.920000, -47.980000)},
        {"sudoeste", Location(-15.790000, -47.930000)},
        {"varjao", Location(-15.720000, -47.860000)},
        {"varjão", Location(-15.720000, -47.860000)},
        {"park way", Location(-15.870000, -47.960000)},
        {"estrutural", Location(-15.790000, -47.950000)},
        {"jardim botanico", Location(-15.880000, -47.820000)},
        {"itapoa", Location(-15.730000, -47.770000)},
        {"vicente pires", Location(-15.820000, -48.000000)},
    };

    // =================== FEIRAS PRÉ-CADASTRADAS ===================

    feiras.emplace_back("Feira da Ceilândia", "Quadra 12, Ceilândia Sul",
                        Location(-15.817000, -48.112000));

    feiras.emplace_back("Feira da Asa Sul", "308 Sul",
                        Location(-15.810700, -47.912700));

    feiras.emplace_back("Feira do Guará", "QE 25",
                        Location(-15.842200, -47.980300));

    feiras[0].AdicionarProduto(Produto("Tomate", 3.50, "Hortifruti"));
    feiras[0].AdicionarProduto(Produto("Banana", 4.20, "Frutas"));

    feiras[1].AdicionarProduto(Produto("Maçã", 5.00, "Frutas"));
    feiras[1].AdicionarProduto(Produto("Cenoura", 2.50, "Hortifruti"));

    feiras[2].AdicionarProduto(Produto("Alface", 2.00, "Verduras"));
}

// ======================= FUNÇÕES DO SISTEMA =============================

void Sistema::ListarFeiras() const {
    cout << "\n=== FEIRAS CADASTRADAS ===\n";

    for (size_t i = 0; i < feiras.size(); i++) {
        cout << i + 1 << ") " << feiras[i].GetNome()
             << " — " << feiras[i].GetEndereco() << "\n";
    }
}

void Sistema::MostrarProdutosDaFeira() const {
    ListarFeiras();

    cout << "\nEscolha a feira: ";
    int idx;
    cin >> idx;

    if (cin.fail() || idx < 1 || idx > (int)feiras.size()) {
        LimparBuffer();
        cout << "Índice inválido.\n";
        return;
    }

    LimparBuffer();

    const Feira& f = feiras[idx - 1];

    cout << "\n=== PRODUTOS EM " << f.GetNome() << " ===\n";
    for (const auto& p : f.GetProdutos()) {
        cout << "- " << p.getNome() << " (R$ " << p.getPreco() << ")\n";
    }
}

void Sistema::CalcularDistancia() const {
    if (!usuarioCadastrado) {
        cout << "\n⚠ Cadastre um usuário primeiro!\n";
        return;
    }

    ListarFeiras();

    cout << "\nEscolha a feira: ";
    int idx;
    cin >> idx;

    if (cin.fail() || idx < 1 || idx > (int)feiras.size()) {
        LimparBuffer();
        cout << "Índice inválido.\n";
        return;
    }
    LimparBuffer();

    const Feira& f = feiras[idx - 1];

    double dist = usuario.DistanciaPara(f);

    cout << "\nDistância entre " << usuario.GetNome()
         << " e " << f.GetNome() << ": "
         << dist << " km\n";
}

void Sistema::CadastrarUsuario() {
    string nome, regiao;
    cout << "\n=== CADASTRAR USUÁRIO ===\n";

    cout << "Nome: ";
    getline(cin, nome);

    cout << "Região Administrativa: ";
    getline(cin, regiao);

    string chave = NormalizarMinusculo(regiao);

    if (mapaRegioes.count(chave) == 0) {
        cout << "\nRegião não encontrada.\n";
        Pausar();
        return;
    }

    usuario = Usuario(nome, mapaRegioes[chave]);
    usuarioCadastrado = true;

    cout << "\nUsuário cadastrado com sucesso!\n";
    Pausar();
}

// ======================== MENU PRINCIPAL ===============================

void Sistema::Menu() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=== SISTEMA DE COMPRAS EM FEIRAS ===\n";
        cout << "1. Cadastrar usuário\n";
        cout << "2. Listar feiras\n";
        cout << "3. Ver produtos de uma feira\n";
        cout << "4. Calcular distância até uma feira\n";
        cout << "5. (Arthur) Buscar produtos\n";
        cout << "6. (Arthur) Filtrar feiras\n";
        cout << "0. Sair\n";
        cout << "Opção: ";

        cin >> opcao;
        LimparBuffer();

        switch (opcao) {
            case 1: CadastrarUsuario(); break;
            case 2: ListarFeiras(); Pausar(); break;
            case 3: MostrarProdutosDaFeira(); Pausar(); break;
            case 4: CalcularDistancia(); Pausar(); break;

            case 5:
            case 6:
                cout << "\nFunção em desenvolvimento pelo Arthur.\n";
                Pausar();
                break;

            case 0:
                cout << "\nEncerrando...\n";
                break;

            default:
                cout << "Opção inválida.\n";
                Pausar();
                break;
        }
    }
}
