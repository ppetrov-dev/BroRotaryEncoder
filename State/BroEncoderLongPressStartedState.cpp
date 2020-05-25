#include "State/BroEncoderLongPressStartedState.h"
#include "State/BroEncoderLongPressStoppedState.h"

void BroEncoderLongPressStartedState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (!isButtonPressed)
    {
        SetStopTime(milliseconds);
        TransitionTo(new BroEncoderLongPressStoppedState());
    }
}
void BroEncoderLongPressStartedState::Drop(const bool &isButtonPressed)
{
    RaiseLongPressStopIfNotNull();
    BroEncoderStateBase::Drop(isButtonPressed);
}
