int led = 5;//LED pin
int sensor = 6; //sensor pin
int val; //numeric variable

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT); //set sensor pin as input
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(sensor); //Read the sensor
  if(val == HIGH) //when magnetic field is detected, turn led on
  {
    digitalWrite(led, HIGH);
    Serial.println("detect");
  }
  else
  {
    digitalWrite(led, LOW);
  }
}
