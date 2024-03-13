#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
//#include <LiquidCrystal.h>
// #include "TFT_eSPI.h"

// Screen Global Variables
// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

// Hall Sensor Global Variables
int periodRPM = 4000; //Change depending on speed
long elapsedTimeRPM  = 0;
int revState = 0;
int revolutions = 0;
int hallSensorPin = 4;
int rpm = 0;

int rpm2 = 0;

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
 
  //deselect all SPI devices
  pinMode(TFT_CS, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(7, HIGH);
  tft.begin();
  //tft.setRotation(1);
  tft.fillScreen(ILI9341_WHITE);

  pinMode(hallSensorPin, INPUT);
}

void loop() {
  if ((millis() - elapsedTimeRPM) >= periodRPM) {
    Serial.print("revolutions: ");
    Serial.println(revolutions);
    rpm = revsPM();
    elapsedTimeRPM = millis();
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
  rev();

  //tft.fillScreen(ILI9341_WHITE);

  unsigned long start = micros();
  tft.setCursor(0, 40);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5);
  tft.println(rpm2);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(5);
  tft.println("RPM: ");
  tft.println(rpm);
  tft.println();
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(4);
  tft.println("Flow Rate: ");
  // flow rate equation goes here
  //tft.println(flowRate)
  tft.println();
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2.5);
  tft.println("Wind Velocity: ");
  // wind velocity based on wind tunnel testing goes here
    //tft.println(windVelocity)
  rpm2 = rpm;
  tft.println();
  return micros() - start;
}

int revsPM() {
  int revspermin = (revolutions * (60000)) / periodRPM;
  revolutions = 0;
  return revspermin;
}

void rev() {
  switch(revState) {
    case 0:
      if (digitalRead(hallSensorPin)) {
        revState = 0;
      }
      else {
        revState = 1;
        revolutions++;
        Serial.println("increasing revolutions");
      }
    case 1:
      if (digitalRead(hallSensorPin)) {
        revState = 0;
      }
      else {
        revState = 1;
      }

  }
}
