/* Magic Wand TV Remote
 * Updated December 2014
 * By Allie Fauer
 * Based on Arduino User JohnChi's MPU-6050 Short Example sketch and Chris Young's IRsend Demo from the IR Lib
 * Public Domain
 * http://www.instructables.com/id/Magic-Wand-TV-Remote/
 */
 
#include <IRLib.h>
#include<Wire.h>

const int MPU=0x68;  // I2C address of the MPU-6050

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

IRsend My_Sender;

void setup()
{
   Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
   Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  if ( AcY < -9000 && AcZ > 6000) { //  swing down
   for (int i=0; i <= 15; i++){
    
    My_Sender.send(NEC, 0x20DF10EF, 32); // TV-Power
    delay(100); 
  
 }}
 
  if (AcY > -6000 && AcZ < -20000) { // turn upsidedown
    
    My_Sender.send(PANASONIC_OLD, 0x37C107, 22); // Cable-Power 
    delay(2000);  
  
  }
 
  if (AcY > 11000 && AcZ < 5000) { // bring down, swing up
  for (int i=0; i <= 15; i++){
    
    My_Sender.send(NEC, 0x20DF639C, 32); // HDMI
    delay(100);  
  }}  
  
   if (AcY < -5500 && AcZ < 9000) { // tap up
  for (int i=0; i <= 3; i++){
    
    My_Sender.send(NEC, 0x20DF40BF, 32); // Volume Up
    delay(100);  
  }}  
  
    if (AcY > 7000 && AcZ < 10000) { // tap down
  for (int i=0; i <= 5; i++){
    
    My_Sender.send(NEC, 0x20DFC03F, 32); // Volume Down
    delay(100);  
  }}  
  
  if (AcZ < 5000 && AcZ > 0 && AcX > 5000) { // twist right
    
    My_Sender.send(PANASONIC_OLD, 0x377111, 22); // Channel Up 
    delay(2000);  
  
  }
  
  if (AcZ < 5000 && AcZ > 0 && AcX < -4000) { // twist left
    
    My_Sender.send(PANASONIC_OLD, 0x36F121, 22); // Channel Down 
    delay(2000);  
  
  }
  
  }
