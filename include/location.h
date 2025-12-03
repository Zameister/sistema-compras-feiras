/**
 * @file location.h
 * @brief Definicao da classe Location (GPS)
 * @author Luidgi Varela Carneiro
 * @date 2025
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <string>

/**
 * @class Location
 * @brief Representa uma posicao geografica usando latitude e longitude
 *
 * Esta classe armazena coordenadas GPS e permite calculo de distancias
 * entre localizacoes usando a formula de Haversine.
 */
class Location {
private:
    double latitude;   ///< Latitude em graus (-90 a +90)
    double longitude;  ///< Longitude em graus (-180 a +180)

public:
    /**
     * @brief Construtor padrao
     *
     * @pre Nenhuma
     * @post Cria localizacao em (0, 0) - ponto nulo
     * @post latitude == 0.0 e longitude == 0.0
     */
    Location();

    /**
     * @brief Construtor com parametros (EU003)
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
     * @brief Obtem a latitude
     *
     * @return Latitude em graus
     *
     * @pre Nenhuma
     * @post Retorna latitude sem modificar o estado
     */
    double GetLatitude() const;

    /**
     * @brief Obtem a longitude
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
     * @brief Calcula distancia ate outra localizacao (EU003)
     *
     * Utiliza a formula de Haversine para calcular a distancia
     * ortodromica (great-circle distance) entre dois pontos na Terra.
     *
     * @param outra Localizacao de destino
     * @return Distancia em quilometros
     *
     * @pre outra com coordenadas validas
     * @post Retorna distancia >= 0.0
     * @post Estado desta localizacao nao modificado
     */
    double DistanciaPara(const Location& outra) const;
};

#endif
