#define PUERTO_LED 3

void setup() {
  // put your setup code here, to run once:
  pinMode(PUERTO_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PUERTO_LED, HIGH);
  delay(500);
  digitalWrite(PUERTO_LED, LOW);
  delay(500);
}
