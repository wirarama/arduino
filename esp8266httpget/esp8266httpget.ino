#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "mikrotek";
const char* password = "test1234";
int out = 2;
void setup () {

Serial.begin(115200);
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print("Connecting..");
 
}
 
}
 
void loop() {
 
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
HTTPClient http;  //Declare an object of class HTTPClient
 
http.begin("http://192.168.88.253/mine/iot/test.php?p="+String(out));  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
if(out==2){
  out=1; 
}else{
  out+=1;
}
if (httpCode > 0) { //Check the returning code
 
String payload = http.getString();   //Get the request response payload
Serial.println(payload);                     //Print the response payload
if(payload=="matikan"){
   Serial.println("ok boss siap dimatikan");
}else{
  Serial.println("ok boss siap dihidupkan");
}
}
 
http.end();   //Close connection
 
}
 
delay(5000);    //Send a request every 30 seconds
 
}
