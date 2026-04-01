#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 23
#define OLED_CLK  18
#define OLED_DC   2
#define OLED_RESET 4
#define OLED_CS   -1   // no CS

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS
);

// Eye positions
int leftEyeX = 40;
int rightEyeX = 88;
int eyeY = 26;

// Mouth position
int mouthX = 64;
int mouthY = 48;

void drawFace(int offsetX, int offsetY) {
  display.clearDisplay();

  // Eyes
  display.fillRoundRect(leftEyeX - 18, eyeY - 12, 36, 24, 12, WHITE);
  display.fillRoundRect(rightEyeX - 18, eyeY - 12, 36, 24, 12, WHITE);

  // Pupils
  display.fillCircle(leftEyeX + offsetX, eyeY + offsetY, 5, BLACK);
  display.fillCircle(rightEyeX + offsetX, eyeY + offsetY, 5, BLACK);

  // Sparkle
  display.fillCircle(leftEyeX + offsetX - 2, eyeY + offsetY - 2, 2, WHITE);
  display.fillCircle(rightEyeX + offsetX - 2, eyeY + offsetY - 2, 2, WHITE);

  // Cute smile 😊
  display.drawLine(mouthX - 12, mouthY, mouthX + 12, mouthY, WHITE);
  display.drawPixel(mouthX - 13, mouthY - 1, WHITE);
  display.drawPixel(mouthX + 13, mouthY - 1, WHITE);

  display.display();
}

void blink() {
  for (int h = 12; h >= 0; h -= 2) {
    display.clearDisplay();

    display.fillRoundRect(leftEyeX - 18, eyeY - h/2, 36, h, 10, WHITE);
    display.fillRoundRect(rightEyeX - 18, eyeY - h/2, 36, h, 10, WHITE);

    // keep mouth visible
    display.drawLine(mouthX - 12, mouthY, mouthX + 12, mouthY, WHITE);

    display.display();
    delay(40);
  }

  delay(100);

  for (int h = 0; h <= 12; h += 2) {
    display.clearDisplay();

    display.fillRoundRect(leftEyeX - 18, eyeY - h/2, 36, h, 10, WHITE);
    display.fillRoundRect(rightEyeX - 18, eyeY - h/2, 36, h, 10, WHITE);

    display.drawLine(mouthX - 12, mouthY, mouthX + 12, mouthY, WHITE);

    display.display();
    delay(40);
  }
}

void happyFace() {
  display.clearDisplay();

  // Happy eyes 😊
  display.drawLine(leftEyeX - 12, eyeY, leftEyeX + 12, eyeY + 4, WHITE);
  display.drawLine(rightEyeX - 12, eyeY, rightEyeX + 12, eyeY + 4, WHITE);

  // Big smile 😄
  display.drawLine(mouthX - 15, mouthY, mouthX + 15, mouthY, WHITE);
  display.drawPixel(mouthX - 16, mouthY - 1, WHITE);
  display.drawPixel(mouthX + 16, mouthY - 1, WHITE);

  display.display();
  delay(1000);
}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println("OLED failed");
    while(true);
  }

  display.clearDisplay();
}

void loop() {
  // Look center
  drawFace(0, 0);
  delay(800);

  // Look right
  drawFace(5, 0);
  delay(600);

  // Look left
  drawFace(-5, 0);
  delay(600);

  // Look up
  drawFace(0, -3);
  delay(600);

  // Look down
  drawFace(0, 3);
  delay(600);

  // Blink
  blink();

  // Happy mode
  happyFace();
}
