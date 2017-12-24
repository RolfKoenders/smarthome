#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(000, 000, 0, 000);
IPAddress server(000, 000, 0, 000);

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

// Doorbell pin
const int doorbellPin = 0;

void setup() {
  pinMode(doorbellPin, INPUT);
  Serial.begin(9600);
  Serial.println("connect to network");
  Ethernet.begin(mac, ip);
  
  if (client.connect("client-id", "user", "pass")) {
    Serial.println("connected to mosquitto");
  }
}

void loop() {
  client.loop();
  int input = digitalRead(doorbellPin);
  if (input == 0) {
    sendRequest();
    delay(5000);
  }
}

void sendRequest() {
  client.publish("hass/doorbell", "ding");
}
