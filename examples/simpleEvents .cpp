#include <Arduino.h>
#include "BroRotaryEncoder.h"

#define PIN_EncoderClk 3
#define PIN_EncoderDt 2

BroSimpleRotaryEncoder _encoder = BroSimpleRotaryEncoder(PIN_EncoderClk, PIN_EncoderDt);

void OnLeftTurnHandler()
{
    Serial.println("Left Turn");
}
void OnRightTurnHandler()
{
    Serial.println("Right Turn");
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial OK");

    _encoder.Init();
    _encoder.AttachOnRightTurn(&OnRightTurnHandler);
    _encoder.AttachOnDoubleClick(&OnDoubleClickHandler);
}

void loop()
{
    _encoder.Tick();
}