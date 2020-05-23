#include <MicroGear.h>
#include <WiFi.h>
#include <DHT.h>
#include <EasyBuzzer.h>
const char* ssid     = "FANCIA_2.4G";
const char* password = "NAVINASAWIN";

#define APPID   "iotproject1234"
#define KEY     "1hSwWjllFpQhqjy"
#define SECRET  "YNvylCG5XQe9DqCnlghTKJ02G"
#define ALIAS   "ESP32"
//const int kPin_Photocell = 13;//light ///will change pin values
int sensorPin = 14; //fire  // will change pin values
int sensorsval = 0;
int Flame = HIGH;

#define DHTTYPE DHT11

uint8_t DHTPin = 13; 
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
//const int potPin = 34;
const int sensor = 35;
 int val = 0; 
//const int trigPin = 2;
//const int echoPin = 5;
#include <NewPing.h>
const int TRIGGER_PIN = 2;
const int ECHO_PIN = 5;
const int MAX_DISTANCE = 600;
const int Sound = 34;
const int buzz =27; 
//long duration;
//int distance;
// const int vulu = 2;
// int lightInit;
// int lightVal;


WiFiClient client;
int timer = 0;
MicroGear microgear(client);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);

//  microgear.publish("/Sensor/try","56",true);

  int pot = dht.readTemperature();
  delay(1000);
  int pot1 = dht.readHumidity();
  delay(1000);

//  val = analogRead(potPin);
//  delay(500);
  int value = analogRead(kPin_Photocell);
  
  int volu = 0;
  int count = 0;
  long confirm = digitalRead(sensor);
  int lighting =0;
  int ko = 0;
//  int Flame = 0;
  Flame = digitalRead(sensorPin);
  if (Flame==LOW){

//      Serial.println(Flame);
 
    Serial.println("Fire Detected Run");
  microgear.chat("Sensor/aag","Fire Detected");
  delay(1000);
  
//  delay(2000);
  
//  delay(1000);
//  Serial.println("Fire");
  }else{
    Serial.println("Peace no Fire");
    microgear.chat("Sensor/aag","Peace No Fire");
//    delay(2000);
//    delay(200);
//    Serial.println(ko);
    
  }
  delay(200);
  

  if(value<200){
    microgear.chat("Sensor/light11","dark");
    Serial.println(value);
  }else{
    microgear.chat("Sensor/light11","lightaagaya");
    Serial.println(value);
  }
  
//  delay(1000);
  
  
  
 if(pot>=32){

  microgear.chat("Sensor/tempu","danger");
  microgear.publish("/will42/project","danger");
  Serial.print ("Push notification sent ->");
  microgear.chat("Sensor/temperaturings", pot);
 }else{
   microgear.chat("Sensor/temperaturings", pot);
  
 }
//  digitalWrite(trigPin, LOW);
//delayMicroseconds(2);
//// Sets the trigPin on HIGH state for 10 micro seconds
//digitalWrite(trigPin, HIGH);
//delayMicroseconds(10);
//digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH,250000);
//  distance = duration*0.034/2;
//  Serial.print(distance);
//  Serial.println(" cm");
//    delay(50);
    int distance = sonar.ping_cm();
   Serial.print(distance);
   Serial.println("cm");
  if(distance<=50){
//    microgear.chat("Sensor/distance","someone just passed by !!ALERTTTTT");
//    delay(100);
    microgear.chat("Sensor/distance1",distance);
  }else if(distance <= 200 && distance >= 50){
//    microgear.chat("Sensor/distance","something  is  very wrong at home");
//    delay(200);
    microgear.chat("Sensor/distance1",distance);
    
  }else {
//    microgear.chat("Sensor/distance","everything is fine ");
//        delay(1000);
    microgear.chat("Sensor/distance1",distance);
    
    
    
  }
//  delay(2000);
  



val = analogRead(Sound);

//Serial.println(val,DEC);
delay(100); 
if (val >= 150) {
  microgear.chat("Sensor/sound",val);
//  microgear.chat("Sensor/sound", "Sound detected");
} else {
  microgear.chat("Sensor/sound",val);
//  microgear.chat("Sensor/sound", "Sound detected");
}
  
 microgear.chat("Sensor/humiditings",pot1);
   
//    Serial.print ("Push notification sent ->");
//  delay(1000);
//  microgear.chat("Sensor/Sound",val);
  if(confirm==HIGH){
    volu  = 1;
    microgear.chat("Sensor/Motion",1);
    microgear.chat("Sensor/deet","Motion detected");
    
//    microgear.chat("Sensor/deetu","Motion detected");
    
  }else{
    volu=0;
    microgear.chat("Sensor/Motion",0);
    microgear.chat("Sensor/deet","Motion  Not detected");
    
    
  }
  delay(2000);



  if(confirm==HIGH  && distance<=50){
    
    count = count+1;
    microgear.chat("Sensor/Detection","Person Detected");
    Serial.print("Someone detected:");
    Serial.print("Distance="+distance);
//    Serial.print("Sound Level="+val);
    Serial.print("Motion= True");
    
   
    microgear.publish("/will42/project","someonedetected");
    
    Serial.print ("Push notification sent ->");
    
    EasyBuzzer.singleBeep(1000,200);
  }else{
    microgear.chat("Sensor/Detection","Person Not Detected");
    EasyBuzzer.stopBeep();


  }
  microgear.chat("Sensor/countar",count);

     if(value<80){
    microgear.chat("Sensor/Light","Dark");
    Serial.print(" No Light");
    Serial.print(value);
   
    
   
  }else{
    microgear.chat("Sensor/Light","light");
    Serial.print("Light came");
    Serial.print(value);

  
    
    
//     digitalWrite (buzz, HIGH);
//    delayMicroseconds(1137);
//    digitalWrite(buzz,LOW);
//    delayMicroseconds(1137);

    
  }
  delay(1000);
  
  
//  delay(2000);
// lightVal = analogRead(vulu);
////  lighting = analogRead(vulu);
// if(lightVal - lightInit < 50)
//  {
//      lighting = 0;
//      microgear.chat("Sensor/light",0);
//  }else{
//    lighting=1;
//    microgear.chat("Sensor/light",1);
//  }
  
//delay(500);
    
  
  
  
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Found new member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Lost member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  /* Set the alias of this microgear ALIAS */
  microgear.setAlias(ALIAS);
}


void setup() {
  /* Add Event listeners */
  pinMode(DHTPin, INPUT);
//  pinMode(potPin, INPUT);
  pinMode(sensor, INPUT);
//   pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
  pinMode(Sound, INPUT) ;
   pinMode(sensorPin, INPUT);
//   pinMode(sensorPin, INPUT);// fire sensor
//  pinMode(buzz,OUTPUT);
EasyBuzzer.setPin(buzz);

  

//  lightInit = analogRead(vulu);

  dht.begin();  
  /* Call onMsghandler() when new message arraives */
  microgear.on(MESSAGE, onMsghandler);

  /* Call onFoundgear() when new gear appear */
  microgear.on(PRESENT, onFoundgear);

  /* Call onLostgear() when some gear goes offline */
  microgear.on(ABSENT, onLostgear);

  /* Call onConnected() when NETPIE connection is established */
  microgear.on(CONNECTED, onConnected);

  Serial.begin(115200);
  Serial.println("Starting...");

  /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
  /* You may want to use other method that is more complicated, but provide better user experience */
  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /* Initial with KEY, SECRET and also set the ALIAS here */
  microgear.init(KEY, SECRET, ALIAS);

  /* connect to NETPIE to a specific APPID */
  microgear.connect(APPID);
  
}

void loop() {
  EasyBuzzer.update();
  /* To check if the microgear is still connected */
  if (microgear.connected()) {
    Serial.println("connected");

    /* Call this method regularly otherwise the connection may be lost */
    microgear.loop();

    if (timer >= 1000) {
      Serial.println("Publish...");

      /* Chat with the microgear named ALIAS which is myself */
      microgear.chat(ALIAS, "Hello");
      timer = 0;
      
    }
    else timer += 100;
  }
  else {
    Serial.println("connection lost, reconnect...");
    if (timer >= 5000) {
      microgear.connect(APPID);
      timer = 0;
    }
    else timer += 100;
  }
  delay(100);
}
