/*************************************************************
  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
*************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6QLPex1BU"
#define BLYNK_TEMPLATE_NAME "IOT"
#define BLYNK_AUTH_TOKEN "y1l_fkYGgLqRy5K2YqK3P4yXJ94KWXBl"  // Your Blynk Auth Token

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>  // Include the DHT library
#include <Wire.h> // Include Wire library for I2C communication
#include <Adafruit_BMP280.h> // Include BMP280 library

// Define Sensor Pins
#define LDR_PIN A0           // LDR connected to A0 (Analog input)
#define DHT_PIN D6           // DHT11 connected to GPIO12 (D6)
#define DHT_TYPE DHT11       // Define DHT sensor type
#define RAIN_DIGITAL D7      // Raindrop sensor connected to GPIO13 (D7)

// BMP280 I2C pins
#define BMP_SDA D2           // SDA connected to D2
#define BMP_SCL D1           // SCL connected to D1

// Wi-Fi credentials
char ssid[] = "MITAS";    // Wi-Fi SSID
char pass[] = "123456781";  // Wi-Fi Password

// Initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Initialize BMP280 sensor
Adafruit_BMP280 bmp; // Create BMP280 object

BlynkTimer timer;

// This function reads sensor data and sends it to Blynk
void readSensorData()
{
  // Read LDR (Light Intensity)
  int ldrValue = analogRead(LDR_PIN);  // Read analog value from LDR
  float lightIntensity = map(ldrValue, 0, 1023, 0, 100);  // Map to percentage (0-100%)

  // Read DHT11 (Temperature and Humidity)
  float temperature = dht.readTemperature();  // Read temperature in Celsius
  float humidity = dht.readHumidity();        // Read humidity in %

  // Read Raindrop Sensor (Digital Output)
  bool isRaining = digitalRead(RAIN_DIGITAL);  // Read digital value (0 or 1)

  // Read BMP280 (Pressure and Altitude)
  float pressure = bmp.readPressure() / 100.0F; // Read pressure in hPa
  float altitude = bmp.readAltitude(1013.25);   // Read altitude in meters (assuming sea level pressure = 1013.25 hPa)

  // Check if DHT sensor reads failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print sensor data to the Serial Monitor
  Serial.print("Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.print(" %, Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Rain: ");
  Serial.print(isRaining ? "No" : "Yes");
  Serial.print(", Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa, Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  // Send sensor data to Blynk App
  Blynk.virtualWrite(V0, lightIntensity);  // Send light intensity to Virtual Pin V0
  Blynk.virtualWrite(V1, temperature);    // Send temperature to Virtual Pin V1
  Blynk.virtualWrite(V2, humidity);       // Send humidity to Virtual Pin V2
  Blynk.virtualWrite(V4, pressure);       // Send pressure to Virtual Pin V4
  Blynk.virtualWrite(V5, altitude);       // Send altitude to Virtual Pin V5

  // Send Rain Status as text to Virtual Pin V3 (for LCD widget)
  String rainStatus = isRaining ? "No" : "Yes";
  Blynk.virtualWrite(V3, rainStatus);     // Send rain status as text to Virtual Pin V3
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Initialize DHT sensor
  dht.begin();

  // Set Raindrop Sensor pin as input
  pinMode(RAIN_DIGITAL, INPUT);

  // Initialize BMP280 sensor
  Wire.begin(BMP_SDA, BMP_SCL); // Initialize I2C communication
  if (!bmp.begin(0x76)) {       // Default I2C address for BMP280 is 0x76
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  // Initialize Blynk with your Wi-Fi credentials
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Print connection status to the Serial Monitor
  Serial.println("Connecting to Wi-Fi and Blynk...");

  // Setup a function to read sensor data every 2 seconds
  timer.setInterval(2000L, readSensorData);
}

void loop()
{
  Blynk.run();
  timer.run();
}