void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(random(-100, 100)); // Escribe en el puerto un numero aleatorio de -100 a 100
  delay(2000);
}
