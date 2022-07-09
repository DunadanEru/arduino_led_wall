
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define numPWM 16 // number of pwms to init
#define numPins 9 // number of pins attached
#define serial_speed 19200
#define i2c_speed 100000
#define debug_toggle 1 
const int blockondelay = 100;     // delay if incorrect command recieved from desktop app

int chipselect(int num1);
void operate_controlElements(int num1, int pinState, int chipNum);
void operate_relays(int icPin, int pinState, int chipNum, int printPin);

uint8_t Pin[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; // array of pins

// Initialize Adafruit boards / chips /IC's
Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x43);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x44);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver(0x45);
Adafruit_PWMServoDriver pwm6 = Adafruit_PWMServoDriver(0x46);
Adafruit_PWMServoDriver pwm7 = Adafruit_PWMServoDriver(0x47);
Adafruit_PWMServoDriver pwm8 = Adafruit_PWMServoDriver(0x48);
Adafruit_PWMServoDriver pwm9 = Adafruit_PWMServoDriver(0x49);
Adafruit_PWMServoDriver pwm10 = Adafruit_PWMServoDriver(0x4a);
Adafruit_PWMServoDriver pwm11 = Adafruit_PWMServoDriver(0x4b);
Adafruit_PWMServoDriver pwm12 = Adafruit_PWMServoDriver(0x4c);
Adafruit_PWMServoDriver pwm13 = Adafruit_PWMServoDriver(0x4d);
Adafruit_PWMServoDriver pwm14 = Adafruit_PWMServoDriver(0x4e);
Adafruit_PWMServoDriver pwm15 = Adafruit_PWMServoDriver(0x4f);

int inChar = 0;       // used for string
int pinState = 0;     // desired state of IC pin high or low
int pinNum = 0;       // incoming number from PC
int ctrlLED = 0;      // led control number incoming from PC
int chipNum = 0;      // number of controller in use
String inString = ""; // string to hold input
int dtime = 1;

void setup()
{
  Serial.begin(serial_speed);

  pwm0.begin();
  pwm0.setPWMFreq(1000);
  pwm1.begin();
  pwm1.setPWMFreq(1000);
  pwm2.begin();
  pwm2.setPWMFreq(1000);
  pwm3.begin();
  pwm3.setPWMFreq(1000);
  pwm4.begin();
  pwm4.setPWMFreq(1000);
  pwm5.begin();
  pwm5.setPWMFreq(1000);
  pwm6.begin();
  pwm6.setPWMFreq(1000);
  pwm7.begin();
  pwm7.setPWMFreq(1000);
  pwm8.begin();
  pwm8.setPWMFreq(1000);
  pwm9.begin();
  pwm9.setPWMFreq(1000);
  pwm10.begin();
  pwm10.setPWMFreq(1000);
  pwm11.begin();
  pwm11.setPWMFreq(1000);
  pwm12.begin();
  pwm12.setPWMFreq(1000);
  pwm13.begin();
  pwm13.setPWMFreq(1000);
  pwm14.begin();
  pwm14.setPWMFreq(1000);
  pwm15.begin();
  pwm15.setPWMFreq(1000);

  /*  Serial.println("RESET in 3 Seconds");
    delay(3000);
    pwm0.reset();
    pwm1.reset();
    pwm2.reset();
    pwm3.reset();
    pwm4.reset();
    pwm5.reset();
    pwm6.reset();
    pwm7.reset();
    pwm8.reset();
    pwm9.reset();
    pwm10.reset();
    pwm11.reset();
    pwm12.reset();
    pwm13.reset();
    pwm14.reset();
    pwm15.reset();*/

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(i2c_speed);

  for (int i = 0; i <= 15; i++)
  { // Turn off all relays
    pwm0.setPWM(i, 4096, 0);
    delay(dtime);
    pwm1.setPWM(i, 4096, 0);
    delay(dtime);
    pwm2.setPWM(i, 4096, 0);
    delay(dtime);
    pwm3.setPWM(i, 4096, 0);
    delay(dtime);
    pwm4.setPWM(i, 4096, 0);
    delay(dtime);
    pwm5.setPWM(i, 4096, 0);
    delay(dtime);
    pwm6.setPWM(i, 4096, 0);
    delay(dtime);
    pwm7.setPWM(i, 4096, 0);
    delay(dtime);
    pwm8.setPWM(i, 4096, 0);
    delay(dtime);
    pwm9.setPWM(i, 4096, 0);
    delay(dtime);
    pwm10.setPWM(i, 4096, 0);
    delay(dtime);
    pwm11.setPWM(i, 4096, 0);
    delay(dtime);
    pwm12.setPWM(i, 4096, 0);
    delay(dtime);
    pwm13.setPWM(i, 4096, 0);
    delay(dtime);
    pwm14.setPWM(i, 4096, 0);
    delay(dtime);
    pwm15.setPWM(i, 4096, 0);
    delay(dtime);
  }
  Serial.println("Setup Done!");
  Serial.println("WS Museum LED WALL 2/2");
  delay(500);
}

void loop()
{

  // Read serial input for commands from desktop app, monitoring LED Wall with Kinect
  if (Serial.available() > 0)
  {
    inChar = Serial.read(); // get incoming byte from serial
    if (isDigit(inChar))    // check if incoming character is number
    {
      inString += (char)inChar; // convert the incoming byte to a char and add it to the string
    }

    // if you get a newline (command ends), parse string to get which LED need to be contrilled
    if (inChar == '\n')
    {
      pinNum = inString.toInt();                // convert to int
      pinState = (pinNum % 10);                 // get last digit which is NEW state of LED
      ctrlLED = ((pinNum - pinState) / 10) - 1; // get LED number to control
      chipNum = chipselect(ctrlLED);            // get on which IC controled LED is located
      inString = "";                            // RESET string for new input:
      // DEBUG
      // Serial.print("LED to control #");
      // Serial.println(ctrlLED);
      // Serial.println(chipNum);

      operate_controlElements(ctrlLED, pinState, chipNum); // num1 = ctrlLED (LED to control), pinState = pinState, chipNum = chipNum (on which IC LED is located)
    }
  }
}

void operate_controlElements(int ctrlLED, int pinState, int chipNum) // ctrlLED (LED to control), pinState = pinState, chipNum (on which IC LED is located)
{
  int printPin = ctrlLED + 1;
  int icPin = ctrlLED - (chipNum * 16); // select pin on IC to control
  // Serial.print("PIN on IC Selected - ");
  // Serial.println(icPin);

  // Serial.println(chipNum);

  for (int i; i < numPWM; i++){
    if (chipNum == i){
      operate_relays(icPin, pinState, chipNum, printPin);
    }
  }
}

int chipselect(int num1)
{
  int result;
  result = ((num1 - (num1 % numPWM)) / numPWM);

  return result;
}

void operate_relays(int icPin, int pinState, int chipNum, int printPin)
{
  switch (pinState)
  {
  case 0:
    pwm15.setPWM(icPin, 4096, 0);
    Serial.print("LED #");
    Serial.print(printPin);
    Serial.print(" on IC#");
    Serial.print(chipNum);
    Serial.println(" ==> OFF");
    break;
  case 1:
    pwm15.setPWM(icPin, 0, 4096);
    Serial.print("LED #");
    Serial.print(printPin);
    Serial.print(" on IC#");
    Serial.print(chipNum);
    Serial.println(" ==> ON");
    break;
  case 8:
    for (int ik = 0; ik <= 15; ik++)
    {
      pwm15.setPWM(ik, 0, 4096);
      delay(blockondelay);
    }
    Serial.print("ALL Pins");
    Serial.print(" on IC#");
    Serial.print(chipNum);
    Serial.println(" ==> ON");
    break;
  default:
    Serial.print("WRONG state Command for LED ==>");
    Serial.print(printPin);
    Serial.println(" - No state change!");
    break;
  }
}