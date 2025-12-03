/**
 * @file database.cpp
 * @brief Sistema de persistencia de dados em JSON
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

// Estrutura para armazenar usuarios cadastrados
struct UsuarioCadastrado {
    std::string nome;
    std::string ra;
    std::string dataCadastro;
};

// Lista global de usuarios cadastrados
static std::vector<UsuarioCadastrado> usuariosCadastrados;

/**
 * @brief Inicializa banco de dados com dados padrao
 */
void InicializarBancoDeDados(Sistema* sistema) {
    // Feira 1: Ceilandia
    Location loc1(-15.817, -48.112);
    Feira feira1("Feira da Ceilandia", "Quadra 12, Ceilandia Sul", loc1);

    Produto p1_1("Tomate", 3.50, "Hortifruti", "Feira da Ceilandia");
    p1_1.AdicionarAvaliacao(4.5); p1_1.AdicionarAvaliacao(5.0); p1_1.AdicionarAvaliacao(4.0);
    feira1.AdicionarProduto(p1_1);

    Produto p1_2("Alface", 2.00, "Hortifruti", "Feira da Ceilandia");
    p1_2.AdicionarAvaliacao(4.2); p1_2.AdicionarAvaliacao(4.8);
    feira1.AdicionarProduto(p1_2);

    Produto p1_3("Banana", 4.20, "Frutas", "Feira da Ceilandia");
    p1_3.AdicionarAvaliacao(3.5); p1_3.AdicionarAvaliacao(4.0); p1_3.AdicionarAvaliacao(4.5); p1_3.AdicionarAvaliacao(5.0);
    feira1.AdicionarProduto(p1_3);

    Produto p1_4("Arroz (kg)", 5.00, "Graos", "Feira da Ceilandia");
    p1_4.AdicionarAvaliacao(4.8); p1_4.AdicionarAvaliacao(5.0);
    feira1.AdicionarProduto(p1_4);

    Produto p1_5("Cebola (kg)", 3.80, "Hortifruti", "Feira da Ceilandia");
    p1_5.AdicionarAvaliacao(3.9); p1_5.AdicionarAvaliacao(4.1); p1_5.AdicionarAvaliacao(4.0);
    feira1.AdicionarProduto(p1_5);

    Produto p1_6("Manga", 5.50, "Frutas", "Feira da Ceilandia");
    p1_6.AdicionarAvaliacao(5.0); p1_6.AdicionarAvaliacao(4.5); p1_6.AdicionarAvaliacao(4.8);
    feira1.AdicionarProduto(p1_6);

    Produto p1_7("Feijao (kg)", 6.90, "Graos", "Feira da Ceilandia");
    p1_7.AdicionarAvaliacao(4.2);
    feira1.AdicionarProduto(p1_7);

    Produto p1_8("Pao frances (kg)", 11.50, "Padaria", "Feira da Ceilandia");
    p1_8.AdicionarAvaliacao(4.7); p1_8.AdicionarAvaliacao(4.9); p1_8.AdicionarAvaliacao(5.0);
    feira1.AdicionarProduto(p1_8);

    sistema->AdicionarFeira(feira1);

    // Feira 2: Taguatinga
    Location loc2(-15.839, -48.052);
    Feira feira2("Feira de Taguatinga", "Pistao Sul, Taguatinga", loc2);
    Produto p2_1("Tomate", 3.80, "Hortifruti", "Feira de Taguatinga");
    p2_1.AdicionarAvaliacao(4.0); p2_1.AdicionarAvaliacao(4.5);
    feira2.AdicionarProduto(p2_1);
    Produto p2_2("Batata (kg)", 4.20, "Hortifruti", "Feira de Taguatinga");
    p2_2.AdicionarAvaliacao(4.3); p2_2.AdicionarAvaliacao(4.7); p2_2.AdicionarAvaliacao(5.0);
    feira2.AdicionarProduto(p2_2);
    Produto p2_3("Feijao (kg)", 7.00, "Graos", "Feira de Taguatinga");
    p2_3.AdicionarAvaliacao(3.8); p2_3.AdicionarAvaliacao(4.2);
    feira2.AdicionarProduto(p2_3);
    Produto p2_4("Queijo (kg)", 35.00, "Laticinios", "Feira de Taguatinga");
    p2_4.AdicionarAvaliacao(4.9); p2_4.AdicionarAvaliacao(5.0); p2_4.AdicionarAvaliacao(4.8);
    feira2.AdicionarProduto(p2_4);
    Produto p2_5("Laranja (kg)", 4.50, "Frutas", "Feira de Taguatinga");
    p2_5.AdicionarAvaliacao(4.5);
    feira2.AdicionarProduto(p2_5);
    Produto p2_6("Cenoura (kg)", 3.20, "Hortifruti", "Feira de Taguatinga");
    p2_6.AdicionarAvaliacao(4.6); p2_6.AdicionarAvaliacao(4.4);
    feira2.AdicionarProduto(p2_6);
    Produto p2_7("Frango (kg)", 16.50, "Carnes", "Feira de Taguatinga");
    p2_7.AdicionarAvaliacao(4.1); p2_7.AdicionarAvaliacao(4.0); p2_7.AdicionarAvaliacao(4.3);
    feira2.AdicionarProduto(p2_7);
    Produto p2_8("Pao de forma", 8.90, "Padaria", "Feira de Taguatinga");
    p2_8.AdicionarAvaliacao(4.8); p2_8.AdicionarAvaliacao(4.6);
    feira2.AdicionarProduto(p2_8);
    sistema->AdicionarFeira(feira2);

    // Feira 3: Plano Piloto
    Location loc3(-15.794, -47.883);
    Feira feira3("Feira do Plano Piloto", "CLN 209, Asa Norte", loc3);
    Produto p3_1("Tomate", 4.50, "Hortifruti", "Feira do Plano Piloto");
    p3_1.AdicionarAvaliacao(3.5); p3_1.AdicionarAvaliacao(4.0);
    feira3.AdicionarProduto(p3_1);
    Produto p3_2("Alface", 2.50, "Hortifruti", "Feira do Plano Piloto");
    p3_2.AdicionarAvaliacao(5.0); p3_2.AdicionarAvaliacao(4.9); p3_2.AdicionarAvaliacao(4.8);
    feira3.AdicionarProduto(p3_2);
    Produto p3_3("Pao frances (kg)", 12.00, "Padaria", "Feira do Plano Piloto");
    p3_3.AdicionarAvaliacao(4.2); p3_3.AdicionarAvaliacao(4.5);
    feira3.AdicionarProduto(p3_3);
    Produto p3_4("Leite (L)", 5.50, "Laticinios", "Feira do Plano Piloto");
    p3_4.AdicionarAvaliacao(4.7); p3_4.AdicionarAvaliacao(4.8);
    feira3.AdicionarProduto(p3_4);
    Produto p3_5("Maca (kg)", 7.50, "Frutas", "Feira do Plano Piloto");
    p3_5.AdicionarAvaliacao(4.0); p3_5.AdicionarAvaliacao(4.5); p3_5.AdicionarAvaliacao(4.3);
    feira3.AdicionarProduto(p3_5);
    Produto p3_6("Carne bovina (kg)", 38.00, "Carnes", "Feira do Plano Piloto");
    p3_6.AdicionarAvaliacao(3.9); p3_6.AdicionarAvaliacao(4.2);
    feira3.AdicionarProduto(p3_6);
    Produto p3_7("Abobora (kg)", 3.90, "Hortifruti", "Feira do Plano Piloto");
    p3_7.AdicionarAvaliacao(4.4);
    feira3.AdicionarProduto(p3_7);
    Produto p3_8("Iogurte", 6.50, "Laticinios", "Feira do Plano Piloto");
    p3_8.AdicionarAvaliacao(4.9); p3_8.AdicionarAvaliacao(5.0);
    feira3.AdicionarProduto(p3_8);
    sistema->AdicionarFeira(feira3);

    // Feira 4: Samambaia
    Location loc4(-15.878, -48.085);
    Feira feira4("Feira de Samambaia", "QN 318, Samambaia Norte", loc4);
    Produto p4_1("Banana", 4.00, "Frutas", "Feira de Samambaia");
    p4_1.AdicionarAvaliacao(4.6); p4_1.AdicionarAvaliacao(4.8); p4_1.AdicionarAvaliacao(4.4);
    feira4.AdicionarProduto(p4_1);
    Produto p4_2("Maca (kg)", 6.50, "Frutas", "Feira de Samambaia");
    p4_2.AdicionarAvaliacao(4.3); p4_2.AdicionarAvaliacao(4.5);
    feira4.AdicionarProduto(p4_2);
    Produto p4_3("Arroz (kg)", 4.80, "Graos", "Feira de Samambaia");
    p4_3.AdicionarAvaliacao(5.0); p4_3.AdicionarAvaliacao(4.9);
    feira4.AdicionarProduto(p4_3);
    Produto p4_4("Frango (kg)", 15.00, "Carnes", "Feira de Samambaia");
    p4_4.AdicionarAvaliacao(4.4); p4_4.AdicionarAvaliacao(4.2); p4_4.AdicionarAvaliacao(4.6);
    feira4.AdicionarProduto(p4_4);
    Produto p4_5("Pimentao (kg)", 5.20, "Hortifruti", "Feira de Samambaia");
    p4_5.AdicionarAvaliacao(4.1);
    feira4.AdicionarProduto(p4_5);
    Produto p4_6("Mamao", 4.80, "Frutas", "Feira de Samambaia");
    p4_6.AdicionarAvaliacao(4.7); p4_6.AdicionarAvaliacao(4.5);
    feira4.AdicionarProduto(p4_6);
    Produto p4_7("Carne suina (kg)", 22.00, "Carnes", "Feira de Samambaia");
    p4_7.AdicionarAvaliacao(4.3); p4_7.AdicionarAvaliacao(4.8);
    feira4.AdicionarProduto(p4_7);
    Produto p4_8("Leite (L)", 5.20, "Laticinios", "Feira de Samambaia");
    p4_8.AdicionarAvaliacao(4.9);
    feira4.AdicionarProduto(p4_8);
    sistema->AdicionarFeira(feira4);

    // Feira 5: Aguas Claras
    Location loc5(-15.834, -48.026);
    Feira feira5("Feira de Aguas Claras", "Avenida das Araucarias", loc5);
    Produto p5_1("Tomate", 4.20, "Hortifruti", "Feira de Aguas Claras");
    p5_1.AdicionarAvaliacao(4.4); p5_1.AdicionarAvaliacao(4.2);
    feira5.AdicionarProduto(p5_1);
    Produto p5_2("Alface", 2.30, "Hortifruti", "Feira de Aguas Claras");
    p5_2.AdicionarAvaliacao(4.8); p5_2.AdicionarAvaliacao(5.0); p5_2.AdicionarAvaliacao(4.9);
    feira5.AdicionarProduto(p5_2);
    Produto p5_3("Cenoura (kg)", 3.50, "Hortifruti", "Feira de Aguas Claras");
    p5_3.AdicionarAvaliacao(4.5);
    feira5.AdicionarProduto(p5_3);
    Produto p5_4("Pao integral (kg)", 18.00, "Padaria", "Feira de Aguas Claras");
    p5_4.AdicionarAvaliacao(4.7); p5_4.AdicionarAvaliacao(4.6); p5_4.AdicionarAvaliacao(4.9);
    feira5.AdicionarProduto(p5_4);
    Produto p5_5("Uva (kg)", 12.00, "Frutas", "Feira de Aguas Claras");
    p5_5.AdicionarAvaliacao(5.0); p5_5.AdicionarAvaliacao(4.8);
    feira5.AdicionarProduto(p5_5);
    Produto p5_6("Brocolis", 4.50, "Hortifruti", "Feira de Aguas Claras");
    p5_6.AdicionarAvaliacao(4.3); p5_6.AdicionarAvaliacao(4.4);
    feira5.AdicionarProduto(p5_6);
    Produto p5_7("Queijo minas (kg)", 32.00, "Laticinios", "Feira de Aguas Claras");
    p5_7.AdicionarAvaliacao(4.9); p5_7.AdicionarAvaliacao(5.0); p5_7.AdicionarAvaliacao(4.7);
    feira5.AdicionarProduto(p5_7);
    Produto p5_8("Melancia", 8.50, "Frutas", "Feira de Aguas Claras");
    p5_8.AdicionarAvaliacao(4.6);
    feira5.AdicionarProduto(p5_8);
    sistema->AdicionarFeira(feira5);

    std::cout << "✅ Banco de dados inicializado com 5 feiras e 40 produtos\n";
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
            json << "          \"categoria\": \"" << EscapeJSON(p.GetCategoria()) << "\",\n";
            json << "          \"nota\": " << p.GetNota() << ",\n";
            json << "          \"numAvaliacoes\": " << p.GetNumAvaliacoes() << "\n";
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
 * @brief Adiciona usuario cadastrado ao sistema
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
    std::cout << "✅ Usuario cadastrado: " << nome << " (" << ra << ")\n";
}

/**
 * @brief Retorna lista de usuarios cadastrados em JSON
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
