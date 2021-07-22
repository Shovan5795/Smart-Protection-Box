#include<SoftwareSerial.h>
SoftwareSerial GPRS(7,8);

unsigned char buffer[64];
int count = 0;
void setup() {
  // put your setup code here, to run once:
  GPRS.begin(9600);
  Serial.begin(9600);
  GPRS.println("AT");
  delay(1000);
   GPRS.println("AT+CMGF=1");
  delay(1000);
  GPRS.println("AT+CMGF?");
  delay(3000);
   
  
}
void sum(){
GPRS.println("AT+CMGS=\"+8801557267336\"");
  delay(3000);
  GPRS.println("GOOD EVENING.*");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  sum();
  while(GPRS.available())
  {
    buffer[count++]=GPRS.read();
    if(count==64)
    {
      break;
    }
  }

  Serial.write(buffer,count);
  clearBufferArray();
  count=0;
   
  if(Serial.available()){
    byte b= Serial.read();
    if(b=='*'){
      
  

      GPRS.write(0x1a);

    }
    else 
      GPRS.write(b);
  }
}

void clearBufferArray()
{
  for(int i=0;i<count;i++)
  {
    buffer[i]=NULL;
  }
}

