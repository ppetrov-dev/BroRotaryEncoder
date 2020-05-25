#include "State/BroEncoderDoubleClickingState.h"
#include "State/BroEncoderDoubleClickedState.h"

void BroEncoderDoubleClickingState::RaiseEventIfNeeded()
{
    RaiseDoubleClickIfNotNull();
    TransitionTo(new BroEncoderDoubleClickedState());
}
