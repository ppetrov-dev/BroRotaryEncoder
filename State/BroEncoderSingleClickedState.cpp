#include "State/BroEncoderSingleClickedState.h"
#include "State/BroEncoderNormalState.h"

void BroEncoderSingleClickedState::RaiseEventIfNeeded()
{
    RaiseClickIfNotNull();
    TransitionTo(new BroEncoderNormalState());
}
