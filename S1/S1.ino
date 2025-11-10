#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>


WiFiClient client;
PubSubClient mqtt(client);
//pin usados

const byte TRIGGER_ULTRA = 22;
const byte ECHO_ULTRA = 23;
const byte LED = 19;
const byte LDR = 34;
const byte RGB_R = 14;
const byte RGB_G = 26;
const byte RGB_B = 25;

//dh11 config
#define DHT_PIN 4
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

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
  pinMode(TRIGGER_ULTRA, OUTPUT);
  pinMode(ECHO_ULTRA, INPUT);
  // dht começar
  dht.begin();

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
  digitalWrite(TRIGGER_ULTRA, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_ULTRA, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_ULTRA, LOW);
  
  long duracao = pulseIn(ECHO_ULTRA, HIGH);
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


  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Erro na leitura do DHT11");
  }else{
  
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print("%  Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C");
  }


  mqtt.loop();
  delay(2000);

}
