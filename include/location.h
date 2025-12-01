/**
 * @file location.h
 * @brief Definição da classe Location (GPS)
 * @author Luidgi
 * @date 2025
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <string>

/**
 * @class Location
 * @brief Representa uma posição geográfica usando latitude e longitude.
 */
class Location {
private:
    double latitude;   ///< Latitude em graus
    double longitude;  ///< Longitude em graus

public:
    // Construtores
    Location();
    Location(double latitude, double longitude);

    // Getters
    double GetLatitude() const;
    double GetLongitude() const;

    // Setters
    void SetLatitude(double novaLat);
    void SetLongitude(double novaLon);

    /**
     * @brief Calcula a distância entre esta localização e outra.
     * @param outra A localização destino.
     * @return Distância em quilômetros.
     */
    double DistanciaPara(const Location& outra) const;
};

#endif
