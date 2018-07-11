#include <cactus_io_AM2302.h>

#define AM2302_PIN 3

AM2302 dht(AM2302_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("SENSOR");

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  dht.readTemperature();

  if (isnan(dht.temperature_C)) {
    Serial.println("AM2302 failure");
    return;    
  }
  
  Serial.print("TEMPERATURA C");
  Serial.print(dht.temperature_C);
  Serial.print("TEMPERATURA F");
  Serial.print(dht.temperature_F);
  delay(3000);
}


