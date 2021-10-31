String str;
void setup(){
 Serial.begin(115200);
 delay(2000);
}
void loop()
{
  str = "test 1234";
  Serial.println(str);
  delay(5000);
}
