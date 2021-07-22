#include<SoftwareSerial.h>
SoftwareSerial GPRS(7,8);
boolean state,laststate;
int count=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  GPRS.begin(9600);
  Serial.begin(9600);
  GPRS.println("AT");
  delay(1000);  
}

void loop() {
  // put your main code here, to run repeatedly
  while(GPRS.available())
  {
   Serial.write(GPRS.read());
  }
  Serial.println(count);
  //state = false;
  //state = digitalRead(2);  
  if(digitalRead(2)==HIGH && count==0){
      sendMessage();
      count=1;
   }
   delay(2000);
}

void sendMessage()
{
  Serial.println("Switch was turned on");
  //Serial.println(state ? "on" : "off");

  GPRS.println("AT + CMGF = 1 ");

  delay(500);

  GPRS.println("AT + CMGS = \"+8801839772045\" ");

  delay(500);

  GPRS.print("Box was turned on.");
  //GPRS.println(state ? "on" : "off");
  GPRS.write(0x1a );

  delay(500);
}

