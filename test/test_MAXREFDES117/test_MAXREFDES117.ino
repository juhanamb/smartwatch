// Install MAX30105 library by Sparkfun to test the sensor

#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing MAXREFDES117...");

    // Initialize I2C and MAX30102
    if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
        Serial.println("MAXREFDES117 not found. Check wiring!");
        while (1);
    }

    Serial.println("MAXREFDES117 detected!");

    // Configure the sensor
    particleSensor.setup();
    particleSensor.setPulseAmplitudeRed(0x0A);  // IR LED Current
    particleSensor.setPulseAmplitudeIR(0x0A);   // Red LED Current
}

void loop() {
    // Read sensor values
    long irValue = particleSensor.getIR();
    long redValue = particleSensor.getRed();

    Serial.print("IR: "); Serial.print(irValue);
    Serial.print("\tRed: "); Serial.println(redValue);

    // Basic check if finger is placed
    if (irValue < 50000) {
        Serial.println("No finger detected!");
    }

    delay(500);  // Delay for readability
}