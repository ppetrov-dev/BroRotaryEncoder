#include "State/BroEncoderSingleClickedState.h"
#include "State/BroEncoderNormalState.h"
#include "BroRotaryEncoder.h"

void BroEncoderSingleClickedState::RaiseEventIfNeeded()
{
    RaiseClickIfNotNull();
    TransitionTo(new BroEncoderNormalState());
}
