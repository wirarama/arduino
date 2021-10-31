/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = D2;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

uint16_t rawData[135] = {4554, 4502,  614, 1632,  612, 1632,  610, 1634,  640, 484,  560, 562,  640, 484,  562, 562,  612, 512,  560, 1682,  614, 1630,  610, 1660,  614, 482,  560, 564,  560, 562,  560, 562,  614, 510,  560, 564,  612, 1630,  612, 512,  642, 482,  560, 564,  610, 512,  614, 510,  668, 456,  560, 1684,  612, 510,  610, 1660,  612, 1604,  638, 1606,  614, 1630,  562, 1682,  668, 1574,  642, 46748,  4646, 4394,  672, 1574,  642, 1600,  672, 1572,  672, 452,  670, 452,  642, 482,  668, 454,  668, 456,  642, 1602,  644, 1600,  642, 1602,  670, 454,  640, 482,  642, 482,  640, 482,  668, 456,  672, 450,  642, 1602,  728, 396,  670, 454,  642, 480,  640, 482,  700, 422,  642, 482,  668, 1600,  646, 452,  644, 1600,  644, 1626,  644, 1572,  672, 1574,  642, 1602,  644, 1600,  642};  // SAMSUNG E0E040BF


// Update these with values suitable for your network.

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "192.168.1.16";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int stremote = 0;
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char mm[20];
  for (int i = 0; i < length; i++) {
    mm[i] = (char)payload[i];
  }
  Serial.println(mm);
  Serial.println();

  if ((char)payload[0] == '1') {
    irsend.sendRaw(rawData, 135, 38);  // Send a raw data capture at 38kHz.
    if(stremote == 0){
      stremote = 1;
      snprintf (msg, 50, "TV dinyalakan");
    }else{
      stremote = 0;
      snprintf (msg, 50, "TV dimatikan");
    }
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("laptopin","terhubung dari wemos");
      // ... and resubscribe
      client.subscribe("laptopout");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  snprintf (msg, 50, "k");
  
    irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if((char)msg[0]!='k'){
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("laptopin",msg);
    snprintf (msg, 50, "k");
    delay(2000);
  }
}
