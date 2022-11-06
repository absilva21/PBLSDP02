#include "gpio.h" 
#include "uart.h"
int analogValue;
int comand;
int addr;
void setup() {
  // put your setup code here, to run once:
   GPIO_OUTPUT_SET(GPIO_ID_PIN(2),1);
   Serial.begin(9600);
   analogValue = 0;
   comand = 0;
   addr = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()  == 2){
    comand = Serial.read();
    addr = Serial.read();
    interp(comand,addr);
  }
}

void interp(int com, int adds){
  switch (com){
    case 0x03:
      status();
    break;
    case 0x04:
      inputAnalog(adds);
    break;
    case 0x05:
    break:
  }
}

void status(){
  if(ESP.checkFlashCRC()){
    Serial.print(0x00,HEX);
  }else{
    Serial.print(0x1F,HEX);
  }
}

void inputAnalog(int adds){
  analogValue = analogRead(A0);
  Serial.print(0x01,HEX);
  Serial.print(analogValue);
  analogValue = 0;
}