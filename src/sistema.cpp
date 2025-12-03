/**
 * @file sistema.cpp
 * @brief Implementacao da classe Sistema
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 *
 * Implementa o sistema principal de busca e comparacao de produtos em feiras.
 * Gerencia usuarios, feiras, produtos e calculo de distancias.
 *
 * Historias de Usuario: EU001, EU002, EU003, EU006, EU007
 */

#include "sistema.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <tuple>

using namespace std;

// ========================== AUXILIARES ===============================

/**
 * @brief Limpa o buffer de entrada
 *
 * Remove caracteres pendentes do buffer para evitar problemas com cin.
 */
void LimparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * @brief Pausa a execucao aguardando ENTER
 *
 * Exibe mensagem e aguarda usuario pressionar ENTER para continuar.
 */
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
    // Mapa de Regioes Administrativas do DF
    mapaRegioes = {
        {"plano piloto", Location(-15.793889, -47.882778)},
        {"asa norte", Location(-15.750000, -47.880000)},
        {"asa sul", Location(-15.830000, -47.920000)},
        {"gama", Location(-16.016667, -48.066667)},
        {"taguatinga", Location(-15.835000, -48.050000)},
        {"brazlandia", Location(-15.670000, -48.200000)},
        {"brazlandia", Location(-15.670000, -48.200000)},
        {"sobradinho", Location(-15.650000, -47.780000)},
        {"planaltina", Location(-15.610000, -47.640000)},
        {"paranoa", Location(-15.780000, -47.780000)},
        {"paranoa", Location(-15.780000, -47.780000)},
        {"nucleo bandeirante", Location(-15.870000, -47.950000)},
        {"nucleo bandeirante", Location(-15.870000, -47.950000)},
        {"ceilandia", Location(-15.817000, -48.112000)},
        {"ceilandia", Location(-15.817000, -48.112000)},
        {"guara", Location(-15.842200, -47.980300)},
        {"guara", Location(-15.842200, -47.980300)},
        {"cruzeiro", Location(-15.790000, -47.950000)},
        {"samambaia", Location(-15.860000, -48.080000)},
        {"santa maria", Location(-16.020000, -48.040000)},
        {"sao sebastiao", Location(-15.890000, -47.780000)},
        {"sao sebastiao", Location(-15.890000, -47.780000)},
        {"recanto das emas", Location(-15.905000, -48.050000)},
        {"lago sul", Location(-15.840000, -47.880000)},
        {"riacho fundo", Location(-15.880000, -47.970000)},
        {"lago norte", Location(-15.720000, -47.890000)},
        {"candangolandia", Location(-15.860000, -47.950000)},
        {"candangolandia", Location(-15.860000, -47.950000)},
        {"aguas claras", Location(-15.840000, -48.020000)},
        {"aguas claras", Location(-15.840000, -48.020000)},
        {"riacho fundo ii", Location(-15.920000, -47.980000)},
        {"sudoeste", Location(-15.790000, -47.930000)},
        {"varjao", Location(-15.720000, -47.860000)},
        {"varjao", Location(-15.720000, -47.860000)},
        {"park way", Location(-15.870000, -47.960000)},
        {"estrutural", Location(-15.790000, -47.950000)},
        {"jardim botanico", Location(-15.880000, -47.820000)},
        {"itapoa", Location(-15.730000, -47.770000)},
        {"vicente pires", Location(-15.820000, -48.000000)},
    };

    // =================== FEIRAS PRE-CADASTRADAS ===================

    feiras.emplace_back("Feira da Ceilandia", "Quadra 12, Ceilandia Sul",
                        Location(-15.817000, -48.112000));

    feiras.emplace_back("Feira da Asa Sul", "308 Sul",
                        Location(-15.810700, -47.912700));

    feiras.emplace_back("Feira do Guara", "QE 25",
                        Location(-15.842200, -47.980300));

    feiras[0].AdicionarProduto(Produto("Tomate", 3.50, "Hortifruti", "Feira da Ceilandia"));
    feiras[0].AdicionarProduto(Produto("Banana", 4.20, "Frutas", "Feira da Ceilandia"));

    feiras[1].AdicionarProduto(Produto("Maca", 5.00, "Frutas", "Feira da Asa Sul"));
    feiras[1].AdicionarProduto(Produto("Cenoura", 2.50, "Hortifruti", "Feira da Asa Sul"));

    feiras[2].AdicionarProduto(Produto("Alface", 2.00, "Verduras", "Feira do Guara"));
}

// ======================= FUNCOES DO SISTEMA =============================

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
        cout << "Indice invalido.\n";
        return;
    }

    LimparBuffer();

    const Feira& f = feiras[idx - 1];

    cout << "\n=== PRODUTOS EM " << f.GetNome() << " ===\n";
    for (const auto& p : f.GetProdutos()) {
        cout << "- " << p.GetNome() << " (R$ " << p.GetPreco() << ")\n";
    }
}

// ==============================================================================
// EU003: Como usuario, quero calcular a distancia ate uma feira
//        para planejar meu deslocamento
// ==============================================================================
void Sistema::CalcularDistancia() const {  // EU003
    if (!usuarioCadastrado) {
        cout << "\n⚠ Cadastre um usuario primeiro!\n";
        return;
    }

    ListarFeiras();

    cout << "\nEscolha a feira: ";
    int idx;
    cin >> idx;

    if (cin.fail() || idx < 1 || idx > (int)feiras.size()) {
        LimparBuffer();
        cout << "Indice invalido.\n";
        return;
    }
    LimparBuffer();

    const Feira& f = feiras[idx - 1];

    double dist = usuario.DistanciaPara(f);

    cout << "\nDistancia entre " << usuario.GetNome()
         << " e " << f.GetNome() << ": "
         << dist << " km\n";
}

// ==============================================================================
// EU005: Como usuario, quero me cadastrar informando minha regiao
//        para receber informacoes personalizadas sobre feiras proximas
// ==============================================================================
void Sistema::CadastrarUsuario() {  // EU005
    string nome, regiao;
    cout << "\n=== CADASTRAR USUARIO ===\n";

    cout << "Nome: ";
    getline(cin, nome);

    cout << "Regiao Administrativa: ";
    getline(cin, regiao);

    string chave = NormalizarMinusculo(regiao);

    if (mapaRegioes.count(chave) == 0) {
        cout << "\nRegiao nao encontrada.\n";
        Pausar();
        return;
    }

    usuario = Usuario(nome, mapaRegioes[chave]);
    usuarioCadastrado = true;

    cout << "\nUsuario cadastrado com sucesso!\n";
    Pausar();
}

// ======================== MENU PRINCIPAL ===============================

void Sistema::Menu() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=== SISTEMA DE COMPRAS EM FEIRAS ===\n";
        cout << "1. Cadastrar usuario\n";
        cout << "2. Listar feiras\n";
        cout << "3. Ver produtos de uma feira\n";
        cout << "4. Calcular distancia ate uma feira\n";
        cout << "5. Buscar produtos\n";
        cout << "6. Filtrar feiras\n";
        cout << "0. Sair\n";
        cout << "Opcao: ";

        cin >> opcao;
        LimparBuffer();

        switch (opcao) {
            case 1: CadastrarUsuario(); break;
            case 2: ListarFeiras(); Pausar(); break;
            case 3: MostrarProdutosDaFeira(); Pausar(); break;
            case 4: CalcularDistancia(); Pausar(); break;
            case 5:
                BuscarProdutos();
                Pausar();
                break;
            case 6:
                FiltrarFeiras();
                Pausar();
                break;
            case 0:
                cout << "\nEncerrando...\n";
                break;
            default:
                cout << "Opcao invalida.\n";
                Pausar();
                break;
        }
    }
}

// ==============================================================================
// EU001: Como usuario, quero procurar produtos pelo nome para encontrar
//        os melhores precos nas feiras proximas
// ==============================================================================
void Sistema::BuscarProdutos() {  // EU001
    std::string termo;
    std::cout << "\n=== BUSCAR PRODUTOS ===\n";
    std::cout << "Digite o nome do produto (ou parte dele): ";
    std::getline(std::cin, termo);
    
    // Normalizar busca (minusculas)
    std::transform(termo.begin(), termo.end(), termo.begin(), ::tolower);
    
    if (termo.empty()) {
        std::cout << "Termo de busca nao pode ser vazio!\n";
        return;
    }
    
    std::vector<std::tuple<std::string, double, std::string, std::string>> resultados;
    
    // Buscar em todas as feiras
    for (const auto& feira : feiras) {
        for (const auto& produto : feira.GetProdutos()) {
            std::string nomeProduto = produto.GetNome();
            std::transform(nomeProduto.begin(), nomeProduto.end(),
                          nomeProduto.begin(), ::tolower);

            if (nomeProduto.find(termo) != std::string::npos) {
                resultados.push_back(std::make_tuple(
                    produto.GetNome(),
                    produto.GetPreco(),
                    produto.GetCategoria(),
                    feira.GetNome()
                ));
            }
        }
    }
    
    if (resultados.empty()) {
        std::cout << "\nNenhum produto encontrado com o termo: " << termo << "\n";
    } else {
        std::cout << "\n=== RESULTADOS DA BUSCA ===\n";
        std::cout << "Encontrados " << resultados.size() << " produto(s):\n\n";
        
        for (const auto& resultado : resultados) {
            std::cout << "Produto: " << std::get<0>(resultado) << "\n";
            std::cout << "Preco: R$ " << std::fixed << std::setprecision(2) 
                     << std::get<1>(resultado) << "\n";
            std::cout << "Categoria: " << std::get<2>(resultado) << "\n";
            std::cout << "Feira: " << std::get<3>(resultado) << "\n";
            std::cout << "----------------------------\n";
        }
    }
}

// ==============================================================================
// EU002: Como usuario, quero filtrar feiras por categoria, produto ou preco
//        para encontrar opcoes que atendam minhas necessidades
// ==============================================================================
void Sistema::FiltrarFeiras() {  // EU002
    std::cout << "\n=== FILTRAR FEIRAS ===\n";
    std::cout << "1. Filtrar por categoria de produto\n";
    std::cout << "2. Filtrar por produto especifico\n";
    std::cout << "3. Filtrar por preco maximo\n";
    std::cout << "Escolha uma opcao: ";
    
    int opcao;
    std::cin >> opcao;
    LimparBuffer();
    
    switch (opcao) {
        case 1: {
            std::string categoria;
            std::cout << "Digite a categoria: ";
            std::getline(std::cin, categoria);
            
            std::cout << "\n=== FEIRAS COM PRODUTOS DA CATEGORIA: " << categoria << " ===\n";
            bool encontrou = false;
            
            for (const auto& feira : feiras) {
                bool temCategoria = false;
                for (const auto& produto : feira.GetProdutos()) {
                    if (produto.GetCategoria() == categoria) {
                        temCategoria = true;
                        break;
                    }
                }
                
                if (temCategoria) {
                    std::cout << "Feira: " << feira.GetNome() << "\n";
                    std::cout << "Endereco: " << feira.GetEndereco() << "\n";
                    std::cout << "----------------------------\n";
                    encontrou = true;
                }
            }
            
            if (!encontrou) {
                std::cout << "Nenhuma feira encontrada com essa categoria.\n";
            }
            break;
        }
        
        case 2: {
            std::string nomeProduto;
            std::cout << "Digite o nome do produto: ";
            std::getline(std::cin, nomeProduto);
            
            std::transform(nomeProduto.begin(), nomeProduto.end(), 
                          nomeProduto.begin(), ::tolower);
            
            std::cout << "\n=== FEIRAS QUE VENDEM: " << nomeProduto << " ===\n";
            bool encontrou = false;
            
            for (const auto& feira : feiras) {
                bool temProduto = false;
                for (const auto& produto : feira.GetProdutos()) {
                    std::string nomeTemp = produto.GetNome();
                    std::transform(nomeTemp.begin(), nomeTemp.end(),
                                  nomeTemp.begin(), ::tolower);

                    if (nomeTemp.find(nomeProduto) != std::string::npos) {
                        temProduto = true;
                        break;
                    }
                }

                if (temProduto) {
                    std::cout << "Feira: " << feira.GetNome() << "\n";
                    std::cout << "Endereco: " << feira.GetEndereco() << "\n";
                    std::cout << "----------------------------\n";
                    encontrou = true;
                }
            }
            
            if (!encontrou) {
                std::cout << "Nenhuma feira encontrada com esse produto.\n";
            }
            break;
        }
        
        case 3: {
            double precoMax;
            std::cout << "Digite o preco maximo: R$ ";
            std::cin >> precoMax;
            LimparBuffer();
            
            std::cout << "\n=== FEIRAS COM PRODUTOS ATE R$ " << std::fixed 
                     << std::setprecision(2) << precoMax << " ===\n";
            bool encontrou = false;
            
            for (const auto& feira : feiras) {
                bool temProdutoBarato = false;
                for (const auto& produto : feira.GetProdutos()) {
                    if (produto.GetPreco() <= precoMax) {
                        temProdutoBarato = true;
                        break;
                    }
                }
                
                if (temProdutoBarato) {
                    std::cout << "Feira: " << feira.GetNome() << "\n";
                    std::cout << "Endereco: " << feira.GetEndereco() << "\n";
                    std::cout << "----------------------------\n";
                    encontrou = true;
                }
            }
            
            if (!encontrou) {
                std::cout << "Nenhuma feira encontrada nessa faixa de preco.\n";
            }
            break;
        }
        
        default:
            std::cout << "Opcao invalida!\n";
            break;
    }
}

// ========== Metodos para API REST ==========

const std::vector<Feira>& Sistema::GetFeiras() const {
    return feiras;
}

void Sistema::AdicionarFeira(const Feira& feira) {
    feiras.push_back(feira);
}
