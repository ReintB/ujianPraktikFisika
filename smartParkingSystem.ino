#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo gateServo;

const int entrySensorPin = 2; 
const int exitSensorPin = 3;
const int slot1Pin = 4;       
const int slot2Pin = 5;
const int slot3Pin = 6;   

bool slot1Occupied = false;
bool slot2Occupied = false;
bool slot3Occupied = false;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UJIAN PRAKTIK FISIKA");
  lcd.setCursor(0, 1);
  lcd.print("KELAS XII-4");
  lcd.setCursor(0, 2);
  lcd.print("KELOMPOK-4");
  lcd.setCursor(0, 3);
  lcd.print("SMART PARKING SYSTEM");
  gateServo.attach(9);
  gateServo.write(0);

  pinMode(entrySensorPin, INPUT);
  pinMode(exitSensorPin, INPUT);
  pinMode(slot1Pin, INPUT);
  pinMode(slot2Pin, INPUT);
  pinMode(slot3Pin, INPUT);

  delay(2000);
  lcd.clear();
}

void loop() {
  bool entryDetected = digitalRead(entrySensorPin) == LOW;
  bool exitDetected = digitalRead(exitSensorPin) == LOW;
  bool slot1Detected = digitalRead(slot1Pin) == LOW;
  bool slot2Detected = digitalRead(slot2Pin) == LOW;
  bool slot3Detected = digitalRead(slot3Pin) == LOW;

  slot1Occupied = slot1Detected;
  slot2Occupied = slot2Detected;
  slot3Occupied = slot3Detected;

  int availableSlots = 0;
  if (!slot1Occupied) availableSlots++;
  if (!slot2Occupied) availableSlots++;
  if (!slot3Occupied) availableSlots++;

  lcd.setCursor(0, 0);
  if (availableSlots > 0) {
    lcd.print("Slot Tersedia: " + String(availableSlots) + "   ");
  } else {
    lcd.print("Maaf, Parkir Penuh");
  }

  lcd.setCursor(0, 1);
  lcd.print("Slot 1: ");
  lcd.print(slot1Occupied ? "Terisi " : "Kosong ");
  lcd.setCursor(0, 2);
  lcd.print("Slot 2: ");
  lcd.print(slot2Occupied ? "Terisi " : "Kosong ");
  lcd.setCursor(0, 3);
  lcd.print("Slot 3: ");
  lcd.print(slot3Occupied ? "Terisi " : "Kosong ");

  if (entryDetected) {
    if (availableSlots > 0) {
      gateServo.write(90);
      delay(1000);
    } else {
      gateServo.write(0);
    }
  }

  if (exitDetected) {
    if (availableSlots > 0) {
      gateServo.write(90);
      delay(1000);
    }
  } else if (!entryDetected && !exitDetected) {
    gateServo.write(0);
  }

  delay(100);
}