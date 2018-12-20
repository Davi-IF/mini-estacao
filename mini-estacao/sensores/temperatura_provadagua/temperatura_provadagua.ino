#include <OneWire.h>
#include <DallasTemperature.h>

#define pinSensorTemperaturaSolo 3

OneWire oneWire(pinSensorTemperaturaSolo);
DallasTemperature sensor(&oneWire);

void setup() {
  Serial.begin(9600);
  Serial.println("Sensor de temperatura Dallas DS18b20");
  
  sensor.begin();
  
  
}

void loop() {
  sensor.requestTemperatures();
  float leitura=sensor.getTempCByIndex(0);
  Serial.println(leitura); 
  delay(1000);
}
