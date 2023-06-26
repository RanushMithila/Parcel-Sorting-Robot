#include <WiFi.h>
#include <WebServer.h>
#include "camera_pins.h"

const char *ssid = "AAA";
const char *password = "181321418";
WebServer server(80);

#define CAMERA_MODEL_AI_THINKER // Has PSRAM

void setup()
{
  Serial.begin(115200);
  delay(1000);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the server
  server.on("/data", handleData);
  server.begin();
  Serial.println("Server started");
  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
}

void loop()
{
  server.handleClient();
  // Add any additional code for the main loop
}

void handleData()
{
  if (server.hasArg("qr_data"))
  {
    String qrData = server.arg("qr_data");
    // Process the received QR code data
    // Add your code here to perform actions based on the received data
    // For example, you can control ESP32-CAM outputs, trigger events, etc.
    // Replace the following line with your desired actions
    Serial.print("Received QR code: ");
    Serial.println(qrData);

    server.send(200, "text/plain", "Data received");
  }
  else
  {
    server.send(400, "text/plain", "Invalid request");
  }
}
