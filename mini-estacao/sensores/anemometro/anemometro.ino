// --- Constantes ---
const float pi = 3.14159265;     //Número de pi
int period = 5000;               //Tempo de medida(miliseconds)
int delaytime = 2000;            //Invervalo entre as amostras (miliseconds)
int radius = 147;                //Raio do anemometro(mm)


// --- Variáveis Globais ---
unsigned int Sample  = 0;       
unsigned int counter = 0;          
unsigned int RPM = 0;          
float speedwind = 0;             //Velocidade do vento (km/h)

void setup()
{
   
  pinMode(2, INPUT);        //configura o digital 2 como entrada
  digitalWrite(2, HIGH);    //internall pull-up active
    
   
  Serial.begin(9600);     
 
} //end setup



void loop()
{
  Sample++;
  Serial.print(Sample);
  Serial.print(": Start measurement...");
  windvelocity();
  Serial.println("   finished.");
  Serial.print("Counter: ");
  Serial.print(counter);
  Serial.print(";  RPM: ");
  RPMcalc();
  Serial.print(RPM);
  Serial.print("\t\t"); 
  SpeedWind();
  Serial.print(speedwind);
  Serial.print(" [km/h] ");  
  Serial.println();


  delay(delaytime);                      
  
}

//Função para medir velocidade do vento
void windvelocity()
{
  speedwind = 0;
  
  counter = 0;  
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();       
  long startTime = millis();
  while(millis() < startTime + period) {}
}


//Função para calcular o RPM
void RPMcalc()
{
  RPM=((counter)*60)/(period/1000);  // Calculate revolutions per minute (RPM)
}

//Velocidade do vento em km/h
void SpeedWind()
{
  speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6;  //Calcula velocidade do vento em km/h
 
} //end SpeedWind


//Incrementa contador
void addcount()
{
  counter++;
} 
