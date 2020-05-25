#ifndef BroEncoderSingleClickCandidateStateH
#define BroEncoderSingleClickCandidateStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderSingleClickCandidateState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

#endif //BroEncoderSingleClickCandidateStateH