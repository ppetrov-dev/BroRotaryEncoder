#include "State/BroEncoderLongPressStoppedState.h"
#include "State/BroEncoderNormalState.h"
#include "BroRotaryEncoder.h"

void BroEncoderLongPressStoppedState::RaiseEventIfNeeded()
{
    RaiseLongPressStopIfNotNull();
    TransitionTo(new BroEncoderNormalState());
}
