#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "yourfirebasehost"
#define FIREBASE_AUTH "yourfirebaseauth"
#define TRIGGERPIN D1
#define ECHOPIN D2
#define ssid  "yourssid"
#define pass  "yourpass"
long duration;
  int distance;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  WiFi.begin(ssid, pass);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("distance", 0);
}
int n = 0;
void loop() {
  

  digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = duration*0.034/2;

  if(distance <= 9) {
    Serial.print(distance);
    Serial.println("cm");
    Firebase.setInt("distance",distance);
    delay(10000);
    return;
  }
  else if(distance >=10){
    Serial.print(distance);
    Serial.println("cm");
    Firebase.setInt("distance",distance);
    delay(50);
    return;
  }
  if(Firebase.failed()){
    Serial.print("pushing/logs failed");
    Serial.println(Firebase.error());
    return;
  }

  delay(100);
  
}
