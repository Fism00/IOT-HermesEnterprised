#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>


WiFiClientSecure client;
PubSubClient mqtt(client);

const String SSID = "FIESC_IOT_EDU";
const String PASS = "8120gv08";

const String URL = "d1afbd3a85c7409fa6447c6f1f6ea1ae.s1.eu.hivemq.cloud";
const int PORT = 8883;

const String USR = "Placa_trem";
const String broker_Pass = "Placa_trem1";

//const String MyTopic = "";
//const String OtherTopic = "";

const int led_azul = 27;
const int led_verde = 26;
const int led_vermelho = 25;

const int led1 = 19;
const int led2 = 18;

const int motor_vel = 12;
const int motor_dir = 14;


void setup() {
  Serial.begin(115200);
  client.setInsecure();

  pinMode(led_azul, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);

  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);

  pinMode (motor_vel, OUTPUT);
  pinMode (motor_dir, OUTPUT);

  Serial.println("Conectando ao Wifi");
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(200);
  }
  Serial.println("\nConectado com sucesso ao Wifi!");

  Serial.println("Conectando ao Broker");
  mqtt.setServer(URL.c_str(), PORT);

  while (!mqtt.connected()) {
    String ID = "TREM_";
    ID += String(random(0xffff), HEX);
    mqtt.connect(ID.c_str(), USR.c_str(), broker_Pass.c_str());
    Serial.print('.');
    delay(200);
  }
  Serial.println("\nConectado com sucesso ao Broker!");

  //se inscrever no topico
  mqtt.subscribe("HermesEnterprise/Trem/velocidade");
  // definir callback
  mqtt.setCallback(callback);
}

void loop() {
  mqtt.loop();
  delay(10);
}

void callback(char* topic, byte* payload, unsigned int length) {
  // ler payload
  String mensagem;
  for(int i = 0; i < length; i++){
        char c = (char)payload[i];
        mensagem += c;
  }
  // converter para int
  int velocidade = mensagem.toInt();
  Serial.printf("Recebido: %s\n",mensagem);
  // 
  if (velocidade > 0){
    //frente
      digitalWrite(led1,HIGH);
      digitalWrite(led2,LOW);
  }
  else if (velocidade < 0){
    //tras
   digitalWrite(led1,LOW);
   digitalWrite(led2,HIGH);
  } 
   
       else {
   //para
   digitalWrite(led1,LOW);
   digitalWrite(led2,LOW);}
}
