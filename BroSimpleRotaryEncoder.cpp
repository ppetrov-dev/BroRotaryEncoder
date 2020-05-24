#include "BroSimpleRotaryEncoder.h"

BroSimpleRotaryEncoder::BroSimpleRotaryEncoder(byte pinClk, byte pinDt)
    : _pinClk(pinClk), _pinDt(pinDt), _broSequenceCombiner(BroSequenceCombiner())
{
    pinMode(_pinClk, INPUT);
    pinMode(_pinDt, INPUT);
}

void BroSimpleRotaryEncoder::AttachOnLeftTurn(void (*newFunction)())
{
    _onLeftTurnCallbackFunc = newFunction;
}

void BroSimpleRotaryEncoder::AttachOnRightTurn(void (*newFunction)())
{
    _onRightTurnCallbackFunc = newFunction;
}

void BroSimpleRotaryEncoder::RaiseLeftTurnIfNotNull(void)
{
    if (_onLeftTurnCallbackFunc != nullptr)
        _onLeftTurnCallbackFunc();
}
void BroSimpleRotaryEncoder::RaiseRightTurnIfNotNull(void)
{
    if (_onRightTurnCallbackFunc != nullptr)
        _onRightTurnCallbackFunc();
}
unsigned char BroSimpleRotaryEncoder::ReadState(void)
{
    return digitalRead(_pinClk) | (digitalRead(_pinDt) << 1);
}
void BroSimpleRotaryEncoder::Tick(void)
{
    auto state = ReadState();
    
    _broSequenceCombiner.EnqueueIfNeeded(state);

    if (!_broSequenceCombiner.IsCompleted())
        return;

    if (_broSequenceCombiner.IsLeftTurn())
        RaiseLeftTurnIfNotNull();
    else if (_broSequenceCombiner.IsRightTurn())
        RaiseRightTurnIfNotNull();

    _broSequenceCombiner.Reset();
}