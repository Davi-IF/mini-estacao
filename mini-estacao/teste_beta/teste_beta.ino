#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

#define pinSensorTemperaturaSolo 3
#define pinSensorUmidadeSolo A0
#define pinSensorChuva A1
#define pinSensorTemperatura 4
#define   pinSensorUV A2

void measure_UV();

 
const float pi = 3.14159265;     //Número de pi
int period = 5000;               //Tempo de medida(miliseconds)
int delaytime = 2000;            //Invervalo entre as amostras (miliseconds)
int radius = 147;                //Raio do anemometro(mm)
unsigned int Sample  = 0;        //Armazena o número de amostras
unsigned int counter = 0;        //Contador para o sensor  
unsigned int RPM = 0;            //Rotações por minuto
float speedwind = 0;             //Velocidade do vento (km/h)
int adc_value = 0,
    UV_index  = 0;

OneWire oneWire(pinSensorTemperaturaSolo);
DallasTemperature sensor(&oneWire);
dht sensorDHT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(2, INPUT);        //configura o digital 2 como entrada
  digitalWrite(2, HIGH);    //internall pull-up active
  pinMode(pinSensorUmidadeSolo, INPUT);
  pinMode(pinSensorChuva, INPUT);
  pinMode(pinSensorUV, INPUT);
  sensor.begin();

  Serial.println("\tUmidade Ar(%),\tTemp Ar(C), \tTemp Solo(C), \tRPM, \tVeloci. Ar, \tUmidade Solo, \t\tChuva, \t\tUV indice");
}

void loop() {
  // put your main code here, to run repeatedly:
  int chk = sensorDHT.read22(pinSensorTemperatura);
  
  // VERIFICA SE HOUVE ERRO
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
  Serial.print(sensorDHT.temperature, 1);
  
  sensor.requestTemperatures();
  float leitura=sensor.getTempCByIndex(0);
  Serial.print(",\t\t");
  Serial.print(leitura);
  
  Sample++;
  windvelocity();
  RPMcalc();
  Serial.print("\t\t");
  Serial.print(RPM);
  Serial.print("\t"); 
  SpeedWind();
  Serial.print(speedwind);
  Serial.print(" [km/h] ");
  
  Serial.print("\t");   
  Serial.print(analogRead(pinSensorUmidadeSolo)); 
  Serial.print("  ");
  
  if (analogRead(pinSensorUmidadeSolo) > 750) {
     Serial.print("BAIXA UMIDADE\t");
  } else {
    Serial.print("ALTA UMIDADE\t");
  }

  Serial.print(analogRead(pinSensorChuva)); 
  Serial.print("  ");
  if (analogRead(pinSensorChuva) > 650) {
     Serial.print("SEM CHUVA\t\t");
  } else {
    Serial.print("COM CHUVA\t\t");
  }

  
  measure_UV();
  Serial.println(UV_index);

  delay(delaytime);   
}

void windvelocity()
{
  speedwind = 0;
  
  counter = 0;  
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();       
  long startTime = millis();
  while(millis() < startTime + period) {}
}

void RPMcalc()
{
  RPM=((counter)*60)/(period/1000); 
}


void SpeedWind()
{
  speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6; 
}

void addcount()
{
  counter++;
} 

void measure_UV()
{
  
    adc_value = analogRead(pinSensorUV);
    
    int mV = (adc_value * (5.0 / 1023.0)) * 1000;
  
    
    //Compara valores da tabela de índice UV
    if(mV > 0 && mV <= 227)   UV_index = 0;
    
    else if(mV > 227 && mV <= 318)  UV_index = 1;
    
    else if (mV > 318 && mV <= 408) UV_index = 2;
    
    else if (mV > 408 && mV <= 503) UV_index = 3;
    
    else if (mV > 503 && mV <= 606) UV_index = 4;
    
    else if (mV > 606 && mV <= 696) UV_index = 5;
    
    else if (mV > 696 && mV <= 795) UV_index = 6;
    
    else if (mV > 795 && mV <= 881) UV_index = 7;
    
    else if (mV > 881 && mV <= 976) UV_index = 8;
   
    else if (mV > 976 && mV <= 1079) UV_index = 9;
   
    else if (mV > 1079 && mV <= 1170) UV_index = 10;
    
    else if (mV > 1170) UV_index = 11;
}
