#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "...";
const char* password = "..";
const char* mqtt_server = "..."; //Сервер MQTT

IPAddress ip(192,168,1,54); //IP модуля
IPAddress gateway(192,168,1,1); // шлюз
IPAddress subnet(255,255,255,0); // маска

WiFiClient espClient;
PubSubClient client(espClient);

#define ID_CONNECT "cupboard"
#define LED     13
#define REL     12
#define BTN     0

void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  digitalWrite(LED, LOW);
}

void reconnect() {
  digitalWrite(LED, !digitalRead(LED));
  while (!client.connected()) {
    if (client.connect(ID_CONNECT)) {
      client.publish("myhome/Cupboard/connection", "true");
      client.publish("myhome/Cupboard/relay", "false");
      client.subscribe("myhome/Cupboard/#");
      digitalWrite(LED, HIGH);
    } else {
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String strTopic = String(topic);
  String strPayload = String((char*)payload);
  ///////////
  if (strTopic == "myhome/Cupboard/relay"){
    if (strPayload == "true"){
        digitalWrite(REL, HIGH);
        client.publish("myhome/Cupboard/relay", "true");
    } else if(strPayload == "false"){
        digitalWrite(REL, LOW);
        client.publish("myhome/Cupboard/relay", "false");
    }
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(REL, OUTPUT);
  pinMode(BTN, INPUT);
  digitalWrite(LED, HIGH);
  Serial.begin(19200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
char* IntToBool (int r) {
    if (r > 0){
      return "true";
    } else{
      return "false";
    }
}

void loop() {
  if (!client.connected()){
    reconnect();
  }
  client.loop();
}
