#ifndef broSimpleRotaryEncoderH
#define broSimpleRotaryEncoderH

#include <Arduino.h>
#include "BroSequenceCombiner.h"
typedef void (*EventHandler)(void);
class BroSimpleRotaryEncoder
{
private:
    byte _pinClk, _pinDt;
    EventHandler GetEventHandlerToExecute();

protected:
    BroSequenceCombiner _broSequenceCombiner;

    void (*_onRightTurnCallbackFunc)() = nullptr;
    void (*_onLeftTurnCallbackFunc)() = nullptr;
    unsigned char ReadState(void);

public:
    BroSimpleRotaryEncoder(byte pinClk, byte pinDt);
    void virtual Init();
    void virtual Reset();

    void Tick(void);
    void AttachOnRightTurn(void (*newFunction)());
    void AttachOnLeftTurn(void (*newFunction)());
};

#endif //broSimpleRotaryEncoderH