#include <Arduino.h>
#include "BroRotaryEncoder.h"

#define PIN_EncoderClk 3
#define PIN_EncoderDt 2
#define PIN_EncoderSw 4

BroRotaryEncoder _encoder = BroRotaryEncoder(PIN_EncoderClk, PIN_EncoderDt, PIN_EncoderSw);

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial OK");

    _encoder.AttachOnClick([]() { Serial.println("Click"); });
    _encoder.AttachOnLeftHoldTurn([]() { Serial.println("Left Hold Turn"); });
    _encoder.AttachOnRightHoldTurn([]() { Serial.println("Right Hold Turn"); });
    _encoder.AttachOnLeftTurn([]() { Serial.println("Left Turn"); });
    _encoder.AttachOnRightTurn([]() { Serial.println("Right Turn"); });
    _encoder.AttachOnDoubleClick([]() { Serial.println("Double Click"); });
    _encoder.AttachOnPressStart([]() { Serial.println("Press Start"); });
    _encoder.AttachOnPressStop([]() { Serial.println("Press Stop"); });
}

void loop()
{
    _encoder.Tick();
}