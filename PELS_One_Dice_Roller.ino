//libraries needed
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED Screen parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte BUTTON_PIN = 2; //D2 pin for Push Button

int dice = 1; //one die

//Start screen/main
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.display();

  randomSeed(analogRead(A0)); //make the numbers truly random

  showDice("Press Button");
}
//button pressed 
void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    rollDiceAnimation();
    delay(250);
  }
}
//Animation of Dice rolling
void rollDiceAnimation() {
  int delayTime = 20;

  for (int i = 0; i < 20; i++) {
    dice = random(1, 7);

    showDice("Rolling...");
    delay(delayTime);

    delayTime += 20;
  }

  showResult();
}
//draws the die
void showDice(const char* message) {
  oled.clearDisplay();

  // center the die
  drawDie(40, 0, dice);

  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(30, 56);
  oled.print(message);

  oled.display();
}
//draws the die after animation
void showResult() {
  oled.clearDisplay();

  drawDie(40, 0, dice);

  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);

  oled.setCursor(45, 56);
  oled.print("Value: ");
  oled.print(dice);

  oled.display();
}
//te exact values needed to draw the die based on each number
void drawDie(int x, int y, int value) {
  oled.drawRect(x, y, 48, 48, SSD1306_WHITE);

  if (value == 1) {
    oled.fillCircle(x + 24, y + 24, 4, SSD1306_WHITE);
  } 
  else if (value == 2) {
    oled.fillCircle(x + 12, y + 12, 4, SSD1306_WHITE);
    oled.fillCircle(x + 36, y + 36, 4, SSD1306_WHITE);
  } 
  else if (value == 3) {
    oled.fillCircle(x + 12, y + 12, 4, SSD1306_WHITE);
    oled.fillCircle(x + 24, y + 24, 4, SSD1306_WHITE);
    oled.fillCircle(x + 36, y + 36, 4, SSD1306_WHITE);
  } 
  else if (value == 4) {
    oled.fillCircle(x + 12, y + 12, 4, SSD1306_WHITE);
    oled.fillCircle(x + 36, y + 12, 4, SSD1306_WHITE);
    oled.fillCircle(x + 12, y + 36, 4, SSD1306_WHITE);
    oled.fillCircle(x + 36, y + 36, 4, SSD1306_WHITE);
  } 
  else if (value == 5) {
    oled.fillCircle(x + 12, y + 12, 4, SSD1306_WHITE);
    oled.fillCircle(x + 36, y + 12, 4, SSD1306_WHITE);
    oled.fillCircle(x + 24, y + 24, 4, SSD1306_WHITE);
    oled.fillCircle(x + 12, y + 36, 4, SSD1306_WHITE);
    oled.fillCircle(x + 36, y + 36, 4, SSD1306_WHITE);
  } 
  else if (value == 6) {
    oled.fillCircle(x + 12, y + 10, 4, SSD1306_WHITE);
    oled.fillCircle(x + 36, y + 10, 4, SSD1306_WHITE);
    oled.fillCircle(x + 12, y + 24, 4, SSD1306_WHITE);
    oled.fillCircle(x + 36, y + 24, 4, SSD1306_WHITE);
    oled.fillCircle(x + 12, y + 38, 4, SSD1306_WHITE);
    oled.fillCircle(x + 36, y + 38, 4, SSD1306_WHITE);
  }
}