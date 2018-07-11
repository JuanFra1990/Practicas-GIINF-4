#include <cactus_io_AM2302.h>

#define AM2302_PIN 2
#define PUERTO_LED 3
#define SENSORPIN A0

AM2302 dht(AM2302_PIN);

float temperatura1 = 100;
float temperaturamedia = 0;

int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("SENSOR");
  dht.begin();

  pinMode(PUERTO_LED, OUTPUT);
}


void loop() {

  for (int j=0; j<=7; j++){
    sensorValue += analogRead(SENSORPIN);  
  }

  sensorValue = sensorValue/7.0;
  
  Serial.println("Valor del potenciometro:");
  Serial.println(sensorValue);
    
  if ( sensorValue >= 900) 
  {
    for(int i=0; i<=7;i++){
      dht.readTemperature(); 
      temperaturamedia += dht.temperature_C; 
    }

    temperaturamedia = temperaturamedia / 8.0;
    
  
    if (isnan(dht.temperature_C)) {
      Serial.println("AM2302 failure");
      return;    
    }

    Serial.print("TEMPERATURA C LECTOR: ");
    Serial.print(dht.temperature_C);
    Serial.println();

    Serial.print("TEMPERATURA C 1: ");
    Serial.print(temperaturamedia);
    Serial.println();

    Serial.print("TEMPERATURA C 2: ");
    Serial.print(temperatura1);
    Serial.println();
  
  
    if (temperaturamedia > temperatura1 ) 
    {
      Serial.print("LED ENCIENDE");
      digitalWrite(PUERTO_LED, HIGH);
      delay(3000);
      digitalWrite(PUERTO_LED, LOW);
      delay(3000);
      Serial.println();
    }

    temperatura1 = temperaturamedia;
    delay(3000);
} 
delay(1000);   
}


