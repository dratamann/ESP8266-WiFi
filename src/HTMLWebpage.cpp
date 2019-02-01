#include <Arduino.h>
#include <HTMLWebpage.h>

Webpage::Webpage() {

}

String Webpage::html(String outputState1, String outputState2) {
  String html;
  html += "<!DOCTYPE html><html>\n";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  html += "<link rel=\"icon\" href=\"data:,\">\n";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  html += ".button { background-color: #5a5a5a; border: none; color: white; padding: 16px 40px;\n";
  html += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\n";
  html += ".button2 {background-color: #5a5a5a;}</style></head>\n";
  html += "<body><h1>ESP8266 Web Server</h1>";

  html += "<p>GPIO 5 - State " + outputState1 + "</p>\n"; //output
  if (outputState1 == "off") {
    html += "<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>\n";
  } else {
    html += "<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>\n";
  }

  html += "<p>GPIO 4 - State " + outputState2 + "</p>\n";
  if (outputState2 == "off") {
    html += "<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>\n";
  } else {
    html += "<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>\n";
  }

  html += "</body></html>\n";

  return html;
}
