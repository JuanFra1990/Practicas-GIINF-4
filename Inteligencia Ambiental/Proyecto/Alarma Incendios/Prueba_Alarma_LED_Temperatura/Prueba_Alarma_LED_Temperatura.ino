#include <cactus_io_AM2302.h>

#define AM2302_PIN 2
#define PUERTO_LED 3

AM2302 dht(AM2302_PIN);

void setup() {
  // put your setup code here, to run once:
  pinMode(PUERTO_LED, OUTPUT);

  Serial.begin(9600);
  Serial.println("SENSOR");
  dht.begin(); 
}

void loop() {
  dht.readTemperature();

  if (isnan(dht.temperature_C)) {
    Serial.println("AM2302 failure");
    digitalWrite(PUERTO_LED, HIGH);
    delay(1000);
    digitalWrite(PUERTO_LED, LOW);
    delay(1000);
    return; 
  }  
  
  Serial.print("TEMPERATURA C LECTOR: ");
  Serial.print(dht.temperature_C);
  Serial.println();
  
  if (dht.temperature_C > 30) {
    digitalWrite(PUERTO_LED, HIGH);
    delay(500);
    digitalWrite(PUERTO_LED, LOW);
    delay(500);
  }
}
