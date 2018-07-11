#include <cactus_io_AM2302.h>

#define AM2302_PIN 2
#define PUERTO_LED 3

AM2302 dht(AM2302_PIN);

float temperatura1 = 100;
float temperatura2 = 100;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("SENSOR");
  dht.begin();

  pinMode(PUERTO_LED, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
   dht.readTemperature();
  
  if (isnan(dht.temperature_C)) {
    Serial.println("AM2302 failure");
    return;    
  }

  temperatura1 = dht.temperature_C;

   Serial.print("TEMPERATURA C LECTOR: ");
  Serial.print(dht.temperature_C);
  Serial.println();

  Serial.print("TEMPERATURA C 1: ");
  Serial.print(temperatura1);
  Serial.println();

  Serial.print("TEMPERATURA C 2: ");
  Serial.print(temperatura2);
  Serial.println();
  
  
  if (temperatura1 > temperatura2 ) {
      Serial.print("LED ENCIENDE");
      digitalWrite(PUERTO_LED, HIGH);
      delay(3000);
      digitalWrite(PUERTO_LED, LOW);
      delay(3000);
      Serial.println();
  }

  temperatura2 = temperatura1;
  
  delay(3000);
}


