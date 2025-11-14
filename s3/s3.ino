#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

WiFiClient client;
PubSubClient mqtt(client);

const String SSID = "FIESC_IOT_EDU";
const String PASS =  "8120gv08";

const String url   = "d1afbd3a85c7409fa6447c6f1f6ea1ae.s1.eu.hivemq.cloud";
const int port     = 8883;
const String USR   = "";
const String Pass  = "";
const String Topic = "DSM1";
const String broker_PASS = "";
const String Mytopic = "Kaus";
const String OtherTopic = "Klahold";
const byte TRIGGER_PIN = 5;
const byte ECHO_PIN = 18;

Servo meuServo;
const byte SERVO_PIN = 21;

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  meuServo.attach(SERVO_PIN);
}

long lerDistancia() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  long duracao = pulseIn(ECHO_PIN, HIGH);
  long distancia = duracao * 349.24 / 2 / 10000;
  
  return distancia;
}

void loop() {
  long distancia = lerDistancia();
  
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");
  
  if (distancia < 10) {
    Serial.println("Objeto próximo!");
      for (int pos = 0; pos <= 180; pos +=1) {
        meuServo.write(pos);
        delay(15);
      }
      for (int pos = 180; pos >= 0; pos -=1) {
        meuServo.write(pos);
        delay(15);
      }
    
    };
     delay(500);
  }
  



