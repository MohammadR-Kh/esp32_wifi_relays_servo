#include <WiFi.h>
#include <ESP32Servo.h>  // Use ESP32-compatible Servo library

Servo servo;

const char* ssid = "KhMrMo";
const char* password = "M.r.k.h.1113.";

WiFiServer server(80);

int servoPin = 25;
int relay1Pin = 26;
int relay2Pin = 27;

void setup() {
  Serial.begin(115200);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);

  // Attach servo
  servo.setPeriodHertz(50); // Standard 50Hz PWM frequency for servos
  servo.attach(servoPin, 500, 2500); // Set min/max pulse width

  servo.write(90); // Start at 90°

  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  Serial.println("New Client Connected!");
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/relay1-on") != -1) {
    digitalWrite(relay1Pin, LOW);
  }
  if (request.indexOf("/relay1-off") != -1) {
    digitalWrite(relay1Pin, HIGH);
  }
  if (request.indexOf("/relay2-on") != -1) {
    digitalWrite(relay2Pin, LOW);
  }
  if (request.indexOf("/relay2-off") != -1) {
    digitalWrite(relay2Pin, HIGH);
  }
  if (request.indexOf("/deg-0") != -1) {
    servo.write(0);
  }
  if (request.indexOf("/deg-45") != -1) {
    servo.write(45);
  }
  if (request.indexOf("/deg-90") != -1) {
    servo.write(90);
  }
  if (request.indexOf("/deg-135") != -1) {
    servo.write(135);
  }
  if (request.indexOf("/deg-180") != -1) {
    servo.write(180);
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE html>");
  client.println("<html><head><title>ESP32 Control</title></head>");
  client.println("<body><h2>Select a Button</h2>");

  client.println("<p><a href=\"/relay1-on\"><button>Activate Relay 1</button></a></p>");
  client.println("<p><a href=\"/relay1-off\"><button>Deactivate Relay 1</button></a></p>");
  client.println("<p><a href=\"/relay2-on\"><button>Activate Relay 2</button></a></p>");
  client.println("<p><a href=\"/relay2-off\"><button>Deactivate Relay 2</button></a></p>");
  client.println("<p><a href=\"/deg-0\"><button>Servo 0</button></a></p>");
  client.println("<p><a href=\"/deg-45\"><button>Servo 45</button></a></p>");
  client.println("<p><a href=\"/deg-90\"><button>Servo 90</button></a></p>");
  client.println("<p><a href=\"/deg-135\"><button>Servo 135</button></a></p>");
  client.println("<p><a href=\"/deg-180\"><button>Servo 180</button></a></p>");

  client.println("</body></html>");
  client.println();
  client.stop();
}
