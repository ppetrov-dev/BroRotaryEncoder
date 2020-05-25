#ifndef BroEncoderLongPressCandidateStateH
#define BroEncoderLongPressCandidateStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderLongPressCandidateState : public BroEncoderStateBase
{
public:
    void RaiseEventIfNeeded() override;
};

#endif //BroEncoderLongPressCandidateStateH