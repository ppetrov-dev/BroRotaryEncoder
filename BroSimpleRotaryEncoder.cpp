#include "BroSimpleRotaryEncoder.h"

BroSimpleRotaryEncoder::BroSimpleRotaryEncoder(byte pinClk, byte pinDt)
    : _pinClk(pinClk), _pinDt(pinDt), _broSequenceCombiner(BroSequenceCombiner())
{
}
void BroSimpleRotaryEncoder::Init()
{
    pinMode(_pinClk, INPUT);
    pinMode(_pinDt, INPUT);

    Reset();
}
void BroSimpleRotaryEncoder::Reset()
{
    _broSequenceCombiner.Reset();
}
void BroSimpleRotaryEncoder::AttachOnLeftTurn(void (*newFunction)())
{
    _onLeftTurnCallbackFunc = newFunction;
}
void BroSimpleRotaryEncoder::AttachOnRightTurn(void (*newFunction)())
{
    _onRightTurnCallbackFunc = newFunction;
}
unsigned char BroSimpleRotaryEncoder::ReadState(void)
{
    return digitalRead(_pinClk) | (digitalRead(_pinDt) << 1);
}
EventHandler BroSimpleRotaryEncoder::GetEventHandlerToExecute()
{
    return _broSequenceCombiner.IsLeftTurn() ? _onLeftTurnCallbackFunc
                                             : _broSequenceCombiner.IsRightTurn()
                                                   ? _onRightTurnCallbackFunc
                                                   : nullptr;
}
void BroSimpleRotaryEncoder::Tick(void)
{
    auto state = ReadState();

    _broSequenceCombiner.EnqueueIfNeeded(state);
    if (!_broSequenceCombiner.IsCompleted())
        return;

    auto action = GetEventHandlerToExecute();
    if (action != nullptr)
        action();
    Reset();
}