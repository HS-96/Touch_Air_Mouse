#include <Wire.h>
#include <MPU6050.h>
#include <Mouse.h>

MPU6050 mpu;
int touchPin = 4;
int touchState = 0;
unsigned long touchStartTime = 0;

// Movement variables
int16_t ax, ay, az, gx, gy, gz;
float vx = 0, vy = 0;

// Movement thresholds
const int threshold = 2; // Lower threshold for more sensitivity
const float smoothingFactor = 0.5; // Increase smoothing factor for better response

void setup() {
  Wire.begin();
  mpu.initialize();
  Mouse.begin();
  
  pinMode(touchPin, INPUT);
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  // Calculate movement using only gx and gy
  float new_vx = -gz * 0.5; // Use gy to control X
  float new_vy = -gx * 0.5; // Use gx to control Y

  // Apply smoothing
  vx = (vx * (1 - smoothingFactor)) + (new_vx * smoothingFactor);
  vy = (vy * (1 - smoothingFactor)) + (new_vy * smoothingFactor);

  // Adjust values to be balanced when pointing toward the screen
  if (abs(vx) < threshold) vx = 0;
  if (abs(vy) < threshold) vy = 0;

  // Center the cursor when finger is pointed forward
  if (ax > 10000) { // You can adjust this value as needed
    // Don't move the mouse, just reset vx and vy
    vx = 0;
    vy = 0;
  } else {
    // Move the mouse if movement is noticeable
    if (abs(vx) > threshold || abs(vy) > threshold) {
      Mouse.move(vx / 100, vy / 100); // Divide speed to improve accuracy
    }
  }
  
  // Read the state of the touch sensor
  touchState = digitalRead(touchPin);
  
  if (touchState == HIGH) {
    if (touchStartTime == 0) {
      touchStartTime = millis(); // Start timing on touch
    } else {
      // Long touch
      if (millis() - touchStartTime > 1000) {
        Mouse.press(MOUSE_LEFT);
      }
    }
  } else {
    if (touchStartTime != 0) {
      if (millis() - touchStartTime < 1000) {
        // Single tap
        Mouse.click(MOUSE_LEFT);
      } else {
        // Release long touch
        Mouse.release(MOUSE_LEFT);
      }
      touchStartTime = 0; // Reset timing
    }
  }
  
  delay(5); // Reduce delay to improve responsiveness
}
