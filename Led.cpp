/* Hello World OLED Test */

// Only needed for Arduino 1.6.5 and earlier
#include <ssd1306.h> // alias for `#include "SSD1306Wire.h"`
#include "DHTesp.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "index.h"


const char* ssid = "Olympus";
const char* password = "I am H3rcul3s";

DHTesp dht;

// Set web server port number to 80
ESP8266WebServer server(80);

// Setup for OLED display
#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

#define OLED_RST 4
//SSD1306_text oled(OLED_RST);
// Variable to store the HTTP request
String header;
float Humidity;
float Temperature;
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleTemp()
{
 server.send(200, "text/plane", String(Temperature)); //Send web page
}

void handleHum()
{
 server.send(200, "text/plane", String(Humidity)); //Send web page
}


void setup() {
	Serial.begin(115200);
	//display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// initialize with the I2C addr 0x3C (for the 128x32)(initializing the display)
	dht.setup(14);

	// Connect to Wi-Fi network with SSID and password
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	// Print local IP address and start web server
	Serial.println("");
	Serial.println("WiFi connected.");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	server.on("/", handleRoot);
	server.on("/readHum", handleHum);
	server.on("/readTemp", handleTemp);
	server.begin();
	Serial.println("HTTP server started");
}
/*static void serverWeb(float hum, float temp) {

	float humOut = 0;
	float tempOut = 0;

	WiFiClient client = server.available();   // Listen for incoming clients

	if (client) {                             // If a new client connects,
		Serial.println("New Client."); // print a message out in the serial port
		String currentLine = ""; // make a String to hold incoming data from the client
		while (client.connected()) {        // loop while the client's connected
			if (client.available()) { // if there's bytes to read from the client,
				char c = client.read();             // read a byte, then
				Serial.write(c);              // print it out the serial monitor
				header += c;
				if (c == '\n') {           // if the byte is a newline character
					// if the current line is blank, you got two newline characters in a row.
					// that's the end of the client HTTP request, so send a response:
					if (currentLine.length() == 0) {
						// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
						// and a content-type so the client knows what's coming, then a blank line:
						client.println("HTTP/1.1 200 OK");
						client.println("Content-type:text/html");
						client.println("Connection: close");
						client.println();

						// turns the GPIOs on and off
						if (header.indexOf("GET /humidity/get") >= 0) {
							Serial.println("Get humidity");
							humOut = hum;
						} else if (header.indexOf("GET /temperature/get")
								>= 0) {
							Serial.println("Get temperature");
							  tempOut = temp;
						}
						// Display the HTML web page
						client.println("<!DOCTYPE html><html>");
						client.println(
								"<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
						client.println("<link rel=\"icon\" href=\"data:,\">");
						// CSS to style the on/off buttons
						// Feel free to change the background-color and font-size attributes to fit your preferences
						client.println(
								"<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
						client.println(
								".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
						client.println(
								"text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
						client.println(
								".button2 {background-color: #77878A;}</style></head>");

						// Web Page Heading
						client.println("<body><h1>ESP8266 Web Server</h1>");

						// Display current state, and ON/OFF buttons for GPIO 5
						client.println(
								"<p>Humidity " + String(hum) + "</p>");
						// displays the Get humidity button
						//     client.println("<p><a href=\"/5/on\"><button class=\"button\">GET HUM</button></a></p>");

						// Display current state, and ON/OFF buttons for GPIO 4
						client.println(
								"<p>Temperature " + String(temp) + "</p>");
						// displays the get temperature button

						//     client.println("<p><a href=\"/4/on\"><button class=\"button\">GET TEMP</button></a></p>");
						client.println("</body></html>");

						// The HTTP response ends with another blank line
						client.println();
						// Break out of the while loop
						break;
					} else { // if you got a newline, then clear currentLine
						currentLine = "";
					}
				} else if (c != '\r') { // if you got anything else but a carriage return character,
					currentLine += c;    // add it to the end of the currentLine
				}
			}
		}
		// Clear the header variable
		header = "";
		// Close the connection
		client.stop();
		Serial.println("Client disconnected.");
		Serial.println("");
	}
}*/
//
//static void textDemo()
//{
//	// Check if any reads failed and exit early (to try again).
//	  if (isnan(h) || isnan(t) || isnan(f)) {
//	    display.clearDisplay(); // clearing the display
//	    display.setTextColor(WHITE); //setting the color
//	    display.setTextSize(1); //set the font size
//	    display.setCursor(5,0); //set the cursor coordinates
//	    display.print("Failed to read from DHT sensor!");
//	    return;
//	  }
//	  display.clearDisplay();
//	  display.setTextColor(WHITE);
//	  display.setTextSize(1);
//	  display.setCursor(0,0);
//	  display.print("Humidity: ");
//	  display.print(h);
//	  display.print(" %\t");
//	  display.setCursor(0,10);
//	  display.print("Temperature: ");
//	  display.print(t);
//	  display.print(" C");
//	  display.setCursor(0,20);
//	  display.print("Temperature: ");
//	  display.print(f);
//	  display.print(" F");
//
//
//}

void loop() {

	Humidity = dht.getHumidity();
	Temperature = dht.getTemperature();

	Serial.print(dht.getStatusString());
	Serial.print("\t");
	Serial.print(Humidity, 1);
	Serial.print("\t\t");
	Serial.print(Temperature, 1);
	Serial.print("\t\n\r");

	//textDemo();
	server.handleClient();
}

/***************************************************
 * Get indoor Temp/Hum data
 ****************************************************/

