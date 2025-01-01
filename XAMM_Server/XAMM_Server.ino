#include<WiFi.h>
#include<HTTPClient.h>

String URL = "http://192.168.31.220/dht11_project/test_data.php";

const char* ssid = "Rajendra";
const char* password = "Krish@2014";

int temperature = 50;
int humidity = 50;

void setup(){
  Serial.begin(11520);
  connectWiFi();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    connectWiFi();
  }

  String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity);

  HTTPClient http;
  http.begin(URL);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);
  String payload = http.getString();

  Serial.print("URL: "); Serial.println(URL);
  Serial.print("Data: "); Serial.println(postData);
  Serial.print("httpCode: "); Serial.println(httpCode);
  Serial.print("payload: "); Serial.println(payload);

}

void connectWiFi() {
WiFi.mode (WIFI_OFF);
delay(1000);
//This line hides the viewing of ESP as wifi hotspot
WiFi.mode (WIFI_STA);

WiFi.begin(ssid, password);
Serial.println("Connecting to WiFi");

while (WiFi.status() != WL_CONNECTED){
delay(500);
Serial.print(".");
}

Serial.print("connected to: "); Serial.println(ssid);
Serial.print("IP address: "); Serial.println(WiFi.localIP());
}
