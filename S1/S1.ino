#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient client;
PubSubClient mqtt(client);

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

void loop() {
  String mensagem = "Heitor: ";
  mensagem += "sinistron voltaras a jogatina";

  mqtt.publish(topic.c_str(),mensagem.c_str);
  mqtt.loop();
  delay(1000);

}
