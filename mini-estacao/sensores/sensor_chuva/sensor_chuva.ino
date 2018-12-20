#define pinSensorChuva A1

void setup() {
  
  pinMode(pinSensorChuva, INPUT);
  Serial.begin(9600);
}

void loop() {

  Serial.print("Chuva:");
  Serial.print(analogRead(pinSensorChuva)); 
  Serial.print("  ");
  
  if (analogRead(pinSensorChuva) > 650) {
     Serial.println("SEM CHUVA");
  } else {
    Serial.println("ESTA CHUVENDO");
  }

  delay(2000);
}
