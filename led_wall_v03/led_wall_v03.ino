#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


int chipselect(int num1);
void operateLED(int num1, int num2, int num3);


// chip init
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
Adafruit_PWMServoDriver pwm10 = Adafruit_PWMServoDriver(0x50);
Adafruit_PWMServoDriver pwm11 = Adafruit_PWMServoDriver(0x51);
Adafruit_PWMServoDriver pwm12 = Adafruit_PWMServoDriver(0x52);
Adafruit_PWMServoDriver pwm13 = Adafruit_PWMServoDriver(0x53);
Adafruit_PWMServoDriver pwm14 = Adafruit_PWMServoDriver(0x54);
Adafruit_PWMServoDriver pwm15 = Adafruit_PWMServoDriver(0x55);


int inChar = 0;          // used for string
int pinState = 0;        // desired state of IC pin high or low
int pinNum = 0;          // incoming number from PC
int chNum = 0;           // number of characters in pinNum 
int ctrlLED = 0;         // led control number incoming from PC
int chipNum = 0;         // number of controller in use
String inString = "";    // string to hold input
int dtime = 1;


void setup() {
  Serial.begin(19200);
  

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
  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);

    for (int i = 0; i <= 15; i++) {   //Turn off all relays
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
  delay(1000);
}





void loop()
{

  // Read serial input:
  if (Serial.available() > 0) {
    inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
        pinNum = inString.toInt();
        pinState = (pinNum % 10);
        ctrlLED = ((pinNum - pinState) / 10) - 1;
        chipNum = chipselect(ctrlLED);
            // Serial.print("LED to control #");
            // Serial.println(ctrlLED);
        //Serial.println(chipNum);
        
        
        inString = ""; // clear the string for new input:
        
        if(pinNum > 9999)
        {
          chNum = 5;
        }
        else if(pinNum > 999)
        {
          chNum = 4;
        }
        else if(pinNum > 99)
        {
          chNum = 3;
        }
        else if(pinNum > 9)
        {
          chNum = 2;
        }
        else
        {
          Serial.println("Wrong Input!");
        }

        operateLED(ctrlLED, pinState, chipNum);  // num1 = ctrlLED (LED to control), num2 = pinState, num3 = chipNum (on which IC LED is located)



    }
  }
}

void operateLED(int num1, int num2, int num3)  // num1 = ctrlLED (LED to control), num2 = pinState, num3 = chipNum (on which IC LED is located)
{
        int printPin = num1 + 1;
        int icPin = num1 - (num3 * 16); // select pin on IC to control
            //Serial.print("PIN on IC Selected - ");
            //Serial.println(icPin);
        
        //Serial.println(num3);
        
        
        switch(num3){
        case 0:
          switch(num2){
          case 0:
          pwm0.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm0.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 1:
          switch(num2){
          case 0:
          pwm1.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm1.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 2:
          switch(num2){
          case 0:
          pwm2.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm2.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 3:
          switch(num2){
          case 0:
          pwm3.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm3.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 4:
          switch(num2){
          case 0:
          pwm4.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm4.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 5:
          switch(num2){
          case 0:
          pwm5.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm5.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 6:
          switch(num2){
          case 0:
          pwm6.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm6.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 7:
          switch(num2){
          case 0:
          pwm7.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm7.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 8:
          switch(num2){
          case 0:
          pwm8.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm8.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 9:
          switch(num2){
          case 0:
          pwm9.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm9.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 10:
          switch(num2){
          case 0:
          pwm10.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm10.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 11:
          switch(num2){
          case 0:
          pwm11.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm11.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 12:
          switch(num2){
          case 0:
          pwm12.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm12.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 13:
          switch(num2){
          case 0:
          pwm13.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm13.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 14:
          switch(num2){
          case 0:
          pwm14.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm14.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        case 15:
          switch(num2){
          case 0:
          pwm15.setPWM(icPin, 4096, 0);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> OFF");
          break;
          case 1:
          pwm15.setPWM(icPin, 0, 4096);
          Serial.print("LED #");
          Serial.print(printPin);
          Serial.print(" on IC#");
          Serial.print(num3);
          Serial.println(" ==> ON");
          break;
          default:
          Serial.print("WRONG Command for LED ==>");
          Serial.print(printPin);
          Serial.println(" - No state change!");
          break;
          }
        break;
        default:
        Serial.println("WRONG IC to control");
        break;
      }
}

int chipselect(int num1) {
  int result;
  result = ((num1 - (num1 % 16)) / 16);
      //Serial.print("IC Selected - ");
      //Serial.println(result);
  return result; 
}