#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include <HTTPClient.h>

using namespace websockets;

WebsocketsClient socket; //instace of webscoket server, enables communication with websocket server
const char* websocketServer = "wss://ws.ifelse.io/";
boolean connected = false; //to monitor the websocket connection

const char* ssid = "Rajendra";
const char* password = "Krish@2014";

void setup() {
  Serial.begin(115200);

  connectWiFi();

  testInternetConnection();

  testHTTP();
  
  connectToWebSocket();

  socket.onMessage(handleMessage); //function to handle msgs recieved from websocket server
  socket.onEvent(handleEvent); //When an event occurs like new connection or close connection this function is called  

}

void loop() {
  socket.poll(); //this function continously listens to incoming msgs and events, to transfer the control to appropriate function to handle the msg / event

  if(!connected){ //to check connection to server
    Serial.println("Connecting to WebSocket server");
    connectToWebSocket();
    }

    }

void handleMessage(WebsocketsMessage message){
  Serial.println(message.data());
  }

void handleEvent(WebsocketsEvent event, WSInterfaceString data){
  //TODO: implement later on
  }

void connectToWebSocket() {
  connected = socket.connect(websocketServer); //initiate connection with the server

  if (connected) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }
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

//TROUBLESHOOTING CODE -------------------------------------------------------------------------------------------------------------------------
void testHTTP() {
  HTTPClient http;
  http.begin("http://jsonplaceholder.typicode.com/posts/1");
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.println("HTTP request successful:");
    Serial.println(http.getString());
  } else {
    Serial.println("HTTP request failed.");
  }
  http.end();
}

void testInternetConnection() {
  HTTPClient http;
  http.begin("http://google.com");
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.println("Internet connection is working.");
  } else {
    Serial.println("No internet connection.");
  }
  http.end();
}
