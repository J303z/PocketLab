#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

int selectedItem = 0;

const char* menuItems[] = {
  "Stopwatch",
  "Calculator",
  "Resistor Helper",
  "Distance Sensor",
  "System Status"
};

void drawMenu() {
     display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("POCKETLAB");

  display.setTextSize(1);
  display.setCursor(0, 15);
  display.println("------------------");

  display.display();

  for (int i = 0; i < 5; i++) {
  int YScreen = 22 + (i * 8);
  display.setTextSize(1);
  display.setCursor(0, YScreen);
  display.println(menuItems[i]);
  display.display();
};
} 

void setup() {
  Serial.begin(9600);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS
      )) {
    Serial.println("OLED initialisation failed!");
    while (true) {}
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  drawMenu();
}

void loop() {
 
}

