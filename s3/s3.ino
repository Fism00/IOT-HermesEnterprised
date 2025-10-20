#include <WiFi.h>
#include <PubSubClient.h>

WifiClient client;
PubSubClient mqtt(client);

const String SSID = "FIESC_IOT_EDU";
const String PASS =  "8120gv08";

const String url   = "test.mosquitto.org";
const int port     = 1883;
const String USR   = "";
const String Pass  = "";
const String Topic = "DSM1";


void setup() {
 Serial.begin(115200);
 Serial.println("Conectando ao Wifi");
 WiFi.begin(SSID, PASS);
 
 while (WiFi.status() != WL_CONNECTED) {
  Serial.print('.');
  delay(200);
 }
 Serial.println("\nConectado com sucesso!");

 Serial.println("Conectando ao Broker");
 mqtt.setServer(URL.c_str(),PORT);
 while(!,qtt.connnected()){
  String ID = "S3_";
  ID += String(random(0xffff), HEX); //cria a parte aleat.
  mqtt.connect(ID.c+str(),USR.c+str(),PASS.c_str());
  Serial.print('.');
  delay(200)
 }
 Serial.println("\nConectado com sucesso ao broker !");
}
 
void loop() {
  String mensagem = "Kaua: ";
  mensagem += "nao escondi um corpo nas moitas do parque são gonçalo na quinta feira";

  mqtt.loop();
  delay(1000);
}