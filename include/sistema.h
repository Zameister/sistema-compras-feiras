/**
 * @file sistema.h
 * @brief Declaracao da classe Sistema - controlador principal do sistema de compras em feiras
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
 * Esta classe e responsavel por gerenciar feiras, produtos, usuarios
 * e fornecer funcionalidades de busca, filtragem e calculo de distancias.
 */
class Sistema {
private:
    std::vector<Feira> feiras;  ///< Lista de feiras cadastradas
    Usuario usuario;  ///< Usuario do sistema
    bool usuarioCadastrado;  ///< Indica se ha um usuario cadastrado

    std::unordered_map<std::string, Location> mapaRegioes;  ///< Mapa de regioes administrativas do DF

    /**
     * @brief Lista todas as feiras cadastradas
     *
     * @pre Nenhuma
     * @post Exibe lista de feiras sem modificar o estado do sistema
     */
    void ListarFeiras() const;

    /**
     * @brief Mostra produtos disponiveis em uma feira especifica
     *
     * @pre Deve haver pelo menos uma feira cadastrada
     * @post Exibe produtos da feira selecionada sem modificar o estado
     */
    void MostrarProdutosDaFeira() const;

    /**
     * @brief Calcula distancia entre usuario e uma feira
     *
     * @pre usuarioCadastrado == true
     * @pre Deve haver pelo menos uma feira cadastrada
     * @post Exibe a distancia calculada sem modificar o estado
     */
    void CalcularDistancia() const;

    /**
     * @brief Normaliza string para minusculas
     *
     * @param s String a ser normalizada
     * @return String convertida para minusculas
     *
     * @pre Nenhuma
     * @post Retorna copia da string em minusculas, original nao e modificada
     */
    std::string NormalizarMinusculo(const std::string& s) const;

public:
    /**
     * @brief Construtor do sistema
     *
     * @pre Nenhuma
     * @post Sistema inicializado com feiras e produtos pre-cadastrados
     * @post mapaRegioes preenchido com todas as RAs do DF
     * @post usuarioCadastrado = false
     */
    Sistema();

    /**
     * @brief Exibe menu principal e gerencia interacao com usuario
     *
     * @pre Nenhuma
     * @post Executa acoes conforme opcoes escolhidas pelo usuario
     */
    void Menu();

    /**
     * @brief Cadastra um novo usuario no sistema (EU005)
     *
     * @pre Nenhuma
     * @post Se regiao valida: usuario atualizado com dados fornecidos
     * @post Se regiao valida: usuarioCadastrado = true
     * @post Se regiao invalida: estado do sistema nao e alterado
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
     * @brief Filtra feiras por criterios diversos (EU002)
     *
     * Permite filtrar por:
     * - Categoria de produto
     * - Produto especifico
     * - Preco maximo
     *
     * @pre Nenhuma
     * @post Exibe feiras que atendem o criterio sem modificar o estado
     */
    void FiltrarFeiras();     // EU002

    /**
     * @brief Retorna lista de feiras cadastradas (para API REST)
     *
     * @return Referencia constante para o vetor de feiras
     *
     * @pre Nenhuma
     * @post Retorna referencia para feiras sem modificar o estado
     */
    const std::vector<Feira>& GetFeiras() const;

    /**
     * @brief Adiciona uma feira ao sistema (para inicializacao do backend)
     *
     * @param feira Feira a ser adicionada
     *
     * @pre Nenhuma
     * @post Nova feira adicionada ao vetor feiras
     */
    void AdicionarFeira(const Feira& feira);
};

#endif
