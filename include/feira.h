/**
 * @file feira.h
 * @brief Definição da classe Feira com localização GPS
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
 * @brief Representa uma feira com localização GPS e produtos
 *
 * Esta classe gerencia informações de feiras incluindo nome, endereço,
 * localização GPS e lista de produtos disponíveis.
 */
class Feira {
private:
    std::string nome;  ///< Nome da feira
    std::string endereco;  ///< Endereço da feira
    Location local;  ///< Localização GPS (latitude/longitude)
    std::vector<Produto> produtos;  ///< Lista de produtos disponíveis

public:
    /**
     * @brief Construtor padrão
     *
     * @pre Nenhuma
     * @post Cria feira com valores vazios/padrão
     * @post produtos.empty() == true
     */
    Feira();

    /**
     * @brief Construtor com parâmetros
     *
     * @param nome Nome da feira
     * @param endereco Endereço da feira
     * @param local Localização GPS da feira
     *
     * @pre nome não vazio
     * @pre endereco não vazio
     * @pre local com coordenadas válidas
     * @post Feira criada com os valores fornecidos
     * @post produtos.empty() == true
     */
    Feira(const std::string& nome,
          const std::string& endereco,
          const Location& local);

    /**
     * @brief Obtém o nome da feira
     *
     * @return Nome da feira
     *
     * @pre Nenhuma
     * @post Retorna nome sem modificar o estado
     */
    std::string GetNome() const;

    /**
     * @brief Obtém o endereço da feira
     *
     * @return Endereço da feira
     *
     * @pre Nenhuma
     * @post Retorna endereço sem modificar o estado
     */
    std::string GetEndereco() const;

    /**
     * @brief Obtém a localização GPS da feira
     *
     * @return Referência constante para a localização
     *
     * @pre Nenhuma
     * @post Retorna localização sem modificar o estado
     */
    const Location& GetLocal() const;

    /**
     * @brief Obtém lista de produtos da feira
     *
     * @return Referência constante para vetor de produtos
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
     * @pre nome não vazio
     * @post this->nome == nome
     */
    void SetNome(const std::string& nome);

    /**
     * @brief Define novo endereço para a feira
     *
     * @param endereco Novo endereço da feira
     *
     * @pre endereco não vazio
     * @post this->endereco == endereco
     */
    void SetEndereco(const std::string& endereco);

    /**
     * @brief Define nova localização GPS para a feira
     *
     * @param novaLocalizacao Nova localização GPS
     *
     * @pre novaLocalizacao com coordenadas válidas
     * @post this->local == novaLocalizacao
     */
    void SetLocal(const Location& novaLocalizacao);

    /**
     * @brief Adiciona um produto à feira (EU004)
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
     * @return true se produto foi removido, false caso contrário
     *
     * @pre Nenhuma
     * @post Se encontrado: produtos.size() diminuído em 1
     * @post Se não encontrado: produtos não modificado
     */
    bool RemoverProduto(const std::string& nomeProduto);

    /**
     * @brief Busca um produto na feira pelo nome (EU001)
     *
     * @param nomeProduto Nome do produto a buscar
     * @return Ponteiro para o produto se encontrado, nullptr caso contrário
     *
     * @pre Nenhuma
     * @post Retorna ponteiro válido se produto existe
     * @post Retorna nullptr se produto não existe
     * @post produtos não modificado
     */
    Produto* BuscarProduto(const std::string& nomeProduto);

    /**
     * @brief Calcula distância da feira até uma localização (EU003)
     *
     * @param destino Localização de destino
     * @return Distância em quilômetros usando fórmula de Haversine
     *
     * @pre destino com coordenadas válidas
     * @post Retorna distância >= 0.0
     * @post Estado da feira não modificado
     */
    double DistanciaPara(const Location& destino) const;
};

#endif
