#include "State/BroEncoderNormalState.h"
#include "State/BroEncoderSingleClickCandidateState.h"

void BroEncoderNormalState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if ( isButtonPressed)
    {
        SetStopTime(milliseconds);
        SetStartTime(milliseconds);
        TransitionTo(new BroEncoderSingleClickCandidateState());
    }
}
