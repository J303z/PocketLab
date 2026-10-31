
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
bool splashScreen = true;

//debounching stuff
int reading = HIGH;
int lastReading = HIGH;
int stableState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// some LED stuff
unsigned long ledStartTime = 0;
bool ledOn = false;

const unsigned long LED_DURATION = 1000;

// rotatory encoder
const int ENCODER_A = 2;
const int ENCODER_B = 3;
const int ENCODER_SW = 4;

// buttons
const int BUTTON_1 = 12;

// LEDs
const int LED_1 = 13;

volatile int direction = 0;
volatile int lastA = HIGH;

const char* menuItems[] = {
  "Stopwatch",
  "Calculator",
  "Resistor Helper",
  "Distance Sensor",
  "System Status"
}; 

const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);

void buttonRead() {
  reading = digitalRead(ENCODER_SW);

  if (splashScreen == false && reading != lastReading) {
    lastDebounceTime = millis();
    lastReading = reading;
  }

  if (splashScreen == false &&
      millis() - lastDebounceTime >= debounceDelay) {

    if (stableState != lastReading) {
      stableState = lastReading;

      if (stableState == LOW) {
        openSelectedItem();
      }
    }
  }
}

void openSelectedItem() {
        switch (selectedItem) {
  case 0:
    Serial.println("Stopwatch");
    break;

  case 1:
    Serial.println("Calculator");
    break;

  case 2:
    Serial.println("Resistor Decoder");
    break;

    case 3:
    Serial.println("Distance Sensor");
    break;

    case 4:
    Serial.println("System Status");
    break;

    default:
    Serial.println("error");
    break;

    }
}

void drawMenu() {
  display.clearDisplay();

  for (int i = 0; i < menuLength; i++) {
    int YScreen = i * 8;

    if (selectedItem == i) {
      int XScreen = 12;

      display.fillRect(
        0, YScreen,
        SCREEN_WIDTH, 8,
        SSD1306_WHITE
      );

      display.setTextColor(SSD1306_BLACK);
      display.setTextSize(1);
      display.setCursor(0, YScreen);
      display.println("> ");

      display.setCursor(XScreen, YScreen);
      display.println(menuItems[i]);
    } else {
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(1);
      display.setCursor(0, YScreen);
      display.println(menuItems[i]);
    }
  }

  display.display();
}

void startUpScreen() {
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("POCKETLAB");

  display.setTextSize(1);
  display.setCursor(0, 17);
  display.println("press/turn any button to enter menu");

  display.display();
}

void readRotate() {
  int a = digitalRead(ENCODER_A);
  int b = digitalRead(ENCODER_B);

  if (a != lastA) {
    if (a == LOW) {
      if (b == HIGH) {
        direction = 1;
      } else {
        direction = -1;
      }
    }

    lastA = a;
  }
}

void triggerLED() {
  digitalWrite(LED_1, HIGH);

  ledOn = true;
  ledStartTime = millis();
}

void updateLED() {
  if (ledOn && millis() - ledStartTime >= LED_DURATION) {
    digitalWrite(LED_1, LOW);
    ledOn = false;
  }
}

void setup() {
  Serial.begin(9600);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS
      )) {
    Serial.println("OLED initialisation failed!");

    while (true) {
    }
  }

  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  pinMode(BUTTON_1, INPUT_PULLUP);

  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, LOW);

  lastA = digitalRead(ENCODER_A);

  attachInterrupt(
    digitalPinToInterrupt(ENCODER_A),
    readRotate,
    CHANGE
  );

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (splashScreen == true) {
    startUpScreen();
  } else if (splashScreen == false) {
    drawMenu();
  }
}

void loop() {
  updateLED();

  noInterrupts();
  int movement = direction;
  direction = 0;
  interrupts();

  if (splashScreen) {
    if (
      movement != 0 ||
      digitalRead(ENCODER_SW) == LOW
    ) {
      splashScreen = false;
      triggerLED();
      drawMenu();
    } else if (digitalRead(BUTTON_1) == LOW) {
      splashScreen = false;
      triggerLED();
      drawMenu();
    }

    return;
  }

  if (movement != 0) {
    selectedItem += movement;

    if (selectedItem < 0) {
      selectedItem = menuLength - 1;
    }

    if (selectedItem >= menuLength) {
      selectedItem = 0;
    }

    drawMenu();
  }
  buttonRead();
}
