#include <ESP8266WiFi.h>

// Define pins
#define SOIL_MOISTURE_PIN A0  // Soil moisture sensor pin
#define MOTOR_PIN D1           // Motor control pin (5V motor via PWM)

int soilMoistureValue;
int threshold = 400;  // Adjust this value based on calibration
int motorSpeed = 512; // PWM speed (0-1023 for ESP8266)

void setup() {
    Serial.begin(115200);
    pinMode(SOIL_MOISTURE_PIN, INPUT);
    pinMode(MOTOR_PIN, OUTPUT);
    analogWrite(MOTOR_PIN, 0); // Ensure motor is OFF initially
}

void loop() {
    soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
    Serial.print("Soil Moisture: ");
    Serial.println(soilMoistureValue);

    // Automatic motor control using PWM
    if (soilMoistureValue > threshold) {
        analogWrite(MOTOR_PIN, motorSpeed);  // Run motor at controlled speed
        Serial.println("Motor ON");
    } else {
        analogWrite(MOTOR_PIN, 0);  // Turn OFF motor
        Serial.println("Motor OFF");
    }
    delay(2000); // Wait 2 seconds before next reading
}
