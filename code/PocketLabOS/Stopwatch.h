#pragma once

#include <Arduino.h>

void openStopwatch();
void updateStopwatch();

enum StopwatchState {
    STOPWATCH_READY,
    STOPWATCH_RUNNING,
    STOPWATCH_FINISHED
};

extern StopwatchState stopwatchState;
extern unsigned long stopwatchStart;
extern unsigned long elapsedTime;
