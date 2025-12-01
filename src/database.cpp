/**
 * @file database.cpp
 * @brief Sistema de persistência de dados em JSON
 * @author Arthur Souza Chagas
 * @date 2025
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "../include/sistema.h"

// Estrutura para armazenar usuários cadastrados
struct UsuarioCadastrado {
    std::string nome;
    std::string ra;
    std::string dataCadastro;
};

// Lista global de usuários cadastrados
static std::vector<UsuarioCadastrado> usuariosCadastrados;

/**
 * @brief Inicializa banco de dados com dados padrão
 */
void InicializarBancoDeDados(Sistema* sistema) {
    // Feira 1: Ceilândia
    Location loc1(-15.817, -48.112);
    Feira feira1("Feira da Ceilândia", "QNM 11, Ceilândia Norte", loc1);
    feira1.AdicionarProduto(Produto("Tomate", 3.50, "Hortifruti", "Feira da Ceilândia"));
    feira1.AdicionarProduto(Produto("Alface", 2.00, "Hortifruti", "Feira da Ceilândia"));
    feira1.AdicionarProduto(Produto("Banana", 4.50, "Hortifruti", "Feira da Ceilândia"));
    feira1.AdicionarProduto(Produto("Arroz (kg)", 5.00, "Grãos", "Feira da Ceilândia"));
    sistema->AdicionarFeira(feira1);

    // Feira 2: Taguatinga
    Location loc2(-15.839, -48.052);
    Feira feira2("Feira de Taguatinga", "Pistão Sul, Taguatinga", loc2);
    feira2.AdicionarProduto(Produto("Tomate", 3.80, "Hortifruti", "Feira de Taguatinga"));
    feira2.AdicionarProduto(Produto("Batata (kg)", 4.20, "Hortifruti", "Feira de Taguatinga"));
    feira2.AdicionarProduto(Produto("Feijão (kg)", 7.00, "Grãos", "Feira de Taguatinga"));
    feira2.AdicionarProduto(Produto("Queijo (kg)", 35.00, "Laticínios", "Feira de Taguatinga"));
    sistema->AdicionarFeira(feira2);

    // Feira 3: Plano Piloto
    Location loc3(-15.794, -47.883);
    Feira feira3("Feira do Plano Piloto", "CLN 209, Asa Norte", loc3);
    feira3.AdicionarProduto(Produto("Tomate", 4.50, "Hortifruti", "Feira do Plano Piloto"));
    feira3.AdicionarProduto(Produto("Alface", 2.50, "Hortifruti", "Feira do Plano Piloto"));
    feira3.AdicionarProduto(Produto("Pão francês (kg)", 12.00, "Padaria", "Feira do Plano Piloto"));
    feira3.AdicionarProduto(Produto("Leite (L)", 5.50, "Laticínios", "Feira do Plano Piloto"));
    sistema->AdicionarFeira(feira3);

    // Feira 4: Samambaia
    Location loc4(-15.878, -48.085);
    Feira feira4("Feira de Samambaia", "QN 318, Samambaia Norte", loc4);
    feira4.AdicionarProduto(Produto("Banana", 4.00, "Hortifruti", "Feira de Samambaia"));
    feira4.AdicionarProduto(Produto("Maçã (kg)", 6.50, "Hortifruti", "Feira de Samambaia"));
    feira4.AdicionarProduto(Produto("Arroz (kg)", 4.80, "Grãos", "Feira de Samambaia"));
    feira4.AdicionarProduto(Produto("Frango (kg)", 15.00, "Carnes", "Feira de Samambaia"));
    sistema->AdicionarFeira(feira4);

    // Feira 5: Águas Claras
    Location loc5(-15.834, -48.026);
    Feira feira5("Feira de Águas Claras", "Avenida das Araucárias", loc5);
    feira5.AdicionarProduto(Produto("Tomate", 4.20, "Hortifruti", "Feira de Águas Claras"));
    feira5.AdicionarProduto(Produto("Alface", 2.30, "Hortifruti", "Feira de Águas Claras"));
    feira5.AdicionarProduto(Produto("Cenoura (kg)", 3.50, "Hortifruti", "Feira de Águas Claras"));
    feira5.AdicionarProduto(Produto("Pão integral (kg)", 18.00, "Padaria", "Feira de Águas Claras"));
    sistema->AdicionarFeira(feira5);

    std::cout << "✅ Banco de dados inicializado com 5 feiras e 20 produtos\n";
}

/**
 * @brief Escapa string para JSON
 */
std::string EscapeJSON(const std::string& s) {
    std::ostringstream o;
    for (char c : s) {
        switch (c) {
            case '"': o << "\\\""; break;
            case '\\': o << "\\\\"; break;
            case '\b': o << "\\b"; break;
            case '\f': o << "\\f"; break;
            case '\n': o << "\\n"; break;
            case '\r': o << "\\r"; break;
            case '\t': o << "\\t"; break;
            default: o << c; break;
        }
    }
    return o.str();
}

/**
 * @brief Converte Sistema para JSON
 */
std::string SistemaParaJSON(Sistema* sistema) {
    std::ostringstream json;
    json << "{\n";
    json << "  \"feiras\": [\n";

    const auto& feiras = sistema->GetFeiras();
    for (size_t i = 0; i < feiras.size(); ++i) {
        const Feira& feira = feiras[i];
        json << "    {\n";
        json << "      \"nome\": \"" << EscapeJSON(feira.GetNome()) << "\",\n";
        json << "      \"endereco\": \"" << EscapeJSON(feira.GetEndereco()) << "\",\n";
        json << "      \"latitude\": " << feira.GetLocal().GetLatitude() << ",\n";
        json << "      \"longitude\": " << feira.GetLocal().GetLongitude() << ",\n";
        json << "      \"produtos\": [\n";

        const auto& produtos = feira.GetProdutos();
        for (size_t j = 0; j < produtos.size(); ++j) {
            const Produto& p = produtos[j];
            json << "        {\n";
            json << "          \"nome\": \"" << EscapeJSON(p.GetNome()) << "\",\n";
            json << "          \"preco\": " << p.GetPreco() << ",\n";
            json << "          \"categoria\": \"" << EscapeJSON(p.GetCategoria()) << "\"\n";
            json << "        }";
            if (j < produtos.size() - 1) json << ",";
            json << "\n";
        }

        json << "      ]\n";
        json << "    }";
        if (i < feiras.size() - 1) json << ",";
        json << "\n";
    }

    json << "  ]\n";
    json << "}\n";

    return json.str();
}

/**
 * @brief Adiciona usuário cadastrado ao sistema
 */
void AdicionarUsuarioCadastrado(const std::string& nome, const std::string& ra) {
    // Obter data/hora atual
    time_t now = time(0);
    char buffer[80];
    struct tm* timeinfo = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    UsuarioCadastrado usuario;
    usuario.nome = nome;
    usuario.ra = ra;
    usuario.dataCadastro = std::string(buffer);

    usuariosCadastrados.push_back(usuario);
    std::cout << "✅ Usuário cadastrado: " << nome << " (" << ra << ")\n";
}

/**
 * @brief Retorna lista de usuários cadastrados em JSON
 */
std::string ListarUsuariosJSON() {
    std::ostringstream json;
    json << "{\n";
    json << "  \"usuarios\": [\n";

    for (size_t i = 0; i < usuariosCadastrados.size(); ++i) {
        const auto& user = usuariosCadastrados[i];
        json << "    {\n";
        json << "      \"nome\": \"" << EscapeJSON(user.nome) << "\",\n";
        json << "      \"ra\": \"" << EscapeJSON(user.ra) << "\",\n";
        json << "      \"dataCadastro\": \"" << user.dataCadastro << "\"\n";
        json << "    }";
        if (i < usuariosCadastrados.size() - 1) json << ",";
        json << "\n";
    }

    json << "  ],\n";
    json << "  \"total\": " << usuariosCadastrados.size() << "\n";
    json << "}\n";

    return json.str();
}

/**
 * @brief Adiciona produto a uma feira
 */
bool AdicionarProdutoFeira(Sistema* sistema, const std::string& nomeFeira,
                           const std::string& nomeProduto, double preco,
                           const std::string& categoria) {
    auto& feiras = const_cast<std::vector<Feira>&>(sistema->GetFeiras());

    for (auto& feira : feiras) {
        if (feira.GetNome() == nomeFeira) {
            Produto novoProduto(nomeProduto, preco, categoria, nomeFeira);
            feira.AdicionarProduto(novoProduto);
            std::cout << "✅ Produto adicionado: " << nomeProduto << " na " << nomeFeira << "\n";
            return true;
        }
    }

    return false;
}

/**
 * @brief Remove produto de uma feira
 */
bool RemoverProdutoFeira(Sistema* sistema, const std::string& nomeFeira,
                         const std::string& nomeProduto) {
    auto& feiras = const_cast<std::vector<Feira>&>(sistema->GetFeiras());

    for (auto& feira : feiras) {
        if (feira.GetNome() == nomeFeira) {
            return feira.RemoverProduto(nomeProduto);
        }
    }

    return false;
}
