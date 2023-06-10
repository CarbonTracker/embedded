#pragma once

#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 13

class DHT11Sensor {
public:
	DHT11Sensor();
	void begin();

	float getTemperature();
	float getHumidity();

private:
	DHT m_dht;
};