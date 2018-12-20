#define pinSensorUmidadeSolo A0

void setup() {
  pinMode(pinSensorUmidadeSolo, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("  Umidade:");
  Serial.print(analogRead(pinSensorUmidadeSolo)); 
  Serial.print("  ");
  
  if (analogRead(pinSensorUmidadeSolo) > 750) {
     Serial.println("BAIXA UMIDADE");
  } else {
    Serial.println("ALTA UMIDADE");
  }

  delay(2000);
}
