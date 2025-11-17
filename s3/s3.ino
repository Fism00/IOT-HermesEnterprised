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
int estado_movimento = 0;

Servo meuServo2;
const byte SERVO2_PIN = 19;



void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  meuServo.attach(SERVO_PIN);
  meuServo2.attach(SERVO2_PIN);

  meuServo.write(90);
  meuServo2.write(90);
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
    if (estado_movimento == 0) {
      Serial.println("Objeto próximo!");
      meuServo.write(180);
      meuServo2.write(0);
      estado_movimento = 1;

      delay(1500);
    } else if (estado_movimento == 1){
      Serial.println("Objeto próximo!");
      meuServo.write(0);
      meuServo2.write(180);
      estado_movimento = 0;

      delay (1500);
    }
    
 delay(500);
  }

  delay(50);
}
  



