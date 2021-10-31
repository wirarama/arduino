int sensor = 8;
void setup(){
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  digitalWrite(sensor,LOW);
}
void loop(){
  if(digitalRead(sensor)==HIGH){
    Serial.println("high");
  }else{
    Serial.println("low");
  }
  delay(500);
}
