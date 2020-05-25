#include "State/BroEncoderDoubleClickingState.h"
#include "State/BroEncoderDoubleClickedState.h"
#include "BroRotaryEncoder.h"

void BroEncoderDoubleClickingState::RaiseEventIfNeeded()
{
    RaiseDoubleClickIfNotNull();
    TransitionTo(new BroEncoderDoubleClickedState());
}
