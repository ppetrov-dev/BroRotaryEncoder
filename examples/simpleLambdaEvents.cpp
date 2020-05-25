#include <Arduino.h>
#include "BroRotaryEncoder.h"

#define PIN_EncoderClk 3
#define PIN_EncoderDt 2

BroSimpleRotaryEncoder _encoder = BroSimpleRotaryEncoder(PIN_EncoderClk, PIN_EncoderDt);

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial OK");

    _encoder.Init();
    _encoder.AttachOnLeftTurn([]() { Serial.println("Left Turn"); });
    _encoder.AttachOnRightTurn([]() { Serial.println("Right Turn"); });
}

void loop()
{
    _encoder.Tick();
}