#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include <unordered_map>

#include "feira.h"
#include "usuario.h"
#include "distancias.h"

class Sistema {
private:
    std::vector<Feira> feiras;
    Usuario usuario;
    bool usuarioCadastrado = false;

    std::unordered_map<std::string, Location> mapaRegioes;

    // Funções internas
    void ListarFeiras() const;
    void MostrarProdutosDaFeira() const;
    void CalcularDistancia() const;
    std::string NormalizarMinusculo(const std::string& s) const;

public:
    Sistema();

    // Fluxo principal
    void Menu();

    // Cadastro
    void CadastrarUsuario();

    // Arthur - Busca e filtros
    void BuscarProdutos();
    void FiltrarFeiras();
};

#endif
