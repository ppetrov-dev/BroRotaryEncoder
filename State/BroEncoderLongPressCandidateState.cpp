#include "State/BroEncoderLongPressCandidateState.h"
#include "State/BroEncoderLongPressStartedState.h"

void BroEncoderLongPressCandidateState::RaiseEventIfNeeded()
{
    RaiseLongPressStartIfNotNull();
    TransitionTo(new BroEncoderLongPressStartedState());
}
