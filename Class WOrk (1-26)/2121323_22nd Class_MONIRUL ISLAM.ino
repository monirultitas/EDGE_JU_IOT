/*************************************************************
  MQ-9 Gas Sensor with Blynk and Gauge Widget
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6Z4JQubxf"  // Replace with your Template ID
#define BLYNK_TEMPLATE_NAME         "MQ-9 Gas Sensor"
#define BLYNK_AUTH_TOKEN            "5-JaKiP1kOfRv7mtv4rM34JU1XpaxsV3" // Replace with your Auth Token

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials
char ssid[] = "IIT-JU-DLAB";       // WiFi SSID
char pass[] = "iitju1239";         // WiFi password

// MQ-9 gas sensor pin
#define MQ9_PIN A0  // Analog pin connected to MQ-9 sensor

BlynkTimer timer;

// Function to read MQ-9 sensor and send data to Blynk
void sendGasValue() {
  // Read the gas value from the MQ-9 sensor
  int gasValue = analogRead(MQ9_PIN);

  // Optionally, convert the analog reading to voltage
  float voltage = gasValue * (3.3 / 1023.0);

  // Send gas value to the Gauge widget on Virtual Pin V2
  Blynk.virtualWrite(V2, gasValue);

  // Debugging: Print the gas value and voltage to Serial Monitor
  Serial.print("Gas Value (Raw): ");
  Serial.println(gasValue);
  Serial.print("Voltage: ");
  Serial.println(voltage);
}

void setup() {
  // Debug console
  Serial.begin(115200);

  // Connect to WiFi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Set up a timer to call sendGasValue() every second
  timer.setInterval(1000L, sendGasValue);
}

void loop() {
  Blynk.run();  // Run Blynk
  timer.run();  // Run timer
}
