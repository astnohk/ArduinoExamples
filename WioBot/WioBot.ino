/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <Wire.h>

#define MIC_I2C_ADDR 0x30

Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

TFT_eSPI tft = TFT_eSPI();

int target = 90;

void setup()
{
  Serial.println("start");
  Wire.begin();
  
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  normalEye();
  normalMouth();

  // If the sound threshold could be fixed at some value.
  //writeThreshold(13);

  myservo.attach(0);  // attaches the servo on pin 9 to the Servo object
}

int16_t readAngle()
{
  int16_t val = 0;
  Wire.beginTransmission(MIC_I2C_ADDR);
  Wire.write(0x00);
  Wire.endTransmission(false);
  Wire.requestFrom(MIC_I2C_ADDR, 2, true);
  while (Wire.available())
  {
    char c = Wire.read();
    val = (val << 8) | c;
  }
  return val;
}

uint16_t readVolume()
{
  uint16_t val = 0;
  Wire.beginTransmission(MIC_I2C_ADDR);
  Wire.write(0x04);
  Wire.endTransmission(false);
  Wire.requestFrom(MIC_I2C_ADDR, 2, true);
  while (Wire.available())
  {
    char c = Wire.read();
    val = (val << 8) | c;
  }
  return val;
}

void writeThreshold(uint16_t val)
{
  char data[4];
  data[0] = 0x04;
  data[1] = 0xff & (val >> 8);
  data[2] = 0xff & val;
  Wire.beginTransmission(MIC_I2C_ADDR);
  Wire.write(data, 3);
  Wire.endTransmission();
}

void normalEye()
{
  tft.fillRect(20, 115, 90, 10, TFT_WHITE);
  tft.fillRect(130, 115, 90, 10, TFT_WHITE);
}

void smileEye()
{
  tft.fillCircle(65, 120, 45, TFT_WHITE);
  tft.fillCircle(65, 120, 35, TFT_BLACK);
  tft.fillCircle(175, 120, 45, TFT_WHITE);
  tft.fillCircle(175, 120, 35, TFT_BLACK);
  tft.fillRect(0, 120, 240, 50, TFT_BLACK);
}

void normalMouth()
{
  tft.fillTriangle(70, 180, 120, 240, 170, 180, TFT_WHITE);
  tft.fillTriangle(70, 170, 120, 230, 170, 170, TFT_BLACK);
}

void smileMouth()
{
  tft.fillTriangle(70, 200, 120, 220, 170, 200, TFT_WHITE);
  tft.fillTriangle(70, 190, 120, 210, 170, 190, TFT_BLACK);
}

void loop()
{
  uint16_t th = readVolume();
  Serial.print(th, DEC);
  Serial.print("\n");

  int8_t detect = 0;
  int16_t val = readAngle();
  int16_t angle = val / 10 - 180; // Convert front (180 [deg]) to 0 [deg]
  Serial.print(angle, DEC);
  Serial.print("\n");
  if (val >= 0)
  {
    detect = 1;
    target = target + angle;
    if (target < 0)
    {
      target = 0;
    }
    else if (target > 180)
    {
      target = 180;
    }
  }
  //Serial.print(target, DEC);
  //Serial.print("\n");
  if (detect)
  {
    // Change to smile face
    tft.fillScreen(TFT_BLACK);
    smileEye();
    smileMouth();
    // Servo
    myservo.write(target); // 0 to 180
    delay(2200);
    // Change to normal face
    tft.fillScreen(TFT_BLACK);
    normalEye();
    normalMouth();
  }
  //Serial.print(target - myservo.read());
  delay(50);
}
