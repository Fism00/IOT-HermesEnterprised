#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

WiFiClientSecure client;
PubSubClient mqtt(client);

//pin usados
const byte TRIGGER_ULTRA_1 = 25;
const byte ECHO_ULTRA_1 = 33;
const byte TRIGGER_ULTRA_2 = 27;
const byte ECHO_ULTRA_2 = 34;
const byte PINO_LED = 19;

//constantes p/broker
const String URL   = "d1afbd3a85c7409fa6447c6f1f6ea1ae.s1.eu.hivemq.cloud";
const int PORT     = 8883;
const String USR   = "Placa_s2";
const String PASS  = "Placa_s2";

//topicos
const String topicPresença1 = "IOT-HermesEnterprise/S2/presenca1";
const String topicPresença2 = "IOT-HermesEnterprise/S2/presenca2";
const String topicIlum = "IOT-HermesEnterprise/S1/Ilum";

//constantes p/wifi
const String ssid = "FIESC_IOT_EDU";
const String pass = "8120gv08";

// callback para acender o led
void callback(char* topic, byte* payload, unsigned int length) {
  String mensagem;

  // Transforma o payload recebido em texto
  for (unsigned int i = 0; i < length; i++)
    mensagem += (char)payload[i];

  Serial.print("Recebido em [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(mensagem);

  // Se a mensagem veio do tópico de iluminação
  if (String(topic) == topicIlum) {

    if (mensagem == "escuro")
      digitalWrite(PINO_LED, HIGH);  // Liga LED

    else if (mensagem == "claro")
      digitalWrite(PINO_LED, LOW);   // Desliga LED
  }}

  

void setup() {

  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);
  
  Serial.begin(115200);
  client.setInsecure();

// designação

  pinMode(TRIGGER_ULTRA_1 ,OUTPUT);
  pinMode(TRIGGER_ULTRA_2 ,OUTPUT);
  pinMode(ECHO_ULTRA_1 ,INPUT);
  pinMode(ECHO_ULTRA_2 ,INPUT);


  Serial.println("Conectando ao WiFi");
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {

    Serial.print(".");
    delay(200);

  }
  Serial.println("\nConectado com sucesso!");

  mqtt.setServer(URL.c_str(),PORT);
  while(!mqtt.connected()){
    String ID = "S2_";
    ID += String(random(0xffff),HEX); //cria a parte aleatoria
    mqtt.connect(ID.c_str(),USR.c_str(),PASS.c_str());
    Serial.print(".");
    delay(200);

  }
  Serial.println("\nConectado com sucesso ao broker!");

mqtt.subscribe(topicIlum.c_str());

mqtt.setCallback(callback);
}

long lerPresenca_1() {
  digitalWrite(TRIGGER_ULTRA_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_ULTRA_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_ULTRA_1, LOW);
  
  long duracao = pulseIn(ECHO_ULTRA_1, HIGH);
  long distancia_1 = duracao * 349.24 / 2 / 10000;
  
  return distancia_1;
}

long lerPresenca_2() {
  digitalWrite(TRIGGER_ULTRA_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_ULTRA_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_ULTRA_2, LOW);
  
  long duracao = pulseIn(ECHO_ULTRA_2, HIGH);
  long distancia_2 = duracao * 349.24 / 2 / 10000;
  
  return distancia_2;
}

void loop() {

  mqtt.subscribe(topicIlum.c_str());

  long presenca_1 = lerPresenca_1();
  long presenca_2 = lerPresenca_2();
  
  Serial.print("Distância sensor 1: ");
  Serial.print(presenca_1);
  Serial.println(" cm");

  if (presenca_1 < 10) {
    Serial.println("Objeto próximo do primeiro sensor!");
    mqtt.publish(topicPresença1.c_str(), "Esteve na estação 2");
  }

   Serial.println("---");

  Serial.print("Distância sensor 2: ");
  Serial.print(presenca_2);
  Serial.println(" cm");

   if (presenca_2 < 10) {
    Serial.println("Objeto próximo do segundo sensor!");
    mqtt.publish(topicPresença2.c_str(), "Esteve na estação 3");
  }

  Serial.println("---");

  delay(500);

  mqtt.loop();
  delay(2000);

}
