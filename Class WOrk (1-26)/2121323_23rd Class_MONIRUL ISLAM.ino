#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the I2C address for the LCD (usually 0x27 or 0x3F)
#define LCD_I2C_ADDRESS 0x27

// Create an LCD object with I2C address, columns, and rows
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, 20, 4);

// Define the MQ9 sensor pin
#define MQ9_PIN A0

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();              // Initialize the LCD
  lcd.backlight();         // Turn on the backlight
  lcd.setCursor(0, 0);     // Set cursor to the first row, first column
  lcd.print("MQ9 Sensor Init"); // Print initialization message

  delay(2000); // Wait for 2 seconds
  lcd.clear(); // Clear the display
}

void loop() {
  // Read the analog value from the MQ9 sensor
  int mq9Value = analogRead(MQ9_PIN);

  // Print the sensor value to the Serial Monitor
  Serial.print("MQ9 Sensor Value: ");
  Serial.println(mq9Value);

  // Display the sensor value on the LCD
  lcd.setCursor(0, 0); // Set cursor to the first row, first column
  lcd.print("MQ9 Sensor Value: ");
  lcd.setCursor(0, 1); // Set cursor to the second row, first column
  lcd.print("Reading: ");
  lcd.print(mq9Value); // Display the analog value
  lcd.print("   ");    // Clear any leftover characters

  delay(1000); // Wait for 1 second before the next reading
}

