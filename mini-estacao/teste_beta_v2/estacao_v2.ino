// bibliotecas usadas

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h> 
#include <dht.h>

// definindo pinos usados nos sensores
#define pinSensorDHT 8 //pino usado no sensor DHT22
#define pinSensorAnemo 2 //pino usado no anemometro
#define UVOUT A0 // Pino Usado para saida do sensor UV
#define REF_3V3 A1 //pino ligado na porta de energia 3.3v

// ** assinatura das funções ** // 
void umidade_temperatura();
void calc_pressao();
void calc_UV();
int averageAnalogRead(int pinToRead);
void windvelocity();
void RPMcalc();
void WindSpeed();


//instância dos sensores
dht dhtSensor;

/*imporatante resaltar que o sensor bmp280 utilizado 
tem 6 pinos, sendo eles: vcc, gnd, scl, sda, csb, sdo 
onde exceto o csb é conectado. 
vcc e sdo é na porta 3.3;
gnd é na gnd;
scl pode ser na A5, portando comigo não funcionou por isso pesquisei o pinout do arduino uno e usei a propria porta dedicada a  scl
sda pode ser na A4, portando comigo não funcionou por isso pesquisei o pinout do arduino uno e usei a propria porta dedicada a  sda
*/ 
Adafruit_BMP280 bmpSensor;

//variaveis utilizadas 
int iteracao;                    // Variavel usado para guardar a iteração da estação
float umid;                      // Armazena a umidade do ar 
float temp;                      // Variavel que armazena a temperatura 
float pres;                      // Variavel que armazena a pressão do ar
float intensidadeUV;             // Variavel que armazena a radiação solar
const float pi = 3.14159265;     //Número de pi
int period = 5000;               //Tempo de medida(miliseconds)
int delaytime = 2000;            //Invervalo entre as amostras (miliseconds)
int radius = 147;                //Raio do anemometro(mm)
unsigned int counter = 0;        //Contador para o sensor
unsigned int RPM = 0;            //Rotações por minuto
float windspeed = 0;             //Velocidade do vento (m/s)


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  iteracao = 1;

  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);

  if(!bmpSensor.begin()){
    Serial.println("Sensor BMP280 não encontrado!");
    while(1);
  }
}

void loop() {
  //Chamando as funções abaixo
  umidade_temperatura();
  calc_pressao();
  calc_UV();
  windvelocity();
  RPMcalc();
  WindSpeed();

  //imprimindo na serial, no formato de acordo com o arquivo .csv
  Serial.print(iteracao++);
  Serial.print(",");
  Serial.print(pres);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.print(umid);
  Serial.print(",");
  Serial.print(intensidadeUV,10);
  Serial.print(",");
  Serial.println(windspeed);
  
  
  //intervalo de 2seg
  delay(2000);
}

// função que calcula umidade e temperatura
void umidade_temperatura(){
  int readData = dhtSensor.read22(pinSensorDHT);
  umid = dhtSensor.humidity;
  temp = dhtSensor.temperature;
}

// função responsavel por pegar a pressão atmosferica 
void calc_pressao(){
  pres = bmpSensor.readPressure()/100;
}

void calc_UV(){
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Uso o 3.3 por conta de maior precissão
  float outputVoltage = 3.3 / refLevel * uvLevel;

  //saida em mW/cm2
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);

  //conversão para kJ/cm2
  uvIntensity /= 1000;
  //multiplica pelo o numero de segundos
  intensidadeUV  = uvIntensity * 2;
  intensidadeUV  /= 1000;
  
}

/* 
 * função do Nathan Seidle da SparkFun Eletronics
 * Pega a leitura do pin passado como parametro e retorna a média
*/
 
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Função para medir velocidade do vento
void windvelocity() {
  windspeed = 0;

  counter = 0;
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();
  long startTime = millis();
  while (millis() < startTime + period) {}
}

//Função para calcular o RPM
void RPMcalc() {
  RPM = ((counter) * 60) / (period / 1000); // Calculate revolutions per minute (RPM)
}

//Velocidade do vento em m/s
void WindSpeed() {
  windspeed = ((4 * pi * radius * RPM) / 60) / 1000; //Calcula a velocidade do vento em m/s
}

//Incrementa contador
void addcount() {
  counter++;
}
