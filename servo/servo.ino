#define servobin 8
bool m1=1 , m2=0;
long servotime;
long long tim1=0;

void servo(char servoangle){
   servotime =map(servoangle,-90,90,1000,2000);
  if((micros()-tim1>=servotime)&&(m1)){
    digitalWrite(servobin,LOW);
    tim1=micros();
    m1=0;
    m2=1;
  }
  if((micros()-tim1>=(20000-servotime))&&(m2)){
    digitalWrite(servobin,HIGH);
    tim1=micros();
    m1=1;
    m2=0;
  }
}
void setup() {
  pinMode(servobin,OUTPUT);
  digitalWrite(servobin,HIGH);
  tim1=micros();
}

void loop() {
  
  servo(45);
  
}
