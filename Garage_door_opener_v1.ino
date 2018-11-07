#include <SPI.h>  
#include <Ethernet2.h>  
#include <PubSubClient.h>  
  
#define CONTACT1 2  
#define CONTACT2 3  
#define RELAY1 7  
#define RELAY2 8  
int prevState1 = HIGH;  
int prevState2 = HIGH;  
  
byte mac[] = { 0x90, 0xA2, 0xDK, 0x12, 0x34, 0xE5 }; //You have to change your Arduino MAC address
IPAddress ip(0, 0, 0, 0); //You have to set your Arduino IP address
IPAddress server(0, 0, 0, 0);   // You have to set your Domoticz server IP adress
  
const char *inTopic = "domoticz/out";  
const char *outTopic = "domoticz/in";  
const char *onmsg1 = "{\"idx\" : 1,\"nvalue\" : 0 }";  // you have to change your Domoticz switch idx
const char *offmsg1 = "{\"idx\" : 1,\"nvalue\" : 1 }"; // you have to change your Domoticz switch idx 
const char *onmsg2 = "{\"idx\" : 2,\"nvalue\" : 0 }";  // you have to change your Domoticz switch idx
const char *offmsg2 = "{\"idx\" : 2,\"nvalue\" : 1 }"; // you have to change your Domoticz switch idx 
  
  
  void callback(char* topic, byte* payload, unsigned int length) {  
    Serial.print("Message arrived [");  
    Serial.print(topic);  
    Serial.print("] ");  
    for (int i=0;i<length;i++) {  
      Serial.print((char)payload[i]);  
    }  
    Serial.println();
    if((char)payload[0] == '1') {
      digitalWrite(RELAY1, LOW);
      delay(500);
      digitalWrite(RELAY1, HIGH);
    }
    if((char)payload[0] == '2') {
      digitalWrite(RELAY2, LOW);
      delay(500);
      digitalWrite(RELAY2, HIGH);
    }
  }  
    
  EthernetClient ethClient;  
  PubSubClient client(ethClient);  
    
  void reconnect() {  
    // Loop until we're reconnected  
    while (!client.connected()) {  
      Serial.print("Attempting MQTT connection...");  
      // Attempt to connect  
      if (client.connect("arduinoClient")) {  
        Serial.println("connected");  
        // Once connected, publish an announcement...  
        client.publish(outTopic,"The arduinoClient connected successfully to MQTT server");  
        // ... and resubscribe  
        client.subscribe(inTopic);  
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
pinMode(CONTACT1, INPUT);   
pinMode(CONTACT2, INPUT);   
pinMode(RELAY1, OUTPUT);   
pinMode(RELAY2, OUTPUT);   
digitalWrite(CONTACT1, HIGH);   
digitalWrite(CONTACT2, HIGH); 
digitalWrite(RELAY1, HIGH);   
digitalWrite(RELAY2, HIGH);
 
   
  client.setServer(server, 1883);  
  client.setCallback(callback);  
   
   
Ethernet.begin(mac, ip);  
Serial.println(Ethernet.localIP());  
delay(1500);  
}  
   
void loop() {  
int curState1 = digitalRead(CONTACT1);  
int curState2 = digitalRead(CONTACT2);  
  
  if (!client.connected()) {  
    reconnect();  
  }  
    
if (curState1 != prevState1) {  
prevState1=curState1;    
 
if (prevState1 == LOW){   
client.publish(outTopic, offmsg1);    
}   
if (prevState1 == HIGH){   
client.publish(outTopic, onmsg1);    
}  }
else if (curState2 != prevState2){
prevState2=curState2; 

if (prevState2 == LOW){   
client.publish(outTopic, offmsg2); 
}   
if (prevState2 == HIGH) {   
client.publish(outTopic, onmsg2);  
} }
delay(2000);
  client.loop();  
}  
