#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <HTMLWebpage.h>

WiFiServer server(80);
const char* ssid = ""; //The SSID of your router
const char* password = ""; //Your password

// Variable to store the HTTP request
String header;
Webpage html = Webpage();

int Led1 = 5;
int Led2 = 4;

String outputState1 = "off";
String outputState2 = "off";

void sendResponseCode(WiFiClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
}

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);

  // Connection wait
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // print some parameters pertaining to server IP etc.
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // IP address given to NodeMCU

  server.begin();                  // begin server
  Serial.println("HTTP server started");
}


void loop(){
  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            sendResponseCode(client);

            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              outputState1 = "on";
              digitalWrite(Led1, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              outputState1 = "off";
              digitalWrite(Led1, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              outputState2 = "on";
              digitalWrite(Led2, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              outputState2 = "off";
              digitalWrite(Led2, LOW);
            }

            //send webpage
            client.print(html.html(outputState1, outputState2));

            // Break out of the while loop
            break;
          }
          else { // if you got a newline, then clear currentLine
            currentLine = "";
      }
    }
    else if (c != '\r') {  // if you got anything else but a carriage return character,
      currentLine += c;      // add it to the end of the currentLine
      }
    }
  }

  // Clear the header variable
  header = "";
  // Close the connection
  client.stop();
  }
}
