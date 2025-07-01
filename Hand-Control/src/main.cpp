#include <Arduino.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// +ADDR:0022:01:0018BD

#define BT_NAME   "BT_Master"
#define SLAVE_ADDRESS "0022,01,0018BD"  //98d3:31:8095c3
#define THRE 45
SoftwareSerial mySerial(2, 3); // RX, TX

MPU6050 mpu6050(Wire);
long timer = 0;


void updateSerial(void)
{
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  pinMode(LED_BUILTIN, OUTPUT);
  

  mySerial.begin(38400);
  Serial.println("Arduino Sender");

  mySerial.print("AT\r\n");
  updateSerial();
  delay(200);
  mySerial.print("AT+RMAAD\r\n");
  updateSerial();
  delay(200);
  mySerial.print("AT+ROLE=1\r\n");
  updateSerial();
  delay(200);  
  mySerial.print("AT+NAME="+String(BT_NAME)+"\r\n");
  updateSerial();
  delay(200);
  mySerial.print("AT+PSWD=\"1234\"\r\n");
  updateSerial();
  delay(200);
  mySerial.print("AT+BIND="+String(SLAVE_ADDRESS)+"\r\n");
  updateSerial();
  delay(200);
  mySerial.print("AT+UART=38400,0,0\r\n");
  updateSerial();
  delay(500);
  mySerial.print("AT+UART?\r\n");
  updateSerial();
  delay(200);

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  mpu6050.update();
  // if (mySerial.available())
  //   Serial.write(mySerial.read());
  // if (Serial.available())
  //   mySerial.write(Serial.read());

  // myserial.print("X:");
  // if (mpu6050.getAngleX() >THRESH || mpu6050.getAngleX() < -THRE ||
  //     mpu6050.getAngleY() > THRE || mpu6050.getAngleY() < -THRE ||
  //     mpu6050.getAngleZ() > THRE || mpu6050.getAngleZ() < -THRE) {
  //   mySerial.print("X:");
  //   mySerial.print(mpu6050.getAngleX());
  //   mySerial.print("\tY:");
  //   mySerial.print(mpu6050.getAngleY());
  //   mySerial.print("\tZ:");
  //   mySerial.println(mpu6050.getAngleZ());
  // }
  // if(millis() - timer > 1000){
  //   // mySerial.print("HHHHHH");
  //   // Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
  //   // Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
  //   // Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
  //   // // Serial.println("=======================================================\n");
  //   // timer = millis();
    
  // }

  if(mpu6050.getAngleX() > THRE){
    mySerial.println("r");
  }
  if(mpu6050.getAngleX() < -THRE){
    mySerial.println("l");
  }
  if(mpu6050.getAngleY() > THRE){
    mySerial.println("f");
  }
  if(mpu6050.getAngleY() < -THRE){
    mySerial.println("b");
  }
  if(mpu6050.getAngleZ() > THRE){
    mySerial.println("u");
  }
  if(mpu6050.getAngleZ() < -THRE){
    mySerial.println("d");
  }
  if(mpu6050.getAngleX() <= THRE && mpu6050.getAngleX() >= -THRE &&
     mpu6050.getAngleY() <= THRE && mpu6050.getAngleY() >= -THRE &&
     mpu6050.getAngleZ() <= THRE && mpu6050.getAngleZ() >= -THRE){
    mySerial.println("s");
  }
  // delay(100);    
  // Serial.print("X:");

}

