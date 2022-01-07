#include<SoftwareSerial.h>
#include <LiquidCrystal.h>

#define TxD 1
#define RxD 0
SoftwareSerial bluetoothSerial(TxD, RxD);
char r = ' ';

#define change 6
float read1 = 0, read2 = 0, v1, v2, percent1, percent2;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  bluetoothSerial.begin(9600);
  Serial.begin(9600);
  pinMode(change, OUTPUT);
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(change, LOW);
  delay(500);
  read1 = analogRead(A0);
  v1 = read1 * 5.0 / 1023;
  digitalWrite(change, HIGH);
  delay(500);
  read2 = analogRead(A1);
  v2 = read2 * 5.0 / 1023;
  percent1 = map(v1, 3.6, 4.2, 0, 100);
  percent2 = map(v2, 3.6, 4.2, 0, 100);
  bluetoothSerial.write("battery1 ");
  bluetoothSerial.write(percent1);
  bluetoothSerial.write(" ");
  bluetoothSerial.write("battery2 ");
  bluetoothSerial.write(percent2);
  if (bluetoothSerial.available()) {
    r = bluetoothSerial.read();
  }
  if (r == '1' || percent2 >= 100) {
    digitalWrite(change, LOW);
  }
  else if (r == '2' || percent1 >= 100) {
    digitalWrite(change, HIGH);
  }
  lcd.setCursor(0, 0);
  lcd.print("B1: ");
  lcd.print(percent1);
  lcd.setCursor(0, 1);
  lcd.print("B2: ");
  lcd.print(percent2);
  delay(1000);
}
