#include "State/BroEncoderSingleClickCandidateState.h"
#include "State/BroEncoderNormalState.h"
#include "State/BroEncoderSingleClickState.h"
#include "State/BroEncoderLongPressCandidateState.h"
#include "BroRotaryEncoder.h"

void BroEncoderSingleClickCandidateState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (!isButtonPressed)
    {
        if (IsDebounceExpiredWithStartTime(milliseconds))
        {
            SetStopTime(milliseconds);
            TransitionTo(new BroEncoderSingleClickState());
        }
        else
            TransitionTo(new BroEncoderNormalState());
    }
    else if (IsPressTicksExpired(milliseconds))
        TransitionTo(new BroEncoderLongPressCandidateState());
}
