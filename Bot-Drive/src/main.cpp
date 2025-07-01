#include <Arduino.h>
#include <SoftwareSerial.h>
#define BT_NAME   "BT_Slave"

#define ENA 10
#define ENB 5
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6


SoftwareSerial mySerial(2, 3); // RX, TX

void stop();
void forward();
void backward();
void left();
void right();
void uturn();
void dturn();

void setup()
{
  Serial.begin(9600);

  mySerial.begin(38400);
  Serial.println("Arduino receiver");

  mySerial.print("AT\r\n");
  delay(200);
  mySerial.print("AT+RMAAD\r\n");
  delay(200);
  mySerial.print("AT+ADDR?\r\n");
  delay(200);

  mySerial.print("AT+NAME="+String(BT_NAME)+"\r\n");
  delay(200);
  mySerial.print("AT+PSWD=\"1234\"\r\n");
  delay(200);
  mySerial.print("AT+ROLE?\r\n");
  delay(200);
  mySerial.print("AT+UART=38400,0,0\r\n");
  delay(500);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


}

void loop()
{
  // Serial.println(mySerial.readStringUntil('\n'));

  mySerial.flush();
  String data = mySerial.readStringUntil('\n');
  if(data == "s")
  {
    Serial.println("s");
    stop();
    delay(10);
  }
  if(data == "f")
  {
    Serial.println("f");
    forward();
    delay(10);
  }
  if(data == "b")
  {
    Serial.println("b");
    backward();
    delay(10);
  }
  if(data == "l")
  {
    Serial.println("l");
    left();
    delay(10);
  }
  if(data == "r")
  {
    Serial.println("r");
    right();
    delay(10);
  }
  if(data == "u")
  {
    Serial.println("u");
    uturn();
    delay(10);
  }
  if(data == "d")
  {
    Serial.println("d");
    dturn();
    delay(10);
  }
}


void forward(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("forward");
}

void backward(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("backward");
}

void left(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("left");
}

void right(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("right");
} 

void uturn(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("uturn");
}

void dturn(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("dturn");
}

void stop(){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("stop");
}

