#include <Wire.h>
#include <LiquidCrystal_I2C.h>//Library for the LCD

#define MQ2_PIN 34      // MQ2 Sensor Analog Pin
#define LED_PIN 32      // LED Pin
#define BUZZER_PIN 16   // Buzzer Pin
#define GAS_THRESHOLD 400  // Adjust based on testing

// Initialize LCD (I2C address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {//part of the code runs one time
  Serial.begin(115200); //Sets the baud rate to 115200 to enable serial communication
  
  pinMode(LED_PIN, OUTPUT);//sets pin 32 of ESP to output
  pinMode(BUZZER_PIN, OUTPUT);//sets pin 16 of ESP to output

  lcd.init();// turns the LCD on
  lcd.backlight();//turns the LCD backlight on
  lcd.setCursor(0, 0);// sets the cursor on the LCD to Column 0, Row 0
  lcd.print("Gas Sensor Ready");// Prints Gas Sensor Ready
  delay(2000); // Ensures the string displays for 2seconds
  lcd.clear();// Clears the LCD
}

void loop() {
  int gasValue = analogRead(MQ2_PIN);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(gasValue);
  lcd.setCursor(0, 1);
  
  if (gasValue > GAS_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.print("DANGER! HIGH GAS");
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.print("Safe");
  }

  delay(1000);
}