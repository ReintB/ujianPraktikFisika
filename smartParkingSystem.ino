#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C LCD 20x4

Servo entryGateServo; // Servo untuk palang masuk
Servo exitGateServo;  // Servo untuk palang keluar

const int entrySensorPin = 2;  // Pin sensor masuk
const int exitSensorPin = 3;   // Pin sensor keluar
const int slot1Pin = 4;        // Pin sensor slot 1
const int slot2Pin = 5;        // Pin sensor slot 2
const int slot3Pin = 6;        // Pin sensor slot 3
const int slot4Pin = 7;        // Pin sensor slot 4
const int slot5Pin = 8;        // Pin sensor slot 5
const int slot6Pin = 10;       // Pin sensor slot 6

bool slot1Occupied = false; // Status slot 1
bool slot2Occupied = false; // Status slot 2
bool slot3Occupied = false; // Status slot 3
bool slot4Occupied = false; // Status slot 4
bool slot5Occupied = false; // Status slot 5
bool slot6Occupied = false; // Status slot 6

void setup() {
  Serial.begin(9600);

  // Inisialisasi LCD
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

  // Inisialisasi servo
  entryGateServo.attach(9);  // Servo palang masuk di pin 9
  exitGateServo.attach(11);  // Servo palang keluar di pin 11
  entryGateServo.write(0);   // Palang masuk tertutup
  exitGateServo.write(0);    // Palang keluar tertutup

  // Inisialisasi pin sensor
  pinMode(entrySensorPin, INPUT);
  pinMode(exitSensorPin, INPUT);
  pinMode(slot1Pin, INPUT);
  pinMode(slot2Pin, INPUT);
  pinMode(slot3Pin, INPUT);
  pinMode(slot4Pin, INPUT);
  pinMode(slot5Pin, INPUT);
  pinMode(slot6Pin, INPUT);

  delay(2000); // Delay awal untuk stabilisasi
  lcd.clear(); // Bersihkan LCD setelah delay
}

void loop() {
  // Baca status sensor
  bool entryDetected = digitalRead(entrySensorPin) == LOW;
  bool exitDetected = digitalRead(exitSensorPin) == LOW;
  bool slot1Detected = digitalRead(slot1Pin) == LOW;
  bool slot2Detected = digitalRead(slot2Pin) == LOW;
  bool slot3Detected = digitalRead(slot3Pin) == LOW;
  bool slot4Detected = digitalRead(slot4Pin) == LOW;
  bool slot5Detected = digitalRead(slot5Pin) == LOW;
  bool slot6Detected = digitalRead(slot6Pin) == LOW;

  // Update status slot
  slot1Occupied = slot1Detected;
  slot2Occupied = slot2Detected;
  slot3Occupied = slot3Detected;
  slot4Occupied = slot4Detected;
  slot5Occupied = slot5Detected;
  slot6Occupied = slot6Detected;

  // Hitung slot yang tersedia
  int availableSlots = 0;
  if (!slot1Occupied) availableSlots++;
  if (!slot2Occupied) availableSlots++;
  if (!slot3Occupied) availableSlots++;
  if (!slot4Occupied) availableSlots++;
  if (!slot5Occupied) availableSlots++;
  if (!slot6Occupied) availableSlots++;

  // Tampilkan status slot di LCD
  lcd.setCursor(0, 0);
  if (availableSlots > 0) {
    lcd.print("Slot Tersedia: " + String(availableSlots) + "   ");
  } else {
    lcd.print("Maaf, Parkir Penuh");
  }

  lcd.setCursor(0, 1);
  lcd.print("S1:");
  lcd.print(slot1Occupied ? "Terisi " : "Kosong");
  lcd.setCursor(0, 2);
  lcd.print("S2:");
  lcd.print(slot2Occupied ? "Terisi " : "Kosong");
  lcd.setCursor(0, 3);
  lcd.print("S3:");
  lcd.print(slot3Occupied ? "Terisi " : "Kosong");

  lcd.setCursor(10, 1);
  lcd.print("S4:");
  lcd.print(slot4Occupied ? "Terisi " : "Kosong");
  lcd.setCursor(10, 2);
  lcd.print("S5:");
  lcd.print(slot5Occupied ? "Terisi " : "Kosong");
  lcd.setCursor(10, 3);
  lcd.print("S6:");
  lcd.print(slot6Occupied ? "Terisi " : "Kosong");

  // Kontrol palang masuk
  if (entryDetected) {
    if (availableSlots > 0) {
      entryGateServo.write(90); // Buka palang masuk
      Serial.println("En ya" + entryDetected);
      while (digitalRead(entrySensorPin) == LOW) {
        // Tetap terbuka selama sensor masih mendeteksi obstacle
        delay(100); // Delay kecil untuk menghindari busy-waiting
      }
      // delay(3000); // Biarkan palang terbuka selama 3 detik setelah obstacle hilang
      entryGateServo.write(0); // Tutup palang masuk
    }
  }

  // Kontrol palang keluar
  if (exitDetected) {
    exitGateServo.write(180); // Buka palang keluar
    Serial.println("Ex ya" + exitDetected);
    while (digitalRead(exitSensorPin) == LOW) {
      // Tetap terbuka selama sensor masih mendeteksi obstacle
      delay(100); // Delay kecil untuk menghindari busy-waiting
    }
    // delay(3000); // Biarkan palang terbuka selama 3 detik setelah obstacle hilang
    exitGateServo.write(0); // Tutup palang keluar
  }

  delay(100); // Delay kecil untuk stabilisasi pembacaan sensor
}
