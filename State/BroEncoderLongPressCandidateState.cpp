#include "State/BroEncoderLongPressCandidateState.h"
#include "State/BroEncoderLongPressStartedState.h"
#include "BroRotaryEncoder.h"

void BroEncoderLongPressCandidateState::RaiseEventIfNeeded()
{
    RaiseLongPressStartIfNotNull();
    TransitionTo(new BroEncoderLongPressStartedState());
}
