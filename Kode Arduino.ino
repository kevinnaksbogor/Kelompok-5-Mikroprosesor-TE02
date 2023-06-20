#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2);

int Pintrigger = 9;
int PinEcho = 8;
int Buzzer = 11;
int LEDM = 2;
int LEDK = 3;
int LEDH = 4;
float duration,distance;
int tinggiSensordaritanah = 50;

// Sensor pins
#define sensorPin A0

// Value for storing water level
int val = 0;


void setup() {
  lcd.init();
  lcd.backlight(); //supaya lampu backlightnya nyala
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("KELOMPOK 5");
  lcd.setCursor(0,1);
  lcd.print("Tinggi : ");
  pinMode(Pintrigger, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(PinEcho, INPUT);
  pinMode(LEDM, OUTPUT);
  pinMode(LEDK, OUTPUT);
  pinMode(LEDH, OUTPUT);
  Serial.begin(9600);
  
  // Set D7 as an OUTPUT
	
	// Set to LOW so no power flows through the sensor
	
	Serial.begin(9600);

}

void loop() {
  digitalWrite(Pintrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Pintrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Pintrigger, LOW);
  duration = pulseIn(PinEcho, HIGH);
  distance = (duration*.0343)/2;

  int tinggiBanjir = tinggiSensordaritanah-distance;
  lcd.setCursor(9,1);
  lcd.print(String(tinggiBanjir)+" cm    ");
  Serial.println(tinggiBanjir);
  if (distance <= 10){
    digitalWrite(LEDH,1);
    digitalWrite(LEDM,1);
    digitalWrite(LEDK,1);
  } else if (distance < 20 && distance > 10){
   digitalWrite(LEDK,1);
   digitalWrite(LEDH,1);
   digitalWrite(LEDM,0);
 } else if (distance >= 20){
   digitalWrite(LEDM,0);
   digitalWrite(LEDH,1);
   digitalWrite(LEDK,0);
 }
 //get the reading from the function below and print it
	int val = analogRead(sensorPin);
	Serial.print("Water level: ");
	Serial.println(val);
	
	delay(120);

  if(val > 400){
    digitalWrite(Buzzer,1);
    
  }else{
    digitalWrite(Buzzer,0);
  }
  delay(50);
  
}
