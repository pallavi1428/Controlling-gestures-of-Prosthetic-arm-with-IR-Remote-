#include <IRremote.h>
#include <ESP32Servo.h>

#define IR_RECEIVE_PIN 5
// Define the servo motor pins
const int SM_T = 16;    // Thumb
const int SM_MI = 19;  // Middle & Index
const int SM_RL = 14;  // Ring & Little


// Create a servo object
Servo servoT;
Servo servoMI;
Servo servoRL;

unsigned long lastRawValue = 0;
unsigned long lastDebounceTime = 0; // Declare lastDebounceTime
unsigned long debounceDelay = 50; // Adjust this value based on your needs

unsigned int currentPosition = 0; // Make sure this line is present


void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  servoT.attach(SM_T);  // Attach the servo to pin 9
  servoMI.attach(SM_MI);
  servoRL.attach(SM_RL);

}


void loop() {
  if (IrReceiver.decode()) {
    unsigned long rawValue = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(rawValue);



    // Simple filtering and debouncing
    if ((rawValue - lastRawValue) > 100 && millis() - lastDebounceTime > debounceDelay) {
      lastRawValue = rawValue;

      // Use decodedRawData to trigger different actions
      switch (rawValue) {
        case 0xF30CFF00:
          // Trigger action for the first button
          servoT.write(180);
          servoMI.write(180);
          servoRL.write(180);
          // servoT.write(0;) // Move motor to position 0
          break;
        case 0xE718FF00: // Thumbs_Up
          servoT.write(0);
          servoMI.write(180);
          servoRL.write(180);
          break;
        case 0xA15EFF00: // Victory
          servoT.write(180);
          servoMI.write(0);
          servoRL.write(180);
          break;
        case 0xF708FF00: // Yoga
          servoT.write(180);
          servoMI.write(180);
          servoRL.write(0);
          break;
        case 0xE31CFF00: // Shoot
          servoT.write(0);
          servoMI.write(0);
          servoRL.write(180);
          break;
        case 0xA55AFF00: // Swag
          servoT.write(0);
          servoMI.write(180);
          servoRL.write(0);
          break;
        case 0xBD42FF00: // Salute
          servoT.write(180);
          servoMI.write(0);
          servoRL.write(0);
          break;
        case 0xAD52FF00: // Open
          servoT.write(0);
          servoMI.write(0);
          servoRL.write(0);
          break;
        case 0xBC43FF00: // Forward button
          movePosition(1); // Move to the next position
          break;

        case 0xBB44FF00: // Backward button
          movePosition(-1); // Move to the previous position
          break;
        default:
          break;
      }
      lastDebounceTime = millis();
    }

    IrReceiver.resume(); // Enable receiving of the next value
  }
}




void movePosition(int direction) {
  // Increment or decrement current position and ensure it wraps around
  currentPosition = (currentPosition + direction + 8) % 8;

  // Set servos based on the new current position
  switch (currentPosition) {
    case 0:
      servoT.write(180);
      servoMI.write(180);
      servoRL.write(180);
      break;
    case 1:
      servoT.write(0);
      servoMI.write(180);
      servoRL.write(180);
      break;
    case 2:
      servoT.write(180);
      servoMI.write(0);
      servoRL.write(180);
      break;
    case 3:
      servoT.write(180);
      servoMI.write(180);
      servoRL.write(0);
      break;
    case 4:
      servoT.write(0);
      servoMI.write(0);
      servoRL.write(180);
      break;
    case 5:
      servoT.write(0);
      servoMI.write(180);
      servoRL.write(0);
      break;
    case 6:
      servoT.write(180);
      servoMI.write(0);
      servoRL.write(0);
      break;
    case 7:
      servoT.write(0);
      servoMI.write(0);
      servoRL.write(0);
      break;
  }
}