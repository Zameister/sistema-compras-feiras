/**
 * @file location.cpp
 * @brief Implementacao da classe Location (GPS)
 */

#include "location.h"
#include <cmath>

// Constantes para o calculo da distancia (raio da Terra)
static constexpr double kRaioTerraKm = 6371.0;
static constexpr double kPi = 3.14159265358979323846;

// ---------------------------------------------------------
// Construtores
// ---------------------------------------------------------

Location::Location() : latitude(0.0), longitude(0.0) {}

Location::Location(double latitude, double longitude)
    : latitude(latitude), longitude(longitude) {}


// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------

double Location::GetLatitude() const {
    return latitude;
}

double Location::GetLongitude() const {
    return longitude;
}


// ---------------------------------------------------------
// Setters
// ---------------------------------------------------------

void Location::SetLatitude(double novaLat) {
    latitude = novaLat;
}

void Location::SetLongitude(double novaLon) {
    longitude = novaLon;
}


// ---------------------------------------------------------
// Calculo da Distancia (Formula de Haversine)
// ---------------------------------------------------------

double Location::DistanciaPara(const Location& outra) const {
    // Converter graus para radianos
    double lat1 = latitude * (kPi / 180.0);
    double lon1 = longitude * (kPi / 180.0);
    double lat2 = outra.latitude * (kPi / 180.0);
    double lon2 = outra.longitude * (kPi / 180.0);

    // Diferencas
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    // Formula de Haversine
    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2) * std::sin(dlon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return kRaioTerraKm * c;
}
