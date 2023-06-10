#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

#include "credentials.hpp"
#include "heltec.h"
#include "sensors/dht11.hpp"

WiFiClientSecure espClient;
PubSubClient client(espClient);

DHT11Sensor dht11Sensor;

void connectMQTT() {
	Serial.print("Connecting to MQTT broker...");
	espClient.setInsecure();
	client.setServer(BROKER_SERVER, BROKER_PORT);
	while (!client.connected()) {
		if (client.connect("MicrocontrollerClient", BROKER_USER, BROKER_PASSWORD)) {
			Serial.println("  done!.");
		} else {
			Serial.print("failed with state ");
			Serial.print(client.state());
			delay(2000);
		}
	}
}

void connectWIFI() {
	Serial.print("Connecting to WiFi...");
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("  done!.");
}

void setup() {
	Heltec.begin(true, false, true, true);

	Heltec.display->init();
	Heltec.display->flipScreenVertically();

	Heltec.display->setFont(ArialMT_Plain_16);
	Heltec.display->drawString(32, 10, "Starting...");
	Heltec.display->display();

	delay(2000);

	dht11Sensor.begin();

	connectWIFI();
	connectMQTT();
}

void loop() {
	Heltec.display->clear();

	Heltec.display->drawString(
		0, 10, String(dht11Sensor.getTemperature()) + "°C" + " / " + String(dht11Sensor.getHumidity()) + "%");

	Heltec.display->display();

	client.publish("temperature", String(dht11Sensor.getTemperature()).c_str());
	client.publish("humidity", String(dht11Sensor.getHumidity()).c_str());

	delay(1000);
}