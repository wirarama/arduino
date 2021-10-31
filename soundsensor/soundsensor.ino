int soundSensor = 2;
int LED = 3;

void setup() 
{
  Serial.begin(9600);
  pinMode (soundSensor, INPUT);
  pinMode (LED, OUTPUT);
}

void loop()
{
  int statusSensor = digitalRead (soundSensor);
  
  if (statusSensor == 1)
  {
    digitalWrite(LED, HIGH);
    Serial.println("ada suara");
  }
  
  else
  {
    digitalWrite(LED, LOW);
    Serial.println("sunyi");
  }
  delay(1000);
}
