#define interrupt1 2

#include<SoftwareSerial.h>
SoftwareSerial arduino_serial (10,11); //RX , TX
void setup() {
  arduino_serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interrupt1), IR1, RISING);
 delay(400);
}

void loop() {
}

void IR1(){
   arduino_serial.print("S1 E");
}
