#include "Stopwatch.h"

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

//some screen stuff
int selectedItem = 0;
bool stopwatchScreen = false;
bool splashScreen = true;

//encoder?
bool encoderPressed = false;
bool backPressed = false;

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

//some functions open things
void openCalculator();
void openResistorDecoder();
void openSystemStatus();

struct MenuItem {
    const char* name;
    void (*openFunction)();
};

MenuItem menuItems[] = {
    {"Stopwatch", openStopwatch},
    {"Calculator", openCalculator},
    {"Resistor decoder", openResistorDecoder},
    {"System Status", openSystemStatus}
};

const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);

bool buttonJustPressed(int pin, bool &wasPressed) {
  bool isPressed = (digitalRead(pin) == LOW);

  if (isPressed && !wasPressed) {
    wasPressed = true;
    return true;
  }

  if (!isPressed) {
    wasPressed = false;
  }

  return false;
}

void openResistorDecoder() {
    Serial.println("resistor decoder");
}

void openCalculator() {
    Serial.println("calculator");
}

void openSystemStatus() {
    Serial.println("system status");
}

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
    if (selectedItem >= 0 && selectedItem < menuLength) {
        menuItems[selectedItem].openFunction();

        encoderPressed = (digitalRead(ENCODER_SW) == LOW);
        backPressed = (digitalRead(BUTTON_1) == LOW);
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
      display.println(menuItems[i].name);
    } else {
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(1);
      display.setCursor(0, YScreen);
      display.println(menuItems[i].name);
    }
  }

  display.display();
  Serial.println(stopwatchState);
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

  Wire.begin();

Serial.println("Scanning I2C...");

for (byte address = 1; address < 127; address++) {
  Wire.beginTransmission(address);

  if (Wire.endTransmission() == 0) {
    Serial.print("Found device at 0x");
    Serial.println(address, HEX);
  }
}

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
      encoderPressed = (digitalRead(ENCODER_SW) == LOW);
backPressed = (digitalRead(BUTTON_1) == LOW);
      triggerLED();
      drawMenu();
    } else if (digitalRead(BUTTON_1) == LOW) {
      splashScreen = false;
      encoderPressed = (digitalRead(ENCODER_SW) == LOW);
backPressed = (digitalRead(BUTTON_1) == LOW);
      triggerLED();
      drawMenu();
    }

    return;
  }


if (stopwatchScreen) {

  if (buttonJustPressed(ENCODER_SW, encoderPressed)) {

    if (stopwatchState == STOPWATCH_READY) {
      stopwatchStart = millis();
      stopwatchState = STOPWATCH_RUNNING;
    }

    else if (stopwatchState == STOPWATCH_RUNNING) {
      elapsedTime = millis() - stopwatchStart;
      stopwatchState = STOPWATCH_FINISHED;
    }

    else if (stopwatchState == STOPWATCH_FINISHED) {
      elapsedTime = 0;
      stopwatchStart = millis();
      stopwatchState = STOPWATCH_RUNNING;
    }
  }

  // D12: return to menu
  if (buttonJustPressed(BUTTON_1, backPressed)) {
    stopwatchScreen = false;
    drawMenu();
    return;
  }

  updateStopwatch();
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
