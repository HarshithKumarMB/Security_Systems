#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "ssid_name";
const char* password = "password";

const char* host = "maker.ifttt.com";
const int httpsPort = 443;
int sound = A0;
int val = 0;
int info_pin = D2;
void setup() {
  Serial.begin(115200);
  pinMode(sound, INPUT);
  pinMode(info_pin, OUTPUT);
  digitalWrite(info_pin, LOW);
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  val = analogRead(sound);
  Serial.println(val);
  delay(200);
  if(val>685){
    BearSSL::WiFiClientSecure client;
  const int API_TIMEOUT = 10000;  //keep it long if you want to receive headers from client
  client.setInsecure();
  client.setTimeout(API_TIMEOUT);

  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/trigger/esp/with/key/hxJ7O-vJCkfIWeEhzNfI1A-uufDhXXXXXXXXXXX";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');

  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
  digitalWrite(info_pin, HIGH);
  delay(3000);
  digitalWrite(info_pin, LOW);
  }

}
