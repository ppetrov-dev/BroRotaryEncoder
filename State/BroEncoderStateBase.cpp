#include "State/BroEncoderStateBase.h"
#include "State/BroEncoderNormalState.h"
#include "State/BroEncoderUnreleasedState.h"
#include "BroRotaryEncoder.h"

void BroEncoderStateBase::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
}
void BroEncoderStateBase::RaiseEventIfNeeded()
{
}
void BroEncoderStateBase::Drop(const bool &isButtonPressed)
{
    if (isButtonPressed)
        TransitionTo(new BroEncoderUnreleasedState());
    else
        TransitionTo(new BroEncoderNormalState());
}
void BroEncoderStateBase::SetContext(BroRotaryEncoder *context)
{
    _context = context;
}
void BroEncoderStateBase::SetStartTime(const unsigned long &milliseconds)
{
    _context->_startTime = milliseconds;
}

void BroEncoderStateBase::SetStopTime(const unsigned long &milliseconds)
{
    _context->_stopTime = milliseconds;
}
bool BroEncoderStateBase::IsDebounceExpiredWithStartTime(const unsigned long &milliseconds)
{
    return milliseconds - _context->_startTime > _context->_debounceTicks;
}
bool BroEncoderStateBase::IsDebounceExpiredWithStopTime(const unsigned long &milliseconds)
{
    return milliseconds - _context->_stopTime > _context->_debounceTicks;
}
bool BroEncoderStateBase::IsClickTicksExpired(const unsigned long &milliseconds)
{
    return milliseconds - _context->_startTime > _context->_clickTicks;
}
bool BroEncoderStateBase::IsPressTicksExpired(const unsigned long &milliseconds)
{
    return milliseconds - _context->_startTime > _context->_pressTicks;
}
bool BroEncoderStateBase::ContainsDoubleClickHandler()
{
    return _context->_onDoubleClickCallbackFunc != nullptr;
}

void BroEncoderStateBase::TransitionTo(BroEncoderStateBase *state)
{
    _context->TransitionTo(state);
}
void BroEncoderStateBase::RaiseLongPressStartIfNotNull()
{
    if (_context->_onLongPressStartCallbackFunc != nullptr)
        _context->_onLongPressStartCallbackFunc();
}
void BroEncoderStateBase::RaiseClickIfNotNull()
{
    if (_context->_onClickCallbackFunc != nullptr)
        _context->_onClickCallbackFunc();
}
void BroEncoderStateBase::RaiseLongPressStopIfNotNull()
{
    if (_context->_onLongPressStopCallbackFunc != nullptr)
        _context->_onLongPressStopCallbackFunc();
}
void BroEncoderStateBase::RaiseDoubleClickIfNotNull()
{
    if (_context->_onDoubleClickCallbackFunc != nullptr)
        _context->_onDoubleClickCallbackFunc();
}