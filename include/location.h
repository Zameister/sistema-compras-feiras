/**
 * @file location.h
 * @brief Definição da classe Location (GPS)
 * @author Luidgi Varela Carneiro
 * @date 2025
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <string>

/**
 * @class Location
 * @brief Representa uma posição geográfica usando latitude e longitude
 *
 * Esta classe armazena coordenadas GPS e permite cálculo de distâncias
 * entre localizações usando a fórmula de Haversine.
 */
class Location {
private:
    double latitude;   ///< Latitude em graus (-90 a +90)
    double longitude;  ///< Longitude em graus (-180 a +180)

public:
    /**
     * @brief Construtor padrão
     *
     * @pre Nenhuma
     * @post Cria localização em (0, 0) - ponto nulo
     * @post latitude == 0.0 e longitude == 0.0
     */
    Location();

    /**
     * @brief Construtor com parâmetros (EU003)
     *
     * @param latitude Latitude em graus
     * @param longitude Longitude em graus
     *
     * @pre -90.0 <= latitude <= 90.0
     * @pre -180.0 <= longitude <= 180.0
     * @post this->latitude == latitude
     * @post this->longitude == longitude
     */
    Location(double latitude, double longitude);

    /**
     * @brief Obtém a latitude
     *
     * @return Latitude em graus
     *
     * @pre Nenhuma
     * @post Retorna latitude sem modificar o estado
     */
    double GetLatitude() const;

    /**
     * @brief Obtém a longitude
     *
     * @return Longitude em graus
     *
     * @pre Nenhuma
     * @post Retorna longitude sem modificar o estado
     */
    double GetLongitude() const;

    /**
     * @brief Define nova latitude
     *
     * @param novaLat Nova latitude em graus
     *
     * @pre -90.0 <= novaLat <= 90.0
     * @post this->latitude == novaLat
     */
    void SetLatitude(double novaLat);

    /**
     * @brief Define nova longitude
     *
     * @param novaLon Nova longitude em graus
     *
     * @pre -180.0 <= novaLon <= 180.0
     * @post this->longitude == novaLon
     */
    void SetLongitude(double novaLon);

    /**
     * @brief Calcula distância até outra localização (EU003)
     *
     * Utiliza a fórmula de Haversine para calcular a distância
     * ortodrômica (great-circle distance) entre dois pontos na Terra.
     *
     * @param outra Localização de destino
     * @return Distância em quilômetros
     *
     * @pre outra com coordenadas válidas
     * @post Retorna distância >= 0.0
     * @post Estado desta localização não modificado
     */
    double DistanciaPara(const Location& outra) const;
};

#endif
