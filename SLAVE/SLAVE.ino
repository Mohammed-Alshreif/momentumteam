#define PIN 13
#include<SoftwareSerial.h>
SoftwareSerial Slave_serial (5,4); //RX , TX

char c , contant;
String stringc,X;
void setup() {
  Slave_serial.begin(9600);
  pinMode(PIN,OUTPUT);
}

void loop() {
  while(Slave_serial.available()>0){
    c=Slave_serial.read();
    if(c=='\n'){break;}
    else{stringc+=c;}
  }
  
  
  if(c =='\n'){
    X=stringc.substring(stringc.indexOf('S'),stringc.indexOf('E')).substring(1);
    stringc="";c ='s';
    if(X=="1"){
      digitalWrite(PIN,~digitalRead(PIN));
    }
  }

}
