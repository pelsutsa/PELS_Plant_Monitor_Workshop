#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Could be AC instead of A0
#define SOIL_PIN A0

// Calibration
int dryValue = 800; // changes based on the plant (Dry)
int wetValue = 300; //changes based on plant (Wet)

// Blink timing
unsigned long lastBlink = 0;
bool eyesOpen = true;
const unsigned long blinkInterval = 1800;
const unsigned long blinkLength = 180;

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  // TEST VALUE:
  // 850 = very dry -> sad
  // 550 = medium -> okay
  // 300 = wet -> happy
  //int rawValue = 300;

  int rawValue = analogRead(SOIL_PIN);

  int moisturePercent = map(rawValue, dryValue, wetValue, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  int mood;
  if (moisturePercent < 30) {
    mood = 0;   // sad
  } else if (moisturePercent < 70) {
    mood = 1;   // okay
  } else {
    mood = 2;   // happy
  }

  unsigned long currentMillis = millis();

  if (eyesOpen && currentMillis - lastBlink >= blinkInterval) {
    eyesOpen = false;
    lastBlink = currentMillis;
  }

  if (!eyesOpen && currentMillis - lastBlink >= blinkLength) {
    eyesOpen = true;
    lastBlink = currentMillis;
  }

  drawScreen(moisturePercent, mood, rawValue);
  delay(100);
}

void drawScreen(int percent, int mood, int rawValue) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Left side text
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Plant");

  display.setTextSize(2);
  display.setCursor(0, 12);
  display.print(percent);
  display.print("%");

  display.setTextSize(1);
  display.setCursor(0, 38);

  if (mood == 0) {
    display.print("Need water");
  } else if (mood == 1) {
    display.print("Okay");
  } else {
    display.print("Happy");
  }

  display.setCursor(0, 54);
  display.print("Raw:");
  display.print(rawValue);

  drawCuteFlower(76, 2, mood, eyesOpen);

  display.display();
}

void drawCuteFlower(int x, int y, int mood, bool eyesOpen) {
  // petals
  display.fillCircle(x + 18, y + 6, 5, SSD1306_WHITE);
  display.fillCircle(x + 10, y + 10, 5, SSD1306_WHITE);
  display.fillCircle(x + 26, y + 10, 5, SSD1306_WHITE);
  display.fillCircle(x + 7, y + 18, 5, SSD1306_WHITE);
  display.fillCircle(x + 29, y + 18, 5, SSD1306_WHITE);
  display.fillCircle(x + 10, y + 26, 5, SSD1306_WHITE);
  display.fillCircle(x + 26, y + 26, 5, SSD1306_WHITE);
  display.fillCircle(x + 18, y + 30, 5, SSD1306_WHITE);

  // face
  display.fillCircle(x + 18, y + 18, 9, SSD1306_WHITE);
  display.drawCircle(x + 18, y + 18, 9, SSD1306_BLACK);

  // stem
  display.drawLine(x + 18, y + 27, x + 18, y + 42, SSD1306_WHITE);
  display.drawLine(x + 19, y + 27, x + 19, y + 42, SSD1306_WHITE);

  // leaf
  display.drawLine(x + 18, y + 36, x + 28, y + 31, SSD1306_WHITE);
  display.drawLine(x + 18, y + 37, x + 28, y + 32, SSD1306_WHITE);
  display.drawLine(x + 28, y + 31, x + 29, y + 39, SSD1306_WHITE);
  display.drawLine(x + 28, y + 32, x + 29, y + 39, SSD1306_WHITE);

  // pot
  display.fillRoundRect(x + 7, y + 43, 22, 10, 2, SSD1306_WHITE);
  display.fillRect(x + 10, y + 53, 16, 5, SSD1306_WHITE);

  // face features
  int fx = x + 18;
  int fy = y + 17;

  // eyes
  if (eyesOpen) {
    display.fillCircle(fx - 3, fy - 2, 1, SSD1306_BLACK);
    display.fillCircle(fx + 3, fy - 2, 1, SSD1306_BLACK);
  } else {
    display.drawLine(fx - 4, fy - 2, fx - 2, fy - 2, SSD1306_BLACK);
    display.drawLine(fx + 2, fy - 2, fx + 4, fy - 2, SSD1306_BLACK);
  }

  // mouth
  if (mood == 0) {
    // SAD: upside-down curve
    display.drawPixel(fx - 3, fy + 5, SSD1306_BLACK);
    display.drawLine (fx - 2, fy + 4, fx + 2, fy + 4, SSD1306_BLACK);
    display.drawPixel(fx + 3, fy + 5, SSD1306_BLACK);
  } 
  else if (mood == 1) {
    // OKAY: flat mouth
    display.drawLine(fx - 3, fy + 5, fx + 3, fy + 5, SSD1306_BLACK);
  } 
  else {
    // HAPPY: smile
    display.drawPixel(fx - 3, fy + 4, SSD1306_BLACK);
    display.drawLine (fx - 2, fy + 5, fx + 2, fy + 5, SSD1306_BLACK);
    display.drawPixel(fx + 3, fy + 4, SSD1306_BLACK);
  }
}
