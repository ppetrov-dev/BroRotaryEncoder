#include <Arduino.h>
#include "BroRotaryEncoder.h"

#define PIN_EncoderDt 2
#define PIN_EncoderClk 3
#define PIN_EncoderSw 4

BroRotaryEncoder _encoder = BroRotaryEncoder(PIN_EncoderClk, PIN_EncoderDt, PIN_EncoderSw);

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial OK");

    _encoder.Init();
    _encoder.AttachOnLongPressStop([]() {
        Serial.print(_encoder.GetLastPressedTicks());
        Serial.println(" ticks");
    });
}

void loop()
{
    _encoder.Tick();
}