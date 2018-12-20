#include <dht.h>

#define pinSensorTemperatura 4
dht sensorDHT;

void setup() {
  
  Serial.begin(9600);
  Serial.println("\tUmidade(%),\tTemperatura(C)");
}

void loop() {
  int chk = sensorDHT.read22(pinSensorTemperatura);
  
  switch (chk){
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      break;
    case DHTLIB_ERROR_CONNECT:
      Serial.print("Connect error,\t");
      break;
    case DHTLIB_ERROR_ACK_L:
      Serial.print("Ack Low error,\t");
      break;
    case DHTLIB_ERROR_ACK_H:
      Serial.print("Ack High error,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;
  }
  
  Serial.print(sensorDHT.humidity, 1);
  Serial.print(",\t\t");
  Serial.println(sensorDHT.temperature, 1);

  delay(2000);
}
