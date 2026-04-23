#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo1; // First servo
Servo myservo2; // Second servo
#define outputA 6 // CLK pin
#define outputB 7 // DT pin

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns, 2 rows

int pos = 90; // Initial position for the servos and the rotary encoder
int aState;
int aLastState;   
int sens = 80; // Adjusted sensitivity to 80 degrees per step

void setup() 
{
  lcd.begin(16, 2); // Define the LCD with 16 columns and 2 rows
  lcd.backlight(); // Power on the backlight
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  lcd.setCursor(0, 0); 
  lcd.print("Current Pos:90");
  aLastState = digitalRead(outputA);
  
  myservo1.attach(9);  // First servo on digital pin 9
  myservo2.attach(10); // Second servo on digital pin 10
  
  myservo1.write(pos); 
  myservo2.write(pos); // Both servos start at the same position
}

void loop() 
{ 
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occurred
  if (aState != aLastState) 
  {     
    // If the outputB state is different from the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != aState) { 
      pos += sens; // Increase by 60 degrees
    } else {
      pos -= sens; // Decrease by 60 degrees
    }

    // Keep the position within the servo's range
    if (pos < 0) pos = 0;
    if (pos > 180) pos = 180;

    // Calculate the reverse angle to display
    int displayAngle = 180 - pos;

    // Update the LCD and servos
    lcd.setCursor(12, 0); 
    lcd.print(displayAngle); // Print the reversed position
    lcd.print("   "); // Clear leftover characters
    
    myservo1.write(pos); // Update the first servo
    myservo2.write(pos); // Update the second servo

    // Clear second row
    lcd.setCursor(0, 1); 
    lcd.print("             "); 
  } 
  aLastState = aState; // Updates the previous state of the outputA with the current state
}