#include <Arduino.h>
#include <WiFi.h>
#include <Update.h>
#include <ESPmDNS.h>
#include <PubSubClient.h>

int calibrationTime = 20;       

//Время, в которое был принят сигнал отсутствия движения(LOW)
long unsigned int lowIn;        

boolean isEvent = false;
int switchStatus = 0;

int ledPin = 1;   //вывод сигнального диода
int relayPin1 = 13;  //реле пин
int relayPin2 = 12;
int relayPin3 = 14;
int relayPin4 = 27;
int relayPin5 = 26;
int relayPin6 = 25;
int relayPin7 = 33;
int relayPin8 = 32;

const char* ssid = "MikroTik-2G";
const char* password = "";
const char* mqtt_server = "192.168.4.99";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  //for (int i = 0; i < length; i++) {
  //  Serial.print((char)payload[i]);
  //}
  //Serial.println();
  //Serial.println((char)payload[0]);

  // Switch on the LED if an 1 was received as first character
  if (topic == "relay/in/floor/1")
    if ((char)payload[0] == '1') {
      //digitalWrite(ledPin, LOW);   // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is active low on the ESP-01)
      digitalWrite(relayPin1, HIGH);
    } 
    if ((char)payload[0] == '0') {
      //digitalWrite(ledPin, HIGH);  // Turn the LED off by making the voltage HIGH
      digitalWrite(relayPin1, LOW);
    }
  }
  if (topic == "relay/in/floor/2")
    if ((char)payload[0] == '1') digitalWrite(relayPin2, HIGH);
    if ((char)payload[0] == '0') digitalWrite(relayPin2, LOW);
  }
  if (topic == "relay/in/floor/3")
    if ((char)payload[0] == '1') digitalWrite(relayPin3, HIGH);
    if ((char)payload[0] == '0') digitalWrite(relayPin3, LOW);
  }
  if (topic == "relay/in/floor/4")
    if ((char)payload[0] == '1') digitalWrite(relayPin4, HIGH);
    if ((char)payload[0] == '0') digitalWrite(relayPin4, LOW);
  }
  if (topic == "relay/in/floor/5")
    if ((char)payload[0] == '1') digitalWrite(relayPin5, HIGH);
    if ((char)payload[0] == '0') digitalWrite(relayPin5, LOW);
  }
  if (topic == "relay/in/floor/6")
    if ((char)payload[0] == '1') digitalWrite(relayPin6, HIGH);
    if ((char)payload[0] == '0') digitalWrite(relayPin6, LOW);
  }
  if (topic == "relay/in/floor/7")
    if ((char)payload[0] == '1') digitalWrite(relayPin7, HIGH);
    if ((char)payload[0] == '0') digitalWrite(relayPin7, LOW);
  }
  if (topic == "relay/in/floor/8")
    if ((char)payload[0] == '1') digitalWrite(relayPin8, HIGH);
    if ((char)payload[0] == '0') digitalWrite(relayPin8, LOW);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("relay/out/floor/1", "hello world");
      // ... and resubscribe
      client.subscribe("relay/in/floor/1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  //pinMode(ledPin, OUTPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  pinMode(relayPin5, OUTPUT);
  pinMode(relayPin6, OUTPUT);
  pinMode(relayPin7, OUTPUT);
  pinMode(relayPin8, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //!ВНИМАНИЕ! При использовании n-p-n реле необходимо в след. строчке поменять HIGH на LOW
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, HIGH);
  digitalWrite(relayPin4, HIGH);
  digitalWrite(relayPin5, HIGH);
  digitalWrite(relayPin6, HIGH);
  digitalWrite(relayPin7, HIGH);
  digitalWrite(relayPin8, HIGH);
  
  Serial.begin(115200);
  
  Serial.println("старт");
}


void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (digitalRead(relayPin1) == LOW) client.publish("relay/status/floor/1", "1");
  if (digitalRead(relayPin1) == HIGH) client.publish("relay/status/floor/1", "0");
    
  if (digitalRead(relayPin2) == LOW) client.publish("relay/status/floor/2", "1");
  if (digitalRead(relayPin2) == HIGH) client.publish("relay/status/floor/2", "0");

  if (digitalRead(relayPin3) == LOW) client.publish("relay/status/floor/3", "1");
  if (digitalRead(relayPin3) == HIGH) client.publish("relay/status/floor/3", "0");

  if (digitalRead(relayPin4) == LOW) client.publish("relay/status/floor/4", "1");
  if (digitalRead(relayPin4) == HIGH) client.publish("relay/status/floor/4", "0");

  if (digitalRead(relayPin5) == LOW) client.publish("relay/status/floor/5", "1");
  if (digitalRead(relayPin5) == HIGH) client.publish("relay/status/floor/5", "0");

  if (digitalRead(relayPin6) == LOW) client.publish("relay/status/floor/6", "1");
  if (digitalRead(relayPin6) == HIGH) client.publish("relay/status/floor/6", "0");

  if (digitalRead(relayPin7) == LOW) client.publish("relay/status/floor/7", "1");
  if (digitalRead(relayPin7) == HIGH) client.publish("relay/status/floor/7", "0");

  if (digitalRead(relayPin8) == LOW) client.publish("relay/status/floor/8", "1");
  if (digitalRead(relayPin8) == HIGH) client.publish("relay/status/floor/8", "0");  

  //digitalWrite(relayPin, HIGH);
  //delay(2000);
  //digitalWrite(relayPin, LOW);
  //delay(2000);

  delay(50);
}