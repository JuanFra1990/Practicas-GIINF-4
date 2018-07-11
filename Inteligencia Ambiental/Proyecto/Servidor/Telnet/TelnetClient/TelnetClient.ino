/*
  Telnet client
 
 This sketch connects to a a telnet server (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.  You'll need a telnet server 
 to test this with.
 Processing's ChatServer example (part of the network library) works well, 
 running on port 10002. It can be found as part of the examples
 in the Processing application, available at 
 http://processing.org/
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 14 Sep 2010
 modified 9 Apr 2012
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0x90,0xa2,0xda,0x0f,0x44,0x17};
IPAddress ip(192,168,48,197);

// Enter the IP address of the server you're connecting to:
IPAddress server(192,168,48,32); 

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 23 is default for telnet;
// if you're using Processing's ChatServer, use  port 10002):
EthernetClient client;

void setup() {
  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 10002)) {
    Serial.println("connected");
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // as long as there are bytes in the serial queue,
  // read them and send them out the socket if it's open:
  /*while (Serial.available() > 0) {
    char inChar = Serial.read();
    if (client.connected()) {
      client.print(analogRead(sensorPin)); 
      
    }
  }*/

  if (client.connected()) {
      client.print(analogRead(sensorPin));
      delay(1000);
  }
  // if the server's disconnected, stop the client:
  while (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    // do nothing:
    // if you get a connection, report back via serial:
    /*if (client.connect(server, 10002)) {
      Serial.println("connected");
    } */
    while(true){
      // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 10002)) {
    Serial.println("connected");
    break;
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  }
 }
}





