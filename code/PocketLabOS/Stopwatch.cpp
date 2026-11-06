#include "Stopwatch.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;
extern bool stopwatchScreen;

StopwatchState stopwatchState = STOPWATCH_READY;
unsigned long stopwatchStart = 0;
unsigned long elapsedTime = 0;


void openStopwatch() {

    extern bool encoderPressed;
    extern bool backPressed;

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(12, 20);
    display.println("READY TEST");
    display.display();
    
    stopwatchScreen = true;
    stopwatchState = STOPWATCH_READY;
    elapsedTime = 0;
    stopwatchStart = 0;
    Serial.println("Opening stopwatch");
    Serial.println(stopwatchState);

    Serial.println("State:");
    Serial.println(stopwatchState);

    Serial.println("Elapsed:");
    Serial.println(elapsedTime);
}

void updateStopwatch() {
    Serial.println("Updating stopwatch");
    Serial.println(stopwatchState);
  unsigned long currentTime = elapsedTime;

  if (stopwatchState == STOPWATCH_RUNNING) {
    currentTime = millis() - stopwatchStart;
  }

  unsigned long totalSeconds = currentTime / 1000;
  unsigned int minutes = totalSeconds / 60;
  unsigned int seconds = totalSeconds % 60;
  unsigned int centiseconds = (currentTime % 1000) / 10;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (stopwatchState == STOPWATCH_READY) {
  display.setTextSize(1);
  display.setCursor(12, 20);
  display.println("Press SW to start");

  display.setCursor(12, 40);
  display.println("D12: Back");
}

  else {
    display.setTextSize(2);
    display.setCursor(0, 10);

    if (minutes < 10) display.print("0");
    display.print(minutes);
    display.print(":");

    if (seconds < 10) display.print("0");
    display.print(seconds);
    display.print(":");

    if (centiseconds < 10) display.print("0");
    display.print(centiseconds);

    display.setTextSize(1);
    display.setCursor(0, 45);

    if (stopwatchState == STOPWATCH_RUNNING) {
      display.print("RUNNING");
    } else {
      display.print("FINISHED");
      display.setCursor(0, 55);
      display.print("SW: Restart  D12: Menu");
    }
  }

  display.display();
}
