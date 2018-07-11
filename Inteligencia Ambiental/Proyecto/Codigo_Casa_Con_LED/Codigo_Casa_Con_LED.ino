#include <cactus_io_AM2302.h>

#define AM2302_PIN 2
#define PUERTO_LED_ALARMA 3
#define PUERTO_LED_LUZ 1
#define SENSORPIN A0

AM2302 dht(AM2302_PIN);

float temperatura = 100;
float temperatura2 = 100;

int sensorValue = 0;
bool alarmactiva = false;

void setup() {
  // inicializamos los LEDs
  pinMode(PUERTO_LED_ALARMA, OUTPUT);
  pinMode(PUERTO_LED_LUZ, OUTPUT);

  // Abrimos conexion e iniciamos el sensor
  Serial.begin(9600);
  Serial.println("SENSOR");
  dht.begin();
}


void loop() {

  // Hace una lectura del sensor 
    dht.readTemperature();
  
  // si no detecta sensor comenzaria la alarma  
  if (isnan(dht.temperature_C)) {
    Serial.println("AM2302 failure");
    Serial.println("ALARMA ADVERTENCIA ENCIENDE");
    digitalWrite(PUERTO_LED_ALARMA, HIGH);
    delay(1000);
    digitalWrite(PUERTO_LED_ALARMA, LOW);
    delay(1000);
    alarmactiva = true;
    return;    
  }
  //Si la lectura detecta más de 30º comienza la alarma
  if (dht.temperature_C > 30) {
    Serial.println("ALARMA PELIGRO ENCIENDE");
    digitalWrite(PUERTO_LED_ALARMA, HIGH);
    delay(500);
    digitalWrite(PUERTO_LED_ALARMA, LOW);
    delay(500);
    alarmactiva = true;
  } else {
    alarmactiva = false;
    }
  //Si es de día y no esta activa la alarma
  // activamos el sistema de luz
   //Lo primero es comprobar si es de día o de noche
  //Con el bucle eliminamos posibles errores de lectura
  for (int j=0; j<=7; j++){
    sensorValue += analogRead(SENSORPIN);  
  }

  sensorValue = sensorValue/7.0;
  
  Serial.println("Valor del potenciometro:");
  if (sensorValue > 900 ){
    Serial.println("ES TARDE/NOCHE");  
  } else {
    Serial.println("ES DE DÍA");
  }
  
  if (sensorValue >= 900 && !alarmactiva) {
    //Sino hacemos 7 lecturas y despues sacamos la media
    //esto nos permite eliminar el ruido
    for (int i=0; i<7; i++){
      dht.readTemperature();
      temperatura += dht.temperature_C;  
    }
    temperatura = temperatura/8;
  

    Serial.print("TEMPERATURA LECTOR: ");
    Serial.println(temperatura);
    Serial.println(dht.temperature_C);
 
    // Si la temperatura ha subido (Existe presencia)
    //  Por lo que enciende la luz
    if (temperatura > temperatura2 ) {
      Serial.print("LUZ ENCIENDE");
      digitalWrite(PUERTO_LED_LUZ, HIGH);
      delay(3000);
      digitalWrite(PUERTO_LED_LUZ, LOW);
      delay(3000);
      Serial.println();
    }


    //Por ultimo actualizamos nuestra temperatura para comparar
    temperatura2 = temperatura;
  
    delay(3000);
  }
}


