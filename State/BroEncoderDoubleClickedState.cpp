#include "State/BroEncoderDoubleClickedState.h"
#include "State/BroEncoderNormalState.h"
#include "State/BroEncoderUnreleasedState.h"
#include "BroRotaryEncoder.h"

void BroEncoderDoubleClickedState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (isButtonPressed)
        TransitionTo(new BroEncoderUnreleasedState());
    else if (!isButtonPressed)
        TransitionTo(new BroEncoderNormalState());
}
