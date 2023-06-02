#include <Adafruit_CircuitPlayground.h>

volatile int modeControl = 0;
int leftButton = 4;
int rightButton = 5;
volatile bool rightFlag = 0;
volatile bool leftFlag = 0;

void setup() {
  CircuitPlayground.begin();
  randomSeed(analogRead(0)); // Seed the random, randomly
  attachInterrupt(digitalPinToInterrupt(leftButton), leftISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(rightButton), rightISR, FALLING);
}

void loop() {

  if(rightFlag == 1){
    delay(5);
    modeControl++;
    if(modeControl > 4){
      modeControl = 0;
    }
    rightFlag = 0;
  }
  if(leftFlag == 1){
    delay(5);
    modeControl--;
    if(modeControl < 0){
      modeControl = 4;
    }
    leftFlag = 0;
  }

  switch(modeControl){
    case 0: 
      sparkle(200);
      break;
    case 1:
      randomColor();
      break;
    case 2:
      randomPattern();
      break;
    case 3:
      trueRandomness();
      break;
    case 4:
      zigZag();
      break;
    default:
      break;
  }
}

void sparkle(int sparkDelay){
  int randLED = random(10);
  CircuitPlayground.setPixelColor(randLED, 255,   255,   255);
  delay(sparkDelay/2);
  CircuitPlayground.setPixelColor(randLED, 0,   0,   0);
  delay(sparkDelay/2);
}

void randomColor(){
  for(int i = 0; i < 10; i++){
    int randRed = random(256);
    int randBlue = random(256);
    int randGreen = random(256);

    CircuitPlayground.setPixelColor(i, randRed,   randGreen,   randBlue);
    delay(500);
    CircuitPlayground.setPixelColor(i, 0,   0,   0);
    delay(500);
  }
}

void randomPattern(){
  for(int i = 0; i < 10; i++){
    int randomCase = random(3);

    if(randomCase == 0){
      CircuitPlayground.setPixelColor(i, 255,   0,   255);
    } else if(randomCase == 1){
      CircuitPlayground.setPixelColor(i, 0,   255,   255);
    } else if(randomCase == 2){
      CircuitPlayground.setPixelColor(i, 0,   128,   0);
    }
    delay(200);
  }
  delay(1000);
}

void trueRandomness(){
  int randLED = random(10);
  int randRed = random(256);
  int randBlue = random(256);
  int randGreen = random(256);
  int randOn = random(50, 301);
  int randOff = random(50, 301);
  
  CircuitPlayground.setPixelColor(randLED, randRed,   randGreen,   randBlue);
  delay(randOn);
  CircuitPlayground.setPixelColor(randLED, 0,   0,   0);
  delay(randOff);
}

void zigZag(){
  int j = 9;
  for(int i = 0; i < 5; i++){
    CircuitPlayground.setPixelColor(i, randRed,   randGreen,   randBlue);
    delay(200);
    CircuitPlayground.setPixelColor(j, randRedTwo,   randGreenTwo,   randBlueTwo);
    delay(200);

    j--;
  }
}

void leftISR()
{
  leftFlag = 1;
}

void rightISR()
{
  rightFlag = 1;
}
