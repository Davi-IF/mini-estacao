#define   pinSensorUV A2

void measure_UV();

int adc_value = 0,
    UV_index  = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(pinSensorUV, INPUT);
}

void loop()
{
  
  measure_UV();
  Serial.println(UV_index);


  delay(2000);
  
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
