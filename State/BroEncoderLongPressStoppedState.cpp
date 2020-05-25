#include "State/BroEncoderLongPressStoppedState.h"
#include "State/BroEncoderNormalState.h"

void BroEncoderLongPressStoppedState::RaiseEventIfNeeded()
{
    RaiseLongPressStopIfNotNull();
    TransitionTo(new BroEncoderNormalState());
}
