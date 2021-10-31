#include <hcsr04.h>

#define TRIG_PIN 11
#define ECHO_PIN 12

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);
int jarak = 0;
void setup(){
    Serial.begin(9600);
}

void loop() {
    jarak = hcsr04.distanceInMillimeters();
    Serial.print(jarak);
    if(jarak<=100){
    Serial.println("dekat");
    }
    else if(jarak>100 and jarak < 2000){
    Serial.println("sedang");
    }
    else{
    Serial.println("jauh");
    }
    delay(250);
    
}
