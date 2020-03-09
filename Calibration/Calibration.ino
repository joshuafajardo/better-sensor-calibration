#include <Wire.h>
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"

NAU7802 myScale;

#define MEASUREMENTS_PER_WEIGHT 50 //The number of measurements to take per weight

float currentWeight = 0;
int i = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Calibration");

  Wire.begin();
  Wire.setClock(400000);

  if (myScale.begin() == false)
  {
    Serial.println("Scale not detected. Please check wiring. Freezing...");
    while (1);
  }
  myScale.setSampleRate(NAU7802_SPS_320);
  
  Serial.println("When the readings pause, remove current weight and enter a new weight.");
  Serial.println("Report weight in grams.");
  Serial.println("Measurements Per Weight: " + String(MEASUREMENTS_PER_WEIGHT));
  Serial.println("Press any key to continue.");
  while(Serial.available() == 0) delay(10);
  Serial.readStringUntil("\n");
}

void loop()
{
  if (myScale.available() == true)
  {
    long currentReading = myScale.getReading();

    Serial.print(currentWeight, 3); //Print 3 decimal places
    Serial.print(", ");
    Serial.print(currentReading); 
    Serial.print(";");
    Serial.println();
    i++;
  }
  if (i == MEASUREMENTS_PER_WEIGHT)
  {
    while (Serial.available() == 0) delay(10);
    String strWeight = Serial.readStringUntil("\n");
    currentWeight = strWeight.toFloat();
    i = 0;
  }
}
