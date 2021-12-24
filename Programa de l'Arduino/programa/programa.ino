#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Variables del sensor DHT11
DHT dht(A0,DHT11);

// Variables dels LEDs
int ledgaratge = 2;
int leddormitori = 4;
int ledestudi = 5;
int ledbanya = 6;
int ledbanyb = 7;
int ledsala = 8;
int ledcuina = 9;

// Variables del sensor de llum
int ledjardi = 3;
int resistencia = A1;
int valorres = 0;

// Variables de l'alarma
int ledpassadis = 10;
int buzz = 11;
int PIR = 12;
int alarma = 0;
int moviment;

// Variable del servomotor
Servo servo;

char valor;

//Funcions que es realitzen un cop,
//quan el programa s'inicia
void setup() {
  Serial.begin(9600);
  pinMode(ledjardi,OUTPUT);
  pinMode(ledgaratge,OUTPUT);
  pinMode(leddormitori,OUTPUT);
  pinMode(ledestudi,OUTPUT);
  pinMode(ledbanya,OUTPUT);
  pinMode(ledbanyb,OUTPUT);
  pinMode(ledsala,OUTPUT);
  pinMode(ledcuina,OUTPUT);
  pinMode(ledpassadis,OUTPUT);
  pinMode(PIR,INPUT);
  pinMode(buzz,OUTPUT);
  servo.attach(13);
}

//Funcions que es repetiran
void loop() {
  if(Serial.available() > 0 ) valor = Serial.read();

  //LED automàtic
  if(valor == 'A') {
  valorres = analogRead(resistencia);
  valorres = valorres * 255 / 1023;
  analogWrite(ledjardi,valorres);
  }
  if(valor == 'a') digitalWrite(ledjardi,LOW);
  
  //LEDs
  //LED del garatge
  if(valor == 'B') digitalWrite(ledgaratge,HIGH);
  if(valor == 'b') digitalWrite(ledgaratge,LOW);
  //LED del dormitori
  if(valor == 'C') digitalWrite(leddormitori,HIGH);
  if(valor == 'c') digitalWrite(leddormitori,LOW);
  //LED de l'estudi
  if(valor == 'D') digitalWrite(ledestudi,HIGH);
  if(valor == 'd') digitalWrite(ledestudi,LOW);
  //LED del bany A
  if(valor == 'E') digitalWrite(ledbanya,HIGH);
  if(valor == 'e') digitalWrite(ledbanya,LOW);
  //LED del bany B
  if(valor == 'F') digitalWrite(ledbanyb,HIGH);
  if(valor == 'f') digitalWrite(ledbanyb,LOW);
  //LED de la sala d'estar
  if(valor == 'G') digitalWrite(ledsala,HIGH);
  if(valor == 'g') digitalWrite(ledsala,LOW);
   //LED de la cuina
  if(valor == 'H') digitalWrite(ledcuina,HIGH);
  if(valor == 'h') digitalWrite(ledcuina,LOW);

  //Porta del garatge
  if(valor == 'S') servo.write(90);
  if(valor == 's') servo.write(0);

  //Temperatura
  float temperatura;
  float humitat;
  temperatura = dht.readTemperature();
  humitat = dht.readHumidity();
  Serial.print(temperatura);
  Serial.print(" ºC");
  Serial.print("|");
  Serial.print(humitat);
  Serial.print(" %");
  Serial.print("|");
  delay(2000);

  //Alarma
  moviment = digitalRead(PIR);
  if(valor == 'Z') alarma = 1;
  if(valor == 'z') {
    alarma = 0;
    digitalWrite(buzz,LOW);
  }
  if(alarma == 0) {
    if(moviment == HIGH) {
      digitalWrite(ledpassadis,HIGH);
      delay(5000);
      digitalWrite(ledpassadis,LOW);
    }
    
  }
  if(alarma == 1) {
    if(moviment == HIGH) {
       digitalWrite(buzz,HIGH);
      }
    } 
}
