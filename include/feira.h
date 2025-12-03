/**
 * @file feira.h
 * @brief Definicao da classe Feira com localizacao GPS
 * @author Luidgi Varela Carneiro
 * @date 2025
 */

#ifndef FEIRA_H
#define FEIRA_H

#include <string>
#include <vector>
#include "produto.h"
#include "location.h"

/**
 * @class Feira
 * @brief Representa uma feira com localizacao GPS e produtos
 *
 * Esta classe gerencia informacoes de feiras incluindo nome, endereco,
 * localizacao GPS e lista de produtos disponiveis.
 */
class Feira {
private:
    std::string nome;  ///< Nome da feira
    std::string endereco;  ///< Endereco da feira
    Location local;  ///< Localizacao GPS (latitude/longitude)
    std::vector<Produto> produtos;  ///< Lista de produtos disponiveis

public:
    /**
     * @brief Construtor padrao
     *
     * @pre Nenhuma
     * @post Cria feira com valores vazios/padrao
     * @post produtos.empty() == true
     */
    Feira();

    /**
     * @brief Construtor com parametros
     *
     * @param nome Nome da feira
     * @param endereco Endereco da feira
     * @param local Localizacao GPS da feira
     *
     * @pre nome nao vazio
     * @pre endereco nao vazio
     * @pre local com coordenadas validas
     * @post Feira criada com os valores fornecidos
     * @post produtos.empty() == true
     */
    Feira(const std::string& nome,
          const std::string& endereco,
          const Location& local);

    /**
     * @brief Obtem o nome da feira
     *
     * @return Nome da feira
     *
     * @pre Nenhuma
     * @post Retorna nome sem modificar o estado
     */
    std::string GetNome() const;

    /**
     * @brief Obtem o endereco da feira
     *
     * @return Endereco da feira
     *
     * @pre Nenhuma
     * @post Retorna endereco sem modificar o estado
     */
    std::string GetEndereco() const;

    /**
     * @brief Obtem a localizacao GPS da feira
     *
     * @return Referencia constante para a localizacao
     *
     * @pre Nenhuma
     * @post Retorna localizacao sem modificar o estado
     */
    const Location& GetLocal() const;

    /**
     * @brief Obtem lista de produtos da feira
     *
     * @return Referencia constante para vetor de produtos
     *
     * @pre Nenhuma
     * @post Retorna produtos sem modificar o estado
     */
    const std::vector<Produto>& GetProdutos() const;

    /**
     * @brief Define novo nome para a feira
     *
     * @param nome Novo nome da feira
     *
     * @pre nome nao vazio
     * @post this->nome == nome
     */
    void SetNome(const std::string& nome);

    /**
     * @brief Define novo endereco para a feira
     *
     * @param endereco Novo endereco da feira
     *
     * @pre endereco nao vazio
     * @post this->endereco == endereco
     */
    void SetEndereco(const std::string& endereco);

    /**
     * @brief Define nova localizacao GPS para a feira
     *
     * @param novaLocalizacao Nova localizacao GPS
     *
     * @pre novaLocalizacao com coordenadas validas
     * @post this->local == novaLocalizacao
     */
    void SetLocal(const Location& novaLocalizacao);

    /**
     * @brief Adiciona um produto a feira (EU004)
     *
     * @param produto Produto a ser adicionado
     *
     * @pre Nenhuma
     * @post produtos.size() aumentado em 1
     * @post Produto adicionado ao final da lista
     */
    void AdicionarProduto(const Produto& produto);

    /**
     * @brief Remove um produto da feira pelo nome (EU001)
     *
     * @param nomeProduto Nome do produto a remover
     * @return true se produto foi removido, false caso contrario
     *
     * @pre Nenhuma
     * @post Se encontrado: produtos.size() diminuido em 1
     * @post Se nao encontrado: produtos nao modificado
     */
    bool RemoverProduto(const std::string& nomeProduto);

    /**
     * @brief Busca um produto na feira pelo nome (EU001)
     *
     * @param nomeProduto Nome do produto a buscar
     * @return Ponteiro para o produto se encontrado, nullptr caso contrario
     *
     * @pre Nenhuma
     * @post Retorna ponteiro valido se produto existe
     * @post Retorna nullptr se produto nao existe
     * @post produtos nao modificado
     */
    Produto* BuscarProduto(const std::string& nomeProduto);

    /**
     * @brief Calcula distancia da feira ate uma localizacao (EU003)
     *
     * @param destino Localizacao de destino
     * @return Distancia em quilometros usando formula de Haversine
     *
     * @pre destino com coordenadas validas
     * @post Retorna distancia >= 0.0
     * @post Estado da feira nao modificado
     */
    double DistanciaPara(const Location& destino) const;
};

#endif
