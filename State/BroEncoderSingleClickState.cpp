#include "State/BroEncoderSingleClickState.h"
#include "State/BroEncoderSingleClickedState.h"
#include "State/BroEncoderDoubleClickCandidateState.h"
#include "BroRotaryEncoder.h"

void BroEncoderSingleClickState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (!ContainsDoubleClickHandler() || IsClickTicksExpired(milliseconds))
        TransitionTo(new BroEncoderSingleClickedState());
    else if (isButtonPressed && IsDebounceExpiredWithStopTime(milliseconds))
    {
        SetStartTime(milliseconds);
        TransitionTo(new BroEncoderDoubleClickCandidateState());
    }
}
