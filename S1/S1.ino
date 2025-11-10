#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient client;
PubSubClient mqtt(client);
//pin usados
const byte TRIGGER_PIN = 5;
const byte ECHO_PIN = 18;



//constantes p/broker
const String URL   = "test.mosquitto.org";
const int PORT     = 1883;
const String USR   = "";
const String PASS  = "";
const String topic = "DSM1";

//constantes p/wifi
const String ssid = "FIESC_IOT_EDU";
const String pass = "8120gv08";

void setup() {
  
  Serial.begin(115200);

  // pinos output ou input
   pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Conectando ao WiFi");
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {

    Serial.print(".");
    delay(200);

  }
  Serial.println("\nConectado com sucesso!");

  mqtt.setServer(URL.c_str(),PORT);
  while(!mqtt.connected()){
    String ID = "S1_";
    ID += String(random(0xffff),HEX); //cria a parte aleatoria
    mqtt.connect(ID.c_str(),USR.c_str(),PASS.c_str());
    Serial.print(".");
    delay(200);

  }
  Serial.println("\nConectado com sucesso ao broker!");

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
  }
  
  delay(500);

  mqtt.loop();
  delay(1000);

}
