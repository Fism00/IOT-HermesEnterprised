#include <WiFi.h>

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
}

void loop() {
  // put your main code here, to run repeatedly:

}
