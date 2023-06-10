#include "sensors/dht11.hpp"

DHT11Sensor::DHT11Sensor() : m_dht(DHTPIN, DHTTYPE) {}

void DHT11Sensor::begin() { this->m_dht.begin(); }

float DHT11Sensor::getTemperature() { return this->m_dht.readTemperature(false); }	// false = Celsius

float DHT11Sensor::getHumidity() { return this->m_dht.readHumidity(); }