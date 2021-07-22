#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
SoftwareSerial GPRS(7, 9);
LiquidCrystal lcd(0, 1, 3, 4, 5, 6); /// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN,D6 PIN, D7 PIN

//boolean state, laststate;
int count = 0, count1 = 0, count2 = 0;
int clk = 15; //the second remaining for openning the box
const int ledPin = 13;
const int buzzerPin = 11;
const int ldrPin = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(12, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  GPRS.begin(9600);


  GPRS.println("AT");
  delay(1000);
  lcd.begin(16, 2);

}

void loop() {
  // put your main code here, to run repeatedly
  while (GPRS.available())
  {
    Serial.write(GPRS.read());
  }
  // Serial.print("Count: ");
  //Serial.println(count);
  //Serial.print("Count1: ");
  //Serial.println(count1);
  //state = false;
  //state = digitalRead(2);
  int ldrStatus = analogRead(ldrPin);

  if (ldrStatus >= 5 && count <= 15 && count1 == 0) {
    sendMessage();
    delay(2000);
    // digitalWrite(3,HIGH);
    count1 = 1;

  }
  if (count1 == 1) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WARNING");
    buzzer();

  }
  // lcd.clear();
  // Serial.println(clk);
  // delay(1000);

  if (clk < 0) {
    if (count1 != 1) {
      lcd.setCursor(0, 0);
      lcd.print("NOW YOU CAN OPEN");
      lcd.setCursor(0, 1);
      lcd.print("THE BOX");
    }
  }

  else {
    if (count1 != 1) {
      lcd.setCursor(0, 0);
      lcd.print("Remaining time:");

      lcd.setCursor(0, 1);
      lcd.print(clk);
    }
  }
  count++;
  clk--;

  delay(1000);
  lcd.clear();
}


void sendMessage()
{
  Serial.println("Switch was turned on");
  //Serial.println(state ? "on" : "off");

  GPRS.println("AT + CMGF = 1 ");

  delay(2000);

  GPRS.println("AT + CMGS = \"+8801933635970\" ");

  delay(2000);

  GPRS.println("Someone has opened the box no. 0015 before the scheduled time. Please check whether any occurance created or not.");

  delay(1000);
  //GPRS.println(state ? "on" : "off");
  GPRS.write(0x1a );

  delay(2000);
}

void buzzer()
{
  tone(buzzerPin, 50);
  digitalWrite(ledPin, HIGH);
  delay(500);

  noTone(buzzerPin);
  digitalWrite(ledPin, LOW);
}

