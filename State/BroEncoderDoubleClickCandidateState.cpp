#include "State/BroEncoderDoubleClickCandidateState.h"
#include "State/BroEncoderDoubleClickingState.h"

void BroEncoderDoubleClickCandidateState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (IsDebounceExpiredWithStartTime(milliseconds))
    {
        SetStartTime(milliseconds);
        SetStopTime(milliseconds);
        TransitionTo(new BroEncoderDoubleClickingState());
    }
}
