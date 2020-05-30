#include "BroEncoderButtonStates.h"

void BroEncoderUnreleasedState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (!isButtonPressed)
    {
        SetStopTime(milliseconds);
        SetStartTime(milliseconds);
        TransitionTo(new BroEncoderNormalState());
    }
}
void BroEncoderNormalState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (isButtonPressed)
    {
        SetStopTime(milliseconds);
        SetStartTime(milliseconds);
        TransitionTo(new BroEncoderSingleClickCandidateState());
    }
}
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
void BroEncoderSingleClickedState::RaiseEventIfNeeded()
{
    RaiseClickIfNotNull();
    TransitionTo(new BroEncoderNormalState());
}

void BroEncoderDoubleClickCandidateState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (IsDebounceExpiredWithStartTime(milliseconds))
    {
        SetStartTime(milliseconds);
        SetStopTime(milliseconds);
        TransitionTo(new BroEncoderDoubleClickingState());
    }
}
void BroEncoderDoubleClickingState::RaiseEventIfNeeded()
{
    RaiseDoubleClickIfNotNull();
    TransitionTo(new BroEncoderDoubleClickedState());
}

void BroEncoderDoubleClickedState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (isButtonPressed)
        TransitionTo(new BroEncoderUnreleasedState());
    else if (!isButtonPressed)
        TransitionTo(new BroEncoderNormalState());
}
void BroEncoderLongPressCandidateState::RaiseEventIfNeeded()
{
    RaiseLongPressStartIfNotNull();
    TransitionTo(new BroEncoderLongPressStartedState());
}

void BroEncoderLongPressStartedState::Tick(const bool &isButtonPressed, const unsigned long &milliseconds)
{
    if (!isButtonPressed)
    {
        SetStopTime(milliseconds);
        TransitionTo(new BroEncoderLongPressStoppedState());
    }
}
void BroEncoderLongPressStartedState::Drop(const bool &isButtonPressed)
{
    RaiseLongPressStopIfNotNull();
    BroEncoderStateBase::Drop(isButtonPressed);
}

void BroEncoderLongPressStoppedState::RaiseEventIfNeeded()
{
    RaiseLongPressStopIfNotNull();
    TransitionTo(new BroEncoderNormalState());
}
