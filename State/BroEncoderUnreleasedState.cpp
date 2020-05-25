#include "State/BroEncoderUnreleasedState.h"
#include "State/BroEncoderNormalState.h"

void BroEncoderUnreleasedState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (! isButtonPressed)
    {
        SetStopTime(milliseconds);
        SetStartTime(milliseconds);
        TransitionTo(new BroEncoderNormalState());
    }
}
