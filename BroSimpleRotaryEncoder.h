#ifndef broSimpleRotaryEncoderH
#define broSimpleRotaryEncoderH

#include <Arduino.h>
#include "BroSequenceCombiner.h"

class BroSimpleRotaryEncoder
{
private:
    byte _pinClk, _pinDt;

protected:
    BroSequenceCombiner _broSequenceCombiner;

    void (*_onRightTurnCallbackFunc)() = nullptr;
    void (*_onLeftTurnCallbackFunc)() = nullptr;
    unsigned char ReadState(void);
    void RaiseLeftTurnIfNotNull(void);
    void RaiseRightTurnIfNotNull(void);

public:
    BroSimpleRotaryEncoder(byte pinClk, byte pinDt);

    void Tick(void);
    void AttachOnRightTurn(void (*newFunction)());
    void AttachOnLeftTurn(void (*newFunction)());
};

#endif //broSimpleRotaryEncoderH