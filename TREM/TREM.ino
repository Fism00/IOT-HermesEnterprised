#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient client;
PubSubClient mqtt(client);

const String SSID = "FIESC_IOT_EDU";
const String PASS =  "8120gv08";

const String URL   = "test.mosquitto.org";
const int PORT     = 1883;
const String USR   = "";
const String broker_Pass  = "";
const String Topic = "DSM1";


void setup() {
 Serial.begin(115200);
 Serial.println("Conectando ao Wifi");
 WiFi.begin(SSID, PASS);
 
 while (WiFi.status() != WL_CONNECTED) {
  Serial.print('.');
  delay(200);
 }
 Serial.println("\nConectado com sucesso ao Wifi!");

 Serial.println("Conectando ao Broker");
 mqtt.setServer(URL.c_str(),PORT);

 while(!mqtt.connected()){
  String ID = "TREM_";
  ID += String(random(0xffff),HEX);
  mqtt.connect(ID.c_str(),USR.c_str(),broker_Pass.c_str());
  Serial.print('.');
  delay(200);
 }
 Serial.println("\nConectado com sucesso ao Broker!");
}
 
void loop() {
String mensagem = "Gustavo: ";
mensagem += "salve quebrada";

mqtt.publish(Topic.c_str(),mensagem.c_str());
mqtt.loop();
delay(1000);

}