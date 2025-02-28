#include <DHT.h>

// Define Pins
#define LDR_PIN A0           // LDR connected to A0 (Analog input)
#define DHT_PIN D6           // DHT11 connected to GPIO12
#define DHT_TYPE DHT11       // Define DHT sensor type
#define RAIN_DIGITAL D7      // Raindrop sensor connected to GPIO13 (Digital Output)

// Initialize DHT Sensor
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
    
    pinMode(RAIN_DIGITAL, INPUT);  // Set digital pin for raindrop sensor

    Serial.println("Weather Station Initialized...");
}

void loop() {
    // Read LDR Value (Light Intensity)
    int ldrValue = analogRead(LDR_PIN);

    // Read Temperature & Humidity from DHT11
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Read Rain Sensor (Digital Output)
    int rainStatus = digitalRead(RAIN_DIGITAL); // HIGH = No Rain, LOW = Rain detected

    Serial.println("Weather Station Data:");

    // LDR Light Intensity
    Serial.print("LDR Light Intensity: "); 
    Serial.println(ldrValue);

    // DHT11 Temperature & Humidity
    if (!isnan(temperature) && !isnan(humidity)) {
        Serial.print("Temperature: "); Serial.print(temperature); Serial.println("°C");
        Serial.print("Humidity: "); Serial.print(humidity); Serial.println("%");
    } else {
        Serial.println("DHT11 Sensor Error! Check connections.");
    }

    // Raindrop Sensor Status
    Serial.print("Rain Detected: "); 
    Serial.println(rainStatus == LOW ? "Yes" : "No");

    Serial.println("----------------------");
    delay(2000); // Delay for 2 seconds
}
