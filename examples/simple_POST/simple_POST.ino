/* RestClient simple GET request
 *
 * by Chris Continanza (csquared)
 */

#include <WiFiEsp.h>
#include <SPI.h>
#include "RestClient.h"

char[] ssid = "test";
char[] pass = "test";
int status = WL_IDLE_STATUS;

RestClient client = RestClient("arduino-http-lib-test.herokuapp.com");

//Setup
void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  printWifiStatus();

}

String response;

void loop(){
  response = "";

  int statusCode = client.post("/data", "POSTDATA", &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  delay(1000);
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}