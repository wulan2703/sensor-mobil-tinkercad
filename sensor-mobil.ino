#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C (alamat default Tinkercad)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin HC-SR04
const int trigPin = 9;
const int echoPin = 10;

// Pin Piezo Buzzer (DIGITAL!)
const int buzzerPin = 7;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Sensor Dimulai");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Trigger HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca pantulan
  duration = pulseIn(echoPin, HIGH, 30000);

  // Hitung jarak (cm)
  distance = duration * 0.034 / 2;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(distance);
  lcd.print(" cm");

  lcd.setCursor(0, 1);

  // Logika suara + tampilan
  if (distance > 35) {
    lcd.print("Aman");
    noTone(buzzerPin);
  }
  else if (distance > 30) {
    lcd.print("Awas");
    tone(buzzerPin, 800);
  }
  else if (distance > 15) {
    lcd.print("Waspada");
    tone(buzzerPin, 1200);
  }
  else {
    lcd.print("Bahaya");
    tone(buzzerPin, 2000);
  }

  delay(500);
}
