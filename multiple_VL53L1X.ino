#include <Wire.h>
#include <Arduino.h>
#include <VL53L1X.h>
//#include <TCA9548A.h>


//TCA9548A I2CMux;
VL53L1X sen0, sen1, sen2, sen3, sen4, sen5, sen6, sen7;
uint8_t defaultadd = 0b0101001;

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  TCA9548A(0);
  sen0.setTimeout(500);
  if (!sen0.init())
  {
    Serial.println("Failed to detect and initialize sensor0!");
    while (1);
  }
  sen0.setAddress(defaultadd + 0);
  Serial.print("sensor0 Addr: ");
  Serial.println(sen0.getAddress());
  sen0.startContinuous(50);
  TCA9548A(1);
  delay(500);
  sen1.setTimeout(500);  
  if (!sen1.init())
  {
    Serial.println("Failed to detect and initialize sensor1!");
    while (1);
  }
  sen1.setAddress(defaultadd + 1);
  Serial.print("sensor1 Addr: ");
  Serial.println(sen1.getAddress());
  sen1.startContinuous(50);
  Serial.println("start");
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(0b00000011);          // send byte to select bus
  Wire.endTransmission();
  
  

}

  
void loop() {
//  TCA9548A(0);
  Serial.print("sen0 : ");
  Serial.println(sen0.read());
  if (sen0.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
//  delay(500);
//  TCA9548A(1);
  Serial.print("sen1 : ");
  Serial.println(sen1.read());
  if (sen1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
//  delay(500);
}
