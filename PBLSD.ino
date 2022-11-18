
const int ledPin = LED_BUILTIN; 
int analogValue;
int digitalValue;
int comand;
int addr;

void setup() {
  //Desligando a led 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,HIGH);
  //Iniciando a UART e variaveis 
   Serial1.begin(9600);
   analogValue = 0;
   comand = 0;
   addr = 0;
}

void loop() {
  //Caso a Uart esteja com dois bytes na fila
  if(Serial1.available()  == 2){
    comand = Serial1.read();
    addr = Serial1.read();
    interp(comand,addr);
  }
}
//Interpreta o comando recebido pela UART
void interp(int com, int adds){
  switch (com){
    case 0x03:
      status();
    break;
    case 0x04:
      inputAnalog(adds);
    break;
    case 0x05:
      inputDigital(adds);
    break;
    case 0x06:
      digitalWrite(ledPin,LOW);
    break;
  }
}
//Envia o status do dispositivo
void status(){
  if(ESP.checkFlashCRC()){
    Serial1.print(0x00,HEX);
  }else{
    Serial1.print(0x1F,HEX);
  }
}
//Envia o valor da entrada analógica
void inputAnalog(int adds){
  analogValue = analogRead(A0);
  Serial1.print(0x01,HEX);
  Serial1.print(analogValue,HEX);
  analogValue = 0;
}
//Envia o valor da entrada digital
void inputDigital(int adds){
  digitalValue = digitalRead(16);
  Serial1.print(0x02,HEX);
  Serial1.print(digitalValue,HEX);
}