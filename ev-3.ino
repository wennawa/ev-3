#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
// #include "TFT_eSPI.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

int rpm;

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
}

void loop() {
  // put your main code here, to run repeatedly
  unsigned long start = micros();
  tft.setCursor(0, 0);

  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(5);
  tft.println("RPM: ");
     //rpm = 30*1000/(millis() - timeold)*half_revolutions;
     //timeold = millis();
     //half_revolutions = 0;
     
     //Serial.println(rpm,DEC);
     
  tft.println(rpm)
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
  tft.println();
  return micros() - start;
}

void HallSensor() {
//   // digital pin 2 is the hall pin
  int hall_pin = 2;
  // set number of hall trips for RPM reading (higher improves accuracy)
  float hall_thresh = 100.0;

  void setup() {
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    // make the hall pin an input:
    pinMode(hall_pin, INPUT);
  }

  // the loop routine runs over and over again forever:
  void loop() {
    // preallocate values for tach
    float hall_count = 1.0;
    float start = micros();
    bool on_state = false;
    // counting number of times the hall sensor is tripped
    // but without double counting during the same trip
    while(true){
      if (digitalRead(hall_pin)==0){
        if (on_state==false){
          on_state = true;
          hall_count+=1.0;
        }
      } else{
        on_state = false;
      }
    
      if (hall_count>=hall_thresh){
        break;
      }
    }
  
    // print information about Time and RPM
    float end_time = micros();
    float time_passed = ((end_time-start)/1000000.0);
    Serial.print("Time Passed: ");
    Serial.print(time_passed);
    Serial.println("s");
    float rpm_val = (hall_count/time_passed)*60.0;
    Serial.print(rpm_val);
    Serial.println(" RPM");
    delay(1);        // delay in between reads for stability
  }
 }
