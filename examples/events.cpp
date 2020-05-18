#include <Arduino.h>
#include "BroRotaryEncoder.h"

#define PIN_EncoderClk 3
#define PIN_EncoderDt 2
#define PIN_EncoderSw 4

BroRotaryEncoder _encoder = BroRotaryEncoder(PIN_EncoderClk, PIN_EncoderDt, PIN_EncoderSw);

void OnClickHandler()
{
    Serial.println("Click");
}
void OnDoubleClickHandler()
{
    Serial.println("Double Click);
}
void OnLeftHoldTurnHandler()
{
    Serial.println("Left Hold Turn");
}
void OnLeftTurnHandler()
{
    Serial.println("Left Turn");
}
void OnRightHoldTurnHandler()
{
    Serial.println("Right Turn");
}
void OnPressStartHandler()
{
    Serial.println("Press Start");
}
void OnPressStopHandler()
{
    Serial.println("Press Stop");
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial OK");

    _encoder.AttachOnClick(&OnClickHandler);
    _encoder.AttachOnLeftHoldTurn(&OnLeftHoldTurnHandler);
    _encoder.AttachOnRightHoldTurn(&OnRightHoldTurnHandler);
    _encoder.AttachOnLeftTurn(&OnLeftTurnHandler);
    _encoder.AttachOnRightTurn(&OnRightTurnHandler);
    _encoder.AttachOnDoubleClick(&OnDoubleClickHandler);
    _encoder.AttachOnPressStart(&OnPressStartHandler);
    _encoder.AttachOnPressStop(&OnPressStopHandler);
}

void loop()
{
    _encoder.Tick();
}