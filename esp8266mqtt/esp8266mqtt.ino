#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "ssid";
const char* password =  "password";
const char* mqttServer = "ipbroker";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
int i = 0;
 
WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("test", "Hello from ESP8266");
  client.subscribe("test");
  
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
  String kirim = (String)i+","+(String)i;
  const char * c = kirim.c_str();
  client.publish("test",(const char*)i);
  client.publish("test",c);
  i = i+1;
  delay(2000);
}
