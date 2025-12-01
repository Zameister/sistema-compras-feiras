/**
 * @file sistema.h
 * @brief Declaração da classe Sistema - controlador principal do sistema de compras em feiras
 * @author Luidgi Varela Carneiro, Arthur Souza Chagas
 * @date 2025
 */

#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include <unordered_map>

#include "feira.h"
#include "usuario.h"
#include "distancias.h"

/**
 * @class Sistema
 * @brief Classe principal que gerencia o sistema de compras em feiras
 *
 * Esta classe é responsável por gerenciar feiras, produtos, usuários
 * e fornecer funcionalidades de busca, filtragem e cálculo de distâncias.
 */
class Sistema {
private:
    std::vector<Feira> feiras;  ///< Lista de feiras cadastradas
    Usuario usuario;  ///< Usuário do sistema
    bool usuarioCadastrado;  ///< Indica se há um usuário cadastrado

    std::unordered_map<std::string, Location> mapaRegioes;  ///< Mapa de regiões administrativas do DF

    /**
     * @brief Lista todas as feiras cadastradas
     *
     * @pre Nenhuma
     * @post Exibe lista de feiras sem modificar o estado do sistema
     */
    void ListarFeiras() const;

    /**
     * @brief Mostra produtos disponíveis em uma feira específica
     *
     * @pre Deve haver pelo menos uma feira cadastrada
     * @post Exibe produtos da feira selecionada sem modificar o estado
     */
    void MostrarProdutosDaFeira() const;

    /**
     * @brief Calcula distância entre usuário e uma feira
     *
     * @pre usuarioCadastrado == true
     * @pre Deve haver pelo menos uma feira cadastrada
     * @post Exibe a distância calculada sem modificar o estado
     */
    void CalcularDistancia() const;

    /**
     * @brief Normaliza string para minúsculas
     *
     * @param s String a ser normalizada
     * @return String convertida para minúsculas
     *
     * @pre Nenhuma
     * @post Retorna cópia da string em minúsculas, original não é modificada
     */
    std::string NormalizarMinusculo(const std::string& s) const;

public:
    /**
     * @brief Construtor do sistema
     *
     * @pre Nenhuma
     * @post Sistema inicializado com feiras e produtos pré-cadastrados
     * @post mapaRegioes preenchido com todas as RAs do DF
     * @post usuarioCadastrado = false
     */
    Sistema();

    /**
     * @brief Exibe menu principal e gerencia interação com usuário
     *
     * @pre Nenhuma
     * @post Executa ações conforme opções escolhidas pelo usuário
     */
    void Menu();

    /**
     * @brief Cadastra um novo usuário no sistema (EU005)
     *
     * @pre Nenhuma
     * @post Se região válida: usuario atualizado com dados fornecidos
     * @post Se região válida: usuarioCadastrado = true
     * @post Se região inválida: estado do sistema não é alterado
     */
    void CadastrarUsuario();  // EU005

    /**
     * @brief Busca produtos pelo nome em todas as feiras (EU001)
     *
     * @pre Nenhuma
     * @post Exibe produtos encontrados sem modificar o estado
     * @post Se termo vazio: exibe mensagem de erro
     */
    void BuscarProdutos();    // EU001

    /**
     * @brief Filtra feiras por critérios diversos (EU002)
     *
     * Permite filtrar por:
     * - Categoria de produto
     * - Produto específico
     * - Preço máximo
     *
     * @pre Nenhuma
     * @post Exibe feiras que atendem o critério sem modificar o estado
     */
    void FiltrarFeiras();     // EU002
};

#endif
