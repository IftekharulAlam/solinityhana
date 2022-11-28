#define pin1 1
#define pin2 2

#define BLYNK_TEMPLATE_ID "TMPLosMYOTUG"
#define BLYNK_DEVICE_NAME "salinity check"
#define BLYNK_AUTH_TOKEN "Hjg6JyFDmEgBVsYKtkarj-3RPT1XUu6k"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
int analogPin = 0;
int dtime = 500;
int raw = 0;
int Vin = 5;
float Vout = 0;
float R1 = 1000;
float R2 = 0;
float buff = 0;
float avg = 0;
int samples = 5000;
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Fab@IUB";
char pass[] = "@makers#";

void setup(){
  pinMode(pin1,OUTPUT); // define ports pin2 and pin1 for AC 
  pinMode(pin2,OUTPUT);
  pinMode(analogPin,INPUT);
  Serial.begin(9600); // start serial
   Blynk.begin(auth, ssid, pass);
   
}

void loop(){
  float tot = 0;
  for (int i =0; i<samples; i++) {
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,LOW);
    delay(1);
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,HIGH);
    delay(1);
    raw = analogRead(analogPin);
    if(raw){
      buff = raw * Vin;
      Vout = (buff)/1024.0;
      buff = (Vin/Vout) - 1;
      R2= R1 * buff;
      //Serial.print("Vout: ");
      //Serial.println(Vout);
      //Serial.print("R2: ");
      //Serial.println(R2);
      tot = tot + R2;
    }
  }
  avg = tot/samples;
  Serial.print("The average resistance is: ");
  Serial.print(avg);
  Serial.println(" Ohm");

  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  Blynk.virtualWrite(V1, avg);
}
