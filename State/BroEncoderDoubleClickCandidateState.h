#ifndef BroEncoderDoubleClickCandidateStateH
#define BroEncoderDoubleClickCandidateStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderDoubleClickCandidateState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

#endif //BroEncoderDoubleClickCandidateStateH